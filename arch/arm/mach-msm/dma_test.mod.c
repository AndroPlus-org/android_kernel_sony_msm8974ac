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
	{ 0xd6c7fb3e, "misc_deregister" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x6936c60f, "misc_register" },
	{ 0xc436e0be, "arm_dma_ops" },
	{ 0x3e861ed2, "mem_map" },
	{ 0xdf397353, "msm_dmov_exec_cmd" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xa72dab62, "up" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x292857ba, "down" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0xdcc1ee11, "kmalloc_caches" },
	{ 0x9f2ec48e, "kmem_cache_alloc_trace" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x37a0cba, "kfree" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "9C80854EE50AF7E8572E891");
