<?php

/**
 * @file
 * Settings form.
 */

/**
 * Config form shown at admin/config/system/flag_notify.
 */
function flag_notify_admin($form, &$form_state) {
  $config = config('flag_notify.settings');

  $flags_comment_objs = flag_get_flags('comment');
  $flags_content_objs = flag_get_flags('node');
  $flags_term_objs = flag_get_flags('taxonomy_term');
  $flags_comment = array('0' => 'None');
  $flags_content = array('0' => 'None');
  $flags_term = array('0' => 'None');

  foreach ($flags_comment_objs as $flags_comment_obj) {
    $flags_comment[$flags_comment_obj->name] = $flags_comment_obj->title;
  }
  foreach ($flags_content_objs as $flags_content_obj) {
    $flags_content[$flags_content_obj->name] = $flags_content_obj->title;
  }
  foreach ($flags_term_objs as $flags_term_obj) {
    $flags_term[$flags_term_obj->name] = $flags_term_obj->title;
  }
  $form['#config'] = 'flag_notify.settings';
  $form['flag_notify_comment_subscription'] = array(
    '#type' => 'select',
    '#title' => t('Comment Subscription'),
    '#default_value' => $config->get('flag_notify_comment_subscription'),
    '#description' => t('Flag to follow replies to a comment.'),
    '#options' => $flags_comment,
    '#required' => FALSE,
  );
  $form['flag_notify_content_subscription'] = array(
    '#type' => 'select',
    '#title' => t('Content Subscription'),
    '#default_value' => $config->get('flag_notify_content_subscription'),
    '#options' => $flags_content,
    '#description' => t('Flag to follow replies on a content item.'),
    '#required' => FALSE,
  );
  $form['flag_notify_term_subscription'] = array(
    '#type' => 'select',
    '#title' => t('Term Subscription'),
    '#default_value' => $config->get('flag_notify_term_subscription'),
    '#options' => $flags_term,
    '#description' => t('Flag to follow content tagged with a term.'),
    '#required' => FALSE,
  );
  if (module_exists('og')) {
    $form['flag_notify_group_subscription'] = array(
      '#type' => 'select',
      '#title' => t('Group Subscription'),
      '#default_value' => $config->get('flag_notify_group_subscription'),
      '#options' => $flags_content,
      '#description' => t('Flag to follow activity in a group.'),
      '#required' => FALSE,
    );
  }
  $form['flag_notify_url_manage_notifications'] = array(
    '#type' => 'textfield',
    '#title' => t('Manage own notifications URL'),
    '#default_value' => $config->get('flag_notify_url_manage_notifications'),
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('A relative URL (if any) where you allow users to manage their subscriptions, typically using a view. If provided, a text like "manage your notifications" will be added at the end of each sent email. Please provide a URL relative to the Backdrop root, starting without "/".'),
    '#required' => FALSE,
  );
  $form['flag_notify_email_salutation'] = array(
    '#type' => 'textfield',
    '#title' => t('Email salutation'),
    '#default_value' => $config->get('flag_notify_email_salutation'),
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('How to address your users?'),
    '#required' => FALSE,
  );
  $form['flag_notify_email_footer'] = array(
    '#type' => 'textfield',
    '#title' => t('Email footer'),
    '#default_value' => $config->get('flag_notify_email_footer'),
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t("An optional email footer. Basic HTML mark-up will be converted in text equivalent."),
    '#required' => FALSE,
  );
  $use_default_events = array(
    '1' => t('True'),
    '0' => t('False'),
  );
  $form['flag_notify_use_default_events'] = array(
    '#type' => 'select',
    '#title' => t('Use default events'),
    '#default_value' => $config->get('flag_notify_use_default_events'),
    '#description' => t('Flag Notify already comes with its own event handler (new comment, node edit..). If you prefer instead to call directly <em>node_flag_main()</em>, e.g. using rules, change this option to <em>FALSE</em>'),
    '#options' => $use_default_events,
    '#required' => TRUE,
  );
  $suspend_notifications = array(
    '1' => t('True (no email is sent)'),
    '0' => t('False (notifications are active)'),
  );
  $form['flag_notify_suspend_notifications'] = array(
    '#type' => 'select',
    '#title' => t('Suspend all notifications'),
    '#default_value' => $config->get('flag_notify_suspend_notifications'),
    '#description' => t('Use this option when you want to disable all notifications. Events issued during suspended periods will not result in email being sent or even queued for sending.'),
    '#options' => $suspend_notifications,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
