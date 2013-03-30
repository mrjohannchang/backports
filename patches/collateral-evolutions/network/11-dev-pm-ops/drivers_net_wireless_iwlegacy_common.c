--- a/drivers/net/wireless/iwlegacy/common.c
+++ b/drivers/net/wireless/iwlegacy/common.c
@@ -4935,8 +4935,17 @@
 	return 0;
 }
 
+compat_pci_suspend(il_pci_suspend)
+compat_pci_resume(il_pci_resume)
+
 SIMPLE_DEV_PM_OPS(il_pm_ops, il_pci_suspend, il_pci_resume);
+
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 EXPORT_SYMBOL(il_pm_ops);
+#else
+EXPORT_SYMBOL(il_pci_suspend_compat);
+EXPORT_SYMBOL(il_pci_resume_compat);
+#endif
 
 #endif /* CONFIG_PM_SLEEP */
 