<?php

//  TODO clean up function declarations
//  TODO use null coalescing = operator throughout
//  TODO $x = $x ?? 'fred' replaced by $x ??= 'fred'

/////////////////////////////////////////////////////////////////////////////
//
//              sysfuns.inc
//  @version    42.56 13/02/2024)
//  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  System functions
//
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Autoload classes
//////////////////////////////////////////////////////////////////////////////
include($_SERVER['DOCUMENT_ROOT'] . '/incl/autoload.inc');

//////////////////////////////////////////////////////////////////////////////
// DEBUG
//////////////////////////////////////////////////////////////////////////////
fullErrors();

//////////////////////////////////////////////////////////////////////////////
// GLOBAL Site class
//////////////////////////////////////////////////////////////////////////////
$Site ??= new Site();

//////////////////////////////////////////////////////////////////////////////
// GLOBAL Intl class
//////////////////////////////////////////////////////////////////////////////
$Intl ??= new Intl();

//////////////////////////////////////////////////////////////////////////////
// Constants
//////////////////////////////////////////////////////////////////////////////
const PHP_BLANK =   '';                 //  Blank
const PHP_EOP   =   PHP_EOL . PHP_EOL;  //  EOP (End of Paragraph)
const PHP_SP    =   '&nbsp;';           //  Nonbreakable space
const PHP_TAB   =   '    ';             //  Tab = 4 spaces

//////////////////////////////////////////////////////////////////////////////
//
//  addCookie()
//  Version 1.0 (23/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Add new cookie for $iDays (number of days)
//
//  @param          string  $strCookieName  Cookie name
//  @param          string  $strCookieVal   Cookie value
//  @param          int     $iDays          Number of days before cookie expiration
//  @param          string  $strPath        Path where cookie is stored (default: root)
//
//  @return         bool
//
//////////////////////////////////////////////////////////////////////////////

function addCookie(string $strCookieName, string $strCookieVal, ?int $iDays = null, string $strPath = '/') : bool
{
    // Avoid headers already sent error
    if (headers_sent())
        return(false);
    
    $iDays ??= Site::DEF_COOKIE_DURATION;
    
    // Set cookie and return result
    return(setcookie($strCookieName, $strCookieVal, time() + (86400 * $iDays), $strPath));
}

//////////////////////////////////////////////////////////////////////////////
//
//  autoCopyright()
//  Version 1.0 (23/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return either   'start year - current year' OR
//                  'current year' if no start or start year = current year
//
//  @param          string  $strStartYear    Starting year
//
//  @return         ?string
//
//////////////////////////////////////////////////////////////////////////////

function autoCopyright(?string $strStartYear = null) : ?string
{
    $strCurrYear = date('Y');
    
    $strCopyYear = $strCurrYear;
    if (!is_null($strStartYear)) {
        if ($strStartYear != $strCurrYear) {
            $strCopyYear = $strStartYear . ' - ' . $strCurrYear;
        }
    }
    
    return($strCopyYear);
}

//////////////////////////////////////////////////////////////////////////////
//
//  ckBox()
//  Version 1.0 (23/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Display a checkbox, checked or not
//
//  @param          string  $strName    Checkbox name
//  @param          string  $strID      Checkbox ID
//  @param          bool    $bChkVal    Checked or not
//  @param          string  strClass    Checkbox class(es)
//  @param          string  strLabel    Checkbox label
//  @param          bool    $bReadOnly  Read only or not
//
//  @return         string
//
//////////////////////////////////////////////////////////////////////////////

function ckBox(string $strName, string $strID, bool $bChkVal = false, ?string $strClass = null, ?string $strLabel = null, bool $bReadOnly = false) : string
{
    return(
    form_input('checkbox', $strName, $strID, $strClass, $bChkVal, null, $strLabel, $bReadOnly)
    );
}

//////////////////////////////////////////////////////////////////////////////
//
//  dateCreate()
//  Version 1.0 (23/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  date_create override : blank returns null (not today)
//
//  @param          string  $strDate    YYYY-mm-dd
//
//  @return         DateTime object or null
//
//////////////////////////////////////////////////////////////////////////////

function dateCreate(?string $strDate, bool $bBlankIsToday = false) : ?DateTime
{
    if (!is_string($strDate))
        return null;
    
    if (!$bBlankIsToday) {
        if (isEmpty(($strDate))) {
            return null;
        }
    }
    
    return(date_create($strDate));
}

//////////////////////////////////////////////////////////////////////////////
//
//  delCookie()
//  Version 1.0 (23/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Delete (remove) cookier
//
//  @param          string  $strCookie  Name of cookie to deleted (removed)
//
//  @return         bool    Cookie deleted or not
//
//////////////////////////////////////////////////////////////////////////////

function delCookie(string $strCookie) : bool
{
    if (headers_sent())
        return(false);
    
    unset($_COOKIE[$strCookie]);
    return(setcookie($strCookie, '', 1, '/'));
}

//////////////////////////////////////////////////////////////////////////////
//
//  fmtIPv4Add()
//  Version 1.0 (23/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Format an IP v4 address with zero padding
//
//  @param          string  $strIPAdd
//
//  @return         string
//                  properly formatted as XXX.XXX.XXX.XXX
//
//  EXAMPLE         fmtIPv4Add('10.0.0.1');
//  RETURNS         '010.000.000.001'
//
//  EXAMPLE         fmtIPv4Add('localhost');
//  RETURNS         'localhost'
//////////////////////////////////////////////////////////////////////////////

function fmtIPv4Add(string $strIPAdd) : string
{
    // Get 4 IP numbers
    $arrIP = explode('.', $strIPAdd);
    
    if (is_numeric($arrIP[0])) {
        // Build address with padding
        $IPv4Add = sprintf('%03d.%03d.%03d.%03d', $arrIP[0], $arrIP[1], $arrIP[2], $arrIP[3]);
    }
    else {
        // Localhost or server name
        $IPv4Add = $strIPAdd;
    }
    
    return($IPv4Add);
}

// TODO Refactor rename to formInput()

