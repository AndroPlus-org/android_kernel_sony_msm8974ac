/*
 * arch/arm/mach-msm/fast_hotplug.c
 *
 * Copyright (C) 2014 Basile Maret
 * 
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * Author: Basile Maret (pec0ra)
 *
 */
#include <linux/cpu.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/cpufreq.h>

#define HOTPLUG_INFO_TAG	"[HOTPLUG] : "

#define CPU_COUNT		4

#define REFRESH_RATE		100  /* ms */

#define BOOST_DURATION		1000 /* ms */
#define BOOST_FREQ		(1190 * 1000)
#define IDLE_THRESHOLD		500

#define THRESHOLD_TO_BOOST		3000

#define PLUG_IN_CORE_1_THRESHOLD	2500
#define PLUG_IN_CORE_2_THRESHOLD	4000
#define PLUG_IN_CORE_3_THRESHOLD	4500

#define PLUG_IN_CORE_1_DELAY		1
#define PLUG_IN_CORE_2_DELAY		3
#define PLUG_IN_CORE_3_DELAY		3

#define PLUG_OUT_CORE_1_THRESHOLD	2500
#define PLUG_OUT_CORE_2_THRESHOLD	3000
#define PLUG_OUT_CORE_3_THRESHOLD	3500

#define PLUG_OUT_CORE_1_DELAY		3
#define PLUG_OUT_CORE_2_DELAY		2
#define PLUG_OUT_CORE_3_DELAY		1

static DEFINE_MUTEX(mutex);

static struct workqueue_struct *hotplug_wq;
static struct delayed_work hotplug_work;


static unsigned long boost_duration;
static struct timer_list unboost_timer;
static int is_boosted = false;

static unsigned long idle_threshold = IDLE_THRESHOLD;
static unsigned long threshold_to_boost = THRESHOLD_TO_BOOST;
static int singlecore = false;

static unsigned long plug_in_threshold[] = {
	0,
	PLUG_IN_CORE_1_THRESHOLD,
	PLUG_IN_CORE_2_THRESHOLD,
	PLUG_IN_CORE_3_THRESHOLD,
	~0
};

static unsigned int delay_in;
static unsigned int plug_in_delay[] = {
	0,
	PLUG_IN_CORE_1_DELAY,
	PLUG_IN_CORE_2_DELAY,
	PLUG_IN_CORE_3_DELAY,
	~0
};

static unsigned long plug_out_threshold[] = {
	0,
	PLUG_OUT_CORE_1_THRESHOLD,
	PLUG_OUT_CORE_2_THRESHOLD,
	PLUG_OUT_CORE_3_THRESHOLD,
	0
};

static unsigned int delay_out;
static unsigned int plug_out_delay[] = {
	0,
	PLUG_OUT_CORE_1_DELAY,
	PLUG_OUT_CORE_2_DELAY,
	PLUG_OUT_CORE_3_DELAY,
	0
};

extern unsigned long avg_nr_running(void);
extern unsigned long avg_cpu_nr_running(unsigned int cpu);


static int get_slowest_cpu(void){
	int cpu, slowest_cpu = 1;
	unsigned long load, min_load = ~0;
	for_each_online_cpu(cpu){
		load = avg_cpu_nr_running((unsigned int)cpu);
		if(load < min_load){
			min_load = load;
			slowest_cpu = cpu;
		}
	}
	return slowest_cpu;
}

static void plug_in(int online_cpu_count){
	int cpu;
	mutex_lock(&mutex);
	singlecore = false;
	for_each_possible_cpu(cpu){
		if(cpu != 0){
			if(!cpu_online(cpu)){
				cpu_up(cpu);
				break;
			}
		}
	}
	mutex_unlock(&mutex);
	pr_info(HOTPLUG_INFO_TAG"Plugged in a core !");
}
static void plug_out(int online_cpu_count){
	mutex_lock(&mutex);
	cpu_down(get_slowest_cpu());
	if(online_cpu_count <= 2){
		singlecore = true;
		pr_info(HOTPLUG_INFO_TAG"Now running in single core");
	}
	mutex_unlock(&mutex);
	pr_info(HOTPLUG_INFO_TAG"Plugged out a core !");
}

/*
 * Main function of the hotplug
 */
