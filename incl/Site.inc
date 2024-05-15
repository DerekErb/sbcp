<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Site
//  @version    42.0.6 (15/05/2024)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

class Site
{
    public const            VER_NUM             =   '0.2.2';
    public const            CSS_DIR             =   '/css/';
    public const            CSV_EXP_DIR         =   '/impexp/';
    public const            CSV_IMP_DIR         =   '/impexp/';
    public const            FILE_BASE           =   'sbc';
    public const            FONTS_DIR           =   '/fonts/';
    public const            IMGS_DIR            =   '/imgs/';
    public const            JS_DIR              =   '/js/';
    
    // dbTable uses the ImpExp tables
    public const            IMPEXP              =   true;
    
    // Live site published for SE indexing
    public const            B_PUBLISHED         =   false;
    
    protected static bool   $bSecure            =   false;
    
    public static ?string   $strHttp            =   null;
    public static ?string   $strServerName      =   null;
    public static ?string   $strPath            =   null;
    public static ?string   $strRoot            =   null;
    public static ?string   $strSubTit          =   null;
    public static ?string   $strTitle           =   'Silent Book Club';
    
    private const           ARR_COOKIES         =   array(
                                                        'cookies',
                                                    );
    
    //////////////////////////////////////////////////////////
    //
    // SITE DEFAULTS
    //
    //////////////////////////////////////////////////////////
    
    public const            DEF_COOKIE_DURATION =   8;  // days
    public const            DEF_LANG            =   'en';
    public const            DEF_FMTDT           =   'wd';
    public const            DEF_TZONE           =   'Europe/Paris';
    public const            DEF_USERID          =   1;
    protected const         SITE_COPY           =   'Derek Erb Solutions';
    protected const         SITE_COPYSITE       =   'https://derekerb.solutions';
    
    //////////////////////////////////////////////////////////
    //
    // DEV / STAGE / PROD
    //
    //////////////////////////////////////////////////////////
    
    protected static bool   $bDev               =   false;
    protected static bool   $bStage             =   false;
    protected static bool   $bProd              =   false;
    protected static bool   $bLocal             =   false;
    
    private const           ARR_DEV_SITES       =   array(
                                                        'silentbookclubparis.local',
                                                        'silentbookclubparisfr.local',
                                                        'englishsilentbookclubparis.local',
                                                        'englishsilentbookclubparisfr.local',
                                                        'clubdelecturesilencieuseparis.local',
                                                        'clubdelecturesilencieusefr.local',
                                                    );
    private const           ARR_STAGE_SITES     =   array(
                                                        'xxx-prod',
                                                        'des-dev.xxx',
                                                    );
    
    private const           ARR_PROD_SITES      =   array(
                                                        'silentbookclub.paris',
                                                        'silentbookclubparis.fr',
                                                        'englishsilentbookclub.paris',
                                                        'englishsilentbookclub.fr',
                                                        'clubdelecturesilencieuse.paris',
                                                        'clubdelecteuresilencieuse.fr',
                                                    );

    private const           ARR_LOCAL_SITES     =   array(
                                                        'localhost',
                                                        'silentbookclubparis.local',
                                                        'silentbookclubparisfr.local',
                                                        'englishsilentbookclubparis.local',
                                                        'englishsilentbookclubparisfr.local',
                                                        'clubdelecturesilencieuseparis.local',
                                                        'clubdelecturesilencieusefr.local',
                                                    );
    private const           ARR_SSL_DOMAINS =       array(
                                                        'silentbookclubparis.local',
                                                        'silentbookclubparisfr.local',
                                                        'englishsilentbookclubparis.local',
                                                        'englishsilentbookclubparisfr.local',
                                                        'clubdelecturesilencieuseparis.local',
                                                        'clubdelecturesilencieusefr.local',
                                                        'silentbookclub.paris',
                                                        'silentbookclubparis.fr',
                                                        'englishsilentbookclub.paris',
                                                        'englishsilentbookclub.fr',
                                                        'clubdelecturesilencieuse.paris',
                                                        'clubdelecteuresilencieuse.fr',
                                                    );
    
