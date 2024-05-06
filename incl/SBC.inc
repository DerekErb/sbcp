<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       SBC
//  @version    1.1 (12/04/2024)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

enum SiteCode : string
{
    case FR     =   'CDLS';
    case EN     =   'ESBC';
    case GEN    =   'SBC';
}

class SBC extends Site
{
    protected   string  $strSiteTitle   =   '';
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  __construct()
    //  Version 1.1 (30/04/2024)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct()
    {
        switch($this->getSite()) {
            case SiteCode::EN:
                $this->setTitle('English Silent Book Club Paris');
                Site::setLang('en');
                break;
            case SiteCode::FR:
                $this->setTitle('Club de lecture silencieuse Paris');
                Site::setLang('fr');
                break;
            default:
                $this->setTitle('Silent Book Club Paris');
                Site::setLang('en');
                break;
        }
        
        parent::__construct();
    }
    
    function getSite() : SiteCode
    {
        $Site = new Site();
        if (strContains($Site->getServerName(), 'clubdelecture'))
            return(SiteCode::FR);
        if (strContains($Site->getServerName(), 'englishsilentbookclub'))
            return(SiteCode::EN);
        return(SiteCode::GEN);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  writeHeader()
    //
    //  Output page header
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function writeHeader() : void
    {
        echo(t(1) . '<header>' . PHP_EOL);
            echo(t(2) .'<div id="hero">' . PHP_EOL);
                echo(t(3) . '<div id="headtitle">' . PHP_EOL);
                    echo(t(4) . '<h1 translate="no">' . $this->getSiteTitle() . '</h1>' . PHP_EOL);
                echo(t(3) . '</div>' . PHP_EOP);
            echo(t(2) . '</div>' . PHP_EOP);
        echo(t(1) . '</header>' . PHP_EOP);
    }
    
}
