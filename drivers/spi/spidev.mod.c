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
	{ 0x6d044c26, "param_ops_uint" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x33fcb7c5, "no_llseek" },
	{ 0x5234ac82, "device_unregister" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x258fdd9a, "class_destroy" },
	{ 0xebe50821, "driver_unregister" },
	{ 0x8512b0f8, "spi_new_device" },
	{ 0x1ec9047e, "spi_busnum_to_master" },
	{ 0x9d669763, "memcpy" },
	{ 0x81633829, "spi_register_driver" },
	{ 0xa33bc459, "__class_create" },
	{ 0x179bd776, "__register_chrdev" },
	{ 0x3af06b2e, "put_device" },
	{ 0x10d97d08, "spi_setup" },
	{ 0xd05e1d10, "get_device" },
	{ 0xad998077, "complete" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x5f754e5a, "memset" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x2f4ea1ac, "wait_for_completion" },
	{ 0x6027ecb3, "spi_async" },
	{ 0xf087137d, "__dynamic_pr_debug" },
	{ 0x5665a1e3, "nonseekable_open" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xdcc1ee11, "kmalloc_caches" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0xb30d84b8, "__dynamic_dev_dbg" },
	{ 0x99899f9c, "device_create" },
	{ 0xd3dbfbc4, "_find_first_zero_bit_le" },
	{ 0x3bf89010, "__mutex_init" },
	{ 0x9f2ec48e, "kmem_cache_alloc_trace" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x55837517, "mutex_unlock" },
	{ 0x37a0cba, "kfree" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x6ae67835, "device_destroy" },
	{ 0x1d1744fc, "mutex_lock" },
	{ 0xaea99e9d, "_raw_spin_unlock_irq" },
	{ 0x1050508b, "dev_set_drvdata" },
	{ 0xe551272c, "_raw_spin_lock_irq" },
	{ 0xa0413525, "dev_get_drvdata" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

