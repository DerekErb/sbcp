<?php

//////////////////////////////////////////////////////////////////////////////
//
//  Head Class
//  Version 1.0
//
//////////////////////////////////////////////////////////////////////////////

class Head extends Site
{
    protected const     SITE_ARR_PRELOAD_FONTS          =   array(
                                                                'roboto-regular.ttf'    =>  'ttf',
                                                            );
    protected const     SITE_AUTHORS                    =   'Derek Erb Solutions';
    protected const     SITE_CONTENT_SECURITY_POLICY    =    '';
    protected const     SITE_DESIGNER                   =   'Derek Erb Solutions';
    protected const     SITE_GEN                        =   'Hand-coded by Derek Erb Solutions';
    protected const     SITE_RATING                     =   'Safe For Kids';
    
    // SE Indexing revisit site every X days
    protected const     SITE_SE_REVISIT                 =   14;
    
    protected ?array    $arrCSSFiles                    =   null;
    protected ?array    $arrJScriptFiles                =   null;
    protected ?array    $arrExtJSLinks                  =   null;
    
    protected ?array    $arrFavIcons                   =    array(
                                                                '512x512'   => '/favicon-512x512.png',
                                                                '192x192'   =>  '/favicon-192x192.png',
                                                                '96x96'     =>  '/favicon-96x96.png',
                                                                '32x32'     =>  '/favicon-32zx32.png',
                                                                '16x16'     =>  '/favicon-16x16.png',
                                                            );

    protected ?string   $strFileName                    =   null;
    protected string    $strNormaliseCSS                =   'normalise.css';
    protected ?string   $strPgLangCodes                 =   null;
    protected ?string   $strPgTitle                     =   null;
    
    protected ?string   $strSiteAbstract                =   null;
    protected ?string   $strSiteDesc                    =   null;
    protected ?string   $strSiteGoogleTag               =   null;
    protected ?string   $strSiteKeywords                =   null;
    
    protected ?string   $strSiteOwner                   =   'Derek Erb Solutions';
    protected ?string   $strSiteThemeColor              =   '#FFFFFF';
    
    // Article Info
    protected ?string   $strArtAuthor                   =   null;
    protected ?string   $strArtExpTime                  =   null;
    protected ?string   $strArtModTime                  =   null;
    protected ?string   $strArtPubTime                  =   null;
    protected ?string   $strArtSection                  =   null;
    protected ?string   $strArtTags                     =   null;
    
    // Open Graph / Facebook Info
    protected array     $arrSiteOGInfo                  =   array(
                                                                'Image'         =>  'XXX full OG image URL',
                                                                // Alt image description
                                                                'ImageAlt'       =>  '',
                                                                // Image height in pixels
                                                                'ImageHeight'    =>  1200,
                                                                // Image file type
                                                                'ImageType'     =>  'image/png',
                                                                // Image width in pixels
                                                                'ImageWidth'      =>  600,
                                                                'Locale'        =>  'en_US',
                                                                'Type'          =>  'website',
                                                            );

    protected array     $arrSiteOGLocales               =   array(
                                                                'en_GB',
                                                                'fr_FR',
                                                            );

    protected bool      $bOpenGraph                     =   false;
    protected ?string   $strOgDesc                      =   null;
    protected ?string   $strOgImageAlt                  =   null;
    protected ?int      $iOgImageHeight                 =   null;
    protected ?int      $iOgImageWidth                  =   null;
    protected ?string   $strOgImage                     =   null;
    protected ?string   $strOgImageType                 =   null;
    protected ?string   $strOgLocale                    =   null;
    protected ?array    $arrOgLocales                   =   null;
    protected ?string   $strOgTitle                     =   null;
    protected ?string   $strOgType                      =   null;
    protected ?string   $strOgURL                       =   null;
    
    // PWA Info
    protected bool      $bPWA                           =   true;
    protected ?string   $strPWAAppName                  =   null;
    protected ?string   $strPWAManifest                 =   null;
    
    // SEO Header Info
    protected ?string   $strPgAbstract                  =   null;
    protected ?string   $strPgAuthors                   =   null;
    protected ?string   $strPgCopyright                 =   null;
    protected ?string   $strPgDescription               =   null;
    protected ?string   $strPgDesigner                  =   null;
    protected ?string   $strPgGenerator                 =   null;
    protected ?string   $strPgKeywords                  =   null;
    protected ?string   $strPgOwner                     =   null;
    protected ?string   $strPgRating                    =   null;
    
