<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       SBC
//  @version    1.0 (03/03/2024)
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
class SBC
{
    protected   string  $strSiteTitle   =   '';
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // CONSTRUCTOR()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct()
    {
        switch($this->getSite()) {
            case SiteCode::EN:
                $this->setSiteTitle('English Silent Book Club Paris');
                Site::setLang('en');
                break;
            case SiteCode::FR:
                $this->setSiteTitle('Club de lecture silencieuse Paris');
                Site::setLang('fr');
                break;
            default:
                $this->setSiteTitle('Silent Book Club Paris');
                Site::setLang('en');
                break;
        }
        
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
    
    function getSiteTitle() : string
    {
        return($this->strSiteTitle);
    }
    
    function setSiteTitle(string $strSiteTitle) : void
    {
        $this->strSiteTitle = $strSiteTitle;
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
                    echo(t(4) . '<h1>' . $this->getSiteTitle() . '</h1>' . PHP_EOL);
                echo(t(3) . '</div>' . PHP_EOP);
            echo('</div>' . PHP_EOP);
        echo(t(1) . '</header>' . PHP_EOP);
    }
    
}
