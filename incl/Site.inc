<?php

// Load environment variables
if (!getenv('SITE_VER_NUM')) {
    $DotEnv = new DotEnv('site.env');
    $DotEnv->load();
}

//  TODO Check for variables and constants now in Intl class ...

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Site
//  @version    43.2 (09/03/2025)
//  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

class Site
{
    public readonly string      $strCopyright;
    public readonly string      $strCopyrightSite;
    public readonly string      $strCSSDir;
    public readonly string      $strCSSExpDir;
    public readonly string      $strCSSImpDir;
    public readonly int         $iDefCookieDuration;
    public readonly string      $strDefLang;
    public readonly int         $iDefUserID;
    public readonly string      $strFileBase;
    public readonly string      $strFontsDir;
    public readonly string      $strHttp;
    public readonly string      $strImagesDir;
    // dbTable uses the ImpExp tables
    public readonly bool        $bImpExp;
    public readonly string      $strJSDir;
    // Live site published for SE indexing
    public readonly bool        $bPublished;
    public readonly bool        $bSecure;
    public readonly string      $strServerName;
    public readonly string      $strVerNum;
    
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  __construct()
    //  Version 1.1 (06/03/2025)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct()
    {
        $this->setReadOnlyVariables();
        
        // Set site language
        $this->setLang($this->getSiteLang());
        
        $this->getSiteState();
        
        // Error reporting
        error_reporting(self::isProd() ? E_ERROR : E_ALL);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  clearAllCookies()
    //  Version 1.1 (06/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Clear all of the site cookies
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function clearAllCookies() : void
    {
        $DotEnvCookies = new DotEnv('cookies.list');
        $arrCookies = $DotEnvCookies->getList();
        foreach($arrCookies as $strCookie) {
            delCookie($strCookie);
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getDB()
    //  Version 2.0 (06/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
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
            $strList = 'db_stage.list';
        }
        elseif (self::isLocal()) {
            $strList = 'db_local.list';
        }
        else {
            $strList = 'db_prod.list';
        }
        
        $DotEnvDB = new DotEnv($strList);
        $arrDB = $DotEnvDB->getArray();
        $strDBName = 'DBNAME';
        if (self::isLocal()) {
            if (self::isDev())
                $strDBName = 'DBNAME_DEV';
            elseif (self::isStage())
                $strDBName = 'DBNAME_STAGE';
            else
                $strDBName = 'DBNAME_PROD';
        }
        
        // Create data source connection string
        $strConn = 'mysql:host=' . $arrDB['HOST'] . ';dbname=' . $arrDB[$strDBName] . ';charset=utf8';
        
        // DEBUG
        // 	echo($StrConn . '<br/>');
        
        // Connect to database
        try {
            $db = new PDO($strConn, $arrDB['USER'], $arrDB['PASS']);
        }
        catch(Exception $error) {
            die('Connection failed: ' . $error->getMessage());
        }
        
        return($db);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getLang()
    //  Version 1.3 (07/03/2025)
    //  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Site language from URL, cookie or default
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function getLang() : string
    {
        // Return the language from the URL
        if (isset($_GET['lang']))
            return(strtolower($_GET['lang']));
        
        // Return the language from the cookie
        return($_COOKIE['lang'] ?? getenv('SITE_DEF_LANG'));
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getSiteLang()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get language from language sites list of server names
    //  sites_lang_xx.list
    //
    //  @return         string      2-letter language code
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getSiteLang() : ?string
    {
        // Find each file sites_lang_xx.list
        foreach(glob(getenv('SITE_PATH') . '/env/' . 'sites_lang_*.list') as $strFileName) {
            $DotEnvList = new DotEnv(getFileName($strFileName));
            $arrList = $DotEnvList->getList();
            foreach($arrList as $strServer) {
                // Find server name in list file
                if ($strServer === $this->strServerName) {
                    // Lang code = 2 letters after sites_lang_ in filename
                    return(strMid(getFileName($strFileName), 11, 2));
                }
            }
        }
        
        return null;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getSiteState()
    //  Version 1.0 (06/03/2025)
    //  @copyright  2025 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the local / dev / stage / prod site states
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getSiteState() : void
    {
        // Test for local / dev / stage / prod
        $DotEnvLocal = new DotEnv('sites_local.list');
        $arrLocalSites = $DotEnvLocal->getList();
        foreach($arrLocalSites as $strSite) {
            if ($strSite == $this->strServerName) {
                putenv('SITE_LOCAL=1');
                break;
            }
        }
        
        $DotEnvDev = new DotEnv('sites_dev.list');
        $arrDevSites = $DotEnvDev->getList();
        foreach($arrDevSites as $strSite) {
            if ($strSite == $this->strServerName) {
                putenv('SITE_STATE=DEV');
                break;
            }
        }
        
        $DotEnvStage = new DotEnv('sites_stage.list');
        $arrStageSites = $DotEnvStage->getList();
        foreach($arrStageSites as $strSite) {
            if ($strSite == $this->strServerName) {
                putenv('SITE_STATE=STAGE');
                break;
            }
        }
        
        $DotEnvProd = new DotEnv('sites_prod.list');
        $arrProdSites = $DotEnvProd->getList();
        foreach($arrProdSites as $strSite) {
            if ($strSite == $this->strServerName) {
                putenv('SITE_STATE=PROD');
                break;
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isDev()
    //  Version 1.1 (06/03/2025)
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
        return(getenv('SITE_STATE') == 'DEV');
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isLocal()
    //  Version 1.1 (06/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Is local version?
    //
    //  @return         bool
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function isLocal() : bool
    {
        return(getenv('SITE_LOCAL') == '1');
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isProd()
    //  Version 1.1 (06/03/2025)
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
        return(getenv('SITE_STATE') == 'PROD');
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  isStage()
    //  Version 1.1 (06/03/2025)
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
        return(getenv('SITE_STATE') == 'STAGE');
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setLang()
    //  Version 1.2 (06/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
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
        $iDurDays   =   $iDurDays   ??  intval(getenv('SITE_DEF_COOKIE_DURATION'));
        
        // lang already stored
        if (isCookie('lang'))
            // use new lang or currently stored lang
            $strLang ??= readCookie('lang');
        else
            // use new lang or default
            $strLang ??= getenv('SITE_DEF_LANG');
        
        // Set environment variables per language
        $DotEnvLang = new DotEnv('site_' . $strLang . '.env');
        $DotEnvLang->load();
        
        addcookie('lang', $strLang, $iDurDays);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setReadOnlyVariables()
    //  Version 1.0 (05/03/2025)
    //  @copyright  2025 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set Site readonly variables
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setReadOnlyVariables() : void
    {
        $DotEnv = new DotEnv('site.env');
        
        // Set readonly variables
        $this->strCopyright         =   getenv('SITE_COPYRIGHT') ?? '';
        $this->strCopyrightSite     =   getenv('SITE_COPYRIGHTSITE') ?? '';
        $this->strCSSDir            =   getenv('SITE_CSS_DIR') ?? '/css/';
        $this->strCSSExpDir         =   getenv('SITE_CSS_EXP_DIR') ?? '/impexp/';
        $this->strCSSImpDir         =   getenv('SITE_CSS_IMP_DIR') ?? '/impexp/';
        $this->iDefCookieDuration   =   isBlank(getenv('SITE_DEF_COOKIE_DURATION')) ? 8 : intval(getenv('SITE_DEF_COOKIE_DURATION'));
        $this->strDefLang           =   getenv('SITE_DEF_LANG') ?? 'en';
        $this->iDefUserID           =   isBlank(getenv('SITE_USER_ID')) ? 1 : getenv('SITE_USER_ID');
        $this->strFileBase          =   getenv('SITE_FILE_BASE') ?? '';
        $this->strFontsDir          =   getenv('SITE_FONTS_DIR') ?? '/fonts/';
        $this->strImagesDir         =   getenv('SITE_IMAGES_DIR') ?? '/imgs/';
        $this->bImpExp              =   isBlank(getenv('SITE_IMPEXP')) ? false : boolval(getenv('SITE_IMPEXP'));
        $this->strJSDir             =   getenv('SITE_JS_DIR') ?? '/js/';
        $this->bPublished           =   isBlank(getenv('SITE_PUBLISHED')) ? false : boolval(getenv('SITE_PUBLISHED'));
        $this->strVerNum            =   getenv('SITE_VER_NUM') ?? '0.00';
        
        // Set server name
        $strServer                  =   strtolower($_SERVER['SERVER_NAME']);
        $strServer                  =   (strStartsWith($strServer, 'www.') ? strRemoveLeft($strServer, 4) : $strServer);
        $this->strServerName        =   $strServer;
        $DotEnv->addEnv('SITE_SERVER_NAME', $strServer);
        
        // Check for secure
        $bSecure = false;
        if (isset($_SERVER['HTTPS'])) {
            if (!empty($_SERVER['HTTPS'] && $_SERVER['HTTPS'] !== 'off')) {
                $bSecure = true;
            }
        }
        $this->bSecure = $bSecure;
        
        // Get protocol (http or https)
        $this->strHttp = ($this->bSecure ? 'https' : 'http');
        
        // Set path
        $DotEnv->addEnv('SITE_PATH', $_SERVER['DOCUMENT_ROOT']);
        $DotEnv->addEnv('SITE_ROOT', $this->strHttp . '://' . $_SERVER['HTTP_HOST']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  showAllCookies()
    //  Version 1.1 (06/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Show all of the Site cookies
    //
    //  @return         void
    //
    //////////////////////////////////////////////////////////////////////////////
    
    public static function showAllCookies() : void
    {
        $DotEnvCookies = new DotEnv('cookies.list');
        $arrCookies = $DotEnvCookies->getList();
        foreach($arrCookies as $strCookie) {
            showCookie($strCookie);
        }
    }
}

