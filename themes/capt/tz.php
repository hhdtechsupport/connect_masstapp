<?php

// display all errors
error_reporting(E_ALL);
ini_set("display_errors", 1);

$currdir = getcwd();

chdir($_SERVER['DOCUMENT_ROOT']);

define('DRUPAL_ROOT', $_SERVER['DOCUMENT_ROOT']);
require_once("./includes/bootstrap.inc");
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

chdir($currdir);

if (!isset($_SESSION)){
    session_start();
}

if (isset($_SESSION['tz'])) {
    exit;
}

if (isset($_POST['timezone'])) {
    $_SESSION['tz'] = $_POST['timezone'];
    echo 'reload';
    exit;
}
