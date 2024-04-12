<?php

require_once($_SERVER['DOCUMENT_ROOT'] . '/incl/sysfuns.inc');

error_reporting(E_ALL);

$strLang = Site::getLang();

$SBC = new SBC();

$Head = new Head();
$Head->write();

$SBC->writeHeader();

// Description
    if (($SBC->getSite() !== SiteCode::EN) && ($SBC->getSite() !== SiteCode::FR)) {
        echo(t(1) .'<section id="about">' . PHP_EOL);
            echo(t(2) . 'GENERIC BILINGUAL TEXT HERE');
        echo(t(1) . '</section>' . PHP_EOP);
    }
    else {
        if ($SBC->getSite() === SiteCode::FR) {
            echo(t(1) .'<section id="about">' . PHP_EOL);
                echo('<h2>A propos de nous</h2>' . PHP_EOP);
                
                echo('<h3>Le Club de Lecture Silencieuse Paris</h3>' . PHP_EOL);
                
                echo('<h4>Qu’est-ce que c’est un club de lecture silencieuse ?</h4>' . PHP_EOL);
                echo('<p>C’est un club pour lecteurs pas forcément extravertis. Amenez un libre et peut-être un ami.
                Puis mettez-vous à l’aise pour une heure de lecture silencieuse avec d’autres amateurs de livres.
                Il n’y a ni livre obligatoire ni sujets de discussions prédéfinis. C’est justement ça la partie « silencieuse ».
                Mais on aime partager des recommandations de livres et rencontrer d’autres lecteurs comme nous !</p>' . PHP_EOP);
                
                echo('<p>Tous les lecteurs sont les bienvenus y compris les lecteurs d’eBooks et de livres audios.</p>' . PHP_EOP);
                
                echo('<p>Vous pouvez en apprendre plus sur les Silent Book Clubs sur <a href="https://silentbook.club">leur site web</a> <span class="lang">(en anglais)</span>.</p>' . PHP_EOP);
                
                echo('<h4>Pourquoi en ligne seulement ?</h4>' . PHP_EOL);
                echo('<p>Je voulais commencer avec la possibilité la plus rapide et la plus facile à mettre en place pour voir comment ça marche.
                Si tout se passe comme prévu, je suis sûr qu’on va se retrouver avec un mélange des réunions en ligne et d’autres en présentiel
                dans un café ou un bar ou une librairie C’est pas ça qui manque à Paris…<p>' . PHP_EOP);
                
                echo('<h4>Comment ça marche ?</h4>' . PHP_EOL);
                echo('<p>On se réunit, en ligne, toutes les deux semaines :</p>' . PHP_EOL);
                
                echo('<div class="schedule">' . PHP_EOL);
                echo('<div class="times">19h00 – 19h30</div>' . PHP_EOL);
                echo('<div class="events">Introductions et présentations (qui est qui et qui lit quoi)</div>' . PHP_EOL);
                echo('<div class="times">19h30 – 20h30</div>' . PHP_EOL);
                echo('<div class="events">Lecture silencieuse <em>les micros sont coupées</em></div>' . PHP_EOL);
                echo('<div class="times">20h30 – 21h00…</div>' . PHP_EOL);
                echo('<div class="events">Discussion générale (optionnelle) ou continuez votre lecture</div>' . PHP_EOL);
                echo('</div>' . PHP_EOP);
                
                echo('<p>Pour l’instant j\'utilises <a href="https://zoom.us">Zoom</a> pour nos réunions en ligne.</p>' . PHP_EOP);
                
                echo('<p>Caméra coupée et / ou microphone coupé sont acceptées.</p>' . PHP_EOL);
            echo(t(1) . '</section>' . PHP_EOP);

            // Newsletter
            echo(t(1) . '<section id="newsletter">' . PHP_EOL);
                echo('<h2>Newsletter</h2>' . PHP_EOL);
            echo(t(1) . '</section>' . PHP_EOP);
            
            echo(t(1) . '<section id="socialmedia">' . PHP_EOL);
                echo('<h2>Réseaux Sociaux</h2>');
                echo('<ul>' . PHP_EOL);
                    echo('<li>X (Twitter)</li>' . PHP_EOL);
                    echo('<li>Facebook</li>' . PHP_EOL);
                    echo('<li>Instagram</li>' . PHP_EOL);
                    echo('<li>Meetup</li>' . PHP_EOL);
                    echo('<li>Good Reads</li>' . PHP_EOL);
                echo('</ul>' . PHP_EOL);
            echo(t(1) . '</section>' . PHP_EOP);
            
            
            // Session Summaries
            echo(t(1) . '<section id="summaries">' . PHP_EOL);
                echo('<h2>Résumés des Sessions</h2>' . PHP_EOL);
            echo(t(1) . '</section>' . PHP_EOP);
        }
        else {
            echo(t(1) .'<section id="about">' . PHP_EOL);
                echo('<h2>What we’re about</h2>' . PHP_EOP);
                
                echo('<h3>The English language Silent Book Club in Paris, France</h3>' . PHP_EOP);
                
                echo('<h4>What is a Silent Book Club?</h4>' . PHP_EOL);
                echo('<p>Silent Book Club is happy hour for introverts. Bring a book and maybe bring a friend.
                Then settle in for an hour of quiet reading with fellow book lovers - that\'s the "silent" part of our club.
                There\'s no assigned reading. Everyone reads whatever they want.
                But we do like to share book recommendations and meet like-minded readers.</p>' . PHP_EOP);
                
                echo('<p>While some silent reading parties have a strict <em>No Talking!</em> rule, no one will be shushed or shamed at our
                Silent Book Club. All readers are welcome including eReaders and audio book listeners.</p>' . PHP_EOP);
                
                echo('<p>If you\'re interested in the concept and the origins you can learn more about <a href="https://silentbook.club">Silent Book Clubs</a></p>' . PHP_EOP);
                
                echo('<h4>Why English-language?</h4>' . PHP_EOL);
                echo('<p>I wanted to have two different groups for two different discussions. This is the English-language group where we discuss in English
                while we read books in whatever language we want. I also manage a <a href="https://clubdelecturesilencieuse.paris">French-language Silent Book Club</a>.</p>' . PHP_EOL);
                
                echo('<h4>Why online-only?</h4>' . PHP_EOL);
                echo('<p>I wanted to start with the easiest and quickest way possible to see how all of this works and what the interest may be.
                If everything evolves as planned, I\'m sure we\'ll eventually find ourselves with a mixture of online meetings and in-person meetings at a
                café or bar or bookstore. They\'re not that difficult to find here in Paris...</p>' . PHP_EOP);
                
                echo('<h4>How does it work?</h4>' . PHP_EOL);
                echo('<p>We meet once every two weeks:</p>' . PHP_EOP);
                
                echo('<div class="schedule">' . PHP_EOL);
                    echo('<div class="times">19:00 - 19:30</div>' . PHP_EOL);
                    echo('<div class="event">Introductions and general discussions of who\'s reading what</div>' . PHP_EOL);
                    echo('<div class="times">19:30 - 20:30</div>' . PHP_EOL);
                    echo('<div class="event">Quiet Reading Hour <em>(all microphones muted)</em></div>' . PHP_EOL);
                    echo('<div class="times">20:30 - 21:00+</div>' . PHP_EOL);
                    echo('<div class="event">Optional socialising and general discussion ... or keep reading.</div>' . PHP_EOL);
                echo('</div>' . PHP_EOP);
                
                echo('<p>I am currently using <a href="https://zoom.us">Zoom</a> for our online meetings. But I am open to all possibilities...</p>' . PHP_EOL);
                
                echo('<p>Cameras and/or microphones are optional. Text-only chat is also possible.</p>' . PHP_EOL);
            echo(t(1) . '</section>' . PHP_EOP);
            
            // Newsletter
            echo(t(1) . '<section id="newsletter">' . PHP_EOL);
                echo('<h2>Newsletter</h2>' . PHP_EOL);
            echo(t(1) . '</section>' . PHP_EOP);
            
            echo(t(1) . '<section id="socialmedia">' . PHP_EOL);
                echo('<h2>Social Media</h2>');
                echo('<ul>' . PHP_EOL);
                    echo('<li>X (Twitter)</li>' . PHP_EOL);
                    echo('<li>Facebook</li>' . PHP_EOL);
                    echo('<li>Instagram</li>' . PHP_EOL);
                    echo('<li>Meetup</li>' . PHP_EOL);
                    echo('<li>Good Reads</li>' . PHP_EOL);
                echo('</ul>' . PHP_EOL);
            echo(t(1) . '</section>' . PHP_EOP);
        }
        
        // Session Summaries
        echo(t(1) . '<section id="summaries">' . PHP_EOL);
            echo('<h2>Session Summaries</h2>' . PHP_EOL);
        echo(t(1) . '</section>' . PHP_EOP);
    }
$Footer = new Footer();
$Footer->write();
