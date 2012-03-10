<?php

/**
 * @file
 * Nodewords support file.
 */

/**
 * Implements hook_nodewords_tags_info().
 */
function nodewords_verification_tags_nodewords_tags_info() {
  $tags = array(
    'alexa_verification_code' => array(
      'callback' => 'nodewords_verification_tags_alexa_verification_code',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_PAGE,
        ),
      ),
      'label' => t('Alexa verification code'),
      'templates' => array(
        'head' => array(
          'alexaVerifyID' => NODEWORDS_META,
        ),
      ),
    ),
    'bing_webmaster_center' => array(
      'callback' => 'nodewords_verification_tags_bing_webmaster_center',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_PAGE,
        ),
      ),
      'label' => t('Bing Webmaster Center verification code'),
      'templates' => array(
        'head' => array(
          'msvalidate.01' => NODEWORDS_META,
        ),
      ),
    ),
    'google_webmaster_tools' => array(
      'callback' => 'nodewords_verification_tags_google_webmaster_tools',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_PAGE,
        ),
      ),
      'label' => t('Google Webmaster Tools verification code'),
      'templates' => array(
        'head' => array(
          'google-site-verification' => NODEWORDS_META,
        ),
      ),
    ),
    'yahoo_site_explorer' => array(
      'callback' => 'nodewords_verification_tags_yahoo_site_explorer',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_PAGE,
        ),
      ),
      'label' => t('Yahoo! Site Explorer verification code'),
      'templates' => array(
        'head' => array(
          'y_key' => NODEWORDS_META,
        ),
      ),
    ),
    'yandex_webmaster_tools' => array(
      'callback' => 'nodewords_verification_tags_yandex_webmaster_tools',
      'context' => array(
        'allowed' => array(
          NODEWORDS_TYPE_PAGE,
        ),
      ),
      'label' => t('Yandex verification code'),
      'templates' => array(
        'head' => array(
          'yandex-verification' => NODEWORDS_META,
        ),
      ),
    ),
  );

  return $tags;
}
