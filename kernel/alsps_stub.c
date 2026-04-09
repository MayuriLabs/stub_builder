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
 * HQ Notifier Stubs
 * Used by touch drivers in Android 15 (Kernel 6.6)
 */
int register_hq_notify(void *nb) { return 0; }
EXPORT_SYMBOL(register_hq_notify);

int unregister_hq_notify(void *nb) { return 0; }
EXPORT_SYMBOL(unregister_hq_notify);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wulan17");
MODULE_DESCRIPTION("MediaTek SCP/SensorHub Dependency Stub for Recovery");
