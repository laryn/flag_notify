<?php

/**
 * @file
 * Settings form.
 */

/**
 * Config form shown at admin/config/system/flag_notify.
 */
function flag_notify_admin($form, &$form_state) {

  $flags_comment_objs = flag_get_flags('comment');
  $flags_content_objs = flag_get_flags('node');
  $flags_comment = array('0' => 'None');
  $flags_content = array('0' => 'None');

  foreach ($flags_comment_objs as $flags_comment_obj) {
    $flags_comment[$flags_comment_obj->name] = $flags_comment_obj->title;
  }
  foreach ($flags_content_objs as $flags_content_obj) {
    $flags_content[$flags_content_obj->name] = $flags_content_obj->title;
  }
  $form['flag_notify_flag_comment_mname'] = array(
    '#type' => 'select',
    '#title' => t('Comment Notification Flag'),
    '#default_value' => variable_get('flag_notify_flag_comment_mname', '0'),
    '#description' => t('Choose the flag to be used to keep notification of comments follow-ups.'),
    '#options' => $flags_comment,
    '#required' => FALSE,
  );
  $form['flag_notify_flag_content_mname'] = array(
    '#type' => 'select',
    '#title' => t('Content Notification Flag'),
    '#default_value' => variable_get('flag_notify_flag_content_mname', '0'),
    '#options' => $flags_content,
    '#description' => t('Choose the flag to be used to keep notification of comments and modification of a given content.'),
    '#required' => FALSE,
  );
  $form['flag_notify_flag_group_mname'] = array(
    '#type' => 'select',
    '#title' => t('Group Notification Flag.'),
    '#default_value' => variable_get('flag_notify_flag_group_mname', ''),
    '#options' => $flags_content,
    '#description' => t('Choose the flag to be used to keep notification of group activity.'),
    '#required' => FALSE,
  );
  $form['flag_notify_url_manage_notifications'] = array(
    '#type' => 'textfield',
    '#title' => t('Manage own notifications URL'),
    '#default_value' => variable_get('flag_notify_url_manage_notifications', ''),
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('A relative URL (if any) where you allow users to manage their subscriptions, typically using a view. If provided, a text like "manage your notifications" will be added at the end of each sent email. Please provide a URL relative to drupal root, starting without "/".'),
    '#required' => FALSE,
  );
  $form['flag_notify_email_salutation'] = array(
    '#type' => 'textfield',
    '#title' => t('Email salutation'),
    '#default_value' => variable_get('flag_notify_email_salutation', t('Dear')),
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t('How to address your users?'),
    '#required' => FALSE,
  );
  $form['flag_notify_email_footer'] = array(
    '#type' => 'textfield',
    '#title' => t('Email footer'),
    '#default_value' => variable_get('flag_notify_email_footer', ''),
    '#size' => 80,
    '#maxlength' => 255,
    '#description' => t("An optional email footer. Sorry plain test, don't include HTML markup"),
    '#required' => FALSE,
  );
  $use_default_events = array(
    '1' => t('True'),
    '0' => t('False'),
  );
  $form['flag_notify_use_default_events'] = array(
    '#type' => 'select',
    '#title' => t('Use default events'),
    '#default_value' => variable_get('flag_notify_use_default_events', '1'),
    '#description' => t('Flag Notify already comes with its own event handler (node comment, node edit..). If you prefer instead to call directly <em>node_flag_main()</em>, e.g. using rules, change this option to <em>FALSE</em>'),
    '#options' => $use_default_events,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
