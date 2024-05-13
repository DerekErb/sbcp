<?php

/////////////////////////////////////////////////////////////////////////////
//
//  /           index
//  @version    1.0 (13/05/2024)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

require_once($_SERVER['DOCUMENT_ROOT'] . '/incl/sysfuns.inc');

error_reporting(E_ALL);

$strLang = Site::getLang();

$SBC = new SBC();

$Head = new Head();
$Head->write();
$SBC->writeHeader();
$Nav = new Nav();
$Nav->write();

    // Description
    if (($SBC->getSite() !== SiteCode::EN) && ($SBC->getSite() !== SiteCode::FR)) {
        echo(t(1) .'<section id="about">' . PHP_EOL);
            echo(t(2) . 'GENERIC BILINGUAL TEXT HERE');
        echo(t(1) . '</section>' . PHP_EOP);
    }
    else {
        if ($SBC->getSite() === SiteCode::FR) {
            echo(t(1) .'<section id="hero">' . PHP_EOL);
                echo(t(2) . '<h2 translate="no">' . $SBC->getSiteTitle() . '</h2>' . PHP_EOP);
            echo(t(1) . '</section>' . PHP_EOP);
        }
        else {
            echo(t(1) .'<section id="hero">' . PHP_EOL);
                echo(t(2) . '<h2 translate="no">' . $SBC->getSiteTitle() . '</h2>' . PHP_EOP);
            echo(t(1) . '</section>' . PHP_EOP);
        }
    }
    
$Footer = new Footer();
$Footer->write();
