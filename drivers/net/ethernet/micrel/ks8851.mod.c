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
	{ 0x15692c87, "param_ops_int" },
	{ 0x69df6e67, "eth_change_mtu" },
	{ 0x154fd0d7, "eth_validate_addr" },
	{ 0xebe50821, "driver_unregister" },
	{ 0x81633829, "spi_register_driver" },
	{ 0xfcec0987, "enable_irq" },
	{ 0xb78af479, "__netif_schedule" },
	{ 0x2a3aa678, "_test_and_clear_bit" },
	{ 0x46eaba8e, "mii_check_link" },
	{ 0xd0a880ed, "netif_rx_ni" },
	{ 0x30834033, "eth_type_trans" },
	{ 0xd556970, "__dynamic_netdev_dbg" },
	{ 0x5c6b72d9, "skb_put" },
	{ 0xa54c6f2, "__netdev_alloc_skb" },
	{ 0xe9665b48, "register_netdev" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0x44fbf7f2, "netdev_warn" },
	{ 0x5bf27e27, "dev_err" },
	{ 0x1050508b, "dev_set_drvdata" },
	{ 0x3bf89010, "__mutex_init" },
	{ 0x12a38747, "usleep_range" },
	{ 0x8a5c7a80, "regulator_enable" },
	{ 0xb9af72f0, "regulator_get" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x8c7a3757, "of_get_named_gpio_flags" },
	{ 0xe01c6501, "alloc_etherdev_mqs" },
	{ 0x27cb133b, "eeprom_93cx6_multiread" },
	{ 0x822222db, "eeprom_93cx6_write" },
	{ 0x98bb5a22, "eeprom_93cx6_read" },
	{ 0x63d2ff63, "eeprom_93cx6_wren" },
	{ 0xc47abafd, "netif_device_detach" },
	{ 0x92b57248, "flush_work" },
	{ 0x360cca59, "netdev_info" },
	{ 0x62dea94d, "netif_device_attach" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xd378eccd, "consume_skb" },
	{ 0x56d226c1, "skb_dequeue" },
	{ 0x55837517, "mutex_unlock" },
	{ 0x1d1744fc, "mutex_lock" },
	{ 0xe6b3b90a, "arm_delay_ops" },
	{ 0x97963b70, "netdev_err" },
	{ 0x431554d7, "spi_sync" },
	{ 0x27bbf221, "disable_irq_nosync" },
	{ 0xaf692f4f, "mii_ethtool_gset" },
	{ 0x14e82ea5, "mii_ethtool_sset" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x7d7bb615, "mii_nway_restart" },
	{ 0x1ec09e6d, "mii_link_ok" },
	{ 0x66ddb4a8, "skb_queue_tail" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x27e1a049, "printk" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x4f35d423, "netdev_printk" },
	{ 0x178ba18c, "_raw_spin_unlock" },
	{ 0x8949858b, "schedule_work" },
	{ 0x9d669763, "memcpy" },
	{ 0x71c90087, "memcmp" },
	{ 0xc4097c34, "_raw_spin_lock" },
	{ 0xfaf98462, "bitrev32" },
	{ 0xa34f1ef5, "crc32_le" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xf2482b56, "generic_mii_ioctl" },
	{ 0xa7ecd5df, "free_netdev" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x9cf79bdb, "unregister_netdev" },
	{ 0xd85ac634, "regulator_put" },
	{ 0x1258d9d9, "regulator_disable" },
	{ 0xfe990052, "gpio_free" },
	{ 0x3656d9fd, "_dev_info" },
	{ 0xa0413525, "dev_get_drvdata" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=eeprom_93cx6";

