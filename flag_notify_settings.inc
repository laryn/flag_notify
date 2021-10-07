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
  $form['comment_subscription'] = array(
    '#type' => 'select',
    '#title' => t('Comment Subscription'),
    '#default_value' => $config->get('comment_subscription'),
    '#description' => t('Flag to follow replies to a comment.'),
    '#options' => $flags_comment,
    '#required' => FALSE,
  );

  $form['content_subscription'] = array(
    '#type' => 'select',
    '#title' => t('Content Subscription'),
    '#default_value' => $config->get('content_subscription'),
    '#options' => $flags_content,
    '#description' => t('Flag to follow replies on a content item.'),
    '#required' => FALSE,
  );

  $form['term_subscription'] = array(
    '#type' => 'select',
    '#title' => t('Term Subscription'),
    '#default_value' => $config->get('term_subscription'),
    '#options' => $flags_term,
    '#description' => t('Flag to follow content tagged with a term.'),
    '#required' => FALSE,
  );

  if (module_exists('og')) {
    $form['group_subscription'] = array(
      '#type' => 'select',
      '#title' => t('Group Subscription'),
      '#default_value' => $config->get('group_subscription'),
      '#options' => $flags_content,
      '#description' => t('Flag to follow activity in a group.'),
      '#required' => FALSE,
    );
  }
  $use_default_events = array(
    '1' => t('True'),
    '0' => t('False'),
  );
  $form['use_default_events'] = array(
    '#type' => 'select',
    '#title' => t('Use default events'),
    '#default_value' => $config->get('use_default_events'),
    '#description' => t('Flag Notify already comes with its own event handler (new comment, node edit..). If you prefer instead to call directly <em>node_flag_main()</em>, e.g. using rules, change this option to <em>FALSE</em>'),
    '#options' => $use_default_events,
    '#required' => TRUE,
  );
  $suspend_notifications = array(
    '1' => t('True (no email is sent)'),
    '0' => t('False (notifications are active)'),
  );
  $form['suspend_notifications'] = array(
    '#type' => 'select',
    '#title' => t('Suspend all notifications'),
    '#default_value' => $config->get('suspend_notifications'),
    '#description' => t('Use this option when you want to disable all notifications. Events issued during suspended periods will not result in email being sent or even queued for sending.'),
    '#options' => $suspend_notifications,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Config form shown at admin/config/system/flag_notify.
 */
function flag_notify_email_templates($form, &$form_state) {
  $config = config('flag_notify.settings');
  $content_sub = $config->get('content_subscription');
  $comment_sub = $config->get('comment_subscription');
  $term_sub = $config->get('term_subscription');
  $group_sub = $config->get('group_subscription');

  $form['#config'] = 'flag_notify.settings';
  if ($comment_sub || $content_sub || $group_sub) {
    /* New comment notifications */
    $form['comment_subscription_email'] = array(
      '#type' => 'fieldset',
      '#title' => t('Comment subscription email settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array(
        'class' => array(
          'flag-notify-email-settings',
        ),
      ),
    );
    $form['comment_subscription_email']['comment_email_subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#default_value' => $config->get('comment_email_subject'),
      '#size' => 80,
      '#maxlength' => 255,
      '#required' => FALSE,
    );
      $form['comment_subscription_email']['comment_email_body'] = array(
      '#title' => t('Message'),
      '#type' => 'textarea',
      '#default_value' => $config->get('comment_email_body'),
    );
  }
  if ($term_sub || $group_sub) {
    /* New content notification */
    $form['content_subscription_email'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content subscription email settings (new content)'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array(
        'class' => array(
          'flag-notify-email-settings',
        ),
      ),
    );
    $form['content_subscription_email']['content_email_subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#default_value' => $config->get('content_email_subject'),
      '#size' => 80,
      '#maxlength' => 255,
      '#required' => FALSE,
    );
    $form['content_subscription_email']['content_email_body'] = array(
      '#title' => t('Message'),
      '#type' => 'textarea',
      '#default_value' => $config->get('content_email_body'),
    );
  }

  if ($content_sub || $term_sub || $group_sub) {
    /* Edited content notifications */
    $form['content_subscription_email_edited'] = array(
      '#type' => 'fieldset',
      '#title' => t('Content subscription email settings (edited content)'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array(
        'class' => array(
          'flag-notify-email-settings',
        ),
      ),
    );
    $form['content_subscription_email_edited']['content_email_subject_edited'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#default_value' => $config->get('content_email_subject_edited'),
      '#size' => 80,
      '#maxlength' => 255,
      '#required' => FALSE,
    );
    $form['content_subscription_email_edited']['content_email_body_edited'] = array(
      '#title' => t('Message'),
      '#type' => 'textarea',
      '#default_value' => $config->get('content_email_body_edited'),
    );
  }

  if (module_exists('og') && $group_sub) {
    /* New user notification */
    $form['user_subscription_email'] = array(
      '#type' => 'fieldset',
      '#title' => t('Group: New user email settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array(
        'class' => array(
          'flag-notify-email-settings',
        ),
      ),
    );
    $form['user_subscription_email']['user_email_subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Subject'),
      '#default_value' => $config->get('user_email_subject'),
      '#size' => 80,
      '#maxlength' => 255,
      '#required' => FALSE,
    );
    $form['user_subscription_email']['user_email_body'] = array(
      '#title' => t('Message'),
      '#type' => 'textarea',
      '#default_value' => $config->get('user_email_body'),
    );
  }

  return system_settings_form($form);
}
