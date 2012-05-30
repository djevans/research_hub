<?php

class sparql_views_plugin_argument_default_user_field extends views_plugin_argument_default {
 
  function get_argument() {
    watchdog('sparql_views','Trying to get_argument()');
    foreach (range(1, 3) as $i) {
      $account = menu_get_object('user', $i);
      if (!empty($account)) {
        watchdog('sparql_views','Account uid is %acc', array(
          '%acc' => $account->uid,
        ));
        $uid = $account->uid;
        $source_field = $this->options['sparql_options']['source_field'];
        $field = field_get_items('user', $account, $source_field);
        $replacement = $field[0]['value'];
        watchdog('sparql_views','Replacement value is %rep', array(
          '%rep' => $replacement,
        ));
        return $replacement;
      }
    }
  }
  
  /**
   * Retrieve the options when this is a new access
   * control plugin
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['source_field'] = array('default' => '');
    // Attach the SPARQL specific options.

    return $options;
  }
  
  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $fields = array();
    $instance_info = field_info_instances('user');
    foreach ($instance_info as $bundle) {
      foreach ($bundle as $field_name => $field_info) {
        $fields[$field_name] = check_plain(t($field_info['label']));
      }
    }
    $form['sparql_options']['source_field'] = array(
      '#type' => 'select',
      '#title' => t('Source Field'),
      '#options' => $fields,
      '#default_value' => $this->options['sparql_options']['source_field'],
      '#description' => t('The variable in the query will be replaced with the value of this field on the node.'),
      '#weight' => -1,
    );
  }
  
}