    // Twitter Info
    protected ?array    $arrSiteTwitterInfo             =   array(
                                                                'Card'          =>  'summary_large_image',
                                                                'Creator'       =>  'XXX-@twitter handle of creator',
                                                                'Desc'          =>  'XXX-twitter description (<= 140 chars)',
                                                                'Image'         =>  'XXX-full url of twitter image',
                                                                'ImageAlt'      =>  'XXX-alt text for image',
                                                                'ImageType'     =>  'image/png',
                                                                'SiteID'        =>  'XXX-@twitter handle of site',
                                                                'Title'         =>  'XXX-site name',
                                                                'URL'           =>  'XXX-full site url',
                                                            );
    
    protected bool      $bTwitter                       =   false;
    protected ?string   $strTwitterCard                 =   null;
    protected ?string   $strTwitterCreator              =   null;
    protected ?string   $strTwitterDesc                 =   null;
    protected ?string   $strTwitterImage                =   null;
    protected ?string   $strTwitterImageAlt             =   null;
    protected ?string   $strTwitterImageType            =   null;
    protected ?string   $strTwitterSiteID               =   null;
    protected ?string   $strTwitterTitle                =   null;
    protected ?string   $strTwitterURL                  =   null;
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // CONSTRUCTOR()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct()
    {
    
        parent::__construct();
        
        // Get base file name without path or extension
        $this->strFileName = rmvFileExt(basename($_SERVER['PHP_SELF']));
        
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  activateOpenGraph()
    //
    //  Turn on/off the OpenGraph variiable
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function activateOpenGraph(bool $bOG = true) : void
    {
        $this->bOpenGraph= $bOG;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  activatePWA()
    //
    //  Turn on/off the PWA variiable
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function activatePWA(bool $bPWA = true) : void
    {
        $this->bPWA= $bPWA;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  activateTwitter()
    //
    //  Turn on/off the Twitter variiable
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function activateTwitter(bool $bTwit = true) : void
    {
        $this->bTwitter = $bTwit;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  addCSSFile()
    //
    //  Add an additional CSS file to the header
    //
    //  $strCSSFile The filename of the CSS file to be added to the array
    //              of CSS files for the header
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function addCSSFile(string $strCSSFile) : void
    {
        if (is_null($this->arrCSSFiles))
            // Create the array with the CSS file
            $this->arrCSSFiles = array($strCSSFile);
        else {
            if (!in_array($strCSSFile, $this->arrCSSFiles))
                // Add the CSS file to the end of the array
                $this->arrCSSFiles[] = $strCSSFile;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  addJScriptFile()
    //
    //  Add an additional Javascript file to the header
    //
    //  $strCSSFile The filename of the Javascript file to be added to the array
    //              of Javascript files for the header
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function addJscriptFile(string $strJScriptFile) : void
    {
        if (is_null($this->arrJScriptFiles))
            // Create the array with the Javascript file
            $this->arrJScriptFiles = array($strJScriptFile);
        else {
            if (!in_array($strJScriptFile, $this->arrJScriptFiles))
                // Add the CSS file to the end of the array
                $this->arrJScriptFiles[] = $strJScriptFile;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // forceSecure()
    //
    // Test for, and redirect to, secure version of site if SSL domains
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function forceSecure() : void
    {
        if ((!$this->isSecure()) && ($this->isProd())) {
            $arrSSLDomains = $this->getSSLDomains();
            foreach ($arrSSLDomains as $strSSLDomain) {
                if ($this->getServerName() == $strSSLDomain) {
                    header('Location: https://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI']);
                    break;
                }
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getAbstract()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getAbstract() : string
    {
        return($this->strPgAbstract ?? $this->strSiteAbstract);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getCopy()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getCopy() : string
    {
        return ($this->strPgCopyright ?? parent::SITE_COPYSITE);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getDesc()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getDesc() : string
    {
        return($this->strPgDescription ?? $this->strSiteDesc);
        
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getDesigner()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getDesigner() : string
    {
        return($this->strPgDesigner ?? self::SITE_DESIGNER);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getGenerator()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getGenerator() : string
    {
        return($this->strPgGenerator ?? self::SITE_GEN);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getKeywords()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getKeywords() : string
    {
        return($this->strPgKeywords ?? $this->strSiteKeywords);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getLangCodes()
    //
    // Get language codes for head
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getLangCodes() : string
    {
        return($this->strPgLangCodes ?? $this->getLang());
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getOgDesc()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOgDesc() : string
    {
        return($this->strOgDesc ?? $this->strSiteDesc);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getOgLocale()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOgLocale() : string
    {
        return($this->strOgLocale ?? $this->arrSiteOGInfo['Locale']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getOgTitle()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOgTitle() : string
    {
        return($this->strOgTitle ?? $this->getSiteTitle());
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getOgType()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOgType() : string
    {
        return($this->strOgType ?? $this->arrSiteOGInfo['Type']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getOgURL()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOgURL() : string
    {
        return($this->strOgURL ?? $this->getSiteRoot() . $_SERVER['REQUEST_URI']);
    }
    
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getOwner()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getOwner() : string
    {
        return($this->strPgOwner ?? $this->strSiteOwner);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getPgTitle()
    //
    // Prepare title for output
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getPgTitle() : string
    {
        return($this->getSiteTitle() .
            (is_null($this->strPgTitle) ? '' : ' - ' . $this->strPgTitle));
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getRating()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getRating() : string
    {
        return($this->strPgRating ?? self::SITE_RATING);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getTwitterCard()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterCard() : string
    {
        return($this->strTwitterCard ?? $this->arrSiteTwitterInfo['Card']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getTwitterCreator()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterCreator() : string
    {
        return($this->strTwitterCreator ?? $this->arrSiteTwitterInfo['Creator']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getTwitterDesc()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterDesc() : string
    {
        return($this->strTwitterDesc ?? $this->arrSiteTwitterInfo['Desc']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getTwitterSiteID()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterSiteID() : string
    {
        return($this->strTwitterSiteID ?? $this->arrSiteTwitterInfo['SiteID']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getTwitterTitle()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterTitle() : string
    {
        return($this->strTwitterTitle ?? $this->arrSiteTwitterInfo['Title']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // getTwitterURL()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function getTwitterURL() : string
    {
        return($this->strTwitterURL ?? $this->arrSiteTwitterInfo['URL']);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setAbstract()
    //
    // Set the text for the SEO Abstract
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setAbstract(string $strAbs) : void
    {
        $this->strPgAbstract = $strAbs;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setArtAuthor
    //
    // Set the Article Author's Name
    //
    //  $strArtAuthor   Author's name
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtAuthor(string $strArtAuthor) : void
    {
        $this->strArtAuthor = $strArtAuthor;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setArtExpTime
    //
    // Set the Article Expiration Time
    //
    //  $strArtExpTime  YYYY-MM-DDTHH:MM:SS+HH:MM
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtExpTime(string $strArtExpTime) : void
    {
        $this->strArtExpTime = $strArtExpTime;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setArtModTime
    //
    // Set the Article Modification Time
    //
    //  $strArtModTime  YYYY-MM-DDTHH:MM:SS+HH:MM
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtModTime(string $strArtModTime) : void
    {
        $this->strArtModTime = $strArtModTime;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setArtPubTime
    //
    // Set the Article Publication Time
    //
    //  $strArtPubTime  YYYY-MM-DDTHH:MM:SS+HH:MM
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtPubTime(string $strArtPubTime) : void
    {
        $this->strArtPubTime = $strArtPubTime;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setArtSection
    //
    // Set the Article section categories
    //
    //  $strArtSect Article section categories (comma-separated)
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtSection(string $strArtSect) : void
    {
        $this->strArtSection = $strArtSect;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setArtTags
    //
    // Set the Article keyword tags
    //
    //  $strArtSect Article keyword tags (comma-separated)
    //////////////////////////////////////////////////////////////////////////////
    
    function setArtTags(string $strArtTags) : void
    {
        $this->strArtTags = $strArtTags;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // setAuthors()
    //
    // Set the text for the SEO Authors
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setAuthors(string $strAuthors) : void
    {
        $this->strPgAuthors = $strAuthors;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setCSSFiles()
    //
    //  Set the CSS files for the header
    //
    //  $CSSFiles   Either a comma-delimited list of CSS file names or
    //              a pre-declared array of CSS file names
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setCSSFiles(string $strCSSFiles) : void
    {
        $this->arrCSSFiles = explode(',', $strCSSFiles);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setCopyright()
    //
    //  Set the text for the SEO Copyright
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setCopyright(string $strCopy) : void
    {
        $this->strPgCopyright = $strCopy;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setDescription()
    //
    //  Set the text for the SEO Description
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setDescription(string $strDesc) : void
    {
        $this->strPgDescription = $strDesc;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setDesigner()
    //
    //  Set the text for the SEO Designer
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setDesigner(string $strDesigner) : void
    {
        $this->strPgDesigner = $strDesigner;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setExtJSFiles
    //
    //  Set the list of links to external JavaScript links
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setExtJSFiles(string $strExtJSLinks) : void
    {
        $this->arrExtJSLinks = explode(',', $strExtJSLinks);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setGenerator()
    //
    //  Set the text for the SEO Generator
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setGenerator(string $strGenerator) : void
    {
        $this->strPgGenerator = $strGenerator;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setJScriptFiles()
    //
    //  Set the Javascript files for the header
    //
    //  $arrJScriptFiles    Either a comma-delimited list of JavaScript file names
    //                      or a pre-declared array of JavaScript file names
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setJScriptFiles(string $strJScriptFiles) : void
    {
        $this->arrJScriptFiles = explode(',', $strJScriptFiles);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setKeywords()
    //
    //  $strKeys    One string with comma-separated terms
    //  Set the text for the SEO keywords
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setKeywords(string $strKeys) : void
    {
        $this->strPgKeywords = $strKeys;
    }
    
    function setLangCodes(string $strLangCodes) : void
    {
        $this->strPgLangCodes = $strLangCodes;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setNormaliseCSS()
    //
    //  Set the CSS normalisation file
    //////////////////////////////////////////////////////////////////////////////
    
    function setNormaliseCSS(string $strNormaliseCSS) : void
    {
        $this->strNormaliseCSS = $strNormaliseCSS;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOgDesc
    //
    //  Set the Open Graph description
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOgDesc(string $strOgDesc) : void
    {
        $this->activateOpenGraph();
        $this->strOgDesc = $strOgDesc;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOgImage
    //
    //  Set the Open Graph image URL
    //      Full URL (ie. https://calctva.app/calctvalogo200x600.png)
    //
    //  $bRel = Image URL is relative to current site or not
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOgImage(string $strImage, string $strType, ?string $strImageAlt = null, bool $bRel = true, ?int $iWidth = null, ?int $iHeight = null) : void
    {
        $this->activateOpenGraph();
        $this->strOgImage       = ($bRel ? $this->getSiteRoot() : '') . $strImage;
        $this->strOgImageAlt    = $strImageAlt;
        $this->iOgImageHeight   = $iHeight;
        $this->strOgImageType   = 'image/' . $strType;
        $this->iOgImageWidth    = $iWidth;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOgLocale
    //
    //  Set the Open Graph locale
    //      See Language codes
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOgLocale(string $strPgOgLocale) : void
    {
        $this->activateOpenGraph();
        $this->strOgLocale = $strPgOgLocale;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOgLocales
    //
    //  Set the Open Graph alternate locales
    //      See Language codes
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOgLocales(string $strPgOgLocales) : void
    {
        $this->activateOpenGraph();
        $this->arrOgLocales = explode(',', $strPgOgLocales);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOgTitle
    //
    //  Set the Open Graph title
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOgTitle(string $strOgTitle) : void
    {
        $this->activateOpenGraph();
        $this->strOgTitle = $strOgTitle;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOgType
    //
    //  Set the Open Graph type
    //      website, article, blog
    //////////////////////////////////////////////////////////////////////////////
    
    function setOgType(string $strOgType) : void
    {
        $this->activateOpenGraph();
        $this->strOgType = $strOgType;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOgURL
    //
    //  Set the Open Graph URL
    //      website, article, blog
    //
    //  $bRel is URL relative to current site or not
    //////////////////////////////////////////////////////////////////////////////
    
    function setOgURL(string $strOgURL, $bRel = true) : void
    {
        $this->activateOpenGraph();
        $this->strOgURL = ($bRel ? $this->getSiteRoot() : '') . $strOgURL;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setOwner
    //
    //  Set the text for the SEO Owner
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setOwner(string $strOwner) : void
    {
        $this->strPgOwner = $strOwner;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setPWA()
    //
    //  Set PWA attributes
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
    //
    //  $strAppName     PWA Application Name
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setPWAAppName(string $strAppName) : void
    {
        $this->activatePWA();
        $this->strPWAAppName = $strAppName;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setPWAManifest()
    //
    //  $strManifestFile    Relative path and file name of PWA manifest file
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setPWAManifest(string $strManifestFile) : void
    {
        $this->activatePWA();
        $this->strPWAManifest = $strManifestFile;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setRating
    //
    //  Set the rating for the page
    //
    //  $strPgRating    general
    //                  mature
    //                  restricted
    //                  adult
    //                  14 years
    //                  safe for kids
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setRating(string $strPgRating) : void
    {
        $this->strPgRating = $strPgRating;
    }
    
    function setSiteAbstract(string $strSiteAbstract) : void
    {
        $this->strSiteAbstract = $strSiteAbstract;
    }
    
    function setSiteDesc(string $strSiteDesc) : void
    {
        $this->strSiteDesc = $strSiteDesc;
    }
    
    function setSiteKeywords(string $strSiteKeywords) : void
    {
        $this->strSiteKeywords = $strSiteKeywords;
    }
    
    function setSiteOwner(string $strSiteOwner) : void
    {
        $this->strSiteOwner = $strSiteOwner;
    }
    
    function setSiteThemeColor(string $strSiteThemeColor) : void
    {
        $this->strSiteThemeColor = $strSiteThemeColor;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTitle()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTitle(string $strTitle) : void
    {
        $this->strPgTitle = $strTitle;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitter
    //
    //  Set the Twitter Info
    //
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitter(string $strTwitterDesc, ?string $strTwitterCreator = null, ?string $strTwitterCard = null) : void
    {
        $this->activateTwitter();
        $this->strTwitterdesc       =   $strTwitterDesc;
        $this->strTwitterCreator    =   $strTwitterCreator  ??  $this->arrSiteTwitterInfo['Creator'];
        $this->strTwitterCard       =   $strTwitterCard     ??  $this->arrSiteTwitterInfo['Card'];
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterCard
    //
    //  Set the Twitter Card info
    //      summary
    //      summary_large_image
    //
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterCard(string $strTwitterCard) : void
    {
        $this->activateTwitter();
        $this->strTwitterCard = $strTwitterCard;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterCreator
    //
    //  Set the Twitter Creator
    //      @twitterid
    //
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterCreator(string $strTwitterCreator) : void
    {
        $this->activateTwitter();
        $this->strTwitterCreator = $strTwitterCreator;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterDesc
    //
    //  Set the Twitter description
    //
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterDesc(string $strTwitterDesc) : void
    {
        $this->activateTwitter();
        $this->strTwitterDesc = $strTwitterDesc;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitter Image
    //
    //  Set the Twitter image info
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //      Summary card image
    //          Relative URL
    //          Square 1:1 ratio min 144 x 144 px max 4096 x 4096 px
    //          Max 5 MB
    //
    //      Summary Large Image
    //          Relative URL
    //          Rectangle 2:1 ratio min 300 x 157 px max 4096 x 4096 px
    //          Max 5 MB
    //
    //      Image types
    //          GIF, JPEG, PNG, WEBP
    //
    //      $bRel = image URL is relative to current site or not
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterImage(string $strImage, string $strType, ?string $strImageAlt = null, bool $bRel = true) : void
    {
        $this->activateTwitter();
        $this->strTwitterImage       = ($bRel ? $this->getSiteRoot() : '') . $strImage;
        $this->strTwitterImageAlt    = $strImageAlt;
        $this->strTwitterImageType   = 'image/' . $strType;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterSiteID
    //
    //  Set the Twitter siteID
    //      @twitter id of site owner/creator
    //
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-websites/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterSiteID(string $strTwitterSiteID) : void
    {
        $this->activateTwitter();
        $this->strTwitterSiteID = $strTwitterSiteID;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterTitle
    //
    //  Set the Twitter Title
    //
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-webTitles/cards/overview/markup)
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterTitle(string $strTwitterTitle) : void
    {
        $this->activateTwitter();
        $this->strTwitterTitle = $strTwitterTitle;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setTwitterURL
    //
    //  Set the Twitter URL
    //
    //      Full URL (ie. https://developer.twitter.com/en/docs/twitter-for-webURLs/cards/overview/markup)
    //
    //  $bRel is URL relative to current site
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setTwitterURL(string $strTwitterURL, $bRel = true) : void
    {
        $this->activateTwitter();
        $this->strTwitterURL = ($bRel ? $this->getSiteRoot() : '') . $strTwitterURL;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  write()
    //
    //  Output site page head
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function write() : void
    {
        // Force Secure Site
        $this->forceSecure();
        
        echo('<!DOCTYPE HTML>' . PHP_EOL);
        echo('<html lang="' . $this->getLangCodes() . '">' . PHP_EOL . PHP_EOL);
        
        echo('<head>' . PHP_EOL . PHP_EOL);
        
        echo(t(1) . '<meta charset="UTF-8">' . PHP_EOL);
        echo(t(1) . '<meta name="title" content="' . $this->getPgTitle() . '">' . PHP_EOL);
        echo(t(1) . '<meta name="theme-color" content="' . $this->strSiteThemeColor . '" >' . PHP_EOL . PHP_EOL);
        
        //////////////////////////////////////////////////////////////////////////////
        //  Content Security Policy
        //////////////////////////////////////////////////////////////////////////////
        if (!isBlank(self::SITE_CONTENT_SECURITY_POLICY)) {
            echo(t(1) . '<!-- Content Security Policy -->' . PHP_EOL);
            echo(t(1) . '<meta http-equiv="Content-Security-Policy" content="' . self::SITE_CONTENT_SECURITY_POLICY . '">' . PHP_EOL . PHP_EOL);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  PWA
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->bPWA) {
            echo(t(1) . '<!-- PWA Settings -->' . PHP_EOL);
            if (!is_null($this->strPWAManifest)) {
                echo(t(1) . '<link rel="manifest" href="' . $this->strPWAManifest . '">' . PHP_EOL);
            }
            
            if (!is_null($this->strPWAAppName)) {
                echo(t(1) . '<meta name="application-name" content="' . $this->strPWAAppName . '">' . PHP_EOL . PHP_EOL);
            }
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  MOBILE FRIENDLY
        //////////////////////////////////////////////////////////////////////////////
        
        echo(t(1) . '<!-- Mobile Friendly -->' . PHP_EOL);
        echo(t(1) . '<meta name="Viewport" content="width=device-width, initial-scale=1.0" >' . PHP_EOL);
        echo(t(1) . '<meta name="HandheldFriendly" content="true" >' . PHP_EOL);
        echo(t(1) . '<meta name="MobileOptimized" content="320" >' . PHP_EOL . PHP_EOL);
        
        //////////////////////////////////////////////////////////////////////////////
        //  META NAMES
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->isProd()) {
            echo(t(1) . '<!-- Site / Page info -->' . PHP_EOL);
            echo(t(1) . '<meta name="abstract" content="' .
                $this->getAbstract() . '" >' . PHP_EOL);
            echo(t(1) . '<meta name="copyright" content="Copyright @ ' .
                $this->getCopy() . '" >' . PHP_EOL);
            echo(t(1) . '<meta name="description" content="' .
                $this->getDesc() . '" >' . PHP_EOL);
            echo(t(1) . '<meta name="designer" content="' .
                $this->getDesigner() . '" >' . PHP_EOL);
            echo(t(1) . '<meta name="generator" content="' .
                $this->getGenerator() . '" >' . PHP_EOL);
            echo(t(1) . '<meta name="keywords" content="' .
                $this->getKeywords() . '" >' . PHP_EOL);
            echo(t(1) . '<meta name="owner" content="' .
                $this->getOwner() . '" >' . PHP_EOL . PHP_EOL);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  SEO
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->isProd()) {
            echo(t(1) . '<meta name="rating" content="' .
                $this->getRating() . '" >' . PHP_EOL);
            echo(t(1) . '<meta name="resource-type" content="document" >' . PHP_EOL);
            echo(t(1) . '<meta name="distribution" content="global" >' . PHP_EOL);
            if ((parent::B_PUBLISHED) && $this->isProd())
                echo(t(1) . '<meta name="robots" content="all, index, follow" >' . PHP_EOL);
        }
        else {
            echo(t(1) . '<meta name="robots" content="none" >' . PHP_EOL);
            echo(t(1) . '<meta name="googlebot" content="none">' . PHP_EOL);
            echo(t(1) . '<meta name="Ads-bot-Google" content="noindex">' . PHP_EOL);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  OPEN GRAPH / FACEBOOK
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->bOpenGraph) {
            echo(t(1) . '<!-- Open Graph / Facebook -->' . PHP_EOL);
            if (is_null($this->strOgImage)) {
                $strOgImage     = $this->arrSiteOGInfo['Image'];
                $strOgImageAlt  = $this->arrSiteOGInfo['ImageAlt'];
                $iOgImageH      = $this->arrSiteOGInfo['ImageHeight'];
                $iOgImageW      = $this->arrSiteOGInfo['ImageWidth'];
                $strOgImageType = $this->arrSiteOGInfo['ImageType'];
            }
            else {
                $strOgImage     = $this->strOgImage;
                $strOgImageAlt  = $this->strOgImageAlt;
                $iOgImageH      = $this->iOgImageHeight ?? null;
                $iOgImageW      = $this->iOgImageWidth ?? null;
                $strOgImageType = $this->strOgImageType;
            }
            
            echo(t(1) . '<meta property="og:site_name" content="' . $this->getSiteTitle() . '" >' . PHP_EOL);
            if (!isBlank($this->getOgTitle()))
                echo(t(1) . '<meta property=”og:title” content=”' . $this->getOgTitle() . '” >' . PHP_EOL);
            if (!isBlank($this->getOgDesc()))
                echo(t(1) . '<meta property=”og:description” content=”' . $this->getOgDesc() . '” >' . PHP_EOL);
            if (!isBlank($this->getOgType()))
                echo(t(1) . '<meta property=”og:type” content=”' . $this->getOgType() . '” >' . PHP_EOL);
            if (!isBlank($this->getOgURL()))
                echo(t(1) . '<meta property=”og:url” content=”' . $this->getOgURL() . $_SERVER['REQUEST_URI'] . '" >' . PHP_EOP);
            
            echo(t(1) . '<meta property="og:image" content="' . $strOgImage . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="og:image:alt" content="' . $strOgImageAlt . '" >' . PHP_EOL);
            if (!is_null($this->iOgImageHeight))
                echo(t(1) . '<meta property="og:image:height" content="' . $iOgImageH . '" >' . PHP_EOL);
            if ($this->isSecure()) {
                echo(t(1) . '<meta property=”og:image:secure_url” content=”' .
                    str_replace('http:', 'https:', $strOgImage) . '" >' . PHP_EOL);
            }
            echo(t(1) . '<meta property="og:image:type" content="' . $strOgImageType . '" >' . PHP_EOL);
            if (!is_null($this->iOgImageWidth))
                echo(t(1) . '<meta property="og:image:width" content="' . $iOgImageW . '" >' . PHP_EOL);
            
            echo(t(1) . '<meta property="og:locale" content="' . $this->getOGLocale() . '" >' . PHP_EOL);
            if (is_null($this->arrOgLocales)) {
                foreach ($this->arrSiteOGLocales as $strLocale) {
                    echo(t(1) . '<meta property="og:locale:alternate" content="' . $strLocale . '" >' . PHP_EOL);
                }
            }
            else {
                foreach ($this->arrOgLocales as $strLocale) {
                    echo(t(1) . '<meta property="og:locale:alternate" content="' . $strLocale . '" >' . PHP_EOL);
                }
            }
            echo(PHP_EOL);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  TWITTER
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->bTwitter) {
            echo(t(1) . '<!-- Twitter -->' . PHP_EOL);
            if (is_null($this->strTwitterImage)) {
                $strTwitterImage        =   $this->arrSiteTwitterInfo['Image'];
                $strTwitterImageAlt     =   $this->arrSiteTwitterInfo['ImageAlt'];
                $strTwitterImageType    =   $this->arrSiteTwitterInfo['ImageType'];
            }
            else {
                $strTwitterImage        =   $this->strTwitterImage;
                $strTwitterImageAlt     =   $this->strTwitterImageAlt;
                $strTwitterImageType    =   $this->strTwitterImageType;
            }
            
            echo(t(1) . '<meta property="twitter:card" content="' . $this->getTwitterCard() . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:creator" content="' . $this->getTwitterCreator() . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:description" content="' . $this->getTwitterDesc() . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:site" content="' . $this->getTwitterSiteID() . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:title" content="' . $this->getTwitterTitle() . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:url" content="' . $this->getTwitterURL() . '" >' . PHP_EOP);
            
            echo(t(1) . '<meta property="twitter:image" content="' . $strTwitterImage . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:image:alt" content="' . $strTwitterImageAlt . '" >' . PHP_EOL);
            echo(t(1) . '<meta property="twitter:image:type" content="' . $strTwitterImageType . '" >' . PHP_EOP);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  FAVICONS
        //////////////////////////////////////////////////////////////////////////////
        
        echo(t(1) . '<!-- Favicons -->' . PHP_EOL);
        foreach ($this->arrFavIcons as $strSize => $strFile) {
            echo(t(1) . '<link rel="icon" type="image/png" sizes="' . $strSize . '" href="' . $strFile . '" >' . PHP_EOL);
        }
        if (file_exists($this->getPath() . '/apple-touch-icon.png'))
            echo(t(1) . '<link rel="apple-touch-icon" href="/apple-touch-icon.png">' . PHP_EOL);
        if (file_exists($this->getPath() . '/favicon.ico'))
            echo(t(1) . '<link rel="shortcut icon" type="image/x-icon" href="/favicon.ico" >' . PHP_EOP);
        echo(PHP_EOL);
        
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
        
        if (!is_null(self::SITE_ARR_PRELOAD_FONTS)) {
            echo(t(1) . '<!-- Fonts -->' . PHP_EOL);
            foreach (self::SITE_ARR_PRELOAD_FONTS as $strFile => $strType) {
                echo(t(1) . '<link rel="preload" href="' . self::FONTS_DIR . $strFile . '" as="font" type="font/' . $strType . '" crossorigin>' . PHP_EOL);
            }
            echo(PHP_EOL);
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  JAVASCRIPT FILES
        //////////////////////////////////////////////////////////////////////////////
        
        // Global Javascript file
        $strJS = $this->getPath() . parent::JS_DIR . parent::FILE_BASE . '.js';
        if (file_exists($strJS)) {
            echo(t(1) . '<script defer src="' . parent::JS_DIR . parent::FILE_BASE . '.js"></script>' . PHP_EOL);
        }
        
        // If internal Javascript file exists with same file name include it
        $strJS = $this->getPath() . parent::JS_DIR . $this->strFileName . '.js';
        if (file_exists($strJS)) {
            echo(t(1) . '<script defer src="' . parent::JS_DIR . $this->strFileName . '.js"></script>' . PHP_EOL);
        }
        
        // Additional Javascript files
        if (!is_null($this->arrJScriptFiles)) {
            foreach($this->arrJScriptFiles as $strJScriptFile) {
                $strJS = parent::JS_DIR . $strJScriptFile;
                if (file_exists($this->getPath() . $strJS))
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
        echo(t(1) . '<link rel="stylesheet" href="' . parent::CSS_DIR . $this->strNormaliseCSS . '?v=' . parent::VER_NUM . '" >' . PHP_EOL);
        if (file_exists($this->getPath() . parent::CSS_DIR . parent::FILE_BASE . '.css'))
            echo(t(1) . '<link rel="stylesheet" href="' . parent::CSS_DIR . parent::FILE_BASE . '.css?v=' . parent::VER_NUM . '" >' . PHP_EOL);
        
        // If stylesheet exists with same file name include it
        if (file_exists($this->getPath() . parent::CSS_DIR . $this->strFileName . '.css')) {
            echo(t(1) . '<link rel="stylesheet" href="' . parent::CSS_DIR . $this->strFileName . '.css?v=' . parent::VER_NUM . '" >' . PHP_EOL);
        }
        
        // Additional external stylesheets
        if (!is_null($this->arrCSSFiles)) {
            foreach($this->arrCSSFiles as $css_scriptfile) {
                $strCSSFile = parent::CSS_DIR . $css_scriptfile;
                if (file_exists($this->getPath() . $strCSSFile))
                    echo(t(1) . '<link rel="stylesheet" href="' . $strCSSFile . '?v=' . parent::VER_NUM . '" >'. PHP_EOL);
            }
        }
        
        //////////////////////////////////////////////////////////////////////////////
        //  GOOGLE ANALYTICS
        //////////////////////////////////////////////////////////////////////////////
        
        if ($this->isProd() && (!is_null($this->strSiteGoogleTag))) {
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
        echo(t(1) . '<title>' . $this->getPgTitle() . '</title>' . PHP_EOL);
        
        echo("</head>" . PHP_EOP);
        
        echo("<body>" . PHP_EOP);
    }
}

