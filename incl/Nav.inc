<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Nav
//  @version    2.1 (01/05/2024)
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
    //  @version    1.0 (30/04/2024)
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
        $this->strID = self::NAV . $strID;
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
        $strClass   =   is_null($this->strClass)    ?   ''  : ' class="' . $this->strClass . '" ';
        $strID      =   is_null($this->strID)       ?   ''  : ' id="' . $this->strID . '" ';
        
        // *** NAVigation ***
        echo(t(1) . '<!-- *** NAV *** -->' . PHP_EOL);
        echo(t(1) . '<nav ' . $strID . $strClass . '>' . PHP_EOL);
        
        echo(t(1) . '</nav>' . PHP_EOP);
    }
}
