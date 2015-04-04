/*
 * arch/arm/mach-msm/msm_cpu-mpdecision.c
 *
 * CPU auto-hotplug for MSM CPUs
 *
 * Copyright (c) 2012, Dennis Rassmann.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <linux/earlysuspend.h>
#include <linux/init.h>
#include <linux/cpufreq.h>
#include <linux/workqueue.h>
#include <linux/completion.h>
#include <linux/cpu.h>
#include <linux/cpumask.h>

#include "pm.h"
#include "clock.h"
#include "acpuclock.h"

#define MPDEC_TAG "[MPDEC]: "

#ifdef CONFIG_SMP
static struct workqueue_struct *msm_mpdec_wq;
#endif

struct msm_mpdec_suspend_t {
	struct mutex suspend_mutex;
	int device_suspended;
};
static DEFINE_PER_CPU(struct msm_mpdec_suspend_t, msm_mpdec_suspend);

bool scroff_single_core = true;

static void msm_mpdec_early_suspend(struct early_suspend *h)
{
	int cpu = 0;
	for_each_possible_cpu(cpu) {
		mutex_lock(&per_cpu(msm_mpdec_suspend, cpu).suspend_mutex);
		if (((cpu >= (CONFIG_NR_CPUS - 1)) && (num_online_cpus() > 1)) && (scroff_single_core)) {
			pr_info(MPDEC_TAG"Screen -> off. Suspending CPU%d", cpu);
			cpu_down(1);
			per_cpu(msm_mpdec_suspend, cpu).device_suspended = true;
		}
		mutex_unlock(&per_cpu(msm_mpdec_suspend, cpu).suspend_mutex);
	}
}

static void msm_mpdec_late_resume(struct early_suspend *h)
{
	int cpu = 0;
	for_each_possible_cpu(cpu) {
		mutex_lock(&per_cpu(msm_mpdec_suspend, cpu).suspend_mutex);
		if ((cpu >= (CONFIG_NR_CPUS - 1)) && (num_online_cpus() < CONFIG_NR_CPUS)) {
			/* Always enable cpus when screen comes online */
			pr_info(MPDEC_TAG"Screen -> on. Hot plugging CPU%d", cpu);
			cpu_up(1);
			per_cpu(msm_mpdec_suspend, cpu).device_suspended = false;
		}
		mutex_unlock(&per_cpu(msm_mpdec_suspend, cpu).suspend_mutex);
	}
}

static struct early_suspend msm_mpdec_early_suspend_handler = {
	.level = EARLY_SUSPEND_LEVEL_DISABLE_FB,
	.suspend = msm_mpdec_early_suspend,
	.resume = msm_mpdec_late_resume,
};

static int __init msm_mpdec(void)
{
	int cpu, err = 0;
#if 0
	err = sysfs_create_file(&cpu_sysdev_class.kset.kobj,
			&attr_mfreq.attr);
	if (err)
		pr_err("Failed to create sysfs mfreq\n");
#endif
	for_each_possible_cpu(cpu) {
		mutex_init(&(per_cpu(msm_mpdec_suspend, cpu).suspend_mutex));
		per_cpu(msm_mpdec_suspend, cpu).device_suspended = false;
	}

#ifdef CONFIG_SMP
	msm_mpdec_wq = create_workqueue("msm-mpdec");
#endif

	register_early_suspend(&msm_mpdec_early_suspend_handler);

	return err;
}

late_initcall(msm_mpdec);

