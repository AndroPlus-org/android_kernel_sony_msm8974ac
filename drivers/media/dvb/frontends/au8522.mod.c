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
	{ 0xdcc1ee11, "kmalloc_caches" },
	{ 0xf9a482f9, "msleep" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xb101c2f1, "i2c_del_driver" },
	{ 0x21994215, "i2c_transfer" },
	{ 0x2d9da02a, "v4l2_chip_ident_i2c_client" },
	{ 0x55837517, "mutex_unlock" },
	{ 0x27e1a049, "printk" },
	{ 0x1d1744fc, "mutex_lock" },
	{ 0xb007d0df, "v4l2_device_unregister_subdev" },
	{ 0x462e9ba9, "i2c_register_driver" },
	{ 0x791ab099, "v4l2_ctrl_query_fill" },
	{ 0x9f2ec48e, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x9d669763, "memcpy" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xa0413525, "dev_get_drvdata" },
	{ 0x7ed69207, "v4l2_i2c_subdev_init" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:au8522");
