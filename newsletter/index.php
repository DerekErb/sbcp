<?php

/////////////////////////////////////////////////////////////////////////////
//
//  NEWSLETTER  index
//  @version    0.2 (13/05/2024)
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
$Nav->write('Newsletter');

// Newsletter
if ($SBC->getSite() === SiteCode::FR) {
    echo(t(1) . '<section id="newsletter">' . PHP_EOL);
        echo('<h2>Newsletter</h2>' . PHP_EOL);
    echo(t(1) . '</section>' . PHP_EOP);
}
else {
    echo(t(1) . '<section id="newsletter">' . PHP_EOL);
        echo('<h2>Newsletter</h2>' . PHP_EOL);
    echo(t(1) . '</section>' . PHP_EOP);
}

$Contact = new Contact();
$Contact->write();

$Footer = new Footer();
$Footer->write();
