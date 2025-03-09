<?php

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS       Footer
//  @version    3.0 (09/03/2025)
//  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////
class Footer extends Site
{
    //////////////////////////////////////////////////////////////////////////////
    //
    //  write()
    //  Version 2.0 (09/03/2025)
    //  @copyright  2023-2025 © Derek Erb Solutions (https://derekerb.solutions)
    //  @author     Derek Erb Solutions             (https://derekerb.solutions)
    //
    //  Output page head
    //
    //  @param      array   $arrJScriptFiles    Array of additional JavaScript files
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function write(?array $arrJScriptFiles = null) : void
    {
        $SBC = new SBC();
        
        //////////////////////////////////////////////////////////////////////////////
        // Footer
        //////////////////////////////////////////////////////////////////////////////
        
        echo(t(1) . PHP_EOL . '<!-- *** FOOTER *** -->' . PHP_EOL);
        echo(t(1) . '<footer>' . PHP_EOL);
            echo(t(2) . getenv('SITE_TITLE') . '<br>' . PHP_EOL);
            echo(t(2) . 'Version ' . getenv('SITE_VER_NUM') . '<br>' . PHP_EOL);
            
            echo(t(2) . '<address>' . PHP_EOL);
            
            echo(t(2) . '</address>' . PHP_EOL);
        echo(t(1) . '</footer>' . PHP_EOP);
        
        //////////////////////////////////////////////////////////////////////////////
        // JavaScript
        //////////////////////////////////////////////////////////////////////////////
        
        // Additional Javascript files
        if (!is_null($arrJScriptFiles)) {
            foreach ($arrJScriptFiles as $strJScriptFile) {
                $strJS = getenv('SITE_JS_DIR') . $strJScriptFile;
                if (file_exists(getenv('SITE_PATH') . $strJS))
                    echo(t(1) . '<script src="' . $strJS . '"></script>' . PHP_EOL);
            }
        }
        
        echo('</body>' . PHP_EOL . PHP_EOL);
        echo('</html>' . PHP_EOL);
    }
}

