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
	{ 0xd6eda75c, "dvb_ringbuffer_free" },
	{ 0xaee29f3d, "dvb_ringbuffer_init" },
	{ 0x9ca2b1ba, "dvb_ringbuffer_pkt_close" },
	{ 0x178ba18c, "_raw_spin_unlock" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xd7f4ac50, "dvb_unregister_adapter" },
	{ 0xf79f3673, "dvb_ringbuffer_read_user" },
	{ 0xf087137d, "__dynamic_pr_debug" },
	{ 0x55837517, "mutex_unlock" },
	{ 0x207c243d, "dvb_ringbuffer_pkt_dispose" },
	{ 0xb6738f9d, "dvb_ringbuffer_write" },
	{ 0xb2d307de, "param_ops_short" },
	{ 0xa22ee5e6, "mutex_lock_interruptible" },
	{ 0x3bf89010, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0x59a7b43, "dvb_ringbuffer_read" },
	{ 0x84537c5c, "dvb_ringbuffer_pkt_start" },
	{ 0xadc6f061, "dvb_ringbuffer_pkt_next" },
	{ 0xee9aeac0, "dvb_ringbuffer_avail" },
	{ 0x59b1ec3f, "dvb_register_adapter" },
	{ 0xc4097c34, "_raw_spin_lock" },
	{  0xf1338, "__wake_up" },
	{ 0x9d669763, "memcpy" },
	{ 0x4845c423, "param_array_ops" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x19f9616f, "dvb_ringbuffer_pkt_read" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dvb-core";

