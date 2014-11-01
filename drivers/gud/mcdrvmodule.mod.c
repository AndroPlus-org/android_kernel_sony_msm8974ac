#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xdb2ab789, "module_layout" },
	{ 0xe5326737, "clk_unprepare" },
	{ 0x92b57248, "flush_work" },
	{ 0x30a89f62, "cdev_del" },
	{ 0xdcc1ee11, "kmalloc_caches" },
	{ 0x3ed633a8, "cdev_init" },
	{ 0x9b388444, "get_zeroed_page" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0xf6bb0afc, "up_read" },
	{ 0x2ef9aa59, "clk_enable" },
	{ 0x178ba18c, "_raw_spin_unlock" },
	{ 0x3e861ed2, "mem_map" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x83b0ce2, "clk_disable" },
	{ 0xdfabe0ff, "scm_call" },
	{ 0x6ae67835, "device_destroy" },
	{ 0x2e1ca751, "clk_put" },
	{ 0x55837517, "mutex_unlock" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xdd7f8939, "kthread_create_on_node" },
	{ 0x3c1ea6eb, "down_read" },
	{ 0xa7ecf324, "__init_waitqueue_head" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x5f754e5a, "memset" },
	{ 0x5bf27e27, "dev_err" },
	{ 0xa22ee5e6, "mutex_lock_interruptible" },
	{ 0x3bf89010, "__mutex_init" },
	{ 0x3fbae908, "kthread_stop" },
	{ 0xe3f0223, "wait_for_completion_interruptible" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x1d1744fc, "mutex_lock" },
	{ 0x99899f9c, "device_create" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0xecc6e887, "__get_page_tail" },
	{ 0xf1f659bb, "release_pages" },
	{ 0x69c339a0, "cdev_add" },
	{ 0x3656d9fd, "_dev_info" },
	{ 0xbc10dd97, "__put_user_4" },
	{ 0xd9ce8f0c, "strnlen" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0x11e3d90d, "get_user_pages" },
	{ 0x1000e51, "schedule" },
	{ 0xef64157b, "clk_prepare" },
	{ 0xb894926d, "schedule_work_on" },
	{ 0x6ae034d4, "wake_up_process" },
	{ 0x9f2ec48e, "kmem_cache_alloc_trace" },
	{ 0xc4097c34, "_raw_spin_lock" },
	{ 0x72937d6a, "clk_get" },
	{ 0x4302d0eb, "free_pages" },
	{ 0xb1441e61, "sched_setscheduler" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0x1e047854, "warn_slowpath_fmt" },
	{ 0x9c55cec, "schedule_timeout_interruptible" },
	{ 0x37a0cba, "kfree" },
	{ 0x30775d3d, "remap_pfn_range" },
	{ 0xb1b74f6c, "put_page" },
	{ 0x258fdd9a, "class_destroy" },
	{ 0xf5942085, "get_pid_task" },
	{ 0x7b5c8440, "vm_munmap" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0xad998077, "complete" },
	{ 0x2f573056, "vmalloc_to_page" },
	{ 0xf766cca9, "dev_set_name" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x6d044c26, "param_ops_uint" },
	{ 0xa33bc459, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x15ccd6f2, "is_vmalloc_addr" },
	{ 0xf20dabd8, "free_irq" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

