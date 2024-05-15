<?php

/////////////////////////////////////////////////////////////////////////////
//
//  ABOUT       index
//  @version    1.0 (13/05/2024)
//  @copyright  2024 © Derek Erb Solutions      (https://derekerb.solutions)
//  @author     Derek Erb Solutions             (https://derekerb.solutions)
//
/////////////////////////////////////////////////////////////////////////////

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
    echo(t(2) . '<div id="explanation">' . PHP_EOL);
        echo(t(3) . '<h2>C\'est quoi un <span class="SBC">club de lecture silencieuse</span> ?</h2>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "C’est un club pour lecteurs pas forcément extravertis. Amenez un livre et peut-être un ami.
            Puis mettez-vous à l’aise pour une heure de lecture silencieuse avec d’autres amateurs de livres - ça c\'est
            la partie <em>silencieuse</em> de notre club." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Qui lit quoi ?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "Contrairement à la plupart des clubs on ne lit pas tous le même livre. On est ici
            pour lire pour notre plaisir alors on lit ce qu'on veut. Il n'y a jamais de jugement et surtout pas de culpabilité.
            On peut lire n'importe de quel genre :" . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<ul>' . PHP_EOL);
            echo(t(4) . '<li>fiction,</li>' . PHP_EOL);
            echo(t(4) . '<li>sci-fi,</li>' . PHP_EOL);
            echo(t(4) . '<li>fantasie,</li>' . PHP_EOL);
            echo(t(4) . '<li>romance,</li>' . PHP_EOL);
            echo(t(4) . '<li>polars</li>' . PHP_EOL);
            echo(t(4) . '<li>thrillers,</li>' . PHP_EOL);
            echo(t(4) . '<li>non-fiction,</li>' . PHP_EOL);
            echo(t(4) . '<li>biographies et autobiographies,</li>' . PHP_EOL);
            echo(t(4) . '<li>philosophie,</li>' . PHP_EOL);
            echo(t(4) . '<li>sciences humaines,</li>' . PHP_EOL);
            echo(t(4) . '<li>essais,</li>' . PHP_EOL);
            echo(t(4) . "<li>livres scolaires,</li>" . PHP_EOL);
            echo(t(4) . '<li>newsletters,</li>' . PHP_EOL);
            echo(t(4) . '<li>documentation technique,</li>' . PHP_EOL);
            echo(t(4) . '<li>tout, ...</p>' . PHP_EOL);
        echo(t(3) . '</ul>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "On peut lire tous les formats et sans jugement :" . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<ul>' . PHP_EOL);
            echo(t(4) . "<li>livres papiers,</li>" . PHP_EOL);
            echo(t(4) . "<li>comics,</li>" . PHP_EOL);
            echo(t(4) . "<li>bandes-dessinées</li>" . PHP_EOL);
            echo(t(4) . "<li>romans graphiques,</li>" . PHP_EOL);
            echo(t(4) . "<li>journaux,</li>" . PHP_EOL);
            echo(t(4) . "<li>magazines,</li>" . PHP_EOL);
            echo(t(4) . "<li>livres electroniques (<em>eBooks</em>),</li>" . PHP_EOL);
            echo(t(4) . '<li>livres web,</li>' . PHP_EOL);
            echo(t(4) . "<li>livres audios,</li>" . PHP_EOL);
            echo(t(4) . "<li>tout, ...</p>" . PHP_EOL);
        echo(t(3) . '</ul>' . PHP_EOP);
    
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "Vous pouvez en apprendre plus sur les Silent Book Clubs sur
            <a href=\"https://silentbook.club\" translate=\"no\" lang=\"en\" title=\"Silent Book Club website\" target=\"_blank\" rel=\"noreferrer\">leur site web</a>
            <span class=\"lang\">(en anglais)</span>." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    
        echo(t(3) . '<h3>Pourquoi en français ?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "J'ai deux clubs différents pour deux discussions différentes. Celui-ci est le club français où nous discutons en français. On peut
                lire dans la langue qu'on veut. Mais nos discussions sont en français. J'organise aussi le
                <a href=\"https://englishsilentbookclub.paris\" translate=\"no\" lang=\"en\"
                title=\"English Silent Language Book Club website\" target=\"_blank\" rel=\"noreferrer\">English Silent Language Book Club</a>
                <span class=\"lang\">en anglais</span></em>." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Pourquoi en ligne seulement ?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "On voulait commencer avec la possibilité la plus rapide et la plus facile à mettre en place pour voir comment ça marche." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "Quand on sera plus régulièrement assez nombreux alors on pourra se retrouver avec un mélange des réunions en ligne et
                d'autres en présentiel dans un café ou un bar ou une librairie. C'est pas ça qui manque à Paris." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Comment ça marche ?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "On se réunit, en ligne, toutes les deux semaines :" . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    echo(t(2) . '</div>' . PHP_EOP);
    
    echo(t(2) . '<div class="schedule">' . PHP_EOL);
        echo(t(3) . '<div class="times"><time datetime="19:00">19h00</time> – <time datetime="19:30">19h30</time></div>' . PHP_EOL);
        echo(t(3) . '<div class="event">Introductions et présentations (qui est qui et qui lit quoi)</div>' . PHP_EOL);
        echo(t(3) . '<div class="event">On note ce que chaque lecteur va lire (titre, auteur, format, langue, ...)
                            pour mettre dans nos comptes-rendus et nos listes de lecture</div>' . PHP_EOL);
        echo(t(3) . '<div class="times"><time datetime="19:30">19h30</time> – <time datetime="20:30">20h30</time></div>' . PHP_EOL);
        echo(t(3) . '<div class="event">Lecture silencieuse <em>tous les micros sont coupés</em></div>' . PHP_EOL);
        echo(t(3) . '<div class="times"><time datetime="20:30">20h30</time> – <time datetime="21:00">21h00+</time></div>' . PHP_EOL);
        echo(t(3) . '<div class="event">Discussion générale (optionnelle) ou continuez votre lecture</div>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
    
    echo(t(2) . '<div id="explanations">' . PHP_EOL);
        echo(t(3) . '<p id="explanation2">' . PHP_EOL);
            echo(t(4) . "Caméra coupée et / ou microphone coupé sont acceptés. C'est aussi possible de participer uniquement dans le tchat." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);

        echo(t(3) . '<p id="explanation3">' . PHP_EOL);
            echo(t(4) . "Selon le nombre de participants on peut dépasser l'horaire prévu pour les discussions pré-lectures et parfois pour les discussions
                post-lectures. Mais on laisse toujours une heure complète pour notre lecture silencieuse quoi qu'il arrive. Pour les discussions post-lectures il y en
                a parmi nous qui ont d'autres choses à faire, ou d'autres responsabilités, ou on a faim (un soir de semaine). Vous pouvez toujours quitter les séances
                à n'importe de quel moment sans aucun jugement et sans aucune culpabilité. On est toujours content que vous ayez participé" . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p id="explanation4">' . PHP_EOL);
            echo(t(4) . "Pour l’instant on utilise <a href=\"https://zoom.us\" target=\"_blank\" rel=\"noreferrer\">Zoom</a> pour nos réunions en ligne.</p>" . PHP_EOP);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "On enregistre chacune de nos séances et vous entendrez une notification quand vous entrez dans nos séances. On revisionne nos séances
                pour faire nos comptes-rendus pour ne pas être obligé de prendre des notes pendant nos séances. Les enregistrements ne sont jamais
                partagés ou publiés." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Comptes-rendus des séances</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "On établi un compte-rendu après chaque séance avec la liste de ce qui a été lu et un résumé de nos discussions avec des
                des liens vers plus d'info." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "On publie le compte-redu sur nos comptes sur les réseaux sociaux et on les envoie directement aux abonnés de notre
                <a href=\"https://desol.link/cdlsparisnews\" title=\"notre page de newsletter\" target=\"_blank\" rel=\"noreferrer\">newsletter</a>." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    echo(t(2) . '</div>' . PHP_EOP);
}
else {
    echo(t(2) . '<div id="explanation">' . PHP_EOL);
        echo(t(3) . '<h2>What is a <span class="SBC">Silent Book Club</span>?</h2>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . '<span class="SBC">Silent Book Club</span> is happy hour for introverts. Bring a book and maybe bring a friend.
                Then settle in for an hour of quiet reading with fellow book lovers - that\'s the <em>silent</em> 
                part of our club.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Who reads what?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "Unlike most book clubs we don't all read the same book. We are here to read for our personal pleasure so we read whatever we want.
                There is no judgement here and certainly no guilt. We can read any genre:" . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);

        echo(t(3) . '<ul>' . PHP_EOL);
            echo(t(4) . '<li>fiction,</li>' . PHP_EOL);
            echo(t(4) . '<li>sci-fi,</li>' . PHP_EOL);
            echo(t(4) . '<li>fantasy,</li>' . PHP_EOL);
            echo(t(4) . '<li>romance,</li>' . PHP_EOL);
            echo(t(4) . '<li>thrillers,</li>' . PHP_EOL);
            echo(t(4) . '<li>crime,</li>' . PHP_EOL);
            echo(t(4) . '<li>non-fiction,</li>' . PHP_EOL);
            echo(t(4) . "<li>biographies and autobiographies,</li>" . PHP_EOL);
            echo(t(4) . "<li>philosophy,</li>" . PHP_EOL);
            echo(t(4) . '<li>text books,</li>' . PHP_EOL);
            echo(t(4) . '<li>newsletters,</li>' . PHP_EOL);
            echo(t(4) . '<li>technical documentation,</li>' . PHP_EOL);
            echo(t(4) . '<li>anything, ...</li>' . PHP_EOL);
        echo(t(3) . '</ul>' . PHP_EOL);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We can read any format with no judgement:' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<ul>' . PHP_EOL);
            echo(t(4) . '<li>paper books,</li>' . PHP_EOL);
            echo(t(4) . '<li>comic books, </li>' . PHP_EOL);
            echo(t(4) . '<li>graphic novels, </li>' . PHP_EOL);
            echo(t(4) . '<li>newspapers, </li>' . PHP_EOL);
            echo(t(4) . '<li>magazines, </li>' . PHP_EOL);
            echo(t(4) . '<li>eBooks, </li>' . PHP_EOL);
            echo(t(4) . '<li>web books</li>' . PHP_EOL);
            echo(t(4) . '<li>audio books, </li>' . PHP_EOL);
            echo(t(4) . '<li>anything, ...</li>' . PHP_EOL);
        echo(t(3) . '</ul>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'If you\'re interested in the concept and the origins you can learn more about
                <a href="https://silentbook.club" title="Silent Book Clubs website" translate="no" lang="en" target="_blank" rel=\"noreferrer\"><span class="SBC">Silent Book Clubs</span></a>' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Why English-language?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We wanted to have two different groups for two different discussions. This is the
                English-language group where we discuss in English. You can read text in any language you want. But our
                discussions are in English. I also manage the
                <a href="https://clubdelecturesilencieuse.paris"
                title="Club de lecture silencieuse Paris site web" translate="no" lang="fr" target="_blank" rel=\"noreferrer\">Club de Lecture Silencieuse
                Paris</a> <em>(en français)</em>.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We have several participants for whom English is not their first language. Our sessions
                are a great place to practice English language conversation as you can particpate as much or as little
                as you want.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<h3>Why online-only?</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "We wanted to start with the easiest and quickest way possible to see how all of this works and what the interest may be." . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . "When there will be enough of us, on a regular basis, we'll eventually find ourselves with a mixture of online sessions and in-person
                sessions at a café or bar or bookstore. They should not be that difficult to find here in Paris." . PHP_EOL);
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
            echo(t(4) . 'Cameras and/or microphones are optional. Text-only chat is also possible.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    
        echo(t(3) . '<p id="explanation3">' . PHP_EOL);
            echo(t(4) . 'Depending on the number of participants we often go overtime on the pre-reading discussions
                and sometimes on the post-reading discussions. But we always leave a full hour for reading no matter what.
                For the post-reading discussions some of us have other things to do, or other responsibilities, or hunger
                on a weeknight. You can leave the sessions at any time with no judgement and no guilt. We are happy
                you participated.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    
        echo(t(3) . '<p id="explanation4">' . PHP_EOL);
            echo(t(4) . 'We are currently using <a href="https://zoom.us" target="_blank" rel=\"noreferrer\">Zoom</a> for our online sessions.
                But we are open to all possibilities.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We currently record each of our sessions, and you will hear a notification whenever
            you join one of our sessions. However these recordings are for internal use only. We rewatch our sessions
            when we create the session summaries so as to not have to take notes during our sessions. These
            recordings are never shared or published.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
    
        echo(t(3) . '<h3>Session Summaries</h3>' . PHP_EOL);
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We create a summary after each session with the reading list of what was read and a summary of our discussions with relevant links
            to more information.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOP);
        
        echo(t(3) . '<p>' . PHP_EOL);
            echo(t(4) . 'We publish the summary on our various social network accounts and we distribute directly to our
                <a href="https://desol.link/esbcparisnews" title="Our newsletter page" target="_blank" rel=\"noreferrer\">newsletter</a> subscribers.' . PHP_EOL);
        echo(t(3) . '</p>' . PHP_EOL);
    echo(t(2) . '</div>' . PHP_EOP);
}
echo(t(1) . '</section>' . PHP_EOP);

$Contact = new Contact();
$Contact->write();

$Footer = new Footer();
$Footer->write();