    //////////////////////////////////////////////////////////
    //
    // DATABASES
    //
    //////////////////////////////////////////////////////////
    
    private const               ARR_DB_LOCAL        =   array(
        'HOST'      =>  'localhost',
        'USER'      =>  'dbsys',
        'PASS'      =>  'XXX-PASS',
    );
    private const               ARR_DB_STAGE        =   array(
        'HOST'      =>  'XXX-IP-ADDRESS',
        'USER'      =>  'XXX-USER',
        'PASS'      =>  'XXX-PASS',
        'DBNAME'    =>  'XXX-DBNAME',
    );
    private const               ARR_DB_PROD         =   array(
        'HOST'      =>  'XXX-IP-ADDRESS',
        'USER'      =>  'XXX-USER',
        'PASS'      =>  'XXX-PASS',
        'DBNAME'    =>  'XXX-DBNAME',
    );
    
    private const               DB_LOCAL_DEV        =   'XXX-DBNAME';
    private const               DB_LOCAL_STAGE      =   'XXX-DBNAME';
    private const               DB_LOCAL_PROD       =   'XXX-DBNAME';
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  __construct()
    //  Version 1.0 (17/05/2023)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct()
    {
        // Set Absolute Path
        self::$strPath = $_SERVER['DOCUMENT_ROOT'];
        
        // Site root
        self::$strRoot = self::$strHttp . '://' . $_SERVER['HTTP_HOST'];
        
        // Check for secure
        if (isset($_SERVER['HTTPS'])) {
            if (!empty($_SERVER['HTTPS'] && $_SERVER['HTTPS'] !== 'off')) {
                self::$bSecure = true;
            }
        }
        
        // Get protocol (http or https)
        self::$strHttp = (self::isSecure() ? 'https' : 'http');
        
        // Set Server Name
        $this->setServerName();
        
        // Set site language
        $this->setLang();
        
        // Test for dev / stage / prod
        foreach (self::ARR_DEV_SITES as $strSite) {
            if ($strSite == self::$strServerName) {
                self::$bDev = true;
                break;
            }
        }
        foreach (self::ARR_STAGE_SITES as $strSite) {
            if ($strSite == self::$strServerName) {
                self::$bStage = true;
                break;
            }
        }
        foreach (self::ARR_PROD_SITES as $strSite) {
            if ($strSite == self::$strServerName) {
                self::$bProd = true;
                break;
            }
        }
        foreach (self::ARR_LOCAL_SITES as $strSite) {
            if ($strSite == self::$strServerName) {
                self::$bLocal = true;
                break;
            }
        }
        
        // Error reporting
        error_reporting(self::isProd() ? E_ERROR : E_ALL);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  clearAllCookies()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Clear all of the site cookies
    //
    //  @param          none
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function clearAllCookies() : void
    {
        foreach(self::ARR_COOKIES as $strCookie) {
            delCookie($strCookie);
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getDB()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Establish database connection according to server
    //
    //  @return         object
    //                  (connected PDO database object)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getDB() : object
    {
        if (self::isStage()) {
            $strHost        = self::ARR_DB_STAGE['HOST'];
            $strUser        = self::ARR_DB_STAGE['USER'];
            $strPass        = self::ARR_DB_STAGE['PASS'];
            $strDBName      = self::ARR_DB_STAGE['DBNAME'];
        }
        elseif (self::isLocal()) {
            $strHost        = self::ARR_DB_LOCAL['HOST'];
            $strUser        = self::ARR_DB_LOCAL['USER'];
            $strPass        = self::ARR_DB_LOCAL['PASS'];
            if (self::isProd()) {
                $strDBName = self::DB_LOCAL_PROD;
            }
            elseif (self::isStage()) {
                $strDBName = self::DB_LOCAL_STAGE;
            }
            else {
                $strDBName = self::DB_LOCAL_DEV;
            }
        }
        else {
            $strHost        = self::ARR_DB_PROD['HOST'];
            $strUser        = self::ARR_DB_PROD['USER'];
            $strPass        = self::ARR_DB_PROD['PASS'];
            $strDBName      = self::ARR_DB_PROD['DBNAME'];
        }
        
        // Create data source connection string
        $strConn = 'mysql:host=' . $strHost . ';dbname=' . $strDBName . ';charset=utf8';
        
        // DEBUG
        // 	echo($StrConn . '<br/>');
        
        // Connect to database
        try {
            $db = new PDO($strConn, $strUser, $strPass);
        }
        catch(Exception $error) {
            die('Connection failed: ' . $error->getMessage());
        }
        
        return($db);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getLang()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Site language from cookie or default
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getLang() : string
    {
        // Return the language from the cookie
        return($_COOKIE['lang'] ?? self::DEF_LANG);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getPath()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Site path
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getPath() : string
    {
        return(self::$strPath);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getServerName()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Site server name
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getServerName() : string
    {
        return(self::$strServerName);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getSiteRoot()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Site root directory
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getSiteRoot() : string
    {
        return(self::$strRoot);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getSiteTitle()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Site title
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getSiteTitle() : string
    {
        return(self::$strTitle);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getSiteSubTit()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Site subtitle
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getSiteSubTit() : string
    {
        return(self::$strSubTit);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getSSLDomains()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get the domain addresses with SSL certificates
    //
    //  @return         array
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getSSLDomains() : array
    {
        return(self::ARR_SSL_DOMAINS);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getVerNum()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get the Site version number
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getVerNum() : string
    {
        return(self::VER_NUM);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isDev()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Is development version?
    //
    //  @return         bool
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function isDev() : bool
    {
        return(self::$bDev);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isStage()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Is stage version?
    //
    //  @return         bool
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function isStage() : bool
    {
        return(self::$bStage);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isProd()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Is Production version?
    //
    //  @return         bool
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function isProd() : bool
    {
        return(self::$bProd);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isLocal()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Is local version?
    //
    //  @return         bool
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function isLocal() : bool
    {
        return(self::$bLocal);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isSecure()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Is running over https or not?
    //
    //  @return         bool
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function isSecure() : bool
    {
        return(self::$bSecure);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setLang()
    //  Version 1.1 (13/05/2024)
    //  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set Site language
    //
    //  @param          string  $strLang    Site language code
    //  @param          int     $iDurDays   Cookie duration in days
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function setLang(?string $strLang = null, int $iDurDays = null) : void
    {
        $iDurDays   =   $iDurDays   ??  self::DEF_COOKIE_DURATION;
        
        // lang already stored
        if (isCookie('lang'))
            // use new lang or currently stored lang
            $strLang ??= readCookie('lang');
        else
            // use new lang or default
            $strLang ??= self::DEF_LANG;
        
        addcookie('lang', $strLang, $iDurDays);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setServerName()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set Site server name from site's URL
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setServerName() : void
    {
        $strServer = strtolower($_SERVER['SERVER_NAME']);
        $strServer = (strStartsWith($strServer, 'www.') ? strRemoveLeft($strServer, 4) : $strServer);
        
        self::$strServerName = $strServer;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setSubTit()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set Site subtitle
    //
    //  @param          string  $strSubTit  Site subtitle
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setSubTit(string $strSubTit) : void
    {
        self::$strSubTit = $strSubTit;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTitle()
    //  Version 1.1 (03/03/2024)
    //  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set Site title
    //
    //  @param          string  $strTitle   Site Title
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTitle(string $strTitle) : void
    {
        self::$strTitle = $strTitle;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  showAllCookies()
    //  Version 1.0 (19/05/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Show all of the Site cookies
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function showAllCookies() : void
    {
        foreach(self::ARR_COOKIES as $strCookie) {
            showCookie($strCookie);
        }
    }
}

