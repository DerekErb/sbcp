<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Nav
//  @version    2.2 (04/05/2024)
//  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

class Nav
{
    private     const   NAV             =   'Nav';
    protected   ?string $strClass       =   null;
    protected   ?string $strCurrItem    =   null;
    protected   ?string $strID          =   null;
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  __construct()
    //  Version 1.1 (30/04/2024)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct(?string $strClass = null, ?string $strID = null)
    {
        if (!is_null($strID))
            $this->setID($strID);
        
        if (!is_null($strClass))
            $this->setClass($strClass);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  setClass()
    //  @version    1.0 (01/05/2024)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set nav class
    //
    //  $param      string $strClass
    //
    //  EXAMPLE     setClass('Menu');
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function setClass(string $strClass) : void
    {
        $this->strClass = self::NAV . $strClass;
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  setID()
    //  @version    1.1 (04/05/2024)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set nav ID
    //
    //  $param      string $strID
    //
    //  EXAMPLE     setID('Menu');
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function setID(string $strID) : void
    {
        $this->strID = $strID . self::NAV;
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  write()
    //  @version    1.0 (30/04/2024)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Output the navigation
    //
    //  $param      ?string $strCurrItem
    //
    //  EXAMPLE     write('navAbout')
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function write(?string $strCurrItem = null) : void
    {
        $strClass       =   is_null($this->strClass)    ?   ''  : ' class="' . $this->strClass . '" ';
        $strID          =   is_null($this->strID)       ?   ''  : ' id="' . $this->strID . '" ';
        $strCurrItem    =   is_null($strCurrItem)       ?   null: $this::NAV . $strCurrItem;
        
        $arrFolders['NavAbout']             =   'about';
        $arrFolders['NavNewsletter']        =   'newsletter';
        $arrFolders['NavSocial']            =   'socialmedia';
        $arrFolders['NavSummaries']         =   'summaries';
        
        $SBC = new SBC();
        switch($SBC->getSite()) {
            case SiteCode::FR:
                $arrMenu['NavAbout']        =   'C\'est quoi';
                $arrMenu['NavNewsletter']   =   'Newsletter';
                $arrMenu['NavSocial']       =   'Réseaux sociaux';
//                $arrMenu['NavSummaries']    =   'Résumés';
                break;
            default:
                $arrMenu['NavAbout']        =   'About';
                $arrMenu['NavNewsletter']   =   'Newsletter';
                $arrMenu['NavSocial']       =   'Social';
//                $arrMenu['NavSummaries']    =   'Summaries';
                break;
        }
        // *** NAVigation ***
        echo(t(1) . '<!-- *** NAV *** -->' . PHP_EOL);
        echo(t(1) . '<nav' . $strID . $strClass . '>' . PHP_EOL);
        
            echo(t(2) . '<div class="navclass">' . PHP_EOL);
                foreach($arrMenu as $strKey => $strValue) {
                    $strCurr = ($strCurrItem == $strKey) ? ' class="current" ' : '';
                    echo(t(3) . '<ul' . $strCurr . '>' . PHP_EOL);
                        echo(t(4) . '<a href="/' . $arrFolders[$strKey] . '">' . $strValue . '</a>' . PHP_EOL);
                    echo(t(3) . '</div>' . PHP_EOL);
                }
            echo(t(2) . '</div>' . PHP_EOL);
        
        echo(t(1) . '</nav>' . PHP_EOP);
    }
}
