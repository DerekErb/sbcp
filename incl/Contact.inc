<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Contact
//  @version    0.0.1 (15/05/2024)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////
class Contact
{
    function write() : void
    {
        $strLang = Site::getLang();
        
        echo(t(1) . '<section id="contact">' . PHP_EOL);
//            echo(t(2) . '<div>' . PHP_EOL);
//                echo(t(3) . '<h3></h3>' . PHP_EOL);
//            echo(t(2) . '</div>' . PHP_EOL);
            echo(t(2) . '<div>' . PHP_EOL);
                $strContact = ($strLang === 'fr') ? 'Contactez Nous'            : 'Contact Us';
                $strEmail   = ($strLang === 'fr') ? 'silentbookclubparis@gmail.com'   : 'silentbookclub@gmail.com';
                echo(t(3) . '<a href="mailto:' . $strEmail . '">' . $strContact . '</a>' . PHP_EOL);
            echo(t(2) . '</div>' . PHP_EOL);
        echo(t(1) . '</section>' . PHP_EOP);
    }
    
}

