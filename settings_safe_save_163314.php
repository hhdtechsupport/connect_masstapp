<?php
$update_free_access = FALSE;
$drupal_hash_salt = 'fdsa8yfhlk4flsdkh0HNcv24h,kdfhfiohzv4hjhvnu9vnuihjm,/322jhfkas';
# $base_url = 'http://www.example.com';  // NO trailing slash!
ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 200000);
ini_set('session.cookie_lifetime', 2000000);
$conf['404_fast_paths_exclude'] = '/\/(?:styles)\//';
$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['404_fast_html'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';

# $conf['allow_authorize_operations'] = FALSE;
$databases = array();
   $databases['default']['default'] = array(
     'driver' => 'mysql',
     'database' => 'drupal_captconnect',
     'username' => 'captconnect',
     'password' => 'MEkmf0234klhj*y',
     'host' => 'pubdevweb1.edc.org',
     'prefix' => '',
   );
#$conf['environment_indicator_enabled'] = TRUE;
#$conf['environment_indicator_text'] = 'Development SERVER';
#$conf['environment_indicator_color'] = 'green';
