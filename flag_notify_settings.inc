<?php

/**
 * @file
 * Settings form.
 */

/**
 * Config form shown at admin/config/system/flag_notify
 */
function flag_notify_admin($form, &$form_state) {

  $form['flag_notify_flag_group_mname'] = array(
    '#type' => 'textfield',
    '#title' => t('The machine name of the flag to be notified of group activity'),
    '#default_value' => variable_get('flag_notify_flag_group_mname', ''),
    '#size' => 20,
    '#maxlength' => 255,
    '#description' => t('In the flag module create a "Receive notifications of this group\'s activity" flag and write here its machine name.'),
    '#required' => FALSE,
  );
  $form['flag_notify_flag_content_mname'] = array(
    '#type' => 'textfield',
    '#title' => t('The machine name of the flag to be notified of activity related to this content'),
    '#default_value' => variable_get('flag_notify_flag_content_mname', ''),
    '#size' => 20,
    '#maxlength' => 255,
    '#description' => t('In the flag module create a "Receive notifications of this content\'s activity" flag and write here its machine name.'),
    '#required' => FALSE,
  );
  $form['flag_notify_flag_comment_mname'] = array(
    '#type' => 'textfield',
    '#title' => t('The machine name of the flag to be notified of replied to this comment.'),
    '#default_value' => variable_get('flag_notify_flag_comment_mname', ''),
    '#size' => 20,
    '#maxlength' => 255,
    '#description' => t('In the flag module create a "Receive notifications of replies to this comment" flag and write here its machine name.'),
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
    '#description' => t('An optional email footer. Sorry plain test, don\'t include HTML markup'),
    '#required' => FALSE,
  );
  $useDefaultEvents = array(
    '1' => t('True'),
    '0' => t('False'),
  );
  $form['flag_notify_use_default_events'] = array(
    '#type' => 'select',
    '#title' => t('Use default events'),
    '#default_value' => variable_get('flag_notify_use_default_events', '1'),
    '#description' => t('Flag Notify already comes with its own event handler (node comment, node edit..). If you prefer instead to call directly <em>node_flag_main()</em>, e.g. using rules, change this option to <em>FALSE</em>'),
    '#options' => $useDefaultEvents,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
