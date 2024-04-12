<?php

// TODO datetime medium ('Apr 2, 1963' or '2nd April 1963' or '2nd April 1963 15:30' or 'April 2, 1963 3:30 PM)'
// TODO datetime full ('mercredi, le 1er juin, 2023' or 'Wednesday, 1st June 2023' or 'Wednesday, June 1, 2023' ...

require_once($_SERVER['DOCUMENT_ROOT'] . '/incl/sysfuns.inc');

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Intl
//  @version    1.04    (06/02/2024)
//  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

class Intl
{
    protected const     ARR_CURR_SYMBOLS            =   array(
        array(
            'Sym'   =>  '$',
            'B4'    =>  true,
            'Space' =>  false,
        ),
        array(
            'Sym'   =>  '¢',
            'B4'    =>  false,
            'Space' =>  false,
        ),
        array(
            'Sym'   =>  '£',
            'B4'    =>  true,
            'Space' =>  false,
        ),
        array(
            'Sym'   =>  '€',
            'B4'    =>  false,
            'Space' =>  true,
        ),
        array(
            'Sym'   =>  '¥',
            'B4'    =>  true,
            'Space' =>  false,
        ),
    );
    protected const         ARR_PERCENT_SPACE_COUNTRIES =   array(
        'fr', 'es', 'it'
    );
    
    protected const         DEF_CURR_PRECISION          =   2;
    protected const         DEF_DATE_PADDING            =   true;
    protected const         DEF_LOCALE_LANG             =   'fr';
    protected const         DEF_LOCALE_COUNTRY          =   'fr';
    
    protected const         DEF_LOCALE_TIMEZONE         =   'Europe/Paris';
    protected const         DEF_NUM_PRECISION           =   2;
    protected const         DEF_PERCENT_PRECISION       =   0;
    protected const         DEF_TIME_PADDING            =   true;
    
    protected ?array        $arrDateShortFmt            =   null;
    protected ?array        $arrTimeShortFmt            =   null;
    
    protected bool          $bCurrCodeBefore            =   false;
    protected bool          $bCurrCodeSpace             =   true;
    protected bool          $bCurrSymBefore             =   true;
    protected bool          $bCurrSymSpace              =   false;
    protected bool          $bDatePadding               =   true;
    protected bool          $bPercentSpace              =   false;
    protected bool          $bGrouping                  =   true;
    protected bool          $bTimePadding               =   true;
    protected bool          $bYear4Digits               =   true;
    
    protected ?DateTimeZone $dtz                        =   null;
    protected ?int          $iCurrPrecision             =   null;
    protected ?int          $iNumPrecision              =   null;
    protected ?int          $iPercentPrecision          =   null;
    
