<?php

require_once($_SERVER['DOCUMENT_ROOT'] . '/incl/sysfuns.inc');

error_reporting(E_ALL);

$strLang = Site::getLang();

$SBC = new SBC();

$Head = new Head();
$Head->addCSSFile('about.css');
$Head->write();
$SBC->writeHeader();
$Nav = new Nav();
$Nav->write('About');

// Description
echo(t(1) .'<section id="about">' . PHP_EOL);
if ($strLang === 'fr') {
    echo(t(2) . '<h2>A propos de nous</h2>' . PHP_EOP);
    
    echo(t(2) . '<div id="explanation1">' . PHP_EOL);
        echo(t(3) . '<h3>Qu’est-ce que c’est un club de lecture silencieuse ?</h3>' . PHP_EOL);
        echo(t(3) . '<p>C’est un club pour lecteurs pas forcément extravertis. Amenez un libre et peut-être un ami.
        Puis mettez-vous à l’aise pour une heure de lecture silencieuse avec d’autres amateurs de livres.
        Il n’y a ni livre obligatoire ni sujets de discussions prédéfinis. C’est justement ça la partie « silencieuse ».
        Mais on aime partager des recommandations de livres et rencontrer d’autres lecteurs comme nous !</p>' . PHP_EOP);
        
        echo(t(3) . '<p>Tous les lecteurs sont les bienvenus y compris les lecteurs d’eBooks et de livres audios.</p>' . PHP_EOP);
        
        echo(t(3) . '<p>Vous pouvez en apprendre plus sur les Silent Book Clubs sur <a href="https://silentbook.club" translate="no" lan="en">leur site web</a> <span class="lang">(en anglais)</span>.</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Pourquoi en ligne seulement ?</h3>' . PHP_EOL);
        echo(t(3) . '<p>Je voulais commencer avec la possibilité la plus rapide et la plus facile à mettre en place pour voir comment ça marche.
        Si tout se passe comme prévu, je suis sûr qu’on va se retrouver avec un mélange des réunions en ligne et d’autres en présentiel
        dans un café ou un bar ou une librairie C’est pas ça qui manque à Paris…<p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Comment ça marche ?</h3>' . PHP_EOL);
        echo(t(3) . '<p>On se réunit, en ligne, toutes les deux semaines :</p>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
    
    echo(t(2) . '<div id="schedule">' . PHP_EOL);
        echo(t(3) . '<div class="times">19h00 – 19h30</div>' . PHP_EOL);
        echo(t(3) . '<div class="events">Introductions et présentations (qui est qui et qui lit quoi)</div>' . PHP_EOL);
        echo(t(3) . '<div class="times">19h30 – 20h30</div>' . PHP_EOL);
        echo(t(3) . '<div class="events">Lecture silencieuse <em>les micros sont coupées</em></div>' . PHP_EOL);
        echo(t(3) . '<div class="times">20h30 – 21h00…</div>' . PHP_EOL);
        echo(t(3) . '<div class="events">Discussion générale (optionnelle) ou continuez votre lecture</div>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
    
    echo(t(2) . '<div id="explanation2">' . PHP_EOL);
        echo(t(3) . '<p>Pour l’instant j\'utilises <a href="https://zoom.us">Zoom</a> pour nos réunions en ligne.</p>' . PHP_EOP);
        
        echo(t(3) . '<p>Caméra coupée et / ou microphone coupé sont acceptées.</p>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
}
else {
    echo(t(2) . '<h2>What we’re about</h2>' . PHP_EOP);
    
    echo(t(2) . '<div id="explanation">' . PHP_EOL);
        echo(t(3) . '<h3>What is a <span class="SBC">Silent Book Club</span>?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . '<span class="SBC">Silent Book Club</span> is happy hour for introverts. Bring a book and maybe bring a friend.
                Then settle in for an hour of quiet reading with fellow book lovers - that\'s the <em>silent</em> 
                part of our club.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Who reads what?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'Unlike most book clubs there is no assigned reading. Everyone reads whatever they 
                want. We are here to read for our pleasure so we read what we want. It can be any genre:' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);

        echo(t(3) . '<ul>' . PHP_EOL);
            echo(t(4) . '<li>fiction,</li>' . PHP_EOL);
            echo(t(4) . '<li>non-fiction,</li>' . PHP_EOL);
            echo(t(4) . '<li>sci-fi,</li>' . PHP_EOL);
            echo(t(4) . '<li>fantasy,</li>' . PHP_EOL);
            echo(t(4) . '<li>romance,</li>' . PHP_EOL);
            echo(t(4) . '<li>thrillers,</li>' . PHP_EOL);
            echo(t(4) . '<li>crime,</li>' . PHP_EOL);
            echo(t(4) . '<li>anything, ...</li>' . PHP_EOL);
        echo(t(3) . '</ul>' . PHP_EOL);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'It does not have to be a book. We have had readers reading all sorts:' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<ul>' . PHP_EOL);
            echo(t(4) . '<li>text books,</li>' . PHP_EOL);
            echo(t(4) . '<li>newsletters,</li>' . PHP_EOL);
            echo(t(4) . '<li>online listings,</li>' . PHP_EOL);
            echo(t(4) . '<li>...</li>' . PHP_EOL);
        echo(t(3) . '</ul>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We accept all formats with no judgement:' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<ul>' . PHP_EOL);
            echo(t(4) . '<li>paper books,</li>' . PHP_EOL);
            echo(t(4) . '<li>comic books, </li>' . PHP_EOL);
            echo(t(4) . '<li>graphic novels, </li>' . PHP_EOL);
            echo(t(4) . '<li>newspapers, </li>' . PHP_EOL);
            echo(t(4) . '<li>magazines, </li>' . PHP_EOL);
            echo(t(4) . '<li>eBooks, </li>' . PHP_EOL);
            echo(t(4) . '<li>audio books, </li>' . PHP_EOL);
            echo(t(4) . '<li>anything, ...</li>' . PHP_EOL);
        echo(t(3) . '</ul>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'If you\'re interested in the concept and the origins you can learn more about <a href="https://silentbook.club" translate="no" lang="en"><span class="SBC">Silent Book Clubs</span></a>' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Why English-language?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'I wanted to have two different groups for two different discussions. This is the
                English-language group where we discuss in English. You can read text in any language you want. But our
                discussions are in English. I also manage the <a href="https://clubdelecturesilencieuse.paris" translate="no" lang="fr">Club de Lecture Silencieuse Paris</a> <em>(en français)</em>.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We have several participants for whom English is not their first language. Our sessions
                are a great place to practice English language conversation as you can particpate as much or as little
                as you want.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Why online-only?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'I wanted to start with the easiest and quickest way possible to see how all of this works and what the interest may be.
                If everything evolves as planned, I\'m sure we\'ll eventually find ourselves with a mixture of online sessions and in-person sessions at a
                café or bar or bookstore. They should not be that difficult to find here in Paris.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>How does it work?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We meet once every two weeks:' . PHP_EOP);
        echo(t(3) . '</p>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
    
    echo(t(2) . '<div class="schedule">' . PHP_EOL);
        echo(t(3) . '<div class="times"><time datetime="19:00">19:00</time> - <time datetime="19:30">19:30</time></div>' . PHP_EOL);
        echo(t(3) . '<div class="event">Introductions and general discussions of who\'s reading what</div>' . PHP_EOL);
        echo(t(3) . '<div class="event">We note down what each reader is reading (title, author, format, ...) for our session summaries and reading lists');
        echo(t(3) . '<div class="times"><time datetime="19:30">19:30</time> - <time datetime="20:30">20:30</time></div>' . PHP_EOL);
        echo(t(3) . '<div class="event">Quiet Reading Hour <em>(all microphones muted)</em></div>' . PHP_EOL);
        echo(t(3) . '<div class="times"><time datetime="20:30">20:30</time> - <time datetime="21:00">21:00+</time></div>' . PHP_EOL);
        echo(t(3) . '<div class="event">Optional socialising and general discussion or keep reading.</div>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
    
    echo(t(2) . '<div id="explanations">' . PHP_EOL);
        echo(t(3) . '<p id="explanation2">' . PHP_EOL);
            echo(t(4) . 'Depending on the number of participants we often go overtime on the pre-reading discussions
                and sometimes on the post-reading discussions. But we always leave a full hour for reading no matter what.
                For the post-reading discussions some of us have other things to do, or other responsibilities, or hunger
                on a weeknight. You can leave the sessions at any time with no judgement and no guilt. We are happy
                you participated.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    
        echo(t(3) . '<p id="explanation3">' . PHP_EOL);
            echo(t(4) . 'I am currently using <a href="https://zoom.us">Zoom</a> for our online sessions.
                But I am open to all possibilities.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'I currently record each of our sessions, and you will hear a notification whenever
            you join one of our sessions. However these recordings are for internal use only. I rewatch our sessions
            when I create the session summaries so as to not have to take notes during our sessions. These
            recordings are never shared or published.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    
        echo(t(3) . '<p id="explanation4">' . PHP_EOL);
            echo(t(4) . 'Cameras and/or microphones are optional. Text-only chat is also possible.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Session Summaries</h3>' . PHP_EOL);
        echo(t(3) . '<p' . PHP_EOL);
            echo(t(4) . 'We create a summary after each session with the reading list of what was read, a summary of our discussions with relevant links to more information.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We publish the summary on our various social network accounts and we distribute directly to our newsletter subscribers.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
}
echo(t(1) . '</section>' . PHP_EOP);

$Footer = new Footer();
$Footer->write();
