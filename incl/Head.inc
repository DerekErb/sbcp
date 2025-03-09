<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Head
//  @version    3.0c (09/03/2025)
//  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////
class Head extends Site
{
    // Article Info
    protected ?string   $strArtAuthor                   =   null;
    protected ?string   $strArtExpTime                  =   null;
    protected ?string   $strArtModTime                  =   null;
    protected ?string   $strArtPubTime                  =   null;
    protected ?string   $strArtSection                  =   null;
    protected ?string   $strArtTags                     =   null;
    
    protected ?array    $arrCSSFiles                    =   null;
    protected ?array    $arrExtJSLinks                  =   null;
    protected ?string   $strFileName                    =   null;
    protected ?array    $arrJScriptFiles                =   null;
    
    
    // Page info
    protected ?string   $strPgAbstract =   null;
    protected ?string   $strPgAuthors                   =   null;
    protected ?string   $strPgCopyright                 =   null;
    protected ?string   $strPgDescription               =   null;
    protected ?string   $strPgDesigner                  =   null;
    protected ?string   $strPgGenerator                 =   null;
    protected ?string   $strPgKeywords                  =   null;
    protected ?string   $strPgLangCodes                 =   null;
    protected ?string   $strPgOwner                     =   null;
    protected ?string   $strPgRating   =   null;
    protected ?string   $strPgTitle    =   null;
    
    protected bool      $bPublic                        =   true;
    
    // Site info
    protected string    $strSiteAbstract;
    protected string    $strSiteAuthors;
    protected string    $strSiteContentSecurityPolicy;
    protected string    $strSiteDescription;
    protected array     $arrSiteFavicons;
    protected string    $strSiteGenerator;
    protected string    $strSiteGoogleTag;
    protected string    $strSiteKeywords;
    protected string    $strSiteDesigner;
    protected string    $strSiteNormaliseCSS;
    protected string    $strSiteOGDescription;
    protected string    $strSiteOGImage;
    protected string    $strSiteOGImageAlt;
    protected int       $iSiteOGImageHeight;
    protected string    $strSiteOGImageType;
    protected int       $iSiteOGImageWidth;
    protected string    $strSiteOGLocale;
    protected string    $strSiteOGTitle;
    protected string    $strSiteOGType;
    protected string    $strSiteOGURL;
    protected bool      $bSiteOpenGraph;
    
    protected string    $strSiteOwner;
    protected array     $arrSitePreloadFonts;
    
    protected bool      $bSitePWA;
    protected string    $strSitePWAAppName;
    protected string    $strSitePWAManifest;
    protected string    $strSiteRating;
    protected int       $iSiteSERevisit;
    protected string    $strSiteThemeColor;
    
