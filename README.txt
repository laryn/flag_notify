FLAG NOTIFY DRUPAL MODULE

A simple but flexible module that uses the great flag module for email
notifications of site activity and optionally integrates with organic groups.

It uses a hierarchical notification system organised in three levels:
groups,nodes,comments, where users are always notified only once for the same
event, with preference to the most relevant for them (i.e. a reply to own
comment is notified as such rather than "there is a comment in your group").

Flag Notify purposely do not build the flags in code (it just ask for the flag
machine name), nor it creates views of elements that have been subscribed.
While this approach require little bit extra work from the users, it increases
the flexibility and avoid potential problems if the og module is
enabled/disabled after this module.
If necessary, I can provide an export of flags and/or views.

Default notification for users are managed trough an option field in user
profile so they can can choose their default notification settings when they
submit a comment, a node or join a group.

All these three "levels" are optional and if the og module is not installed the
group level is just hidden.

Currently the notification email text is fixed (with a few customisation as
footer and salutation). A token-based email may be developed in the next
versions if there is request for that.

This project is sponsored by Associazione Alessandro Bartola and Università
Politecnica delle Marche that pay for my time :-)

For Installation instructions please read the INSTALL.txt file.
