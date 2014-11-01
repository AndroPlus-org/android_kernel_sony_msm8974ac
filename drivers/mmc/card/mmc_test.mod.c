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
	{ 0x67d3e13d, "single_release" },
	{ 0xe7b465af, "seq_read" },
	{ 0xd564c053, "seq_lseek" },
	{ 0xaf9702d3, "mmc_unregister_driver" },
	{ 0x9727cb15, "mmc_register_driver" },
	{ 0x1424f59, "sg_copy_to_buffer" },
	{ 0x8371daff, "sg_copy_from_buffer" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x66b2a859, "nr_free_buffer_pages" },
	{ 0x3e861ed2, "mem_map" },
	{ 0xd5152710, "sg_next" },
	{ 0x1b174547, "page_address" },
	{ 0xf88c3301, "sg_init_table" },
	{ 0x1a16460, "mmc_start_req" },
	{ 0x3656d9fd, "_dev_info" },
	{ 0xefdd2345, "sg_init_one" },
	{ 0xc2611448, "mmc_set_blocklen" },
	{ 0x46608fa0, "getnstimeofday" },
	{ 0x1d4c33ac, "mmc_can_trim" },
	{ 0x43e298a0, "mmc_wait_for_req" },
	{ 0xcb830dc7, "mmc_erase" },
	{ 0x23549d78, "mmc_can_erase" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xe4036cce, "debugfs_remove" },
	{ 0x5bf27e27, "dev_err" },
	{ 0xe0a64f78, "debugfs_create_file" },
	{ 0x6a9c9d18, "contig_page_data" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x1526c965, "mmc_rpm_release" },
	{ 0x2863b3c9, "mmc_release_host" },
	{ 0xbbd83a6f, "__mmc_claim_host" },
	{ 0x266d9a8e, "mmc_rpm_hold" },
	{ 0x2b9a6a1a, "__alloc_pages_nodemask" },
	{ 0x86a4889a, "kmalloc_order_trace" },
	{ 0x11a13e31, "_kstrtol" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x37a0cba, "kfree" },
	{ 0x62b50d18, "__free_pages" },
	{ 0xe6da44a, "set_normalized_timespec" },
	{ 0xdcc1ee11, "kmalloc_caches" },
	{ 0x9f2ec48e, "kmem_cache_alloc_trace" },
	{ 0x59e5070d, "__do_div64" },
	{ 0x27e1a049, "printk" },
	{ 0x122a4cdf, "mmc_wait_for_cmd" },
	{ 0x5f754e5a, "memset" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xa1bad0db, "mmc_set_data_timeout" },
	{ 0xd2982474, "mmc_can_reset" },
	{ 0xe7dc72c7, "mmc_hw_reset_check" },
	{ 0x55837517, "mutex_unlock" },
	{ 0xd67319, "seq_printf" },
	{ 0x1d1744fc, "mutex_lock" },
	{ 0x346893c, "single_open" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

