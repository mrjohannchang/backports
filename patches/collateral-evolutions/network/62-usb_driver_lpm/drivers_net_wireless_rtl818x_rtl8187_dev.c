--- a/drivers/net/wireless/rtl818x/rtl8187/dev.c
+++ b/drivers/net/wireless/rtl818x/rtl8187/dev.c
@@ -1673,7 +1673,9 @@
 	.id_table	= rtl8187_table,
 	.probe		= rtl8187_probe,
 	.disconnect	= rtl8187_disconnect,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(rtl8187_driver);