static void hotplug(struct work_struct *work){
	int online_cpu_count;
	unsigned long load = avg_nr_running();


	// We minimize the work when calculations are not
	// needed to spare resources when cpu is almost idle
	if(load < idle_threshold && singlecore)
		goto delay_work;

	online_cpu_count = num_online_cpus();
// 	pr_info(HOTPLUG_INFO_TAG"The load is %lu, we have %d cpu online and the in threshold is : %lu. The delay is %d, out : %lu, %d", load, online_cpu_count, plug_in_threshold[online_cpu_count], plug_in_delay[online_cpu_count], plug_out_threshold[online_cpu_count - 1], plug_out_delay[online_cpu_count - 1]);
	
	// If boosted, we don't hesitate to plug in cores if there is some load
	if(is_boosted && load > threshold_to_boost && singlecore){
		plug_in(online_cpu_count);

	// If we have enough load, we decrement the delay until we can plug in
	} else if(load > plug_in_threshold[online_cpu_count]){
		delay_out = plug_out_delay[online_cpu_count];
		if(delay_in > 0){
			pr_info(HOTPLUG_INFO_TAG"We decrement the in delay %d from %d\n", online_cpu_count - 1, delay_out);
			delay_in--;
		}
		else
			plug_in(online_cpu_count);
	} else if(!is_boosted && load < plug_out_threshold[online_cpu_count - 1]){
		delay_in = plug_in_delay[online_cpu_count -1];
		if(delay_out > 0){
			pr_info(HOTPLUG_INFO_TAG"We decrement the out delay %d from %d\n", online_cpu_count - 1, delay_out);
			delay_out--;
		}
		else
			plug_out(online_cpu_count);

	// Nothing special happens, we just reset the delays
	} else {
		delay_out = plug_out_delay[online_cpu_count];
		delay_in = plug_in_delay[online_cpu_count];
	}

delay_work:
	queue_delayed_work_on(0, hotplug_wq, &hotplug_work, msecs_to_jiffies(REFRESH_RATE));
}


/*
 * Boost / Unboost cpu when the screen is touched
 */
static void unboost_cpu(unsigned long data){
	is_boosted = false,
	pr_info(HOTPLUG_INFO_TAG"Cpu unboosted !\n");
}

static void hotplug_input_event(struct input_handle *handle,
		unsigned int type, unsigned int code, int value)
{
	if(is_boosted){
		mod_timer(&unboost_timer, jiffies + boost_duration);
		return;
	}
	is_boosted = true;
	mod_timer(&unboost_timer, jiffies + boost_duration);

}

/* 
 * This part of the code is about managing touchscreen event
 */
static int hotplug_input_connect(struct input_handler *handler,
		struct input_dev *dev, const struct input_device_id *id)
{
	struct input_handle *handle;
	int error;

	handle = kzalloc(sizeof(struct input_handle), GFP_KERNEL);
	if (!handle)
		return -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "hotplug";

	error = input_register_handle(handle);
	if (error)
		goto err2;

	error = input_open_device(handle);
	if (error)
		goto err1;
	return 0;
err1:
	input_unregister_handle(handle);
err2:
	kfree(handle);
	return error;
}

static void hotplug_input_disconnect(struct input_handle *handle)
{
	input_close_device(handle);
	input_unregister_handle(handle);
	kfree(handle);
}

static const struct input_device_id hotplug_ids[] = {
	{
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT |
			 INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_ABS) },
		.absbit = { [BIT_WORD(ABS_MT_POSITION_X)] =
			    BIT_MASK(ABS_MT_POSITION_X) |
			    BIT_MASK(ABS_MT_POSITION_Y) },
	}, /* multi-touch touchscreen */
	{
		.flags = INPUT_DEVICE_ID_MATCH_KEYBIT |
			 INPUT_DEVICE_ID_MATCH_ABSBIT,
		.keybit = { [BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH) },
		.absbit = { [BIT_WORD(ABS_X)] =
			    BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) },
	}, /* touchpad */
	{ },
};

static struct input_handler hotplug_input_handler = {
	.event          = hotplug_input_event,
	.connect        = hotplug_input_connect,
	.disconnect     = hotplug_input_disconnect,
	.name           = "hotplug_handler",
	.id_table       = hotplug_ids,
};

/*
 * Initialization of the module
 */
static int __init hotplug_init(void)
{
	int rc;

	rc = input_register_handler(&hotplug_input_handler);


	boost_duration = msecs_to_jiffies(BOOST_DURATION);
	unboost_timer.function = unboost_cpu;
	unboost_timer.expires = jiffies;
	init_timer(&unboost_timer);

	hotplug_wq = alloc_workqueue("hotplug", WQ_HIGHPRI | WQ_UNBOUND, 1);
// 	boost_wq = alloc_workqueue("boost", WQ_HIGHPRI | WQ_UNBOUND, 1);

// 	INIT_DELAYED_WORK(&boost_work, boost_cpu);
	INIT_DELAYED_WORK(&hotplug_work, hotplug);
	queue_delayed_work_on(0, hotplug_wq, &hotplug_work, msecs_to_jiffies(1000));

	pr_info(HOTPLUG_INFO_TAG"Hotplug succesfully initialized !");
	return 0;
}


late_initcall(hotplug_init);
