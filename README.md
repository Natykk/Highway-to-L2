# ProjetL2 : Highway to L2

Bienvenue dans le README pour notre projet type roguelike en SDL2 nommé "Highway to L2". 

## Introduction

Ce projet est un roguelike développé en C à l'aide de la bibliothèque SDL2. Un roguelike est un type de jeu de rôle dans lequel le joueur explore des donjons, combat des monstres, trouve des trésors, etc. Les roguelikes sont connus pour leur difficulté élevée et leur génération procédurale de niveaux, ce qui signifie que chaque fois que vous jouez, vous rencontrez un nouveau donjon avec des ennemis et des objets différents. Le but de ce projet est de créer un roguelike jouable et amusant.

## Installation

Pour compiler et exécuter ce projet, vous aurez besoin de la bibliothèque SDL2 et des ces extension image,ttf,mixer ainsi que de la librairie OPENSSL. Vous pouvez les installer en utilisant votre gestionnaire de paquets système préféré. Sur Debian/Ubuntu, vous pouvez utiliser les commande suivante :

SDL2 : ``` sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev ```
OPENSSL : ``` sudo apt-get install libssl-dev `


Une fois que vous avez installé les dépendances, vous pouvez compiler le projet en exécutant la commande ```make``` dans le répertoire racine du projet 

## Utilisation

Une fois que vous avez compilé le projet, vous pouvez l'exécuter en exécutant la commande suivante à partir du répertoire bin :

```
./jeu
```

Le jeu est contrôlé avec les touches fléchées et ZQSD. Vous pouvez vous déplacer dans les quatre directions et attaquer les ennemis adjacents.Les enemis tué vous font gagner des items et en appuyant sur la touche «TAB» vous pouvez voir les items récupéré actuellement dans votre inventaire. Le jeu se termine lorsque vous êtes mort ou que vous avez atteint le dernier niveau.

## Fonctionnalités

Le projet comporte les fonctionnalités suivantes :

- Génération de niveaux procéduraux
- Déplacement du joueur
- Ennemis qui suivent le joueur et attaquent le joueur lorsqu'ils sont adjacents
- Combat entre le joueur et les ennemis
- Arbre de compétence avec 4 classes 

## Contributions

Les contributions à ce projet sont les bienvenues ! Si vous avez des idées d'amélioration ou des bugs à signaler, n'hésitez pas à créer une issue ou une pull request.
    
    
    
    
    
