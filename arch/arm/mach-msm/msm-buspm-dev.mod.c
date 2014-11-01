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
	{ 0xda56340f, "noop_llseek" },
	{ 0xd6c7fb3e, "misc_deregister" },
	{ 0x6936c60f, "misc_register" },
	{ 0xbbccdff9, "msm_rpm_free_request" },
	{ 0xcd9436d6, "msm_rpm_wait_for_ack" },
	{ 0xd60cf4cf, "msm_rpm_send_request" },
	{ 0x47cfdaeb, "msm_rpm_add_kvp_data" },
	{ 0x980434a2, "msm_rpm_create_request" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x75af334f, "memory_pool_node_paddr" },
	{ 0x1ae9a10c, "allocate_contiguous_ebi" },
	{ 0x27e1a049, "printk" },
	{ 0x30775d3d, "remap_pfn_range" },
	{ 0xdcc1ee11, "kmalloc_caches" },
	{ 0x9f2ec48e, "kmem_cache_alloc_trace" },
	{ 0xc6cbbc89, "capable" },
	{ 0x37a0cba, "kfree" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x7c3bcca8, "free_contiguous_memory" },
	{ 0xf087137d, "__dynamic_pr_debug" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "22BB7A0D6D1A7A533C9DEC2");
