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
$strSiteCode = $SBC->getSiteCode();

$Head = new Head();
$Head->write();
$Header = new Header();
$Header->write();

//$SBC->writeHeader();
//$Nav = new Nav();
//$Nav->write();

    // Description
    if ($strSiteCode === 'gen') {
        echo(t(1) .'<section id="hero">' . PHP_EOL);
            echo(t(2) . '<h1 translate="no">GENERIC BILINGUAL TEXT HERE</h1>' . PHP_EOL);
        echo(t(1) . '</section>' . PHP_EOP);
    }
    else {
        echo(t(1) .'<section id="hero">' . PHP_EOL);
            echo(t(2) . '<h1 translate="no">' . getenv('SITE_TITLE') . '</h1>' . PHP_EOP);
            
            echo(t(2) . '<div class="action1st">' . PHP_EOL);
                $strLink = $strLang === 'fr' ? "C'est quoi un club de lecture silencieuse ?" : "What is a Silent Book Club?";
                echo(t(3) . '<a href="/about/">' . $strLink . '</a>' . PHP_EOL);
            echo(t(2) . '</div>' . PHP_EOP);
            
            echo(t(2) . '<div class="social">' . PHP_EOL);
                echo(t(3) . '<div class="item_social" id="fb">' . PHP_EOL);
                    $strLangLink = $strLang === 'fr' ? 'silentbookclubparis' : 'englishsilentbookclubparis';
                    $strLink = '<a href="https://facebook.com/groups/' . $strLangLink . '" title="Facebook" target="_blank" rel="noreferrer">';
                    echo(t(4) . '<div class="logo_social" data-label="Facebook">' . PHP_EOL);
                        echo(t(5) . $strLink . '</a>' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                    echo(t(4) . '<div class="link_social">' . PHP_EOL);
                        echo(t(5) . $strLink . 'Facebook</a>' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                echo(t(3) . '</div>' . PHP_EOP);
                
                echo(t(3) . '<div class="item_social" id="instagram">' . PHP_EOL);
                    $strLangLink = $strLang === 'fr' ? 'clubdelecturesilencieuseparis' : 'englishsbcparis';
                    $strLink = '<a href="https://instagram.com/' . $strLangLink . '/" title="Instagram" target="_blank" rel="noreferrer">';
                    echo(t(4) . '<div class="logo_social" data-label="Instagram">' . PHP_EOL);
                        echo(t(5) . $strLink . '</a>' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                    echo(t(4) . '<div class="link_social">' . PHP_EOL);
                        echo(t(5) . $strLink . 'Instagram</a>' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                echo(t(3) . '</div>' . PHP_EOP);
                
//                echo(t(3) . '<div class="item_social" id="mastodon">' . PHP_EOL);
//                    $strLangLink = $strLang === 'fr' ? 'clubdelecturesilenceuseparis' : 'englishsbcparis';
//                    $strLink = '<a href="https://mastodon.org/' . $strLangLink . '" title="Mastodon" target="_blank" rel="noreferrer">';
//                    echo(t(4) . '<div class="logo_social" data-label="Mastodon">' . PHP_EOL);
//                        echo(t(5) . $strLink . '</a>' . PHP_EOL);
//                    echo(t(4) . '</div>' . PHP_EOL);
//                    echo(t(4) . '<div class="link_social">' . PHP_EOL);
//                        echo(t(5) . $strLink . 'Mastodon</a>' . PHP_EOL)
//                    echo(t(4) . '</div>' . PHP_EOL);
//                echo(t(3) . '</div>' . PHP_EOP);

//                echo(t(3) . '<div class="item_social" id="threads">' . PHP_EOL);
//                    $strLangLink = $strLang === 'fr' ? 'clubdelecturesilenceuseparis' : 'englishsbcparis';
//                    $strLink = '<a href="https://mastodon.org/' . $strLangLink . '" title="Mastodon" target="_blank" rel="noreferrer">';
//                    echo(t(4) . '<div class="logo_social" data-label="Threads">' . PHP_EOL);
//                        echo(t(5) . $strLink . '</a>' . PHP_EOL);
//                    echo(t(4) . '</div>' . PHP_EOL);
//                    echo(t(4) . '<div class="link_social">' . PHP_EOL);
//                        echo(t(5) . $strLink . 'Threads</a>' . PHP_EOL);
//                    echo(t(4) . '</div>' . PHP_EOL);
//                echo(t(3) . '</div>' . PHP_EOP);
//
                echo(t(3) . '<div class="item_social" id="twitter">' . PHP_EOL);
                    $strLangLink = $strLang === 'fr' ? '' : '';
        $strLink = ($strLang === 'fr' ? 'fb' : 'fb');
                    echo(t(4) . '<div class="logo_social" data-label="X (Twitter)">' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                    echo(t(4) . '<div class="link_social">' . PHP_EOL);
        echo(t(5) . '<a href="https://facebook.com/' . $strLink . '">X (Twitter)</a>' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                echo(t(3) . '</div>' . PHP_EOP);
                echo(t(3) . '<div class="item_social" id="goodreads">' . PHP_EOL);
        $strLink = ($strLang === 'fr' ? 'fb' : 'fb');
                    echo(t(4) . '<div class="logo_social" data-label="Goodreads">' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                    echo(t(4) . '<div class="link_social">' . PHP_EOL);
        echo(t(5) . '<a href="https://facebook.com/' . $strLink . '">Goodreads</a>' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                echo(t(3) . '</div>' . PHP_EOP);
                echo(t(3) . '<div class="item_social" id="meetup">' . PHP_EOL);
        $strLink = ($strLang === 'fr' ? 'fb' : 'fb');
                    echo(t(4) . '<div class="logo_social" data-label="Meetup">' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                    echo(t(4) . '<div class="link_social">' . PHP_EOL);
        echo(t(5) . '<a href="https://facebook.com/' . $strLink . '">Meetup</a>' . PHP_EOL);
                    echo(t(4) . '</div>' . PHP_EOL);
                echo(t(3) . '</div>' . PHP_EOP);
            echo(t(2) . '</div>' . PHP_EOP);
        
            echo(t(2) . '<div class="action2nd">' . PHP_EOL);
                $strLink = $strLang === 'fr' ? "Abonnez-vous à notre Newsletter" : "Sign up for our Newsletter";
                echo(t(3) . '<a href="/newsletter/">' . $strLink . '</a>' . PHP_EOL);
            echo(t(2) . '</div>' . PHP_EOP);
        
        
        echo(t(1) . '</section>' . PHP_EOP);
    }
    
$Contact = new Contact();
$Contact->write();

$Footer = new Footer();
$Footer->write();

