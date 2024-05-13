<?php

/////////////////////////////////////////////////////////////////////////////
//
//  SOCIAL      index
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
$Nav->write('Social');

// Social networks
if ($SBC->getSite() == SiteCode::FR) {
    echo(t(1) . '<section id="socialmedia">' . PHP_EOL);
        echo('<h2>Réseaux Sociaux</h2>');
        echo('<ul>' . PHP_EOL);
            echo('<li>X (Twitter)</li>' . PHP_EOL);
            echo('<li>Facebook</li>' . PHP_EOL);
            echo('<li>Instagram</li>' . PHP_EOL);
            echo('<li>Meetup</li>' . PHP_EOL);
            echo('<li>Good Reads</li>' . PHP_EOL);
        echo('</ul>' . PHP_EOL);
    echo(t(1) . '</section>' . PHP_EOP);
}
else {
    echo(t(1) . '<section id="socialmedia">' . PHP_EOL);
        echo('<h2>Social Media</h2>');
        echo('<ul>' . PHP_EOL);
            echo('<li>X (Twitter)</li>' . PHP_EOL);
            echo('<li>Facebook</li>' . PHP_EOL);
            echo('<li>Instagram</li>' . PHP_EOL);
            echo('<li>Meetup</li>' . PHP_EOL);
            echo('<li>Good Reads</li>' . PHP_EOL);
        echo('</ul>' . PHP_EOL);
    echo(t(1) . '</section>' . PHP_EOP);
}
        
$Footer = new Footer();
$Footer->write();