    protected bool      $bTwitter;
    protected string    $strTwitterCard;
    protected string    $strTwitterCreator;
    protected string    $strTwitterDescription;
    protected string    $strTwitterImage;
    protected string    $strTwitterImageAlt;
    protected string    $strTwitterImageType;
    protected string    $strTwitterSiteID;
    protected string    $strTwitterTitle;
    protected string    $strTwitterURL;
    
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // CONSTRUCTOR()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct($strPgTitle = null)
    {
        // Only Prod  pages are public
        if (!Site::isProd())
            $this->bPublic = false;
        
        // Get base file name without path or extension
        $this->strFileName = rmvFileExt(basename($_SERVER['PHP_SELF']));
        
        // Set individual page title
        if (!is_null($strPgTitle))
            $this->strPgTitle = $strPgTitle;
        
        $this->initSiteVariables();
        
        parent::__construct();
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  activateOpenGraph()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Turn on/off the OpenGraph variable
    //
    //  @param          bool    $bOG        Open Graph on/off
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function activateOpenGraph(bool $bOG = true) : void
    {
        $this->bSiteOpenGraph= $bOG;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  activatePWA()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Turn on/off the PWA variable
    //
    //  @param          bool    $bOG        PWA on/off
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function activatePWA(bool $bPWA = true) : void
    {
        $this->bSitePWA= $bPWA;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  activateTwitter()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Turn on/off the Twitter variable
    //
    //  @param          bool    $bOG        Twitter on/off
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function activateTwitter(bool $bTwit = true) : void
    {
        $this->bTwitter = $bTwit;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  forceSecure()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    // Test for, and redirect to, secure version of site if SSL domains
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function forceSecure() : void
    {
        if (Site::isProd()) {
            $DotEnvSSL = new DotEnv('ssl_domains.list');
            $arrSSLDomains = $DotEnvSSL->getList();
            foreach ($arrSSLDomains as $strSSLDomain) {
                if (getenv('SITE_SERVER_NAME') == $strSSLDomain) {
                    header('Location: https://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI']);
                    break;
                }
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getAbstract()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getAbstract() : string
    {
        return($this->strPgAbstract ?? $this->strSiteAbstract);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getAuthors()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getAuthors() : string
    {
        return ($this->strPgAuthors ?? $this->strSiteAuthors);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getCopy()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getCopy() : string
    {
        return ($this->strPgCopyright ?? $this->strCopyright);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getDescription()
    //  Version 1.0a (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getDescription() : string
    {
        return($this->strPgDescription ?? $this->strSiteDescription);
        
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getDesigner()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getDesigner() : string
    {
        return($this->strPgDesigner ?? $this->strSiteDesigner);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getGenerator()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getGenerator() : string
    {
        return($this->strPgGenerator ?? $this->strSiteGenerator);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getKeywords()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getKeywords() : string
    {
        return($this->strPgKeywords ?? $this->strSiteKeywords);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getLangCodes()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getLangCodes() : string
    {
        return($this->strPgLangCodes ?? $this->getLang());
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getOGDescription()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOGDescription() : string
    {
        return($this->strSiteOGDescription);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getOGLocale()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOGLocale() : string
    {
        return($this->strOgLocale ?? $this->strSiteOGLocale);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getOGTitle()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOGTitle() : string
    {
        return($this->strOgTitle ?? getenv('SITE_TITLE'));
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getOGType()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOGType() : string
    {
        return($this->strOgType ?? $this->strSiteOGType);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getOGURL()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOGURL() : string
    {
        return($this->strSiteOGURL ?? getenv('SITE_ROOT') . $_SERVER['REQUEST_URI']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getOwner()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOwner() : string
    {
        return($this->strPgOwner ?? $this->strSiteOwner);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getPgTitle()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getPgTitle() : string
    {
        return(getenv('SITE_TITLE') .
            (is_null($this->strPgTitle) ? '' : ' - ' . $this->strPgTitle));
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getRating()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getRating() : string
    {
        return($this->strPgRating ?? $this->strSiteRating);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getTwitterCard()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterCard() : string
    {
        return($this->strTwitterCard);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getTwitterCreator()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterCreator() : string
    {
        return($this->strTwitterCreator);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getTwitterDescription()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterDescription() : string
    {
        return($this->strTwitterDescription);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getTwitterSiteID()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterSiteID() : string
    {
        return($this->strTwitterSiteID);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getTwitterTitle()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterTitle() : string
    {
        return($this->strTwitterTitle);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  getTwitterURL()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @return         string
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterURL() : string
    {
        return($this->strTwitterURL);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  initSiteVariables()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Initialise the site variables
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function initSiteVariables() : void
    {
        $this->strSiteNormaliseCSS          =   getenv('SITE_NORMALISE_CSS') ?? '';
        $this->strSiteAuthors               =   getenv('SITE_AUTHORS') ?? '';
        $this->strSiteContentSecurityPolicy =   getenv('SITE_CONTENT_SECURITY_POLICY') ?? '';
        $this->strSiteDescription           =   getenv('SITE_DESCRIPTION') ?? '';
        $this->strSiteGenerator             =   getenv('SITE_GENERATOR') ?? '';
        $this->strSiteGoogleTag             =   getenv('SITE_GOOGLE_TAG') ?? '';
        $this->strSiteKeywords              =   getenv('SITE_KEYWORDS ') ?? '';
        $this->strSiteDesigner              =   getenv('SITE_DESIGNER') ?? '';
        
        $this->bSiteOpenGraph               =   isblank(getenv('SITE_OG')) ? false : boolval(getenv('SITE_OG'));
        $this->strSiteOGDescription         =   getenv('SITE_OG_DESCRIPTION') ?? '';
        $this->strSiteOGImage               =   getenv('SITE_OG_IMAGE') ?? '';
        $this->strSiteOGImageAlt            =   getenv('SITE_OG_IMAGE_ALT') ?? '';
        $this->iSiteOGImageHeight           =   isblank(getenv('SITE_OG_IMAGE_HEIGHT')) ? 0 : intval(getenv('SITE_OG_IMAGE_HEIGHT'));
        $this->strSiteOGImageType           =   getenv('SITE_OG_IMAGE_TYPE') ?: '';
        $this->iSiteOGImageWidth            =   isblank(getenv('SITE_OG_IMAGE_WIDTH')) ? 0 : intval(getenv('SITE_OG_IMAGE_WIDTH'));
        $this->strSiteOGLocale              =   getenv('SITE_OG_LOCALE') ?? '';
        $this->strSiteOGTitle               =   getenv('SITE_OG_TITLE') ?? '';
        $this->strSiteOGType                =   getenv('SITE_OG_TYPE') ?? '';
        $this->strSiteOGURL                 =   getenv('SITE_OG_URL') ?? '';
        
        $this->strSiteAbstract              =   getenv('SITE_SITE_ABSTRACT') ?? '';
        $this->strSiteOwner                 =   getenv('SITE_OWNER') ?? '';
        
        $this->bSitePWA                     =   isblank(getenv('SITE_PWA')) ? false : boolval(getenv('SITE_PWA'));
        $this->strSitePWAAppName            =   getenv('SITE_PWA_APP_NAME') ?? '';
        $this->strSitePWAManifest           =   getenv('SITE_PWA_MANIFEST') ?? '';
        
        $this->strSiteRating                =   getenv('SITE_RATING') ?? '';
        
        $this->iSiteSERevisit               =   isblank(getenv('SITE_SE_REVISIT')) ? 1 : intval(getenv('SITE_SE_REVISIT'));
        $this->strSiteThemeColor            =   getenv('SITE_THEME_COLOR') ?? '';
        
        $this->bTwitter                     =   isblank(getenv('SITE_TWITTER')) ? false : boolval(getenv('SITE_TWITTER'));
        $this->strTwitterCard               =   getenv('SITE_TWITTER_CARD') ?? '';
        $this->strTwitterCreator            =   getenv('SITE_TWITTER_CREATOR') ?? '';
        $this->strTwitterDescription        =   getenv('SITE_TWITTER_DESCRIPTION') ?? '';
        $this->strTwitterImage              =   getenv('SITE_TWITTER_IMAGE') ?? '';
        $this->strTwitterImageAlt           =   getenv('SITE_TWITTER_IMAGE_ALT') ?? '';
        $this->strTwitterImageType          =   getenv('SITE_TWITTER_IMAGE_TYPE') ?? '';
        $this->strTwitterSiteID             =   getenv('SITE_TWITTER_SITE_ID') ?? '';
        $this->strTwitterTitle              =   getenv('SITE_TWITTER_TITLE') ?? '';
        $this->strTwitterURL                =   getenv('SITE_TWITTER_URL') ?? '';
        
        // Load lists
        $DotEnvFavicons = new DotEnv('site_favicons.list');
        $this->arrSiteFavicons = $DotEnvFavicons->getArray();
        
        $DotEnvPreloadFonts = new DotEnv('site_preload_fonts.list');
        $this->arrSitePreloadFonts = $DotEnvPreloadFonts->getArray();
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setAbstract()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @param      string      $strAbs     SEO Abstract
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setAbstract(string $strAbs) : void
    {
        $this->strPgAbstract = $strAbs;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setArtAuthor()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article author
    //
    //  @param      string      $strArtAuthor   Article author
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtAuthor(string $strArtAuthor) : void
    {
        $this->strArtAuthor = $strArtAuthor;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setArtExpTime
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article expiration date / time
    //
    //  @param      string      $strArtExpTime  Article expiration datetime
    //                                          YYYY-MM-DD HH:MM:SS+HH:MM
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtExpTime(string $strArtExpTime) : void
    {
        $this->strArtExpTime = $strArtExpTime;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setArtModTime()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article modification date / time
    //
    //  @param      string      $strArtModTime  Article modification datetime
    //                                          YYYY-MM-DD HH:MM:SS+HH:MM
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtModTime(string $strArtModTime) : void
    {
        $this->strArtModTime = $strArtModTime;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setArtPubTime()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article publication date / time
    //
    //  @param      string      $strArtPubTime  Article publication datetime
    //                                          YYYY-MM-DD HH:MM:SS+HH:MM
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtPubTime(string $strArtPubTime) : void
    {
        $this->strArtPubTime = $strArtPubTime;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setArtSection()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article section categories (comma-separated)
    //
    //  @param      string      $strArSection  Article section categories
    //                                         (comma-separated list)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtSection(string $strArtSect) : void
    {
        $this->strArtSection = $strArtSect;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setArtTags()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article keyword tags (comma-separated)
    //
    //  @param      string      $strArtTags Article keyword tags
    //                                      (comma-separated list)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtTags(string $strArtTags) : void
    {
        $this->strArtTags = $strArtTags;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setAuthors()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article authors
    //
    //  @param      string      $strAuthors     Page authors
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setAuthors(string $strAuthors) : void
    {
        $this->strPgAuthors = $strAuthors;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setCopyright()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set page / site copyright
    //
    //  @param      string      $strCopyright   Copyright
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setCopyright(string $strCopy) : void
    {
        $this->strPgCopyright = $strCopy;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setCSSFiles()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set additional CSS files to be loaded
    //
    //  @param      string      $strCSSFiles    List of CSS files
    //                                          (comma-separated list)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setCSSFiles(string $strCSSFiles) : void
    {
        $this->arrCSSFiles = explode(',', $strCSSFiles);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setDescription()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set page / site description
    //
    //  @param      string      $strDescription     Description
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setDescription(string $strDesc) : void
    {
        $this->strPgDescription = $strDesc;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setDesigner()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set page / site designer
    //
    //  @param      string      $strDesigner        Designer
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setDesigner(string $strDesigner) : void
    {
        $this->strPgDesigner = $strDesigner;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setExtJSFiles()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set additional JS files to be loaded
    //
    //  @param      string      $strExtJSLinks  List of JavaScript files
    //                                          (comma-separated list)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setExtJSFiles(string $strExtJSLinks) : void
    {
        $this->arrExtJSLinks = explode(',', $strExtJSLinks);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setGenerator()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set page / site generator
    //
    //  @param      string      $strGenerator       Generator
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setGenerator(string $strGenerator) : void
    {
        $this->strPgGenerator = $strGenerator;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setJSFiles()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set additional JS files to be loaded
    //
    //  @param      string      $strJScriptFiles    List of JavaScript files
    //                                              (comma-separated list)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setJSFiles(string $strJSFiles) : void
    {
        $this->arrJScriptFiles = explode(',', $strJSFiles);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setKeywords()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set article keyword tags (comma-separated)
    //
    //  @param      string      $strKeys    Keywords
    //                                      (comma-separated list)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setKeywords(string $strKeys) : void
    {
        $this->strPgKeywords = $strKeys;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setLanguageCodes()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the language info for the page
    //
    //  @param      string      $strLangCodes   Language codes
    //  https://developer.mozilla.org/en-US/docs/Web/HTML/Global_attributes/lang
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setLanguageCodes(string $strLangCodes) : void
    {
        $this->strPgLangCodes = $strLangCodes;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setNormaliseCSS()
    //  Version 1.0 (08/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the normalise CSS file
    //
    //  @param      string      $strNormaliseCSS    Normalise CSS file name
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setNormaliseCSS(string $strNormaliseCSS) : void
    {
        $this->strSiteNormaliseCSS = $strNormaliseCSS;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOGDescription()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Open Graph description
    //
    //  @param      string      $strOGDesc  Open Graph description
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOGDescription(string $strOGDesc) : void
    {
        $this->activateOpenGraph();
        $this->strSiteOGDescription = $strOGDesc;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOGImage()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Open Graph image attributes
    //
    //  @param      string      $strImage       Image file name
    //  @param      string      $strType        Image file type
    //  @param      string      $strImageAlt    Image alt information
    //  @param      bool        $bRel           File path is relative or not
    //  @param      int         $iWidth         Image width in pixels
    //  @param      int         $iHeight        Image height in pixels
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOGImage(string $strImage, string $strType, ?string $strImageAlt = null, bool $bRel = true, ?int $iWidth = null, ?int $iHeight = null) : void
    {
        $this->activateOpenGraph();
        $this->strSiteOGImage       = ($bRel ? getenv('SITE_ROOT') : '') . $strImage;
        $this->strSiteOGImageAlt    = $strImageAlt;
        $this->iSiteOGImageHeight   = $iHeight;
        $this->strSiteOGImageType   = 'image/' . $strType;
        $this->iSiteOGImageWidth    = $iWidth;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOGLocale()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Open Graph locale
    //
    //  @param      string      $strOGLocale    Open Graph locale
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOGLocale(string $strOGLocale) : void
    {
        $this->activateOpenGraph();
        $this->strSiteOGLocale = $strOGLocale;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOGTitle()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Open Graph title
    //
    //  @param      string      $strOGTitle     Open Graph title
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOGTitle(string $strOGTitle) : void
    {
        $this->activateOpenGraph();
        $this->strSiteOGTitle = $strOGTitle;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOGType()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Open Graph type
    //
    //  @param      string      $strOGType      Open Graph type
    //                                          website, article, blog
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOGType(string $strOGType) : void
    {
        $this->activateOpenGraph();
        $this->strSiteOGType = $strOGType;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOGURL()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Open Graph URL
    //
    //  @param      string      $strOGURL   Open Graph URL
    //  @param      bool        $bRel       URL relative to current site or not
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOGURL(string $strOGURL, $bRel = true) : void
    {
        $this->activateOpenGraph();
        $this->strSiteOGURL = ($bRel ? getenv('SITE_ROOT') : '') . $strOGURL;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOwner()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the owner for SEO
    //
    //  @param      string      $strOwner       Owner
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOwner(string $strOwner) : void
    {
        $this->strPgOwner = $strOwner;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setPWA()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Personal Web App (PWA) attributes
    //
    //  @param      string      $strPWAManifest     PWA manifest
    //  @param      string      $strPWAName         PWA name
    //
    //////////////////////////////////////////////////////////////////////////////
    
    
    function setPWA(string $strPWAManifest, string $strPWAName) : void
    {
        $this->activatePWA();
        $this->setPWAManifest($strPWAManifest);
        $this->setPWAAppName($strPWAName);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setPWAAppName()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the PWA application name
    //
    //  @param      string      $strAppName     PWA application name
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setPWAAppName(string $strAppName) : void
    {
        $this->activatePWA();
        $this->strSitePWAAppName = $strAppName;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setPWAManifest()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the PWA Manifest
    //  Relative path and file name of the PWA manifest file
    //
    //  @param      string      $strManifestFile    Manifest file name
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setPWAManifest(string $strManifestFile) : void
    {
        $this->activatePWA();
        $this->strSitePWAManifest = $strManifestFile;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setRating()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the SEO rating for the page
    //
    //  @param      string      $strPgRating    Page rating:
    //                                          general
    //                                          mature
    //                                          restricted
    //                                          adult
    //                                          14 years
    //                                          safe for kids
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setRating(string $strPgRating) : void
    {
        $this->strPgRating = $strPgRating;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTitle()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the page title
    //
    //  @param      string      $strTitle       Page title
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTitle(string $strTitle) : void
    {
        $this->strPgTitle = $strTitle;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitter()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Twitter attributes
    //
    //  @param      string      $strTwitterDesc     Description
    //  @param      string      $strTwitterCreator  Creator
    //  @param      string      $strTwitterCard     Card
    //
    //  Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitter(string $strTwitterDesc, ?string $strTwitterCreator = null, ?string $strTwitterCard = null) : void
    {
        $this->activateTwitter();
        $this->strTwitterDescription    = $strTwitterDesc;
        $this->strTwitterCreator        = $strTwitterCreator ?? $this->strTwitterCreator;
        $this->strTwitterCard           = $strTwitterCard ?? $this->strTwitterCard;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterCard()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Twitter card info
    //
    //  @param      string      $strTwitterCard     Card info
    //                                              summary
    //                                              summary_large_image
    //
    //  Full URL (i.e. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterCard(string $strTwitterCard) : void
    {
        $this->activateTwitter();
        $this->strTwitterCard = $strTwitterCard;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterCreator()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Twitter creator
    //
    //  @param      string      $strTwitterCreator  Creator
    //                                              @TwitterID
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterCreator(string $strTwitterCreator) : void
    {
        $this->activateTwitter();
        $this->strTwitterCreator = $strTwitterCreator;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterDescription()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Twitter description
    //
    //  @param      string      $strTwitterDescription  Description
    //
    //  Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterDescription(string $strTwitterDescription) : void
    {
        $this->activateTwitter();
        $this->strTwitterDescription = $strTwitterDescription;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterImage()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  @param      string      $strImage       Image file name
    //  @param      string      $strType        Image file type
    //                                          GIF, JPEG, PNG, WEBP
    //  @param      bool        $bRel           Image URL is relative to current site or not
    //
    //  Summary card image
    //          Relative URL
    //          Square 1:1 ratio min 144 x 144 px max 4096 x 4096 px
    //          Max 5 MB
    //
    //  Summary Large Image
    //          Relative URL
    //          Rectangle 2:1 ratio min 300 x 157 px max 4096 x 4096 px
    //          Max 5 MB
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterImage(string $strImage, string $strType, ?string $strImageAlt = null, bool $bRel = true) : void
    {
        $this->activateTwitter();
        $this->strTwitterImage       = ($bRel ? getenv('SITE_ROOT') : '') . $strImage;
        $this->strTwitterImageAlt    = $strImageAlt;
        $this->strTwitterImageType   = 'image/' . $strType;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterSiteID()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Twitter site owner/creator / reference
    //
    //  @param      string      $strTwitterSiteID   @TwitterID
    //
    //  Full URL (i.e. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterSiteID(string $strTwitterSiteID) : void
    {
        $this->activateTwitter();
        $this->strTwitterSiteID = $strTwitterSiteID;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterTitle()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Twitter title
    //
    //  @param      string      $strTwitterTitle    Twitter title
    //
    //  Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-webTitles/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterTitle(string $strTwitterTitle) : void
    {
        $this->activateTwitter();
        $this->strTwitterTitle = $strTwitterTitle;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterURL()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Set the Twitter URL
    //
    //  @param      string      $strTwitterURL      Twitter URL
    //  @param      bool        $bRel               URL is relative to current site or not
    //
    //  Full URL (i.e. https://developer.twitter.com/en/docs/twitter-for-webURLs/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterURL(string $strTwitterURL, $bRel = true) : void
    {
        $this->activateTwitter();
        $this->strTwitterURL = ($bRel ? getenv('SITE_ROOT') : '') . $strTwitterURL;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  write()
    //  Version 1.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Output page head
    //
    //  @param      bool        $bPublic            Page is published to public or not
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function write(?bool $bPublic = null) : void
    {
        // Set private / public page
        $bPublic = $bPublic ?? $this->bPublic;
        
        // Force Secure Site
        $this->forceSecure();
        
        echo('<!DOCTYPE HTML>' . PHP_EOL);
        echo('<html lang="' . $this->getLangCodes() . '">' . PHP_EOP);
        
        echo('<head>' . PHP_EOP);
        
        echo(t(1) . '<meta charset="UTF-8">' . PHP_EOL);
        echo(t(1) . '<meta name="title" content="' . getenv('SITE_TITLE') . '">' . PHP_EOL);
        echo(t(1) . '<meta name="theme-color" content="' . $this->strSiteThemeColor . '">' . PHP_EOP);
        
        //////////////////////////////////////////////////////////////////////////////
        //  Content Security Policy
        //////////////////////////////////////////////////////////////////////////////
        if (!isBlank($this->strSiteContentSecurityPolicy)) {
            echo(t(1) . '<!-- Content Security Policy -->' . PHP_EOL);
            echo(t(1) . '<meta http-equiv="Content-Security-Policy" content="' . $this->strSiteContentSecurityPolicy . '">' . PHP_EOP);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  PWA
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->bSitePWA) {
            echo(t(1) . '<!-- PWA Settings -->' . PHP_EOL);
            if (!isBlank($this->strSitePWAManifest)) {
                echo(t(1) . '<link rel="manifest" href="' . $this->strSitePWAManifest . '">' . PHP_EOL);
            }
            
            if (!isBlank($this->strSitePWAAppName)) {
                echo(t(1) . '<meta name="application-name" content="' . $this->strSitePWAAppName . '">' . PHP_EOP);
            }
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  MOBILE FRIENDLY
        //////////////////////////////////////////////////////////////////////////////
        
        echo(t(1) . '<!-- Mobile Friendly -->' . PHP_EOL);
        echo(t(1) . '<meta name="Viewport" content="width=device-width, initial-scale=1.0">' . PHP_EOL);
        echo(t(1) . '<meta name="HandheldFriendly" content="true">' . PHP_EOL);
        echo(t(1) . '<meta name="MobileOptimized" content="320">' . PHP_EOP);
        
        //////////////////////////////////////////////////////////////////////////////
        //  META NAMES
        //////////////////////////////////////////////////////////////////////////////
        
        if ($bPublic) {
            echo(t(1) . '<!-- Site / Page info -->' . PHP_EOL);
            echo(t(1) . '<meta name="abstract" content="' .
                $this->getAbstract() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="copyright" content="Copyright @ ' .
                $this->getCopy() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="description" content="' .
                $this->getDescription() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="author" content="' .
                $this->getAuthors() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="designer" content="' .
                $this->getDesigner() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="generator" content="' .
                $this->getGenerator() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="keywords" content="' .
                $this->getKeywords() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="owner" content="' .
                $this->getOwner() . '">' . PHP_EOP);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  SEO
        //////////////////////////////////////////////////////////////////////////////
        
        if ($bPublic) {
            echo(t(1) . '<meta name="rating" content="' .
                $this->getRating() . '">' . PHP_EOL);
            echo(t(1) . '<meta name="resource-type" content="document">' . PHP_EOL);
            echo(t(1) . '<meta name="distribution" content="global">' . PHP_EOL);
            if (($this->bPublished) && Site::isProd())
                echo(t(1) . '<meta name="robots" content="all, index, follow">' . PHP_EOL);
        }
        else {
            echo(t(1) . '<meta name="robots" content="none">' . PHP_EOL);
            echo(t(1) . '<meta name="googlebot" content="none">' . PHP_EOL);
            echo(t(1) . '<meta name="Ads-bot-Google" content="noindex">' . PHP_EOL);
        }
        echo(PHP_EOL);
        
        //////////////////////////////////////////////////////////////////////////////
        //  OPEN GRAPH / FACEBOOK
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->bSiteOpenGraph && $bPublic) {
            echo(t(1) . '<!-- Open Graph / Facebook -->' . PHP_EOL);
            if (isBlank($this->strSiteOGImage)) {
                $strOGImage     = $this->strSiteOGImage;
                $strOGImageAlt  = $this->strSiteOGImageAlt;
                $iOGImageH      = $this->iSiteOGImageHeight;
                $iOGImageW      = $this->iSiteOGImageWidth;
                $strOGImageType = $this->strSiteOGImageType;
            }
            else {
                $strOGImage     = $this->strSiteOGImage;
                $strOGImageAlt  = $this->strSiteOGImageAlt;
                $iOGImageH      = $this->iSiteOGImageHeight;
                $iOGImageW      = $this->iSiteOGImageWidth;
                $strOGImageType = $this->strSiteOGImageType;
            }
            
            echo(t(1) . '<meta property="og:site_name" content="' . getenv('SITE_TITLE') . '">' . PHP_EOL);
            if (!isBlank($this->getOGTitle()))
                echo(t(1) . '<meta property=”og:title” content=”' . $this->getOGTitle() . '”>' . PHP_EOL);
            if (!isBlank($this->getOGDescription()))
                echo(t(1) . '<meta property=”og:description” content=”' . $this->getOGDescription() . '”>' . PHP_EOL);
            if (!isBlank($this->getOGType()))
                echo(t(1) . '<meta property=”og:type” content=”' . $this->getOGType() . '”>' . PHP_EOL);
            if (!isBlank($this->getOGURL()))
                echo(t(1) . '<meta property=”og:url” content=”' . $this->getOGURL() . $_SERVER['REQUEST_URI'] . '">' . PHP_EOP);
            
            echo(t(1) . '<meta property="og:image" content="' . $strOGImage . '">' . PHP_EOL);
            echo(t(1) . '<meta property="og:image:alt" content="' . $strOGImageAlt . '">' . PHP_EOL);
            if ($this->iSiteOGImageHeight > 0)
                echo(t(1) . '<meta property="og:image:height" content="' . $iOGImageH . '">' . PHP_EOL);
            if ($this->bSecure) {
                echo(t(1) . '<meta property=”og:image:secure_url” content=”' .
                    str_replace('http:', 'https:', $strOGImage) . '">' . PHP_EOL);
            }
            echo(t(1) . '<meta property="og:image:type" content="' . $strOGImageType . '">' . PHP_EOL);
            if ($this->iSiteOGImageWidth > 0)
                echo(t(1) . '<meta property="og:image:width" content="' . $iOGImageW . '">' . PHP_EOL);
            
            echo(t(1) . '<meta property="og:locale" content="' . $this->getOGLocale() . '">' . PHP_EOP);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  TWITTER
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->bTwitter && $bPublic) {
            echo(t(1) . '<!-- Twitter -->' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:card" content="' . $this->getTwitterCard() . '">' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:creator" content="' . $this->getTwitterCreator() . '">' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:description" content="' . $this->getTwitterDescription() . '">' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:site" content="' . $this->getTwitterSiteID() . '">' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:title" content="' . $this->getTwitterTitle() . '">' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:url" content="' . $this->getTwitterURL() . '">' . PHP_EOP);
            
            echo(t(1) . '<meta property="twitter:image" content="' . $this->strTwitterImage . '">' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:image:alt" content="' . $this->strTwitterImageAlt . '">' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:image:type" content="' . $this->strTwitterImageType . '">' . PHP_EOP);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  FAVICONS
        //////////////////////////////////////////////////////////////////////////////
        
        if (!empty($this->arrSiteFavicons) && $bPublic) {
            echo(t(1) . '<!-- Favicons -->' . PHP_EOL);
            foreach ($this->arrSiteFavicons as $strSize => $strFile) {
                echo(t(1) . '<link rel="icon" type="image/png" sizes="' . $strSize . '" href="' . $strFile . '">' . PHP_EOL);
            }
            if (file_exists(getenv('SITE_PATH') . '/apple-touch-icon.png'))
                echo(t(1) . '<link rel="apple-touch-icon" href="/apple-touch-icon.png">' . PHP_EOL);
            if (file_exists(getenv('SITE_PATH') . '/favicon.ico'))
                echo(t(1) . '<link rel="shortcut icon" type="image/x-icon" href="/favicon.ico">' . PHP_EOL);
            echo(PHP_EOL);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  ARTICLE INFO
        //////////////////////////////////////////////////////////////////////////////
        
        if (!is_null($this->strArtAuthor))
            echo(t(1) . '<meta property="article:author" content="' . $this->strArtAuthor . '">' . PHP_EOL);
        if (!is_null($this->strArtExpTime))
            echo(t(1) . '<meta property="article:expired_time" content="' . $this->strArtExpTime . '">' . PHP_EOL);
        if (!is_null($this->strArtModTime))
            echo(t(1) . '<meta property="article:modified_time" content="' . $this->strArtModTime . '">' . PHP_EOL);
        if (!is_null($this->strArtPubTime))
            echo(t(1) . '<meta property="article:published_time" content="' . $this->strArtPubTime . '">' . PHP_EOL);
        if (!is_null($this->strArtSection))
            echo(t(1) . '<meta property="article:section" content="' . $this->strArtSection . '">' . PHP_EOL);
        if (!is_null($this->strArtTags))
            echo(t(1) . '<meta property="article:tags" content="' . $this->strArtTags . '">' . PHP_EOL);
        
        //////////////////////////////////////////////////////////////////////////////
        //  PRELOAD FONTS
        //////////////////////////////////////////////////////////////////////////////
        
        if (!empty($this->arrSitePreloadFonts)) {
            echo(t(1) . '<!-- Fonts -->' . PHP_EOL);
            foreach ($this->arrSitePreloadFonts as $strFile => $strType) {
                echo(t(1) . '<link rel="preload" href="' . $this->strFontsDir . $strFile . '" as="font" type="font/' . $strType . '" crossorigin>' . PHP_EOL);
            }
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  JAVASCRIPT FILES
        //////////////////////////////////////////////////////////////////////////////
        
        // Global Javascript file
        $strJS = getenv('SITE_PATH') . getenv('SITE_JSS_DIR') . getenv('SITE_FILE_BASE') . '.js';
        if (file_exists($strJS)) {
            echo(t(1) . '<script defer src="' . getenv('SITE_JSS_DIR') . getenv('SITE_FILE_BASE') . '.js"></script>' . PHP_EOL);
        }
        
        // If internal Javascript file exists with same file name include it
        $strJS = getenv('SITE_PATH') . getenv('SITE_JSS_DIR') . $this->strFileName . '.js';
        if (file_exists($strJS)) {
            echo(t(1) . '<script defer src="' . getenv('SITE_JSS_DIR') . $this->strFileName . '.js"></script>' . PHP_EOL);
        }
        
        // Additional Javascript files
        if (!is_null($this->arrJScriptFiles)) {
            foreach($this->arrJScriptFiles as $strJScriptFile) {
                $strJS = getenv('SITE_JSS_DIR') . $strJScriptFile;
                if (file_exists(getenv('SITE_PATH') . $strJS))
                    echo(t(1) . '<script src="' . $strJS . '"></script>'. PHP_EOL);
            }
        }
        
        // Additional external Javascript link(s)
        if (!is_null($this->arrExtJSLinks)) {
            foreach($this->arrExtJSLinks as $strJScriptLink) {
                echo(t(1) . '<script src="' . $strJScriptLink . '"></script>'. PHP_EOL);
            }
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  CSS FILES
        //////////////////////////////////////////////////////////////////////////////
        
        // Global stylesheets
        echo(PHP_EOL);
        echo(t(1) . '<link rel="stylesheet" href="' . getenv('SITE_CSS_DIR') . $this->strSiteNormaliseCSS . '?v=' . getenv('SITE_VER_NUM') . '">' . PHP_EOL);
        echo(t(1) . '<link rel="stylesheet" href="' . getenv('SITE_CSS_DIR') . getenv('SITE_FILE_BASE') . '.css?v=' . getenv('SITE_VER_NUM') . '">' . PHP_EOL);
        
        // If stylesheet exists with same file name include it
        $strCSSFile = getenv('SITE_PATH') . getenv('SITE_CSS_DIR') . $this->strFileName . '.css';
        if (file_exists($strCSSFile)) {
            echo(t(1) . '<link rel="stylesheet" href="' . getenv('SITE_CSS_DIR') . $this->strFileName . '.css?v=' . getenv('SITE_VER_NUM') . '">' . PHP_EOL);
        }
        
        // Additional external stylesheets
        if (!is_null($this->arrCSSFiles)) {
            foreach($this->arrCSSFiles as $css_scriptfile) {
                $strCSSFile = getenv('SITE_CSS_DIR') . $css_scriptfile;
                if (file_exists(getenv('SITE_PATH') . $strCSSFile))
                    echo(t(1) . '<link rel="stylesheet" href="' . $strCSSFile . '?v=' . getenv('SITE_VER_NUM') . '">'. PHP_EOL);
            }
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  GOOGLE ANALYTICS
        //////////////////////////////////////////////////////////////////////////////
        
        if ($bPublic && (!isBlank($this->strSiteGoogleTag)) ) {
            echo(PHP_EOL);
            echo(t(1) . '<!-- ---------------------------------------------------------------' . PHP_EOL);
            echo(t(1) . '-    GOOGLE ANALYTICS' . PHP_EOL);
            echo(t(1) . '---------------------------------------------------------------- -->' . PHP_EOL);
            echo(t(1) . '<script async src="https://www.googletagmanager.com/gtag/js?id=' . $this->strSiteGoogleTag . '"></script>' . PHP_EOL);
            echo(t(1) . '<script>' . PHP_EOL);
            echo(t(2) . 'window.dataLayer = window.dataLayer || [];' . PHP_EOL);
            echo(t(2) . 'function gtag(){dataLayer.push(arguments);}' . PHP_EOL);
            echo(t(2) . 'gtag(\'js\', new Date());' . PHP_EOL);
            echo(t(2) . 'gtag(\'config\', \'' . $this->strSiteGoogleTag . '\');' . PHP_EOL);
            echo(t(1) . '</script>' . PHP_EOL);
        }
        
        // Page title
        echo(PHP_EOL);
        echo(t(1) . '<title>' . $this->getPgTitle() . '</title>' . PHP_EOL);
        
        echo("</head>" . PHP_EOP);
        
        echo("<body>" . PHP_EOP);
    }
}
