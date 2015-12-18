<?php

session_start();

// If browser's timezone has already been added to the session, then return nothing
if (isset($_SESSION['tz'])) {
    exit;
}
// If timezone needs to be added, then return instructions to reload
if (isset($_POST['timezone'])) {
    $_SESSION['tz'] = $_POST['timezone'];
    print 'reload';
    exit;
}
