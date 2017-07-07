<?php

/**
 * @file
 * Administrative page callbacks for the Commerce UBC CBM module.
 */

function commerce_ubc_cbm_form_settings() {
  $form['cbm_merchant'] = array(
    '#type' => 'fieldset',
    '#title' => 'Merchant Account Settings',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['cbm_merchant']['commerce_ubc_cbm_prod_auth_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication Server'),
    '#size' => 100,
    '#default_value' => variable_get('commerce_ubc_cbm_prod_auth_url', 'https://ssc.adm.ubc.ca/authServer/authenticate'),
    '#description' => t('The authentication server URL for production.'),
    '#required' => TRUE,
  );
  $form['cbm_merchant']['commerce_ubc_cbm_prod_pay_url'] = array(
    '#type' => 'textfield',
    '#title' => t('ePayment Web Service'),
    '#size' => 100,
    '#default_value' => variable_get('commerce_ubc_cbm_prod_pay_url', 'https://cbm.adm.ubc.ca/creditcardservice/CreditCardPaymentForm'),
    '#description' => t('The ePayment Web Service URL for production.'),
    '#required' => TRUE,
  );

  $form['cbm_debugging'] = array(
    '#type' => 'fieldset',
    '#title' => t("Testing and Debugging Settings"),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['cbm_debugging']['commerce_ubc_cbm_test_auth_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication Server (Testing)'),
    '#size' => 100,
    '#default_value' => variable_get('commerce_ubc_cbm_test_auth_url', 'https://ssc-test.adm.ubc.ca/authServer/authenticate'),
    '#description' => t('The authentication server URL for testing.'),
  );
  $form['cbm_debugging']['commerce_ubc_cbm_test_pay_url'] = array(
    '#type' => 'textfield',
    '#title' => t('ePayment Web Service (Testing)'),
    '#size' => 100,
    '#default_value' => variable_get('commerce_ubc_cbm_test_pay_url', 'https://cbm-test.adm.ubc.ca/creditcardservice/CreditCardPaymentForm'),
    '#description' => t('The ePayment Web Service URL for testing'),
  );

  $form['cbm_debugging']['commerce_ubc_cbm_test_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Testing Mode'),
    '#description' => t('Handle payment transactions using CBM testing servers only. Uncheck for live production payment transactions.'),
    '#default_value' => variable_get('commerce_ubc_cbm_test_mode', 1),
  );
  $form['cbm_debugging']['commerce_ubc_cbm_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log the messages for debugging'),
    '#default_value' => variable_get('commerce_ubc_cbm_log', 0),
    '#description' => t('Recommended even in production.'),
  );

  return system_settings_form($form);
}
