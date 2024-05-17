# Sujet de programmation impérative

#La page du sujet :

https://www.labri.fr/perso/renault/working/teaching/projets/2023-24-S6-C-Carcassonne.php

#La page sur thor :

https://thor.enseirb-matmeca.fr/ruby/projects/pr105-carc

#Le rapport :

https://www.overleaf.com/5585327627tpxqnfgvfzbw#9c24b4

#La complilation :

Pour compliler les tests,il faut lancer l'une des commandes suivantes dans la racine:
            
            make test
        ou
            make alltests

Pour compliler les bibliothèques dynamiques,lancez:
            
            make client

Pour compiler l'ensemble du code sans les tests,lancez:
            
            make build
        
#L'exécution:

            ./install/server ./install/libplayer1.so ./install/libplayer2.so

Pour visualiser le graphe aprés éxecution :

     	make show