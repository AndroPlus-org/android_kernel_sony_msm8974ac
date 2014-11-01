#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xdb2ab789, "module_layout" },
	{ 0xdcc1ee11, "kmalloc_caches" },
	{ 0xf9a482f9, "msleep" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x21994215, "i2c_transfer" },
	{ 0x55837517, "mutex_unlock" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xa22ee5e6, "mutex_lock_interruptible" },
	{ 0x3bf89010, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0xafecfdf6, "dibx000_exit_i2c_master" },
	{ 0xa79472b4, "dibx000_get_i2c_adapter" },
	{ 0x9f2ec48e, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x51997a7e, "dibx000_init_i2c_master" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dibx000_common";

