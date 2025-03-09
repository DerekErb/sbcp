<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       SBC
//  @version    1.2 (09/03/2025)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

/*enum SiteCode : string
{
    case FR     =   'CDLS';
    case EN     =   'ESBC';
    case GEN    =   'SBC';
}
*/
class SBC extends Site
{
//    protected   string  $strSiteTitle   =   '';
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  __construct()
    //  Version 1.2 (12/05/2024)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct()
    {
/*        switch($this->getSite()) {
            case SiteCode::EN:
                $this->setTitle('English Silent Book Club Paris');
                break;
            case SiteCode::FR:
                $this->setTitle('Club de lecture silencieuse Paris');
                break;
            default:
                $this->setTitle('Silent Book Club Paris');
                Site::setLang(getenv('SITE_DEF_LANG'));
                break;
        }
*/
        parent::__construct();
    }
    
    function getSiteCode() : string
    {
        return(getenv('SITE_CODE'));
    }
    
/*    function getAltLinks(string $strLang) : array
    {
        // Return the alternate language link
        if ($strLang === 'fr') {
            $strLang    =   'en';
            $strURL     =   'https://englishsilentbookclub.paris';
            $strTitle   =   'English Silent Book Club Paris';
        }
        else {
            $strLang    =   'fr';
            $strURL     =   'https://clubdelecturesilencieuse.paris';
            $strTitle   =   'Club de lecture silencieuse Paris';
        }
        
        return(array(
            'AltLang'   =>  $strLang,
            'AltURL'    =>  $strURL,
            'AltTitle'  =>  $strTitle,
            )
        );
    }*/
    
/*    function getSite() : SiteCode
    {
        $Site = new Site();
        if (strContains(getenv('SITE_SERVER_NAME'), 'clubdelecture')) {
            Site::setLang('fr');
            return (SiteCode::FR);
        }
        if (strContains(getenv('SITE_SERVER_NAME'), 'englishsilentbookclub')) {
            Site::setLang('en');
            return (SiteCode::EN);
        }
        return(SiteCode::GEN);
    }*/
    
/*    function setTitle($strTitle) : void
    {
        $strTitle = getenv('SITE_TITLE');
    }
    
    function getSiteTitle() : string
    {
        return(getenv('SITE_TITLE'));
    }*/

    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  writeHeader()
    //
    //  Output page header
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function writeHeader() : void
    {
        $Header = new Header();
        $Header->write();
    }
}
