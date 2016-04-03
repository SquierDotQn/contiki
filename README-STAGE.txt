Pour nous contacter :
Rémy Debue : remy.debue@etudiant.univ-lille1.fr
Théo Plockyn : theo.plockyn@etudiant.univ-lille1.fr

DEBUT =========================================

La VM InstantContiki possède déjà une version de Contiki OS plus récente, mais on peut faire cohabiter les deux, il suffit de : 

renommer le dossier ~/contiki déjà présent :
$ mv contiki/ new-contiki/

ou de créer un nouveau dossier :
$ mkdir sniffer; cd sniffer/

Ensuite :
$ git clone https://github.com/SquierDotQn/contiki.git ; cd contiki/ ; git checkout sniffer

Le code se trouve à l'emplacement contiki/examples/sniffer/sniffer.c

Pour le compiler 
contiki/examples/sniffer$ make TARGET=sky


COOJA =========================================

On peut utiliser n'importe quelle version de cooja, de la version récente ou plus ancienne de Contiki, parce que la compilation du code produit un fichier .sky qui peut être importé directement dans la simulation.

Le plus simple pour prendre en main cooja est de suivre les étapes du quickstart officiel de Contiki. http://www.contiki-os.org/start.html

Pour lancer cooja :
contiki$ cd tools/cooja; ant run &

Une fois la nouvelle simulation créée, une option pratique est d'activer les portées des ondes radio des motes, et pour faire ça, il faut aller dans le menu déroulant "View" de la fenêtre "Network" et activer "Radio environment". Pour voir les portées, il faut cliquer sur les motes de la simulation.

Pour créer la mote sniffer, c'est comme pour créer une mote en général, il suffit d'aller chercher dans le dossier contiki/examples/sniffer/ et prendre sniffer.sky, puis cliquer sur create. Il faut être sûr, cependant, que la mote est dans la portée d'autres motes pour sniffer le traffic radio.