/////////////////////////////////////////////////////////////////////////////
//
//  formInput()
//  @version    1.0 (28/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Display a form input (checkbox / radio)
//
//  @param      $strType    Input type ('checkbox' or 'radio')
//  @param      $strName    Input name
//  @param      $strID      Input ID
//  @param      $strClass   Input CSS class(es)
//  @param      $bChkval    Checked or not
//  @param      $strVal     Input value (radio)
//  @param      $strLabel   Label for input
//  @param      $bReadOnly  Read only or not
//
//  @return     string      The full HTML input string
//
/////////////////////////////////////////////////////////////////////////////

function form_input(string $strType, string $strName, ?string $strID = null, ?string $strClass = null, bool $bChkVal = false, ?string $strVal = null, ?string $strLabel = null, bool $bReadOnly = false) : string
{
    $strInput       =   '<input type="' . $strType . '" name="' . $strName . '" ';
    $strInput       .=  (is_null($strID) ? '' : ' ID="' . $strID . '" ');
    $strInput       .=  (is_null($strClass) ? '' : ' CLASS="' . $strClass . '" ');
    $strInput       .=  ($bChkVal ? ' CHECKED ' : '');
    if ($strType == 'radio')
        $strInput   .=  ' VALUE="'. (is_null($strVal) ? '' : $strVal) . '" ';
    $strInput       .=  ($bReadOnly ? ' READONLY ' : '');
    $strInput       .= '>';
    
    // Add label
    $strInput .= (is_null($strLabel) ? '' : '<label for="' . $strID . '">' . $strLabel . '</label>' . PHP_EOL);
    
    return($strInput);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getCallingFunction()
//  @version    1.0 (28/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Get the name of the function which called the current function
//
//  @return     string  Name of the function called
//
/////////////////////////////////////////////////////////////////////////////

function getCallingFunction() : string
{
    return(debug_backtrace()[1]['function']);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getCurrFileName()
//  @version    1.0 (28/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return file name and local path of current file
//
//  @return     string
//
//  EXAMPLE     getCurrFileName()
//  RETURNS     '/var/www/httpdocs/index.php'
//
/////////////////////////////////////////////////////////////////////////////

function getCurrFilename() : string
{
    return($_SERVER['SCRIPT_FILENAME']);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getCurrPage()
//  @version    1.0 (28/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return current page
//
//  @param      $bPath          Include full remote path
//  @param      $bQueryString   Include trailing query string
//
//  @return     string
//
//  EXAMPLE     getCurrPage()
//  RETURNS     'index.php';
//
//  ExAMPLE     getCurrPage($bPath: true'
//  RETURNS     '/servervars/index.php'
//
//  EXAMPLE     getCurrPage($bPath: false, $bQueryString: true)
//  RETURNS     'index.php?VAR1=val1&VAR2=val2'
//
/////////////////////////////////////////////////////////////////////////////

function getCurrPage(bool $bPath = false, bool $bQuerystring = false) : string
{
    $strCurrPage = $bPath ? $_SERVER['PHP_SELF'] : pathinfo($_SERVER['PHP_SELF'], PATHINFO_BASENAME);
    $strCurrPage .= $bQuerystring ? '?' . $_SERVER['QUERY_STRING'] : '';
    return($strCurrPage);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getCurrQueryString()
//  @version    1.0 (28/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return current trailing query string
//
//  @return     string
//
//  EXAMPLE     getCurrQueryString()
//  RETURNS     'VAR=val&VAR2=val2&VAR#=val3'
//
/////////////////////////////////////////////////////////////////////////////

function getCurrQueryString() : string
{
    return($_SERVER['QUERY_STRING']);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getCurrURL()
//  @version    1.0 (28/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return current URL
//
//  @param      $bScheme        Include server request scheme (htp:// or https://)
//  @param      $bQueryString   Include trailing query string
//
//  @return     string
//
//  EXAMPLE     getCurrURL($bScheme: true, $bQueryString: true);
//  RETURNS     'https://domain.com/servervars/index.php?VAR1=var1'
//
/////////////////////////////////////////////////////////////////////////////

function getCurrURL(bool $bScheme = false, bool $bQuerystring = true) : string
{
    return(($bScheme ? $_SERVER['REQUEST_SCHEME'] . '://' : '') . $_SERVER['HTTP_HOST'] .
        getCurrPage(true, $bQuerystring)
    );
}

// TODO Replaced by Intl::getCurrSymsFromStr()

//////////////////////////////////////////////////////////////////////////////
//
//  getCurrSyms()
//
//  Return currency symbols from currency value
//
//  $str            Currency value string
//  $bWithSpaces    Return symbols with spaces or not
//
//  Returns
//      Currency symbols as a string
//
//  Examples
//      getCurrSyms('$50,000')          :   '$'
//      getCurrSyms('50,000 €')         :   '€'
//      getCurrSyms('50,000 €', true)   :   ' €'
//      getCurrSyms('AU$ 50,000', true) :   'AU$ '
//
//////////////////////////////////////////////////////////////////////////////

function getCurrSyms(string $strCurr, bool $bWithSpaces = false) : string
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

// TODO Replaced by Intl::getDecimalVal()

/////////////////////////////////////////////////////////////////////////////
//
//  getDecimal()
//  @version    1.0 (28/06/2023)
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
//  getFileExt()
//  @version    1.0 (29/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Get just the file extension
//
//  @param      string  $strFileName    File name, with or without path,
//
//  @return     string
//
//  EXAMPLE     getFileExt('/www/httpdocs/lib.incl')
//  RETURNS     '.incl'
//
/////////////////////////////////////////////////////////////////////////////

function getFileExt(string $strFileName) : string
{
    return(pathinfo($strFileName, PATHINFO_EXTENSION));
}

/////////////////////////////////////////////////////////////////////////////
//
//  getFileName()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Get file name with, or without, exension from full file path
//
//  @param      string  $strFullPath    Full path of file and folder
//  @param      bool    $bNoExt         Return file name without extension
//
//  @return     string
//
//  EXAMPLE     getFileName('/dev/testing/example.php')
//  RETURNS     'example.php'
//
//  EXAMPLE     getFileName('/www/index.html', true)
//  RETURNS     'index'
//
/////////////////////////////////////////////////////////////////////////////

function getFileName(string $strFullPath, bool $bNoExt = false) : string
{
    return(
    pathinfo(
        $strFullPath,
        $bNoExt ? PATHINFO_FILENAME : PATHINFO_BASENAME)
    );
}

/////////////////////////////////////////////////////////////////////////////
//
//  getFilePath()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Get full directory path from full file path
//
//  @param      string  $strFullPath    Full path of file and folder
//  @param      bool    $bTrailSep      Return trailing separator at end of path
//
//  @return     string
//
//  EXAMPLE     getFilePath('/dev/testing/example.php')
//  RETURNS     '/dev/testing'
//
//  EXAMPLE     getFileName('/www/index.html', true)
//  RETURNS     '/www/'
/////////////////////////////////////////////////////////////////////////////

function getFilePath(string $strFullPath, bool $bTrailSep = false) : string
{
    return(
        pathinfo($strFullPath, PATHINFO_DIRNAME) .
        ($bTrailSep ? '/' : '')
    );
}

// TODO Replaced by getFilePath()

//////////////////////////////////////////////////////////////////////////////
//
// getFolder()
//
//  Return folder, removing file name and extension, from full file path
//
//  $strFullFile    Full path of file and folder
//                  EXAMPLE: /dev/testing/example.php
//
//  $strSep         Folder separator
//                  DEFAULT: '/'
//
//  $bTrail         Return with trailing separator
//                  DEFAULT: true
//
//////////////////////////////////////////////////////////////////////////////

function getFolder(string $strFullFile, string $strSep = '/', bool $bTrail = true) : string
{
    $strFolder = substr($strFullFile, 0, strrpos($strFullFile, $strSep));
    
    $strFolder .= ($bTrail ? $strSep : '');
    
    return($strFolder);
}

// TODO Replaced by getFilePath()

//////////////////////////////////////////////////////////////////////////////
//
// getFullFilePath()
//
//  Return file name and path with document root folder
//
//////////////////////////////////////////////////////////////////////////////

function getFullFilePath(string $strFName) : string
{
    // Add Full Path if necessary
    if (!hasURLFolderWithin($strFName, $_SERVER['DOCUMENT_ROOT']))
        $strFName = $_SERVER['DOCUMENT_ROOT'] . '/' . $strFName;
    
    return($strFName);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getPrevURL()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Get the full URL of the previous (referring) page/site
//
//  @return     string
//
/////////////////////////////////////////////////////////////////////////////

function getPrevURL() : string
{
    return($_SERVER['HTTP_REFERER'] ?? '/');
}

//////////////////////////////////////////////////////////////////////////////
//
//  getRandomString()
//
//  Generate a random string
//
//  $length     Length of string to create
//  $keyspace   String of all possible characters
//
//	RETURNS
//      Random string
//
//////////////////////////////////////////////////////////////////////////////

// TODO Find usage

//////////////////////////////////////////////////////////////////////////////
//
// getMultilineString()
//
// Replace LF/NL with <br>
//
//  $strMultiline  string to be searched
//
////////////////////////////////////////////////////////////////////////////////

function getMultilineString(string $strMultiline) : string
{
    $strMultiline = str_replace(PHP_EOP, '<br>', $strMultiline);
    $strMultiline = str_replace(PHP_EOL, '<br>', $strMultiline);
    return($strMultiline);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getRandomString()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Generate a random string
//
//  @param      int     $iLen       Length of string to generate
//  @param      bool    $bNumns     Include numbers in string (default: true)
//  @param      bool    $bLetters   Include letters in string (default: true)
//  @param      bool    $bPunct     Includ punctuation in string (default: true)
//  @param      bool    $bMixCase   Mix uppercase and lowercase in string (default: true)
//
//  @return     string  Generated string
//
/////////////////////////////////////////////////////////////////////////////

function getRandomString(int $iLen, bool $bNums = true, bool $bLetters = true, bool $bPunct = true, bool $bMixCase = true) : string
{
    $strKey = ''; $strRandom = '';
    if ($bNums)
        $strKey .= '0123456789';
    if ($bLetters)
        $strKey .= 'abcdefghijklmnopqrstuvwxyz';
    if ($bPunct) {
        for ($strCh = 32; $strCh <= 126; $strCh++) {
            if (ctype_punct(chr($strCh)))
                $strKey .= chr($strCh);
        }
    }
    
    $iKeyLen = strlen($strKey) -1;
    
    // Generate random string
    for ($i = 0; $i < $iLen; ++$i) {
        $iRandom = random_int(0, $iKeyLen);
        $strChar = $strKey[$iRandom];
        if ($bMixCase && isEven($iRandom))
            $strRandom .= strtoupper($strChar);
        else
            $strRandom .= $strChar;
    }
    
    return($strRandom);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getStrBoolOrNull()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return null if string is blank or null
//  Return the string, converted to a boolean, if it is neither blank nor null
//
//  @param      ?string $str    String to be analyzed
//
//  @return     ?bool           Bool or null
//
/////////////////////////////////////////////////////////////////////////////

function getStrBoolOrNull(?string $str) : ?bool
{
    return(isEmpty($str) ? null : boolval($str));
}

/////////////////////////////////////////////////////////////////////////////
//
//  getStrFloatOrNull()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return null if string is blank or null
//  Return the string, converted to a Float, if it is neither blank nor null
//
//  @param      ?string $str    String to be analyzed
//
//  @return     ?float          Float or null
//
/////////////////////////////////////////////////////////////////////////////

function getStrFloatOrNull(?string $str) : ?float
{
    return(isEmpty($str) ? null : floatval($str));
}

/////////////////////////////////////////////////////////////////////////////
//
//  getStrIntOrNull()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return null if string is blank or null
//  Return the string, converted to a Int, if it is neither blank nor null
//
//  @param      ?string $str    String to be analyzed
//
//  @return     ?int            Int or null
//
/////////////////////////////////////////////////////////////////////////////

function getStrIntOrNull(?string $str) : ?int
{
    return(isEmpty($str) ? null : intval($str));
}

/////////////////////////////////////////////////////////////////////////////
//
//  getStrStrOrNull()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return null if string is blank or null
//  Return the string if it is neither blank nor null
//
//  @param      ?string $str    String to be analysed
//
//  @return     ?string         String or null
//
/////////////////////////////////////////////////////////////////////////////

function getStrOrNull(?string $str) : ?string
{
    return(isEmpty($str) ? null : $str);
}

/////////////////////////////////////////////////////////////////////////////
//
//  getStringUpToChar()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return string up to specific character
//
//  @param      string  $str    String to be analysed
//  @param      string  $char   Character to be searched for
//
//  @return     string
//
/////////////////////////////////////////////////////////////////////////////

function getStringUpToChar(string $str, string $char) : string
{
    // Get position of character in string
    $pos = strpos($str, $char);
    
    // If char not found return full string
    if ($pos === false)
        return($str);
    
    return(substr($str, 0, $pos));
}

/////////////////////////////////////////////////////////////////////////////
//
//  hastPassword()
//  @version    1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return propterly hashed password string
//
//  @param      string  $strPass    Password to be hashed
//
//  @return     string              Hashed password string
//
/////////////////////////////////////////////////////////////////////////////

function hashPassword(string $strPass) : string
{
    return(password_hash($strPass, PASSWORD_DEFAULT));
}

//////////////////////////////////////////////////////////////////////////////
//
//  hasURLFolderWithin()
//  Version 1.0 (23/05/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Test if a folder in the URL contains a folder within its path
//
//  @param          string  $strURL         Full URL path
//  @param          string  $strFolder      Folder to search for
//  @param          bool    $bNoAccents
//
//  @return         bool
//
//////////////////////////////////////////////////////////////////////////////

function hasURLFolderWithin(string $strURL, string $strFolder, bool $bNoAccents = false) : bool
{
    return(
    strContains(strtolower($strURL), strtolower($strFolder), $bNoAccents)
    );
}

//////////////////////////////////////////////////////////////////////////////
//
//  isBlank()
//  Version 1.3 (30/01/2024)
//  @copyright  2023-2024 © Derek Erb Solutions (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Test if string is blank
//
//  @param          string  $strBlank   string to be tested
//                  bool    $bSp        optional test for a single space
//                                      or a lone line feed (ASCII 10)
//
//  @return         bool
//
//////////////////////////////////////////////////////////////////////////////

function isBlank(string $strBlank, bool $bSp = false) : bool
{
    // is string empty?
    if (strlen($strBlank) === 0)
        return(true);
    
    // if string is not empty
    if ($bSp) {
        // test for simple space or lf (linefeed)
        return ($strBlank === ' ') || (ord($strBlank) == 10);
    }
    
    return(false);
}

//////////////////////////////////////////////////////////////////////////////
//
//  isCookie()
//  Version 1.0 (08/03/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Test if cookie is set or not
//
//  @param          string  $strCookie  Cookie to be tested
//
//  @return         bool
//
//////////////////////////////////////////////////////////////////////////////

function isCookie(string $strCookie) : bool
{
    return(isset($_COOKIE[$strCookie]));
}

// TODO Rename to isCookiesEnabled()

//////////////////////////////////////////////////////////////////////////////
//
//  isCookiesEnabled()
//  Version 1.0.1 (28/06/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Are cookies enabled?
//
//  @return         bool
//
//////////////////////////////////////////////////////////////////////////////

function isCookiesEnabled() : bool
{
    return(count($_COOKIE) > 0);
}

//////////////////////////////////////////////////////////////////////////////
//
//  isDecimal()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Is there any value after the decimal separator
//
//  @return         bool
//
//  EXAMPLE         isDecimal(42.765)
//  RETURNS         true
//
//  EXAMPLE         isDecimal(42)
//  RETURNS         false
//////////////////////////////////////////////////////////////////////////////

function isDecimal(float $fVal) : bool
{
    return(floor($fVal) != $fVal);
}

// TODO Rename oddEven() to isEven()

//////////////////////////////////////////////////////////////////////////////
//
//  isEmpty()
//  Version 1.0 (30/01/2024)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Test if string is blank or null
//  [REFACTOR of previously named isBlankOrNull]
//
//  @param          string  $strBlank   string to be tested
//                  bool    $bSp        optional test for a single space
//
//  @return         bool
//
//////////////////////////////////////////////////////////////////////////////

function isEmpty(?string $strBlank, bool $bSp = false) : bool
{
    if (is_null($strBlank))
        return(true);
    
    return(isBlank($strBlank, $bSp));
}

//////////////////////////////////////////////////////////////////////////////
//
//  isEven()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Is value even? (if not then odd)
//
//  @param      int $iVal   Value to be tested
//
//  @return     bool
//
//  EXAMPLE     isEven(5)
//  RETURNS     false
//
//  EXAMPLE     isEven(4)
//  RETURNS     true
//////////////////////////////////////////////////////////////////////////////

// REFACTOR RENAME
// function OddEven(int $iVal) : bool
function isEven(int $iVal) : bool
{
    return($iVal %2 == 0);
}

/////////////////////////////////////////////////////////////////////////////
//
//  isFirstCharVowel()
//  @version    1.0 (15/01/2024)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Is the first character in the string a vowel or vowel sound
//
//  @param      string  $str    String to be tested
//
//  EXAMPLE     isFirstCharVowel('hôtel');
//  RETURNS     TRUE
//
/////////////////////////////////////////////////////////////////////////////

function isFirstCharVowel(string $str) : bool
{
    return(preg_match('/ˆ[aeiouh]/', strtolower($str)));
}

//////////////////////////////////////////////////////////////////////////////
//
//  isImageFile()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Test if file exstension is in the list of known image file extensions
//
//  @return         bool
//
//  EXAMPLE         isImageFile('image.jpg')
//  RETURNS         true
//
//  EXAMPLE         isImageFile('image.mov')
//  RETURNS         false
//////////////////////////////////////////////////////////////////////////////

function isImageFile(string $strFName) : bool
{
    $arrImageExts = array('.gif', '.jpeg', '.jpg', '.png', '.webp',);
    
    $strFExt = strtolower(getFileExt($strFName));
    
    return(in_array($strFExt, $arrImageExts));
}

//////////////////////////////////////////////////////////////////////////////
//
//  isSecure()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Test if running over https or not
//
//  @return         bool
//
//////////////////////////////////////////////////////////////////////////////

function isSecure() : bool
{
    if (isset($_SERVER['HTTPS'])) {
        if (!empty($_SERVER['HTTPS'] && $_SERVER['HTTPS'] !== 'off')) {
            return(true);
        }
    }
    
    return(false);
}

//////////////////////////////////////////////////////////////////////////////
//
//  isVideoFile()
//  Version 1.0.1 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Test if file exstension is in the list of known video file extensions
//
//  @return         bool
//
//  EXAMPLE         isImageFile('image.jpg')
//  RETURNS         false
//
//  EXAMPLE         isImageFile('image.mov')
//  RETURNS         true
//////////////////////////////////////////////////////////////////////////////

function isVideoFile(string $strFName) : bool
{
    $arrVidExts = array('.avi', '.mkv', '.m4v', '.mov', '.mp4', '.wmv', '.webm',);
    
    $strFExt = strtolower(getFileExt($strFName));
    
    return(in_array($strFExt, $arrVidExts));
}

//////////////////////////////////////////////////////////////////////////////
//
//  lowerNoAccents()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Return the string all lowercase and with no accents
//
//  @param      string  $str    string to be analysed
//
//  @return     string          string converted to lowercase with no accents
//
//////////////////////////////////////////////////////////////////////////////

function lowerNoAccents(string $str) : string
{
    return(
    strtolower(
        strTrim(
            preg_replace('~[^0-9a-z]+~i', '-', preg_replace('~&([a-z]{1,2})(acute|cedil|circ|grave|lig|orn|ring|slash|th|tilde|uml);~i', '$1', htmlentities($str, ENT_QUOTES, 'UTF-8'))
            ), ' ')
    )
    );
}

//////////////////////////////////////////////////////////////////////////////
//
//  lzPad()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Add leading zeroes to pad number (as string) to desired width
//
//  @param      string  $strNum     Number to be padded
//  @param      int     $iWidth     Width of desired string after padding
//
//  @return         string          String with leading padded zeros
//
//////////////////////////////////////////////////////////////////////////////

function lzPad(string $strNum, int $iWidth) : string
{
    return(
    str_pad($strNum, $iWidth, '0', STR_PAD_LEFT)
    );
}

//////////////////////////////////////////////////////////////////////////////
//
//  newTab()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Open URL in a new tab in browser (using injected JavaScript)
//
//  @param      string  $strURL     URL to be opened in new tab
//
//////////////////////////////////////////////////////////////////////////////

function newTab(string $strURL) : void
{
    echo('<script>' . PHP_EOL);
    echo('window.open("' . $strURL . '","_blank")' . PHP_EOL);
    echo('</script>' . PHP_EOL);
}

//////////////////////////////////////////////////////////////////////////////
//
//  pregMatch()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  preg_match() wrapper to test for, and all, null in subject
//
//  @param      string  $strPattern Pattern to search for
//  @param      string  $strSubject String to be searched
//  @param      array   $arrMatches Array to contain pattern results
//
//  @return     int
//////////////////////////////////////////////////////////////////////////////

function pregMatch(string $strPattern, ?string $strSubject, array &$arrMatches = null) : int
{
    if (is_null($strSubject))
        return(false);
    
    return(preg_match($strPattern, $strSubject, $arrMatches));
}

//////////////////////////////////////////////////////////////////////////////
//
//  radioBtn()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Use formInput() to output a properly formatted form radio button
//
//  @param      string  $strName    Radio button name
//  @param      string  $strVal     Radio button value
//  @param      string  $strID      Radio button ID
//  @param      string  $strClass   Radio button CSS class(es)
//  @param      bool    $bChkval    Checked or not
//  @param      string  $strLabel   Radio button label
//  @param      bool    $bReadOnly  Read only or not
//
//  @return     string      The full HTML input string
//////////////////////////////////////////////////////////////////////////////

function radioBtn(string $strName, string $strVal, ?string $strID = null, ?string $strClass = null, bool $bChkVal = false, ?string $strLabel = null, $bReadOnly = false) : string
{
    return(form_input('radio', $strName, $strID, $strClass, $bChkVal, $strVal, $strLabel, $bReadOnly));
}

//////////////////////////////////////////////////////////////////////////////
//
//  readCookie()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Get cookie value or null
//
//  @param      $strCookie  Nmae of cookie
//
//  @return     ?string     Cookie value or null
//////////////////////////////////////////////////////////////////////////////

function readCookie(string $strCookie) : ?string
{
    return($_COOKIE[$strCookie] ?? null);
}

// TODO replaced by Intl->getDateTimeShortStr();

//////////////////////////////////////////////////////////////////////////////
//
//  readDate()
//
//  $strDate    Date string (YYYY-MM-DD)
//
//  $strDtFmt
//      'WD'    World 'd/m/YYYY' (DEFAULT)
//      'US'    American 'm/d/YYYY'
//      'SQ'    SQL 'YYYY-m-d'
//
//  $yDigits    Number of digits for year (default: 4)
//
//  Returns date string in preferred date format
//
//////////////////////////////////////////////////////////////////////////////

function readDate(string $strDate, int $iYDigits = 4, string $strDtFmt = 'WD') : string
{
    $strFmt = match($strDtFmt) {
        'US'    =>  'm/d/Y',
        'SQ'    =>  'Y-m-d',
        default =>  'd/m/Y',
    };
    
    // lowercase Y = 2 digits for year
    if ($iYDigits != 4)
        $strFmt = strtolower($strFmt);
    
    return(date_format(date_create($strDate), $strFmt));
}

// TODO replaced by Intl->getDateTimeShortStr();

//////////////////////////////////////////////////////////////////////////////
//
//  readDateTime()
//
//  $strDT      DateTime string (YYYY-MM-DD HH:MM:SS)
//
//  $strDtFmt
//      'US'    American 'm/d/Y h:i A' (DEFAULT)
//      'WD'    World 'd/m/Y H:i'
//      'SQ'    SQL 'Y-m-d H;i'
//
//  Returns date and time string in preferred date format
//
//////////////////////////////////////////////////////////////////////////////

function readDateTime(string $strDT, string $strDtFmt = 'WD') : string
{
    $strFmt = match($strDtFmt) {
        'US'    =>  'm/d/Y h:i A',
        'SQ'    =>  'Y-m-d H:i',
        default =>  'd/m/Y H:i',
    };
    
    return(date_format(date_create($strDT), $strFmt));
}

// TODO continue refactoring here

// TODO Add and Move to Intl class

//////////////////////////////////////////////////////////////////////////////
//
//  readFullDate()
//
//  $strDate    Date string (YYYY-MM-DD)
//
//  $strDtFmt
//      'US'    American 'F jS, Y' (DEFAULT)
//      'WD'    World 'jS F, Y'
//
//  $bDay       Include day of the week or not
//
//  Returns full date string in preferred date format
//
//////////////////////////////////////////////////////////////////////////////

function readFullDate(string $strDate, string $strDtFmt = 'WD', bool $bDay = false) : string
{
    // Day of week
    $strFmt = $bDay ? 'l, ' : '';
    
    $strFmt .= match($strDtFmt) {
        'US'    =>  'F jS, Y',
        default =>  'jS F, Y',
    };
    
    return(date_format(date_create($strDate), $strFmt));
}

// TODO Add and move to Intl class

//////////////////////////////////////////////////////////////////////////////
//
//  readFullDateTime()
//
//  $strDT      DateTime string (YYYY-MM-DD HH:MM:SS)
//
//  $strDtFmt
//      'US'    American 'm/d/Y h:i A' (DEFAULT)
//      'WD'    World 'd/m/Y H:i'
//
//
//  $bDay       Include day of the week or not
//
//  Returns full date and time string in preferred date format
//
//////////////////////////////////////////////////////////////////////////////

function readFullDateTime(string $strDT, string $strDtFmt = 'WD', bool $bDay = false) : string
{
    // Day of week
    $strFmt = $bDay ? 'l, ' : '';
    
    $strFmt .= match($strDtFmt) {
        'US'    =>  'F jS, Y g:i a',
        default =>  'jS F, Y H:i',
    };
    
    return(date_format(date_create($strDT), $strFmt));
}

// TODO replaced by Intl->getDateTimeShortStr();

//////////////////////////////////////////////////////////////////////////////
//
//  readTime()
//
//  $strTime    Time string (HH:MM:SS)
//
//  $strDtFmt
//      'US'    American 'h:i A' (DEFAULT)
//      'WD'    World 'H:i'
//      'SQ'    SQL 'H:i'
//
//  Returns time string in preferred date format
//
//////////////////////////////////////////////////////////////////////////////

function readTime(string $strTime, string $strDtFmt = 'WD') : string
{
    $strFmt = match($strDtFmt) {
        'US'    =>  'h:i A',
        default =>  'H:i',
    };
    
    return(date_format(date_create($strTime), $strFmt));
}

//////////////////////////////////////////////////////////////////////////////
//
// redirect()
//
// Redirect to web address
//
//  strURL  Web address to redirect to
//          NULL = root
//  iRedirect   Redirect code to pass
//              301 Permanent redirection
//              302 Temporary redirection (DEFAULT)
//              303 Temporary redirection v1.1
//              307 Temporary redirection v1.1
//              308 Permanent redirection v1.1
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//  redirect()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Redirect to web address
//
//  @param      ?string $strURL     Web address to redirect to (null = root)
//  @param      int     $iRedirect  Redirect code to pass (default: 302)
//                                  301 Permanent redirection
//                                  302 Temporary redirection (DEFAULT)
//                                  303 Temporary redirection v1.1
//                                  307 Temporary redirection v1.1
//                                  308 Permanent redirection v1.1
//////////////////////////////////////////////////////////////////////////////

function redirect(?string $strURL = null, int $iRedirect = 302) : void
{
    $strURL = $strURL ?? '/';
    $strVer = $iRedirect > 302 ? '1.1' : '1.0';
    
    $strHeader = 'HTTP/' . $strVer . ' ' . $iRedirect . ' Redirect';
    
    header($strHeader);
    header('Location: ' . $strURL);
}

//////////////////////////////////////////////////////////////////////////////
//
// remCookie()
//
// ALIAS for delCookie()
//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//  remCookier()
//  Version 1.0 (10/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  ALIAS for delCookie()
//////////////////////////////////////////////////////////////////////////////

function remCookie(string $strCookie) : bool
{
    return(delCookie($strCookie));
}

// TODO Refactor rename to getIPv4Add()

//////////////////////////////////////////////////////////////////////////////
//
//  getIPv4Add()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Get non-zero padded IPv4 address as X.X.X.X
//
//  @param  string $strZeroIPAdd    zero-padded IPv4 address
//
//  @return string                  Non-zero-padded IPv4
//
//  EXAMPLE getIPv4Add('255.255.000.000')
//  RETURNS '255.255.0.0'
//
//  EXAMPLE getIPv4Add('010.000.000.001');
//  RETURNS '10.0.0.1'
//////////////////////////////////////////////////////////////////////////////

function retIPv4Add(string $strZeroIPAdd) : string
{
    
    // Break up IPv4 zero-padded in to an array of 4 integers
    $arrIP = array( substr($strZeroIPAdd, 0, 3),
                    substr($strZeroIPAdd, 4, 3),
                    substr($strZeroIPAdd, 8, 3),
                    substr($strZeroIPAdd, 12, 3),
    );
    
    $strAddIP = '';
    foreach($arrIP as $val) {
        $val = intval($val, 10);
        $strAddIP .= $val . '.';
    }
    $strAddIP = substr($strAddIP, 0, strlen($strAddIP)-1);
    
    return($strAddIP);
}

// TODO Refactor rename to remFileExt()

//////////////////////////////////////////////////////////////////////////////
//
//  remFileExt()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Remove the file name extension
//
//  @param  string $strFileName     Full file name with extension to be removed
//
//  @return string                  File name without extension
//
//  EXAMPLE remFileExt('index.html');
//  RETURNS 'index'
//
//  EXAMPLE remFileExt('/incl/Site.incl');
//  RETURNS '/incl/Site'
//////////////////////////////////////////////////////////////////////////////

function rmvFileExt(string $strFileName) : string
{
    return(
    substr($strFileName, 0, strrpos($strFileName, '.'))
    );
}

//TODO Find somewhere these are used and find out why!

//////////////////////////////////////////////////////////////////////////////
//
// roundDown($rnd, $Downto)
//
// Round Down to the nearest $Downto integer
//
//  $rnd    Number to be rounded
//  $Downto   Nearest integer to be rounded Down to
//
//////////////////////////////////////////////////////////////////////////////

function roundDown(float $fRnd, int $iDownTo) : int
{
    return floor($fRnd / $iDownTo) * $iDownTo;
}

//////////////////////////////////////////////////////////////////////////////
//
// roundUp($rnd, $upto)
//
// Round up to the nearest $upto integer
//
//  $rnd    Number to be rounded
//  $upto   Nearest integer to be rounded up to
//
//////////////////////////////////////////////////////////////////////////////

function roundUp(float $fRnd, int $iUpTo) : int
{
    return ceil($fRnd / $iUpTo) * $iUpTo;
}

//////////////////////////////////////////////////////////////////////////////
//
//  showCookie()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  DEBUG FUNCTION: Echo individual cookie value for debugging
//
//  @param  string  $strCookie  Cookie value to be shown
//////////////////////////////////////////////////////////////////////////////

function showCookie(string $strCookie) : void
{
    echo($strCookie . ' : ' . ($_COOKIE[$strCookie] ?? 'NOT SET') . '<br>' . PHP_EOL);
}

//////////////////////////////////////////////////////////////////////////////
//
//  strContains()
//  Version 1.0 (09/08/2023)
//  @copyright  2023 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
//  Does string contain another string?
//
//  @param  string  $strHaystack        String to be searched
//  @param  string  $strNeedle          String being searched for (containment)
//  @param  bool    $bNoAccents         With or without accents in both string comparisons (default: false)
//  @param  bool    $bCaseInsensitive   Case insensitive or not (default: false)
//
//  @return bool                        String is contained within haystack string or not
//////////////////////////////////////////////////////////////////////////////

function strContains(string $strHaystack, string $strNeedle, bool $bNoAccents = false, bool $bCaseInsensitive = false) : bool
{
    if ($bNoAccents) {
        $strHaystack    = lowerNoAccents($strHaystack);
        $strNeedle      = lowerNoAccents($strNeedle);
    }
    elseif ($bCaseInsensitive) {
        $strHaystack    = strtolower($strHaystack);
        $strNeedle      = strtolower($strNeedle);
    }
    
    return(
        mb_strpos(
            haystack: $bNoAccents   ?   lowerNoAccents($strHaystack)    :   $strHaystack,
            needle: $bNoAccents     ?   lowerNoAccents($strNeedle)      :   $strNeedle,
            offset: 0,
            encoding: 'UTF-8')
        !== false
    );
}

// $Needs a comma separated list or an array
// $bOR  Haystack can contain ANY of the Needles passed
// !$bOR Haystack must contain ALL of the Needles passed
function strContainsMultiple(string $strHaystack, array | string $Needles, bool $bOR = false, bool $bNoAccents = false, bool $bCaseInsensitive = false) : bool
{
    if (is_string($Needles)) {
        $arrNeedles = explode(',', $Needles);
    }
    else
        $arrNeedles = $Needles;
    
    $bCheck = true;
    foreach($arrNeedles as $strNeedle) {
        if (strContains($strHaystack, $strNeedle, $bNoAccents, $bCaseInsensitive)) {
            // found one (or = true)
            if ($bOR)
                return (true);
        }
        else {
            // one was not found (and = false)
            if (!$bOR)
                return (false);
        }
    }
    return(false);
}

// TODO Refactor rename to getStrEnd();

//////////////////////////////////////////////////////////////////////////////
//
//  getStrEnd()
//  Version 1.0 (08/03/2023)
//
//  Returns the last X characters from a string
//
//  @param          string  $strString  String to be analysed
//                  int     $iChars     Number of characters to be returned
//
//  @return         string
//
//////////////////////////////////////////////////////////////////////////////

function strEnd(string $strString, int $iChars) : string
{
    return(substr($strString, -$iChars));
}

//////////////////////////////////////////////////////////////////////////////
//
// strEndsWith()
//
//  Test is string end with text
//
//  $haystack   String to search
//  $needle     String to search for
//
//////////////////////////////////////////////////////////////////////////////

function strEndsWith(string $strHaystack, string $strNeedle) : bool
{
    // search forward starting from end minus needle length characters
    return(
        $strNeedle === "" || (($temp = strlen($strHaystack) - strlen($strNeedle)) >= 0 && mb_strpos($strHaystack, $strNeedle, $temp, 'UTF-8') !== FALSE)
    );
}

//////////////////////////////////////////////////////////////////////////////
//
// strFileExt()
//
//  Get file extension (after last .)
//
//////////////////////////////////////////////////////////////////////////////

function strFileExt(string $strFileName, bool $bWithDot = false) : string
{
    $iLeft = ($bWithDot ? 0 : 1);
    return(strRemoveLeft(strrchr($strFileName, '.'), $iLeft));
}


function strMid(string $strString, int $iPos, int $iChars) : string
{
    return(substr($strString, $iPos, $iChars));
}

//////////////////////////////////////////////////////////////////////////////
//
// strPS($strTxt, $iCtr)
//
//  String plural or singular
//
//  $strTxt         String to be pluralised
//  $iCtr           Number of values (0 or > 1 = plural else singular)
//  $bPrecludeCtr   Show the number before the string
//
//////////////////////////////////////////////////////////////////////////////

// TODO replaced by Intl getPS

function strPS(string $strTxt, int $iCtr, bool $bPrecludeCtr = false) : string
{
    $strTxt = ($bPrecludeCtr ? $iCtr . ' ' . $strTxt : $strTxt);
    return($iCtr == 1 ? $strTxt : $strTxt . 's');
}

//////////////////////////////////////////////////////////////////////////////
//
// strRemoveLeft()
//
//  Remove $i number of characters from the left of $str
//
//  Returns string with characters removed
//
//  $str    String to remove characters from
//  $i      Number of characters to remove
//
//////////////////////////////////////////////////////////////////////////////

function strRemoveLeft(string $strString, int $i) : string
{
    $iLen = strlen($strString);
    
    if ($i > $iLen)
        return('');
    
    return(substr($strString, $i, $iLen-$i));
}

//////////////////////////////////////////////////////////////////////////////
//
// strRemoveRight()
//
//  Remove $i number of characters from the right of $str
//
//  Returns string with characters removed
//
//  $str    String to remove characters from
//  $i      Number of characters to remove
//
//
//////////////////////////////////////////////////////////////////////////////

function strRemoveRight(string $strString, int $i) : string
{
    
    $iLen = strlen($strString);
    
    if ($i > $iLen)
        return('');
    
    return(substr($strString, 0, $iLen-$i));
}

//////////////////////////////////////////////////////////////////////////////
//
// strRepHTML
//
//  Replaces characters with HTML character entities
////
//  Returns string with characters replaced
//
//  $str    String to replace characters in
//
//////////////////////////////////////////////////////////////////////////////

function strRepHTML(string $strString) : string
{
    $strString = str_replace('<', '&lt;', $strString);
    $strString = str_replace('>', '&gt;', $strString);
    
    return($strString);
}

//////////////////////////////////////////////////////////////////////////////
//
// strReplace
//
//  Replaces all instances of characters in a string
//
//  Returns string with characters replaced
//
//  $strNeedle      String being searched for
//  $strReplace     Replacement string
//  $strHaystack    String to be searched
//
//////////////////////////////////////////////////////////////////////////////

function strReplace(string $strNeedle, string $strReplace, ?string $strHaystack) : ?string
{
    return(is_null($strHaystack) ? null : str_replace($strNeedle, $strReplace, $strHaystack));
}

//////////////////////////////////////////////////////////////////////////////
//
// strServer()
//
//	RETURNS
//      Server name, all lowercase, stripped of www.
//
//////////////////////////////////////////////////////////////////////////////

function strServer() : string
{
    
    $StrServer = strtolower($_SERVER['SERVER_NAME']);
    $StrServer = (strStartsWith($StrServer, 'www.') ? strRemoveLeft($StrServer, 4) : $StrServer);
    
    return($StrServer);
}

// TODO Refactor rename to getStrStart()

//////////////////////////////////////////////////////////////////////////////
//
//  strStart()
//  Version 1.0 (08/03/2023)
//
//  Returns the first X characters from a string
//
//  @param          string  $strString  String to analyse
//                  int     $iChars     Number of characters to return
//
//  @return         string
//
//////////////////////////////////////////////////////////////////////////////

function strStart(string $strString, int $iChars) : string
{
    return(substr($strString, 0, $iChars));
}

//////////////////////////////////////////////////////////////////////////////
//
// strStartsWith()
//
//  Test if string starts with text
//
//  $haystack   String to search
//  $needle     String to search for
//
//////////////////////////////////////////////////////////////////////////////

function strStartsWith(string $strHaystack, string $strNeedle) : bool
{
    // search backwards starting from haystack length characters from the end
    return(
        $strNeedle === "" || strrpos($strHaystack, $strNeedle, - strlen($strHaystack)) !== FALSE
    );
}

function strTrim(?string $strTrim, ?string $strChars = null) : ?string
{
    if (is_null($strTrim))
        return null;
    
    if (is_null($strChars))
        return(trim($strTrim));
    
    return(trim($strTrim, $strChars));
}

//////////////////////////////////////////////////////////////////////////////
//
// strUTFLower() & strUTFUpper()
//
//  Change case of string with UTF-8 character set
//
//////////////////////////////////////////////////////////////////////////////

function strUTFLower(string $str) : string
{
    return(mb_strtolower($str, 'UTF-8'));
}

function strUTFUpper(string $str) : string
{
    return(mb_strtoupper($str, 'UTF-8'));
}

//////////////////////////////////////////////////////////////////////////////
//
// t($rep)
//
//  Repeat PHP_TAB
//
//  $rep        Number of repetitions
//
//////////////////////////////////////////////////////////////////////////////

function t(int $iRep) : void
{
    for ($i = 0; $i < $iRep; $i++) {
        echo(PHP_TAB);
    }
}

function tabs(int $iRep) : void
{
    t($iRep);
}

//////////////////////////////////////////////////////////////////////////////
//
//  DEBUG
//
//  fullErrors()
//
//  Display verbose error information
//
////////////////////////////////////////////////////////////////////////////////

function fullErrors() : void
{
    ini_set('display_errors', 1);
    ini_set('html_errors', 0);
    error_reporting(-1);
}

//////////////////////////////////////////////////////////////////////////////
//
//  DEBUG
//
//  showDebug()
//
//  echo debug info in separate div
//
////////////////////////////////////////////////////////////////////////////////

function showDebug(?string $strDebug, bool $bErr = false) : void
{
    $strClass = 'debug' . ($bErr ? ' debug_err' : '');
    echo('<div class="' . $strClass . '">');
        if (is_null($strDebug))
            echo(t(1) . 'NULL');
        else
            echo(t(1) . $strDebug);
    echo('</div>' . PHP_EOL);
}

