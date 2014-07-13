
# Help Document
=========================================================

UBC CBM Payment module was created to be used with Drupal Commerce framework to allow payment transactions with
UBC CBM payment gateway.

Information about UBC CBM Payment gateway can be found at

https://epayment.it.ubc.ca/

For issues or problems relating to the funcitonality of the UBC CBM Module not addressed in this document contact:
UBC Web Services at webservices.ubcit@ubc.ca


## A: Installation
------------------------------------
Edit commerce-ubc-cbm.module constants to be CBM server domains and URI paths.
Server URL and paths can be found at https://eypayment.it.ubc.ca/developers.

FTP commerce_ubc_cbm directory into modules folder.
Navigate to admin/modules.
Enable Commerce_ubc_cbm, which can be found in Commerce (contrib) package.


## Configuration
------------------------------------

1. Go to Store -> Configuration -> Payment methods
    path: admin/commerce/config/payment-methods
2. Enable UBC ePayment
3. Select "UBC ePayment" link or "edit" link
4. Select "Enable payment method: UBC ePayment" or "edit" link in Actions section
5. Enter merchant account information in Payment Settings section.
  * Merchant ID
  *  Merchant Authentication ID (user name provided by SIS/ePayment used to authenticate access to payment servers)
  * Merchant Authentication Credentials (password provide by SIS/ePayment for access to payment servers)
  * Default UBC FMS Account -- one long string for account set up with UBC Financial Management System made up of:
        Fund code (req) + Dept code (req) + program (opt. leave space if not using) + project id (req) + account no. (req)
        e.g.
        fund code = F0000
        dept code = 123010
        program = CINEP
        project id = 12F30103
        account number = 465730
        FMS account would be: F0000123010 12F30103465730 or F0000123010CINEP12F30103465730
        Note: if you have only one account you can contact SIS/ePayment and ask that they assign that account to be used as default for all sales
        See: "Account overriding and splitting" at https://epayment.it.ubc.ca/web-service/accounting-information-and-payment-types
  * check "Testing Mode" to have your transactions handled by the testing servers, uncheck when ready to have purchase handled by production servers
6. Go to People -> Permissions and check to allow "anonymous user" for "Access UBC CBM Payment"

## Applying sales to different FMS accounts
----------------------------------------------------------------------------------------
1. Go to Store -> Products -> Product types at admin/commerce/products/types
2. Select "manage fields" for any of the product types
3. Select CBM GL Account field "edit" link
4. Edit allowed values list in format value|Label adding additional accounts as required
    e.g.
    default|Default Account
    F0000123010 12F30103465730|Account F
    G0000123010 12F30103465730|Account G

5. Save
6. If you want to have one account set as default you can select a new value from drop down list for "Default Value"
    Note: the option "default value" that is provided automatically will use the value provided in Configuration 5.d
7. Edit each of your products selecting the account you wish to applied to their sales, or ensure "Default Account" is set.


## Uninstalling
-------------------------------------
1. Go to Store -> Configuration -> Payment methods
2. "Disable" UBC ePayement
3. Go to Modules -> Commerce (contrib) and deactivate UBC CBM Payment

Notes regarding disabling the UBC CBM Module

* The payment configuration is set up using the Rules module, as of Commerce 7.x-1.3 there is no reliable way to clear out the payment rule set up for your payment method.
  *  By disabling the rule will deactivate it but all data relating to this payment method is still in the database
* When the module is disabled, the payment configuration rule show red warning text that there is no payment module associated with that rule.
* The GL Account field is created as part of the Fields module, like the payment configuration rule the GL Account field is also left behind
  * You can delete go into admin/commerce/products/types/ and choosing a product type "manage fields" delete that field from being associated with that type
  * But this will also delete any data associated with the product in that field will, use with caution



## Trouble-shooting
-----------------------------
1. Enabled module but payment option not shown as option in configuration for Payment methods.
   Try clearing cache, manually running cron and try again.

2. ePayment Servcer refusing transaction with error that GL_ACCT_CD is missing or invalid

  * For store where all sales to go to one UBC Financial Account:
    - go to configuration page (admin/commerce/config/payment-methods) ensure you have provided FMS and it is in the correct format. See section "Configuration" 5.d above.
      -) optionally you can request SIS/ePayment to have default account set with them see:
           "Account overriding and splitting" at https://epayment.it.ubc.ca/web-service/accounting-information-and-payment-types

  * For store where you want sales divided between different UBC Financial Accounts:
    - ensure GL Account Field is set up with correct account values, in correct format (admin/commerce/products/types). See section "Configuration" 5.d above.
    - ensure that Default FMS account value is set up with correct values in correct format in merchant configuration page (admin/commerce/config/payment-methods)
      -ensure that all products have an account selected to be used for their sales.

3. New product type does not have GL Account field option
  * Go to admin/commerce/products/types and "manage fields" for the new product type
    - In "Add existing field" section enter a field label (e.g. CBM GL Account) and select "List (text): commerce_ubc_cbm_gl_account (CBM GL Account)" from the drop list "field to share"

4.  Checkout process stating error "Unable to create a connection with payment server."
  * This error would be due to authentication problem with server. Go to payment configuration (admin/commerce/config/payment-methods) and ensure you have correctly entered
        Merchant Id
        Merchant Authentication ID
        Merchant Authentication credentials
  * To confirm that you are using the correct values contact SIS/ePayment
  * If you have confirmed that the values are correct contact UBC IT Web Services (to investigate if changes have been made to server-to-server communication configuration settings

5. Server failing transaction saying "unable to notify merchant"
  *  This indicates user permission not set correctly, go to People -> Permissions and check to allow "anonymous user" for "Access UBC CBM Payment"

6. Needing to track payment transaction data
   * i) For purchases that have completed transactions Go to Store -> Orders -> and select "payment" link for oreder you are interested in.
   * ii) For purchases that may have stalled or had other issues that kept payment from completing select "shopping carts" tab and then select "payment" link
   * You should see a table with payment details and status, click "view" link to see more detailed information
   * In payload section are all details related to payment transaction communications to and from the ePayment gateway
     * i) "payment request" is sent from commerce site to ePayement server
     * ii) "notifciation request" is sent from ePayment server to commerce site
     * iii) "notification response" is sent from commcerce site to payment server
     * iv) "continuation request" is sent from payment server to commerce site
   * Errors are logged in Reports -> Recent log messages
