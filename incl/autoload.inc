<?php

/////////////////////////////////////////////////////////////////////////////
//
//              autoload.inc
//  @version    1a (08/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Class autoload register function
//
/////////////////////////////////////////////////////////////////////////////

spl_autoload_register(function($className) {
    $file = $_SERVER['DOCUMENT_ROOT'] . '/incl/' . $className . '.inc';
    if (file_exists($file)) {
        include_once($file);
    }
});