    protected ?string       $strCurrCode                =   null;
    protected ?string       $strCurrSym                 =   null;
    protected ?string       $strCurrSymIntl             =   null;
    protected ?string       $strDateShortPattern        =   null;
    protected ?string       $strDateSep                 =   '/';
    protected ?string       $strDecimalSep              =   null;
    protected ?string       $strLocale                  =   null;
    protected string        $strLocaleCountry           =   '';
    protected string        $strLocaleLang              =   '';
    protected ?string       $strLocaleTimeZone          =   null;
    protected ?string       $strThousandsSep            =   null;
    protected ?string       $strTimeShortPattern        =   null;
    protected ?string       $strTimeSep                 =   ':';
    
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // CONSTRUCTOR()
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function __construct(?string $strLocale = null, ?string $strLocaleTimeZone = null)
    {
        $this->strLocaleCountry             =   self::DEF_LOCALE_COUNTRY;
        $this->strLocaleLang                =   self::DEF_LOCALE_LANG;
        $this->strLocaleTimeZone            =   $strLocaleTimeZone ?? self::DEF_LOCALE_TIMEZONE;
        
        $this->bDatePadding                 =   self::DEF_DATE_PADDING;
        $this->bTimePadding                 =   self::DEF_TIME_PADDING;
        
        $this->iCurrPrecision               =   self::DEF_CURR_PRECISION;
        $this->iNumPrecision                =   self::DEF_NUM_PRECISION;
        $this->iPercentPrecision            =   self::DEF_PERCENT_PRECISION;
        
        $this->setLocale($strLocale);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getBinarySizeStr()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get binary size string
    //
    //  @param      int $iNum           The binary size value
    //              int $iPrecision     Number of decimal places to display
    //              string  $strBytes   The initial for bytes
    //
    //  @return     string
    //
    //  EXAMPLE     getBinarySizeStr(1048, 0)
    //  RETURNS     1kb
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getBinarySizeStr(int $iNum, ?int $iPrecision = null, string $strBytes = 'b') : string
    {
        $arrSize = ['b','k','m','g','t','p'];
        
        $iPrecision ??= $this->iNumPrecision;
        
        $iFactor = floor((strlen($iNum) - 1) / 3);
        $NF = new NumberFormatter($this->strLocale, NumberFormatter::PATTERN_DECIMAL);
        $NF->setAttribute(NumberFormatter::FRACTION_DIGITS, $iPrecision);
        $NF->setAttribute(NumberFormatter::GROUPING_USED, $this->bGrouping);
        
        $fSize = $iNum / pow(1024, $iFactor);
        return(($fSize < 1 ? '0' : '') . $NF->format($fSize) . ' ' . $arrSize[$iFactor] . $strBytes);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getBytes()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get the word or intial for bytes based on language
    //
    //  @param      bool    $bFullLen   Full word (true) OR
    //                                  First initial (false)
    //
    //  @return     string
    //
    //  EXAMPLE     getBytes()
    //  RETURNS     'b'
    //
    //  EXAMPLE     getBytes(true)
    //  RETURNS     'bytes'
    /////////////////////////////////////////////////////////////////////////////
    
    function getBytes(bool $bFullLen = false) : string
    {
        
        $strBytes   =   match($this->getLocaleLang()) {
            'fr'    =>  'octets',
            default =>  'bytes',
        };
        
        return($bFullLen ? $strBytes : strStart($strBytes, 1));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrCode()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency code
    //
    //  @return     string
    //
    //  EXAMPLE     getCurrCode()
    //  RETURNS     'USD'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrCode() : string
    {
        return($this->strCurrCode);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrCodeBefore()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency code comes before or not
    //
    //  @return     bool
    //
    //  EXAMPLE     getCurrCodeBefore()
    //  RETURNS     true
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrCodeBefore() : bool
    {
        return($this->bCurrCodeBefore);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrCodeSpace()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency code has a space before/after or not
    //
    //  @return     bool
    //
    //  EXAMPLE     getCurrCodeSpace()
    //  RETURNS     false
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrCodeSpace() : bool
    {
        return($this->bCurrCodeSpace);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrCodeVal()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get string with currency value and currency code
    //
    //  @param      float   $fCurrNum       Currency value
    //  @param      int     $iCurrPrecision Number of decimal places
    //  @param      string  $strCurrCode    Currency code
    //  @param      bool    $bCodeBefore    Currency code comes before value or not
    //
    //  @return     string
    //
    //  EXAMPLE     getCurrCodeVal(1)
    //  RETURNS     '1.00 EUR'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrCodeVal(float $fCurrNum, ?int $iCurrPrecision = null, ?string $strCurrCode = null, ?bool $bCodeBefore = false) : string
    {
        $strCurrCode    ??= $this->strCurrCode;
        $iCurrPrecision ??= $this->iCurrPrecision;
        $bCodeBefore    ??= $this->bCurrCodeBefore;
        $bCodeSpace     =   $this->bCurrCodeSpace ? ' ' : '';
        
        return  ($bCodeBefore ? $strCurrCode . $bCodeSpace : '') .
            $this->getCurrNumVal($fCurrNum, $iCurrPrecision, $this->strDecimalSep, $this->strThousandsSep) .
            ($bCodeBefore ? '' : $bCodeSpace . $strCurrCode);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrNumVal()
    //  @version    1.01 (06/02/2024)
    //  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency number string without currency symbol or currency code
    //
    //  @param      float   $fCurrNum           Currency number
    //  @param      int     $iCurrPrecision     Number of decimal places
    //  @param      string  $strDecimalSep      Decimals separator character
    //  @param      string  $strThousandsSep    Thousands separator character
    //
    //  @return     string
    //
    //  EXAMPLE     getCurrNumVal(1500)
    //  RETURNS     '1,500.00'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    private function getCurrNumVal(float $fCurrNum, int $iCurrPrecision, ?string $strDecimalSep = null, ?string $strThousandsSep = null) : string
    {
        $strDecimalSep      ??= $this->strDecimalSep;
        $strThousandsSep    ??= $this->strThousandsSep;
        return(number_format($fCurrNum, $iCurrPrecision, $strDecimalSep, $strThousandsSep));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrPrecision()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get the number of decimal places set for currency values
    //
    //  @return     int
    //
    //  EXAMPLE     getCurrPrecision()
    //  RETURNS     2
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrPrecision() : int
    {
        return($this->iCurrPrecision);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrSymVal()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency string with currency symbol
    //
    //  @param      float   $fCurrNum       Currency value
    //  @param      int     $iCurrPrecision Number of decimal places
    //  @param      string  $strCurrSym     Currency symbol
    //  @param      bool    $bSymBefore     Currency symbol before or after
    //  @param      bool    $bSymSpace      Space before or after currency symbol or not
    //
    //  @return     string
    //
    //  EXAMPLE     getCurrSymVal(1024)
    //  RETURNS     '1,024.00 €'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrSymVal(float $fCurrNum, ?int $iCurrPrecision = null, ?string $strCurrSym = null, ?bool $bSymBefore = null, ?bool $bSymSpace = null) : string
    {
        $iCurrPrecision ??= $this->iCurrPrecision;
        $strCurrSym     ??= $this->strCurrSym;
        $bSymBefore     ??= $this->bCurrSymBefore;
        $bSymSpace      ??= $this->bCurrSymSpace;
        
        $strSymSpace = $bSymSpace ? ' ' : '';
        
        return  ($bSymBefore ? $strCurrSym . $strSymSpace : '') .
            $this->getCurrNumVal($fCurrNum, $iCurrPrecision, $this->strDecimalSep, $this->strThousandsSep) .
            ($bSymBefore ? '' : $strSymSpace . $strCurrSym);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrSymIntlVal()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency string with international currency symbol
    //
    //  @param      float   $fCurrNum       Currency value
    //  @param      int     $iCurrPrecision Number of decimal places
    //  @param      string  $strCurrSymIntl International currency symbol
    //  @param      bool    $bSymBefore     Currency symbol before or after
    //  @param      bool    $bSymSpace      Space before or after currency symbol or not
    //
    //  @return     string
    //
    //  EXAMPLE     getCurrSymIntlVal(1024)
    //  RETURNS     '1,024.00 €'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrSymIntlVal(float $fCurrNum, ?int $iCurrPrecision = null, ?string $strCurrSymIntl = null, ?bool $bSymBefore = null, ?bool $bSymSpace = null) : string
    {
        $strCurrSymIntl ??= $this->strCurrSymIntl;
        return($this->getCurrSymVal($fCurrNum, $iCurrPrecision, $strCurrSymIntl, $bSymBefore, $bSymSpace));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrSym()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency symbol
    //
    //  @return     string
    //
    //  EXAMPLE     getCurrSym();
    //  RETURNS     '€'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrSym() : string
    {
        return($this->strCurrSym);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrSymBefore()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get whether the currency symbole comes before the value or not
    //
    //  @return     bool
    //
    //  EXAMPLE     getCurrSymBefore()
    //  RETURNS     true
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrSymBefore() : bool
    {
        return($this->bCurrSymBefore);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrSymsFromStr()
    //  @version    1.0 (28/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get currency symbols from a string
    //
    //  @param      $strCurr    String with symbols
    //  @param      $bWithSpace Include spaces (before or after) with currency symbol
    //
    //  @return     Currency symbol(s) from a string
    //
    //  EXAMPLE     getCurrSymsFromStr('$50,000')
    //  RETURNS     '$'
    //
    //  EXAMPLE     getCurrSymsFromStr('50,000 €')
    //  RETURNS     '€'
    //
    //  EXAMPLE     getCurrSymsFromStr(strCurr: '50,000 €', bWithSpace: true)
    //  RETURNS     ' €'
    //
    //  EXAMPLE     getCurrSymsFromStr(strCurr: 'AU$ 50,000', bWithSpace: true)
    //  RETURNS     'AU$ '
    //
    function getCurrSymsFromStr(string $strCurr, bool $bWithSpaces = false) : string
    {
        
        if ($bWithSpaces) {
            // Remove numbers, commas, signs and dots
            return (preg_replace('/[\d,+\-.]+/', '', $strCurr));
        }
        else {
            // Remove numbers, commas, dots, signs and spaces
            return (preg_replace('/[\d,+\-. ]+/', '', $strCurr));
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrSymIntl()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get international currency symbol
    //
    //  @return     string
    //
    //  EXAMPLE     getCurrSymIntl()
    //  RETURNS     '€'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrSymIntl() : string
    {
        return($this->strCurrSymIntl);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getCurrSymSpace()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get whether or not there is a space before/after the currency symbol
    //
    //  @return     bool
    //
    //  EXAMPLE     getCurrSymSpace()
    //  RETURNS     true
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getCurrSymSpace() : bool
    {
        return($this->bCurrSymSpace);
    }
    
    // TODO check and clean up function declarations (FROM HERE)
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getDateTimeShortStr()
    //  @version    2.0 (20/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get short string from date/time/datetime value
    //
    //  @param      string  $strDateTime    Date/Time/DateTime value in format
    //                                      YYYY-MM-DD HH:MM(:SS)
    //  @param      bool    $bDate          Return date (default: true)
    //  @param      bool    $bTime          Return time (default: false)
    //
    //  @return     string
    //
    //  EXAMPLE     getDateTimeShortStr(strDateTime: '2023-06-14 09:21', bTime: true)
    //  RETURNS     '14/06/23 09:21'
    //
    //  EXAMPLE     getDateTimeShortStr('2023-06-14 09:21')
    //  RETURNS     '14/06/2023'
    /////////////////////////////////////////////////////////////////////////////
    
    function getDateTimeShortStr(string $strDateTime, bool $bDate = true, bool $bTime = false) : string
    {
        
        // build up DateTime format
        $strDTPattern           =   ($bDate ? $this->strDateShortPattern : '') .
            ($bDate && $bTime ? ' ' : '') .
            ($bTime ? $this->strTimeShortPattern : '');
        
        $dt =   new DateTimeImmutable($strDateTime, $this->dtz);
        
        return($dt->format($strDTPattern));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getDateTimeZone()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Returns the time z0ne
    //
    //  @return     DateTimeZone object
    /////////////////////////////////////////////////////////////////////////////
    
    function getDateTimeZone() : DateTimeZone
    {
        return($this->dtz);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getDecimalSep()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get the decimal separator character
    //
    //  @return     string
    //
    //  EXAMPLE     getDecimalSep()
    //  RETURNS     '.'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getDecimalSep() : string
    {
        return($this->strDecimalSep);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getDecimalVal()
    //  @version    1.1 (09/08/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Return the decimal portion of a float (to the right of the decimal)
    //
    //  @param      float   $fVal   Value with decimal portion (or not)
    //
    //  @return     float
    //
    //  EXAMPLE     getDecimalVal(5.75)
    //  RETURNS     0.75
    //
    //  EXAMPLE     getDecimalVal(5)
    //  RETURNS     0
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getDecimal(float $fVal) : float
    {
        return(fmod($fVal, 1));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getFileSizeInBytes()
    //  @version    1.01a (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get file size in bytes converted to pb, tb, gb, mb, kb, b
    //
    //  @param      string  $strFName   File name
    //  @param      int     $iPrecision Number of decimal places
    //  @param      string  $strBytes   The word for bytes
    //
    //  @return     string
    //
    //  EXAMPLE     getFileSizeInBytes('index.php');
    //  RETURNS     1.24kb
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getFileSizeInBytes(string $strFName, ?int $iPrecision = null, ?string $strBytes = null) : string
    {
        $iPrecision ??= $this->iNumPrecision;
        $strBytes   ??= $this->getBytes();
        
        $iFSize = filesize(getFullFilePath($strFName));
        
        return($this->getBinarySizeStr($iFSize, $iPrecision, $strBytes));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getGrouping()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get whether or not numerical values are grouped with thousands separators
    //
    //  @return     bool
    //
    //  EXAMPLE     getGrouping()
    //  RETURNS     true
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getGrouping() : bool
    {
        return($this->bGrouping);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getLocale()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get international locale
    //
    //  @return     string
    //
    //  EXAMPLE     getLocale()
    //  RETURNS     'en-gb'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getLocale() : string
    {
        return($this->strLocale);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getLocaleCountry()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get international country
    //
    //  @return     string
    //
    //  EXAMPLE     getLocaleCountry()
    //  RETURNS     'gb'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getLocaleCountry() : string
    {
        return($this->strLocaleCountry);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getLocaleLang()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get international language
    //
    //  @return     string
    //
    //  EXAMPLE     getLocaleLang()
    //  RETURNS     'en'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getLocaleLang() : string
    {
        return($this->strLocaleLang);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getLocaleTimeZoneStr()
    //  @version    1.01 (21/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get Locale Time Zone string
    //
    //  @return     string
    //
    //  EXAMPLE     getLocaleTimeZoneStr()
    //  RETURNS     'Europe/Paris'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getLocaleTimeZoneStr() : string
    {
        return($this->strLocaleTimeZone);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getNumPrecision()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get number of decimal places for numerical values
    //
    //  @return     int
    //
    //  EXAMPLE     getNumPrecision()
    //  RETURNS     2
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getNumPrecision() : int
    {
        return($this->iNumPrecision);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getNumVal()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get numerical value with separators and precision
    //
    //  @param      float   $fNum               Numerical value
    //  @param      int     $iNumPrecision      Number of decimal values
    //  @param      string  $strDecimalSep      Decimal separator character
    //  @param      string  $strThousandsSep    Thousands separator character
    //
    //  @return     string
    //
    //  EXAMPLE     getNumVal(1024)
    //  RETURNS     1,024.00
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getNumVal(float $fNum, ?int $iNumPrecision = null, ?string $strDecimalSep = null, ?string $strThousandsSep = null) : string
    {
        $iNumPrecision      ??= $this->iNumPrecision;
        $strDecimalSep      ??= $this->strDecimalSep;
        $strThousandsSep    ??= $this->strThousandsSep;
        return(number_format($fNum, $iNumPrecision, $strDecimalSep, $strThousandsSep));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getNumWords()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get number in words
    //
    //  @param      float   $fNum   Number
    //
    //  @return     string
    //
    //  EXAMPLE     getNumWords(1024)
    //  RETURNS     'one thousand and twenty-four'
    //
    //  EXAMPLE     getNumWords(2048)
    //  RETURNS     'deux mille quarante-huit'
    /////////////////////////////////////////////////////////////////////////////
    
    function getNumWords(float $fNum) : string
    {
        $NF = new NumberFormatter($this->strLocale, NumberFormatter::SPELLOUT);
        return($NF->format($fNum));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getOrdinalVal()
    //  @version    1.0 (20/01/2024)
    //  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get ordinal value
    //
    //  @param      int     $iNum   Numeric value
    //  @param      bool    $bMasc  Masculine (true) or feminine (false)
    //
    //  @return     string
    //
    //  EXAMPLE     getOrdinalVal(4);
    //  RETURNS     '4th'
    //
    //  EXAMPLE     getOrdinalVal(8)
    //  RETURNS     '8ème'
    //
    //  EXAMPLE     getOrdinalVal(1, false)
    //  RETURNS     '1ère'
    /////////////////////////////////////////////////////////////////////////////
    
    function getOrdinalVal(int $iNum, bool $bMasc = true) : string
    {
        $NF = new NumberFormatter($this->strLocale, NumberFormatter::ORDINAL);
        $strOrdinal = $NF->format($iNum);
        
        if ($this->getLocaleLang() === 'fr') {
            // Première
            if (($iNum == 1) && ($bMasc == false))
                return('1ère');
            
            // Remove non-breakable spaces
            $strOrdinal = str_replace(chr(194).chr(160),'', $strOrdinal);
            // Remove digits and punctuation from ordinal string
            $strOrdinal = preg_replace('/[0-9\s.,]+/', '', $strOrdinal);
            // Correct e to ème
            if ($strOrdinal == 'e') {
                $strOrdinal = $this->getNumVal($iNum, 0) . 'ème';
            }
        }
        
        return($strOrdinal);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getOrdinalValWords()
    //  @version    1.1 (20/01/2024)
    //  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get ordinal word based on value
    //
    //  @param      int     $iNum   Numeric value
    //  @param      bool    $bMasc  Masculine (true) or feminine (false)
    //
    //  @return     string
    //
    //  EXAMPLE     getOrdinalValWords(4);
    //  RETURNS     'fourth'
    //
    //  EXAMPLE     getOrdinalValWords(8)
    //  RETURNS     'huitième'
    /////////////////////////////////////////////////////////////////////////////
    
    function getOrdinalValWords(int $iNum, bool $bMasc = true) : string
    {
        $NF = new NumberFormatter($this->strLocale, NumberFormatter::SPELLOUT);
        $NF->setTextAttribute(NumberFormatter::DEFAULT_RULESET, '%spellout-ordinal');
        $strOrdinal = $NF->format($iNum);
        
        // French particularities
        if ($this->getLocaleLang() === 'fr') {
            if ($iNum === 1)
                $strOrdinal = $bMasc ? 'premier' : 'première';
            else {
                $strLast = strEnd($strOrdinal, 1);
                switch ($strLast) {
                    case 'e' :
                        // Remove trailing e
                        $strOrdinal = strRemoveRight($strOrdinal, 1);
                        break;
                    case 'f' :
                        // Replace f with v
                        $strOrdinal = strRemoveRight($strOrdinal, 1) . 'v';
                        break;
                    case 'q':
                        // Add ue
                        $strOrdinal .= 'ue';
                        break;
                }
                $strOrdinal .= 'ième';
            }
        }
        return($strOrdinal);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getPercentPrecision()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get number of decimal places for percentage values
    //
    //  @return     int
    //
    //  EXAMPLE     getPercentPermission()
    //  RETURNS     2
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getPercentPrecision() : int
    {
        return($this->iPercentPrecision);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getPercentVal()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get percent value with separators and precision
    //
    //  @param      float   $fNum               Numerical value
    //  @param      int     $iPrecision         Number of decimal values
    //  @param      bool    $bPercentSpace      Space before percentage sign or not
    //
    //  @return     string
    //
    //  EXAMPLE     getPercentVal(95)
    //  RETURNS     95.00%
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getPercentVal(float $fPercentNum, ?int $iPrecision = null, ?bool $bPercentSpace = null) : string
    {
        $iPrecision     ??= $this->iPercentPrecision;
        $bPercentSpace  ??= $this->bPercentSpace;
        $strPattern     =   '%.' . $iPrecision . 'f' . ($bPercentSpace ? ' ' : '') . '%%';
        return(sprintf($strPattern, $fPercentNum));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getPS()
    //  @version    1.0 (15/01/2024)
    //  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get plural / singular term
    //
    //  @param      int     iNum        Number of items
    //  @param      string  strSing     Singular term
    //  @param      string  strPlural   Plural term
    //                                  null = add s to singular term
    //  @param      string  strGenre    m or f
    //  @param      bool    bArticle    return string with or without article
    //
    //  @return     string
    //
    //  EXAMPLE     getPS(5, 'cheval', 'chevaux', 'm', true);
    //  RETURNS     'les chevaux';
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getPS(int $iNum, string $strSing, ?string $strPlur = null, string $strGenre = 'm', bool $bArticle = false) : string
    {
        $strPlur ??= $strSing . 's';
        
        if ($iNum == 1) {
            if (isFirstCharVowel($strSing))
                $strArticle = 'l\'';
            else
                $strArticle = ($strGenre === 'm' ? 'le ' : 'la ');
            $strPS = $strSing;
        }
        else {
            $strArticle = 'les ';
            $strPS = $strPlur;
        }
        
        return(($bArticle ? $strArticle : '') . $strPS);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getRomanVal()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get roman number for integer
    //
    //  @param      int $iNum   Numerical value
    //
    //  @return     string
    //
    //  EXAMPLE     getRomanVal(14)
    //  RETURNS     'XIV'
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getRomanVal(int $iNum) : string
    {
        $NF = new NumberFormatter('@numbers=roman', NumberFormatter::DECIMAL);
        return($NF->format($iNum));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  getThousandsSep()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Get the thousands separator character
    //
    //  @return     string
    //
    //  EXAMPLE     getThousandsSep()
    //  RETURNS     ','
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function getThousandsSep() : string
    {
        return($this->strThousandsSep);
    }
    
    function getTimeZoneName() : string
    {
        return($this->dtz->getName());
    }
    
    function getTimeZoneOffset() : int
    {
        $dti = new DateTimeImmutable('now', $this->dtz);
        
        // Return offset in hours
        return($dti->getOffset() / 3600);
    }
    
    function getTimeZoneOffsetStr() : string
    {
        $iOffset = $this->getTimeZoneOffset();
        return('UTC' . ($iOffset >= 0 ? '+' : '') . $iOffset);
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  isCurrency()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Test if there is a currency symbol anywhere in the string
    //
    //  @param      string  $strVal
    //
    //  @return     bool
    //
    //  EXAMPLE     isCurrency('1,024.00 €'
    //  RETURNS     true
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function isCurrency(string $strVal) : bool
    {
        $iLen = count(self::ARR_CURR_SYMBOLS);
        $arrCurrSyms = [];
        for ($i = 0; $i < $iLen; $i++) {
            $arrCurrSyms[] = self::ARR_CURR_SYMBOLS[$i]['Sym'];
        }
        
        return(in_array($strVal, $arrCurrSyms));
    }
    
    /////////////////////////////////////////////////////////////////////////////
    //
    //  isCurrVal()
    //  @version    1.0 (14/06/2023)
    //  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Test if string contains only valid currency characters
    //
    //  @param      string  $strVal
    //
    //  @return     bool
    //
    //  EXAMPLE     isCurrVal('-1,024.00 €'
    //  RETURNS     true
    //
    /////////////////////////////////////////////////////////////////////////////
    
    function isCurrVal(string $strVal) : bool
    {
        $iLen = count(self::ARR_CURR_SYMBOLS);
        $strCurrSyms = '/ˆ[\d,.';
        for ($i = 0; $i < $iLen; $i++) {
            $strCurrSyms .= self::ARR_CURR_SYMBOLS[$i]['Sym'];
        }
        $strCurrSyms .= ' \-]*$/';
        
        return (pregMatch($strCurrSyms, $strVal));
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    //  removeNumSeps()
    //  Version 1.0 (23/05/2023)
    //
    //  Remove ambiguous number separators (thousands and decimals)
    //
    //  @param          string  $strNum Numerical string
    //
    //  @return         string
    //                  contains only numerical sign and numbers with
    //                  dot decimal separator
    //
    //  EXAMPLE         removeNumSeps('1,500.00')
    //  RETURNS         1500.00
    //  EXAMPLE         removeNumSeps('-1.500,00')
    //  RETURNS         -1500.00
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function removeNumSeps(string $strNum) : string
    {
        // Remove everything other than digits, dashes (minuses) and separators
        $strNum = preg_replace('/[^\d.,-]/', '', $strNum);
        
        // Test for comma thousands separator
        if (pregMatch('/,\d{3}/', $strNum)) {
            // Remove commas
            $strNum = str_replace(',','', $strNum);
        }
        // Test for dot thousands separator
        if (pregMatch('/\.\d{3}/', $strNum)) {
            // Remove dots
            $strNum = str_replace('.', '', $strNum);
        }
        // Replace comma decimal separator with dot
        if (pregMatch('/,\d{2}/', $strNum)) {
            $strNum = str_replace(',', '.', $strNum);
        }
        
        return($strNum);
    }

// TODO clean up function declarations (FROM HERE)
    
    function setCurrCode(string $strCurrCode, ?bool $bCurrCodeBefore = null, ?bool $bCurrCodeSpace = null) : void
    {
        $this->strCurrCode      =   $strCurrCode;
        $this->bCurrCodeBefore  =   $bCurrCodeBefore    ??  $this->bCurrCodeBefore;
        $this->bCurrCodeSpace   =   $bCurrCodeSpace     ??  $this->bCurrCodeSpace;
    }
    
    function setCurrCodeBefore(bool $bCurrCodeBefore) : void
    {
        $this->bCurrCodeBefore = $bCurrCodeBefore;
    }
    
    function setCurrCodeSpace(bool $bCurrCodeSpace) : void
    {
        $this->bCurrCodeSpace = $bCurrCodeSpace;
    }
    
    //  Locale Country = ISO 3166 code
    //  @see    https://www.iso.org/obp/ui/#search/code/
    function setCurrFromLocale(?string $strLocale = null) : void
    {
        // EU override
        if ($this->getLocaleCountry() === 'eu') {
            $this->setCurrCode('EU', false, true);
            $this->setCurrSym('EU', false, true);
            $this->setCurrSymIntl('EU');
            return;
        }
        $strLocale ??= $this->strLocale;
        $NF = new NumberFormatter($strLocale, NumberFormatter::CURRENCY);
        $this->setCurrCode($NF->getTextAttribute(NumberFormatter::CURRENCY_CODE));
        $this->setCurrSym($NF->getSymbol(NumberFormatter:: CURRENCY_SYMBOL));
    }
    
    function setCurrPrecision(int $iCurrPrecision) : void
    {
        $this->iCurrPrecision   = $iCurrPrecision;
    }
    
    function setCurrSym(string $strCurrSym, ?bool $bCurrSymBefore = null, ?bool $bCurrSymSpace = null) : void
    {
        $this->strCurrSym       =   $strCurrSym;
        $this->strCurrSymIntl   =   strStart($this->strCurrCode, 2) . $this->strCurrSym;
        
        $iLen                   =   count(self::ARR_CURR_SYMBOLS);
        for ($i = 0; $i < $iLen; $i++) {
            if (self::ARR_CURR_SYMBOLS[$i]['Sym'] === $strCurrSym) {
                $this->bCurrSymBefore   =   self::ARR_CURR_SYMBOLS[$i]['B4'];
                $this->bCurrSymSpace    =   self::ARR_CURR_SYMBOLS[$i]['Space'];
                break;
            }
        }
        
        $this->bCurrSymBefore   =   $bCurrSymBefore ??  $this->bCurrSymBefore;
        $this->bCurrSymSpace    =   $bCurrSymSpace  ??  $this->bCurrSymSpace;
    }
    
    function setCurrSymBefore(bool $bCurrSymBefore) : void
    {
        $this->bCurrSymBefore = $bCurrSymBefore;
    }
    
    function setCurrSymSpace(bool $bCurrSymSpace) : void
    {
        $this->bCurrSymSpace = $bCurrSymSpace;
    }
    
    function setCurrSymIntl(string $strCurrSymIntl) : void
    {
        $this->strCurrSymIntl = $strCurrSymIntl;
    }
    
    function setDateTimeShortFormat(?bool $bYear4Digits = null, ?bool $bDatePadding = null, ?bool $bTimePadding = null, bool $bSecs = false, bool $bTZ = false) : void
    {
        $this->bDatePadding ??= $bDatePadding;
        $this->bTimePadding ??= $bTimePadding;
        $bYear4Digits       ??= $this->bYear4Digits;
        $this->bYear4Digits =   $bYear4Digits;
        
        // EU override
        if ($this->getLocaleCountry() === 'eu') {
            $this->strDateSep = '/';
            $this->arrDateShortFmt = array(
                $this->bDatePadding ? 'd' : 'j',
                $this->bDatePadding ? 'm' : 'n',
                $this->bYear4Digits ? 'Y' : 'y',
            );
            $this->arrTimeShortFmt = array(
                'H' =>  $this->bTimePadding ? 'H' : 'G',
                'M' =>  'i',
            );
            $this->setDateShortPattern();
            $this->setTimeShortPattern();
            return;
        }
        
        // SQL override
        if ($this->getLocaleCountry() === 'sq') {
            $this->strDateSep = '-';
            $this->arrDateShortFmt = array('Y', 'm', 'd');
            $this->arrTimeShortFmt = array(
                'H' => 'H',
                'M' => 'i',
            );
            $this->setDateShortPattern();
            $this->setTimeShortPattern(bSecs: true);
            return;
        }
        
        // Get international short date format from locale
        $IDF =   new IntlDateFormatter(locale: $this->strLocale, dateType: IntlDateFormatter::SHORT, timeType: IntlDateFormatter::SHORT, timezone: $this->dtz, calendar: IntlDateFormatter::GREGORIAN);
        $strFullDateTimePattern = $IDF->getPattern();
        
        // Isolate date format
        $strDatePatternSep  =   strpos($strFullDateTimePattern, ',') ? ', ' : ' ';
        $iDateTimeSepPos    =   strpos($strFullDateTimePattern, $strDatePatternSep);
        $strDatePattern     =   substr($strFullDateTimePattern, 0, $iDateTimeSepPos);
        
        // Date sep = first non-alphabetic character
        pregMatch(strPattern:'/[^a-z]/', strSubject: strtolower($strDatePattern), arrMatches: $arrMatches);
        $this->strDateSep = $arrMatches[0];
        
        // Split date pattern in to three format groupings
        $arrIDFDateFmt = explode($this->strDateSep, $strDatePattern);
        
        // SET DATE FORMATS
        for ($i = 0; $i < 3; $i++) {
            $this->arrDateShortFmt[$i] = match ($arrIDFDateFmt[$i]) {
                'd'         =>  $this->bDatePadding ? 'd' : 'j',
                'dd'        =>  'd',
                'M','L'     =>  $this->bDatePadding ? 'm' : 'n',
                'MM','LL'   =>  'm',
                'y','yy'    =>  $this->bYear4Digits ? 'Y' : 'y',
                'yyy'       =>  'Y',
            };
        }
        $this->setDateShortPattern();
        
        // Isolate Time Pattern
        $strTimePattern = substr($strFullDateTimePattern, $iDateTimeSepPos + strlen($strDatePatternSep));
        
        // Split time pattern in to format groupings
        if (strContains($strTimePattern, ':')) {
            $arrTimeFmtSplit    =   explode(':', $strTimePattern);
            switch ($arrTimeFmtSplit[0]) {
                case 'h':
                    $this->bTimePadding = false;
                    $this->arrTimeShortFmt['H'] = 'g';
                    break;
                case 'hh':
                    $this->arrTimeShortFmt['H'] = 'h';
                    break;
                case 'H':
                    $this->bTimePadding = false;
                    $this->arrTimeShortFmt['H'] = 'G';
                    break;
                case 'HH':
                    $this->arrTimeShortFmt['H'] = 'H';
                    break;
            }
        }
        else {
            // Time separator other than a colon force format
            $this->arrTimeShortFmt['H'] = 'H';
        }
        $this->arrTimeShortFmt['M'] = 'i';
        
        $this->setTimeShortPattern($bSecs, $bTZ);
    }
    
    function setDateShortPattern() : void
    {
        $this->strDateShortPattern = $this->arrDateShortFmt[0] . $this->strDateSep . $this->arrDateShortFmt[1] . $this->strDateSep . $this->arrDateShortFmt[2];
    }
    
    function setDecimalSep(string $strDecimalSep) : void
    {
        $this->strDecimalSep    =  $strDecimalSep;
    }
    
    function setGrouping(bool $bGrouping) : void
    {
        $this->bGrouping = $bGrouping;
    }
    
    function setLocale(?string $strLocale = null, ?string $strLocaleTimeZone = null) : void
    {
        $strLocale ??= strtolower($this->strLocaleLang . '_' . $this->strLocaleCountry);
        
        $this->strLocale = strtolower($strLocale);
        $this->setLocaleLang($strLocale);
        $this->setLocaleCountry($strLocale);
        
        $strLocaleTimeZone  ??= $this->strLocaleTimeZone;
        $this->dtz          =   new DateTimeZone($strLocaleTimeZone);
        
        $this->setCurrFromLocale();
        $this->setDateTimeShortFormat();
    }
    
    function setLocaleCountry(string $strCountry) : void
    {
        // 'CC' (2 char code) OR 'll-CC@extra' full locale
        $this->strLocaleCountry =  (strlen($strCountry) === 2) ? $strCountry : strEnd($strCountry, strlen($strCountry)-3);
        
        // Percentage defaults
        $this->setPercentSpace();
        
        // Number defaults
        $NF = new NumberFormatter($this->strLocale, NumberFormatter::DECIMAL);
        // Override French thousands symbol
        if ($this->strLocaleCountry === 'fr')
            $this->strThousandsSep = '.';
        else
            $this->strThousandsSep = $NF->getSymbol(NumberFormatter::GROUPING_SEPARATOR_SYMBOL);
        $this->strDecimalSep = $NF->getSymbol(NumberFormatter::DECIMAL_SEPARATOR_SYMBOL);
        
        // Currency defaults
        $NF = new NumberFormatter($this->strLocale, NumberFormatter::CURRENCY);
        $this->setCurrCode($NF->getTextAttribute(NumberFormatter::CURRENCY_CODE));
        $this->setCurrSym($NF->getSymbol(NumberFormatter::CURRENCY_SYMBOL));
    }
    
    //  Locale Lang = ISO 639-1 code
    //  @see    https://www.loc.gov/standards/iso639-2/php/code_list.php
    function setLocaleLang(string $strLocaleLang) : void
    {
        // 'll' (2 char code) OR 'll-CC@extra' full locale
        $this->strLocaleLang  =   strStart($strLocaleLang, 2);
    }
    
    function setNumPrecision(int $iNumPrecision) : void
    {
        $this->iNumPrecision = $iNumPrecision;
    }
    
    function setPercentPrecision(int $iPercentPrecision) : void
    {
        $this->iPercentPrecision = $iPercentPrecision;
    }
    
    function setPercentSpace(?bool $bPercentSpace = null) : void
    {
        $this->bPercentSpace = false;
        if (is_null($bPercentSpace)) {
            foreach(self::ARR_PERCENT_SPACE_COUNTRIES as $strVal) {
                if ($strVal === $this->strLocaleCountry) {
                    $this->bPercentSpace = true;
                    break;
                }
            }
        }
        else
            $this->bPercentSpace = $bPercentSpace;
    }
    
    function setThousandsSep(string $strThousandsSep) : void
    {
        $this->strThousandsSep = $strThousandsSep;
    }
    
    function setTimeShortPattern(bool $bSecs = false, bool $bTZ = false) : void
    {
        $this->strTimeShortPattern       =  $this->arrTimeShortFmt['H'] . $this->strTimeSep . $this->arrTimeShortFmt['M'];
        
        if ($bSecs)
            $this->strTimeShortPattern   .= $this->strTimeSep . 's';
        
        // 12-hour AM/PM
        if ($this->arrTimeShortFmt['H'] === 'g' || $this->arrTimeShortFmt['H'] ==='h')
            $this->strTimeShortPattern   .= ' A';
        
        // Time Zone
        if ($bTZ)
            $this->strTimeShortPattern  .=  ' T';
    }
    
    function setTimeZone(string $strTZ) : void
    {
        $this->strLocaleTimeZone    =   $strTZ;
        $this->dtz                  =   new DateTimeZone($strTZ);
    }
    
    function setYear4Digits(bool $bYear4Digits) : void
    {
        $this->bYear4Digits = $bYear4Digits;
    }
    
}
