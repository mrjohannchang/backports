--- a/net/wireless/core.c
+++ b/net/wireless/core.c
@@ -160,6 +160,7 @@
 	return 0;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 int cfg80211_switch_netns(struct cfg80211_registered_device *rdev,
 			  struct net *net)
 {
@@ -204,6 +205,7 @@
 
 	return 0;
 }
+#endif
 
 static void cfg80211_rfkill_poll(struct rfkill *rfkill, void *data)
 {
@@ -372,7 +374,9 @@
 	rdev->wiphy.flags |= WIPHY_FLAG_PS_ON_BY_DEFAULT;
 #endif
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 	wiphy_net_set(&rdev->wiphy, &init_net);
+#endif
 
 	rdev->rfkill_ops.set_block = cfg80211_rfkill_set_block;
 	rdev->rfkill = rfkill_alloc(dev_name(&rdev->wiphy.dev),
@@ -919,8 +923,10 @@
 		wdev->identifier = ++rdev->wdev_id;
 		list_add_rcu(&wdev->list, &rdev->wdev_list);
 		rdev->devlist_generation++;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 		/* can only change netns with wiphy */
 		dev->features |= NETIF_F_NETNS_LOCAL;
+#endif
 
 		if (sysfs_create_link(&dev->dev.kobj, &rdev->wiphy.dev.kobj,
 				      "phy80211")) {
@@ -1081,6 +1087,7 @@
 	.notifier_call = cfg80211_netdev_notifier_call,
 };
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 static void __net_exit cfg80211_pernet_exit(struct net *net)
 {
 	struct cfg80211_registered_device *rdev;
@@ -1098,14 +1105,17 @@
 static struct pernet_operations cfg80211_pernet_ops = {
 	.exit = cfg80211_pernet_exit,
 };
+#endif
 
 static int __init cfg80211_init(void)
 {
 	int err;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 	err = register_pernet_device(&cfg80211_pernet_ops);
 	if (err)
 		goto out_fail_pernet;
+#endif
 
 	err = wiphy_sysfs_init();
 	if (err)
@@ -1142,8 +1152,10 @@
 out_fail_notifier:
 	wiphy_sysfs_exit();
 out_fail_sysfs:
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 	unregister_pernet_device(&cfg80211_pernet_ops);
 out_fail_pernet:
+#endif
 	return err;
 }
 subsys_initcall(cfg80211_init);
@@ -1155,7 +1167,9 @@
 	unregister_netdevice_notifier(&cfg80211_netdev_notifier);
 	wiphy_sysfs_exit();
 	regulatory_exit();
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 	unregister_pernet_device(&cfg80211_pernet_ops);
+#endif
 	destroy_workqueue(cfg80211_wq);
 }
 module_exit(cfg80211_exit);