#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/notifier.h>

/* 
 * Sensor Hub / Proximity Stubs 
 * specifically satisfying dependencies for alsps_common and touch drivers.
 */
int ps_enable_register_notifier(struct notifier_block *nb)
{
    return 0;
}
EXPORT_SYMBOL(ps_enable_register_notifier);

int ps_enable_unregister_notifier(struct notifier_block *nb)
{
    return 0;
}
EXPORT_SYMBOL_GPL(ps_enable_unregister_notifier);

int ps_enable_notifier_call_chain(unsigned long val, void *v) { return 0; }
EXPORT_SYMBOL_GPL(ps_enable_notifier_call_chain);

int ps_send_touch_event(int32_t data) { return 0; }
EXPORT_SYMBOL_GPL(ps_send_touch_event);

int ps_register_recive_touch_event_callback(void) { return 0; }
EXPORT_SYMBOL_GPL(ps_register_recive_touch_event_callback);

int ps_register_control_path(void *path) { return 0; }
EXPORT_SYMBOL(ps_register_control_path);

int ps_register_data_path(void *path) { return 0; }
EXPORT_SYMBOL(ps_register_data_path);

int alsps_driver_add(void *drv) { return 0; }
EXPORT_SYMBOL(alsps_driver_add);

// This is a function pointer used in tpd_notify
int (*ps_tpd)(struct notifier_block *nb) = NULL;
EXPORT_SYMBOL_GPL(ps_tpd);

/*
 * SCP / SensorHub Core Stubs
 * These allow you to skip loading scp.ko and sensorHub.ko
 */
int scp_A_register_notify(void *nb) { return 0; }
EXPORT_SYMBOL(scp_A_register_notify);

int scp_A_unregister_notify(void *nb) { return 0; }
EXPORT_SYMBOL(scp_A_unregister_notify);

int scp_ipi_registration(int id, void *handler, void *data) { return 0; }
EXPORT_SYMBOL(scp_ipi_registration);

int scp_ipi_send(int id, void *buf, unsigned int len, unsigned int wait) { return 0; }
EXPORT_SYMBOL(scp_ipi_send);

int scp_get_reserve_mem_phys(void *addr) { return 0; }
EXPORT_SYMBOL(scp_get_reserve_mem_phys);

int scp_get_reserve_mem_virt(void *addr) { return 0; }
EXPORT_SYMBOL(scp_get_reserve_mem_virt);

int scp_get_reserve_mem_size(void) { return 0; }
EXPORT_SYMBOL(scp_get_reserve_mem_size);

int scp_register_feature(void *f) { return 0; }
EXPORT_SYMBOL(scp_register_feature);

int scp_sensorHub_data_registration(void *data) { return 0; }
EXPORT_SYMBOL(scp_sensorHub_data_registration);

int scp_power_monitor_register(void *nb) { return 0; }
EXPORT_SYMBOL(scp_power_monitor_register);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MediaTek SCP/SensorHub Dependency Stub for Recovery");
