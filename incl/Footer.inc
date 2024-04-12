<?php

//////////////////////////////////////////////////////////////////////////////
//
//  Footer Class
//  Version 1.0
//
//////////////////////////////////////////////////////////////////////////////
    
class Footer extends Site
{
    protected ?array    $arrJScriptFiles    =   null;
    //////////////////////////////////////////////////////////////////////////////
    //
    //  setJScriptFiles()
    //
    //  $arrJScriptFiles    Either a comma-delimited list of JavaScript file names
    //                      or a pre-declared array of JavaScript file names
    //
    //  Add additional JavaScript files to the header
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function setJScriptFiles(string $JScriptFiles) : void
    {
        $this->arrJScriptFiles = explode(',', $JScriptFiles);
    }
    
    //////////////////////////////////////////////////////////////////////////////
    //
    // write()
    //
    // Output site page footer
    //
    //////////////////////////////////////////////////////////////////////////////
    
    function write() : void
    {
        $SBC = new SBC();
        
        //////////////////////////////////////////////////////////////////////////////
        // Footer
        //////////////////////////////////////////////////////////////////////////////
        
        echo(t(1) . PHP_EOL . '<!-- *** FOOTER *** -->' . PHP_EOL);
        echo(t(1) . '<footer>' . PHP_EOL);
            echo(t(2) . $SBC->getSiteTitle() . '<br>' . PHP_EOL);
            echo(t(2) . 'Version ' . parent::VER_NUM . '<br>' . PHP_EOL);
            
            echo(t(2) . '<address>' . PHP_EOL);
            
            echo(t(2) . '</address>' . PHP_EOL);
        echo(t(1) . '</footer>' . PHP_EOP);
        
        //////////////////////////////////////////////////////////////////////////////
        // JavaScript
        //////////////////////////////////////////////////////////////////////////////
        
        // Additional Javascript files
        if (!is_null($this->arrJScriptFiles)) {
            foreach($this->arrJScriptFiles as $strJScriptFile) {
                $strJS = Site::JS_DIR . $strJScriptFile;
                if (file_exists($this->getPath() . $strJS))
                    echo(t(1) . '<script src="' . $strJS . '"></script>'. PHP_EOL);
            }
        }
        
        echo('</body>' . PHP_EOL . PHP_EOL);
        echo('</html>' . PHP_EOL);
    }
}

