<?php

/////////////////////////////////////////////////////////////////////////////
//
//  SUMMARIES   index
//  @version    0.1 (15/05/2024)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

require_once($_SERVER['DOCUMENT_ROOT'] . '/incl/sysfuns.inc');

error_reporting(E_ALL);

$SBC = new SBC();

$Head = new Head();
$Head->write();
$SBC->writeHeader();
$Nav = new Nav();
$Nav->write('Summaries');

// Session Summaries
if ($SBC->getSiteLang() === 'fr') {
    echo(t(1) . '<section id="summaries">' . PHP_EOL);
        echo('<h2>Résumés des Sessions</h2>' . PHP_EOL);
    echo(t(1) . '</section>' . PHP_EOP);
}
else {
    echo(t(1) . '<section id="summaries">' . PHP_EOL);
        echo('<h2>Session Summaries</h2>' . PHP_EOL);
    echo(t(1) . '</section>' . PHP_EOP);
}

$Footer = new Footer();
$Footer->write();
