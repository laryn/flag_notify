FLAG NOTIFY DRUPAL MODULE

Flag Notify module uses the fantastic flag module to implement a simple yet flexible way for users to stay updated with site activity, receiving notification of new comments, content modification or group activity.
It use a hierarchical notification groups/nodes/comment and users are always notified only once for the same event.

This module do not build the flags for you (it just ask for the flag machine name), not it create views of elements that have been subscribed (but you can easily create a view for that).

This module install a field for letting users choose their default notification settings.
If you install the og module AFTER having installed this module and you want to use this module for notification of group activity you have to manually edit the field field_notification_defaults settings to include a default for group activity notifications and give it the 'group' key, e.g. in allowed values you will have:
group|Activity in the groups you join
content|New comments and modifications on content you create
comment|Replies to your comments

These defaults affect only new users, so if you install this module on a established site you have to give users the default options you require.
