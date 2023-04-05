#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../head/competence.h"

t_competence cpt_assassin[NB_CPT]={
    //étage1:
    {non_acquis, "Frappe Rapide", "Cette compétence se concentre sur la rapidité d'attaque pour neutraliser rapidement la cible. Effet : Augmente la vitesse d'attaque.", {NO_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 2, NULL,NULL,1, 1},
    //étage2:
    {non_acquis, "Cotte de Maille", "Armure protégeant des petits dégats. Effet : Augmente les points de vie et légèrement la vitesse d'attaque.",  {MIDDLE_IMPROVE, NO_IMPROVE, SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 2, NULL, NULL, 2, 2},
    {non_acquis, "Cape d'Invisibilité","L'assassin possède à présent une cape lui permettant d'améliorer sa discrétion. Effet : Réduit grandement le périmètre de détection des mobs.",{NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE}, NULL, 1, NULL, 2, NULL, NULL, 2, 2},
    //étage3:
    {non_acquis, "Coup Perçant","L'assassin concentre son énergie dans la pointe de son arme pour assainer des dégats et aspirer de la vie à sa cible. Effet : Augmente les dégats, grandement la vitesse d'attaque et les points de vie.", {MIDDLE_IMPROVE, MIDDLE_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 3},
    {non_acquis, "Entaille Profonde","Cette compétence permet à l'assassin d'asséner des coup plus profond infligeant de gros dégats. Effet : Augmente grandement les dégats et la vitesse d'attaque.", {NO_IMPROVE, BIG_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 3},
    {non_acquis, "Silence Mortel", "Cette compétence améliore la capacité de l'assassin à se cacher ou à se dissimuler pour passer inaperçu. Effet : Réduit grandement le périmètre de détection des mobs, Augmente la vitesse de déplacement et légèrement la vitesse d'attaque.", {NO_IMPROVE,NO_IMPROVE,SMALL_IMPROVE,MIDDLE_IMPROVE,BIG_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 3},
    {non_acquis, "Marche de l'Ombre", "Cette compétence permet à l'assassin de se déplacer plus discrètement. Effet : Réduit grandement le périmètre de détection des mobs, Augmente la vitesse d'attaque et légèrement la vitesse de déplacement", {NO_IMPROVE,NO_IMPROVE,MIDDLE_IMPROVE,SMALL_IMPROVE,BIG_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL, 3, 3},
    //étage4:
    {non_acquis, "Bottes de Célérité","Cette compétence garantit à l'assassin une vitesse de déplacement supérieure. Effet : Augmente grandement la vitesse d'attaque et grandement la vitesse de déplacement.", {NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, BIG_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Bottes de Furtivité","L'assassin se chausse de bottes masquant le bruit de ses pas. Effet : Réduit énormement le périmètre de détection des mobs et Augmente la vitesse de déplacement.",{NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE, ULTRA_IMPROVE}, NULL, 2, NULL, 1, NULL, NULL,3, 4},
    //étage5: Compétence ultime
    {non_acquis, "Chatiment Fatal","L'assassin concentre toute son énergie dans son arme pour rendre chaque coup fatal. Effet : Augmente enormément les dégats, Augmente la furtivité et la vitesse d'attaque.",{NO_IMPROVE, ULTRA_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE}, NULL, 2, NULL, 0, NULL, NULL,3, 5},
};


t_competence cpt_mage[NB_CPT]={
    //étage1:
    {non_acquis, "Bâton de Magie Supérieure", "Le mage possède à présent un bâton de magie améliorant ses pouvoirs. Effet : Augmente les dégats, Augmente légèrement la vitesse d'attaque.", {NO_IMPROVE, MIDDLE_IMPROVE, SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 2, NULL, NULL,1, 1},
    //étage2:
    {non_acquis, "Grand Grimoire", "Aussi appelé Dragon rouge, c'est un grimoire de magie noire, qui aurait été écrit par un certain Antonio Venitiana del Rabina en 1522 à partir de sources plus anciennes qui remonteraient au roi des Juifs Salomon. Effet : Améliore énormément la vitesse d'attaque", {NO_IMPROVE, NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,2, 2},
    {non_acquis, "Bâton Céleste", "Le mage est équipé de l'illustre bâton des cieux. Effet : Augmente énormément les dégats.", {NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL, 2, 2},
    //étage3:
    {non_acquis, "Bénédiction de l'Archange","Le personnage reçoit la bénédiction de l'Archange Gabriel. Effet : Augmente les points vie.",{MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 5, NULL, NULL, 3, 3},
    //étage4:
    {non_acquis, "Magie du Feu","Le mage transforme sa magie de base en une magie de feu. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Magie de l'Eau","Le mage transforme sa magie de base en une magie de l'eau. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Magie Terrestre","Le mage transforme sa magie de base en une magie de terre. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Magie Noire","Le mage transforme sa magie de base en une magie lugubre. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Magie Céleste","Le mage transforme sa magie de base en une magie céleste. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 4},
    //étage5 : Compétence ultime
    {non_acquis, "Artéfact du Merlin", "Cette compétence permet au personnage d'obtenir un artéfact magique augmentant toutes les stats. Effet : Améliore toutes les statistiques", {MIDDLE_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE}, NULL, 5, NULL, 0, NULL, NULL,3, 5}
};


t_competence cpt_guerrier[NB_CPT]={
    //étage1:
    {non_acquis, "Renforcement du Guerrier", "Cette compétence durcit le corps du Guerrier le redant impénétrable. Effet : Augmente grandement les points de vie.", {BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 4, NULL, NULL, 1, 1},
    //étage2:
    {non_acquis, "Katana","Le guerrier échange son épée de base contre un Katana. Effet : Augmente légèrement les dégats et grandement la vitesse d'attaque.", {NO_IMPROVE, SMALL_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL, 2, 2},
    {non_acquis, "Glaive et Bouclier","Le guerrier échange son épée de base contre un glaive et une petit bouclier. Effet : Augmente les points de vie et les dégats.", {MIDDLE_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL, 2, 2},
    {non_acquis, "Epée à 2 Mains","Le guerrier échange son épée de base contre une epée à 2 main. Effet : Augmente énormément les dégats.", {NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL, 2, 2},
    {non_acquis, "Hache","Le guerrier échange son épée de base contre une Hache. Effet : Augmente légèrement la vitesse d'attaque et grandement les dégats.", {NO_IMPROVE, BIG_IMPROVE, SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL, 2, 2},
    //étage3:
    {non_acquis, "Bénédiction de Neptune","Le dieu marin Neptune accorde sa bénédiction au Guerrier pour sa bravoure. Effet : Augmente les points de vies et légèrement la vitesse de déplacement", {MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, SMALL_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 2, NULL, NULL,3, 3},
    {non_acquis, "Armure d'Hadès","Après avoir vaincu le dieu des Enfers, le Guerrier a conservé son armure. Effet : Augmente grandement les points de vies", {BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 2, NULL, NULL,3, 3},
    //étage4:
    {non_acquis, "Bottes des Géants", "Le guerrier s'équipe a présent de bottes donné en cadeau par des Géants au guerrier. Effet : Augmente grandement la vitesse de déplacement et Augmente légèrement les points de vie.", {SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Bottes de Sept Lieues", "Le guerrier s'équipe a présent de bottes donné en cadeau par les Postillons au guerrier. Effet : Augmente grandement la vitesse de déplacement et Réduit légèrement le périmètre de détection des mobs.", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, SMALL_IMPROVE}, NULL, 2, NULL, 1, NULL, NULL,3, 4},
    //étage5: Compétence ultime
    {non_acquis, "Rage du Berzerk", "Le guerrier debloque entièrement sa puissance pour détruire ses adversaire. Effet : Augmente énormémment la vitesse d'attaque, Augmente les dégats et la vitesse de déplacement.", {NO_IMPROVE, MIDDLE_IMPROVE, BIG_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 0, NULL, NULL,3, 5}
};

t_competence cpt_archer[NB_CPT]={
    //étage1:
    {non_acquis, "Déplacement Furtif", "L'archer est capable de se déplacer plus rapidement de manière discrète. Effet : Réduit légèrement le périmètre de détection. Augmente grandement la vitesse de déplacement", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, SMALL_IMPROVE}, NULL, 0, NULL, 3, NULL, NULL,1, 1},
    //étage2:
    {non_acquis, "Arc Séraphin", "Arc légendaire donnée par la plus grande instance de la Hiérarchie Céleste. Effet : Augmente légèrement les points de vie et grandement les dégats.", {SMALL_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,2, 2},
    {non_acquis, "Arc d'Ether", "L'arc de l'Archer s'améliore en l'Arc d'Ether, léger et facile à manier. Effet : Augmente la vitesse de déplacement et la vitesse d'attaque.", {NO_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 2, NULL, NULL,2, 2},
    {non_acquis, "Arc du Vide", "Arc sinistre obtenu dans le tombeau du pharaon Ramsès II. Effet : Augmente énormement les dégats.", {NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL, 2, 2},
    //étage3:
    {non_acquis, "Manteau de la Nuit", "Vêtement de l'archer permettant de réduire la distance de détection des mobs. Effet : Réduit grandement le périmètre de détection des mobs", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE}, NULL, 2, NULL, 2, NULL, NULL,3, 3},
    {non_acquis, "Sandales d'Hermes", "Ces sandales accordent au jours une vitesse déplacement remarquable. Effet : Augmente grandement la vitesse de déplacement.", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 2, NULL, NULL,3, 3},
    //étage4:
    {non_acquis, "Flèches Perforantes", "Les flèches sont affutées pour atteindre plus facilement les ennemis et les transpercer. Effet : Augmente les dégats et légèrement la vitesse de déplacement.", {NO_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, SMALL_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Flèche de Gungnir", "Flèches forgées à partir de la lance d'Odin : Gungnir. Effet : Augmente grandement la vitesse d'attaque", {NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 1, NULL, NULL,3, 4},
    {non_acquis, "Flèche Vorace", "Flèches absorbant la vie de la cible. Effet : Augmente les dégats et légèrement les points de vie.",{SMALL_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1, NULL, NULL,3, 4},
    //étage5: Compétence ultime
    {non_acquis, "Salve Ultime", "L'archer débloque son plein potentiel pour rendre ses flèches plus meurtrières. Effet : Augmente énormement la vitesse d'attaque et de déplacement.", {NO_IMPROVE, NO_IMPROVE, ULTRA_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE}, NULL, 3, NULL, 0, NULL, NULL,3, 5},
};

/**
 * \fn init_obj_necessaires(t_competence* competence, t_classe typeClasse, int indice)
 * \brief Fonction qui initialise les objets nécessaires pour débloquer une compétence
 * \param competence La compétence à initialiser
 * \param typeClasse Le type de classe de la compétence
 * \param indice L'indice de la compétence dans le tableau de compétence
 * \return 0 si tout s'est bien passé, -1 sinon
*/
int init_obj_necessaires(t_competence* competence, t_classe typeClasse, int indice){
    competence->obj_necessaires = malloc(sizeof(objet_inv_t));
    competence->obj_necessaires->nb = malloc(sizeof(int) * competence->taille_tab_obj_nec);
    competence->obj_necessaires->objet = malloc(sizeof(objet_t) * competence->taille_tab_obj_nec);
    switch(typeClasse){
        case ASSASSIN:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //griffe
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[2];     //Fourrure
                    competence->obj_necessaires->nb[1] = 5; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[1];     //Green Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[2];     //Fourrure
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Griffe
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[9];     //Massue
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Griffe
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[1];     //Green Goo
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Fourrure
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Fourrure
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 17;                  
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 18; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[2] = 4; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 10; 
                    competence->obj_necessaires->objet[0] = tab_objet[14];     //Coeur de diable
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[11];     //Corne de diablotin
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[13];     //Lance
                    break;
                default : break;
            }
            break;
        case MAGE:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 9; 
                    competence->obj_necessaires->objet[0] = tab_objet[1];     //Green Goo
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[2] = 6; 
                    competence->obj_necessaires->objet[2] = tab_objet[0];     //Or
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[9];     //Massue
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 14; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 6; 
                    competence->obj_necessaires->objet[2] = tab_objet[3];     //Green Goo
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[1] = 8; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[9];     //Lance-pierre
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 18;                  
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 8; 
                    competence->obj_necessaires->objet[1] = tab_objet[12];    //Queue de Diablotin
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 18; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 8; 
                    competence->obj_necessaires->objet[1] = tab_objet[15];    //Tête
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[1];     //Grey Goo
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 30; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[10];     //Red Goo
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[15];     //Tête
                    break;
                default : break;
            }
            break;
        case GUERRIER:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[2];     //Fourrure
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[4];     //Green Goo
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[2];     //Fourrure
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[9];     //Massue
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 13; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[5];     //Grey Goo
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[9];     //Massue
                    competence->obj_necessaires->nb[2] = 3; 
                    competence->obj_necessaires->objet[2] = tab_objet[2];     //Fourrure
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 17;                  
                    competence->obj_necessaires->objet[0] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[2];     //Fourrure
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 17; 
                    competence->obj_necessaires->objet[0] = tab_objet[0];     //Or
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[2] = 5; 
                    competence->obj_necessaires->objet[2] = tab_objet[2];     //Fourrure
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 20; 
                    competence->obj_necessaires->objet[0] = tab_objet[16];     //Croquettes
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[13];     //Lance
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[10];     //Red Goo
                    break;
                default : break;
            }
            break;
        case ARCHER:
            switch(indice){
                case 0: 
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[1];     //Green Goo
                    break;
                case 1:
                    competence->obj_necessaires->nb[0] = 8; 
                    competence->obj_necessaires->objet[0] = tab_objet[7];     //Lance-pierre
                    competence->obj_necessaires->nb[1] = 5; 
                    competence->obj_necessaires->objet[1] = tab_objet[0];     //Or
                    break;
                case 2:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[3];     //Griffe
                    competence->obj_necessaires->nb[1] = 7; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    break;
                case 3:
                    competence->obj_necessaires->nb[0] = 4; 
                    competence->obj_necessaires->objet[0] = tab_objet[4];     //Grimoire
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[7];     //Lance-pierre
                    break;
                case 4:
                    competence->obj_necessaires->nb[0] = 6; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[2];     //Fourrure
                    competence->obj_necessaires->nb[2] = 7; 
                    competence->obj_necessaires->objet[2] = tab_objet[0];     //Or
                    break;
                case 5:
                    competence->obj_necessaires->nb[0] = 7; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Or
                    competence->obj_necessaires->nb[1] = 5; 
                    competence->obj_necessaires->objet[1] = tab_objet[1];     //Fourrure
                    competence->obj_necessaires->nb[2] = 10; 
                    competence->obj_necessaires->objet[2] = tab_objet[8];     //Cailloux
                    break;
                case 6:
                    competence->obj_necessaires->nb[0] = 19; 
                    competence->obj_necessaires->objet[0] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[1] = 9; 
                    competence->obj_necessaires->objet[1] = tab_objet[8];     //Cailloux
                    competence->obj_necessaires->nb[2] = 9; 
                    competence->obj_necessaires->objet[2] = tab_objet[7];     //Lance-pierre
                    break;
                case 7:
                    competence->obj_necessaires->nb[0] = 17;                  
                    competence->obj_necessaires->objet[0] = tab_objet[13];    //Lance
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[8];     //Massue
                    competence->obj_necessaires->nb[2] = 9; 
                    competence->obj_necessaires->objet[2] = tab_objet[0];     //Or
                    break;
                case 8:
                    competence->obj_necessaires->nb[0] = 18; 
                    competence->obj_necessaires->objet[0] = tab_objet[5];     //Grey Goo
                    competence->obj_necessaires->nb[1] = 10; 
                    competence->obj_necessaires->objet[1] = tab_objet[6];     //Pioche
                    competence->obj_necessaires->nb[2] = 8; 
                    competence->obj_necessaires->objet[2] = tab_objet[8];     //Cailloux
                    break;
                case 9:
                    competence->obj_necessaires->nb[0] = 15; 
                    competence->obj_necessaires->objet[0] = tab_objet[10];     //Red Goo
                    competence->obj_necessaires->nb[1] = 13; 
                    competence->obj_necessaires->objet[1] = tab_objet[12];     //Queue de diablotin
                    competence->obj_necessaires->nb[2] = 12; 
                    competence->obj_necessaires->objet[2] = tab_objet[11];     //Corne de diablotin
                    break;
                default : break;
            }
            break;
        default: break;
    }
    return 1;
}

/**
 * \fn int changer_nomImgCpt(t_competence * competence)
 * \brief Met le nom de la compétence en question à "débloqué"
 * \param competence La compétence dont on veut changer le nom
 * \return 1 si tout s'est bien passé, 0 sinon
*/
int changer_nomImgCpt(t_competence * competence){
    int i;
    for(i=0; i<strlen(competence->name_img); i++);
    i--;
    while(competence->name_img[i] != 'l'){
        i--;
    }
    competence->name_img[i]='u';

    return 1;
}


/**
 * \fn int remplissage_nomImgCpt(t_competence **competences, t_classe typeClasse)
 * \brief Met le nom des compétences à "bloqué" (l=lock)
 * \param competences Les compétences dont on veut changer le nom
 * \param typeClasse Le type de classe dont on veut changer le nom
 * \return 1 si tout s'est bien passé, 0 sinon
*/
int remplissage_nomImgCpt(t_competence **competences, t_classe typeClasse){  
    printf("Attribution du nom\n");
    int i, j, k;
    for(i=0; i<NB_CPT; i++){
        if(competences[i]->name_img==NULL){
            competences[i]->name_img=malloc(sizeof(char)*T_NOM);
            switch(typeClasse){
                case ARCHER: strcpy(competences[i]->name_img, "../img/competences/archer/"); break;
                case ASSASSIN: strcpy(competences[i]->name_img, "../img/competences/assassin/"); break;
                case GUERRIER: strcpy(competences[i]->name_img, "../img/competences/guerrier/"); break;
                case MAGE: strcpy(competences[i]->name_img, "../img/competences/mage/"); break;
                default : break;
            }
            for(j=0, k=strlen(competences[i]->name_img); j<strlen(competences[i]->nom); j++){
                if((competences[i]->nom[j]>='A' && competences[i]->nom[j]<='Z') || (competences[i]->nom[j]>'0' && competences[i]->nom[j]<='9')){
                    competences[i]->name_img[k++] = competences[i]->nom[j];
                }
            }
            competences[i]->name_img[k]='\0';
        }
        strcat(competences[i]->name_img,"_l.png");
    }

    return 1;
}
/**
 * \fn int init_competences(t_competence ** competences, t_classe typeClasse)
 * \brief Initialise les compétences
 * \param competences Les compétences à initialiser
 * \param typeClasse Le type de classe dont on veut initialiser les compétences
 * \return 1 si tout s'est bien passé, 0 sinon
*/
int init_competences(t_competence ** competences, t_classe typeClasse){
    int i, j, k;
    int branche_parcourus=0;
    int reculer=0;
    int avancer=0;

    /* Remplissage nom fichier sprite compétence */
    if(!remplissage_nomImgCpt(competences, typeClasse)) return 0;

    //Remplissage des tableaux de compétences suivantes pour chaque compétence
    for(i=0, k=i+1; i<NB_CPT; i++){
        init_obj_necessaires(competences[i], typeClasse, i);

        if(competences[i]->nb_suiv>0){
            competences[i]->suivantes=malloc(sizeof(t_competence)*competences[i]->nb_suiv);
            for(j=0; j<competences[i]->nb_suiv; j++){
                if(competences[k]->nb_prec>1+branche_parcourus){
                    competences[i]->suivantes[j]=competences[k];
                    branche_parcourus++;
                }
                else{
                    competences[i]->suivantes[j]=competences[k++];
                    branche_parcourus=0;
                }
                //printf("compétence %s[%d] : suivant  %s\n",competences[i].nom, i, competences[i].suivantes[j].nom);
                if(typeClasse==GUERRIER && i==5 && branche_parcourus!=0){
                    k++;
                    reculer=1;
                }
                else if(typeClasse==GUERRIER && i==6 && branche_parcourus!=0){
                    k--;
                    avancer=1;
                }
            }
            if(reculer) k--; reculer=0;
            if(avancer) k++; avancer=0;
        }
        else{
            competences[i]->suivantes=NULL;
        }
    }
    
    //Remplissage des tableaux de compétences précédentes pour chaque compétence
    branche_parcourus=0;
    for(i=NB_CPT-1, k=i-1; i>=0; i--){
        if(competences[i]->nb_prec>0){
            competences[i]->precedentes=malloc(sizeof(t_competence)*competences[i]->nb_prec);
            for(j=0; j<competences[i]->nb_prec ; j++){
                if(competences[k]->nb_suiv>1+branche_parcourus){
                    competences[i]->precedentes[j]=competences[k];
                    branche_parcourus++;
                }
                else{
                    competences[i]->precedentes[j]=competences[k--];
                    branche_parcourus=0;
                }
                //printf("compétence %s[%d] : précédent  %s\n",competences[i].nom, i, competences[i].precedentes[j].nom);
                if(typeClasse==GUERRIER && i==NB_CPT-2 && branche_parcourus!=0){
                    k--;
                    avancer=1;
                }
                else if(typeClasse==GUERRIER && i==NB_CPT-3 && branche_parcourus!=0){
                    k++;
                    reculer=1;
                }
            }
            if(reculer) k--; reculer=0;
            if(avancer) k++; avancer=0;
        }
        else{
            competences[i]->precedentes=NULL;
        }
    }

    return 1;
}
/**
 * \fn void aff_competence(t_competence competence)
 * \brief Affiche les informations d'une compétence
 * \param competence La compétence à afficher
*/
void aff_competence(t_competence competence){
    printf("\n");
    if(competence.competence_acquise == non_acquis){
        printf("(NON ACQUISE) ");
    }
    else{
        printf("(ACQUISE) ");
    }
    printf("%s : %s (%lu)\nDesc : %s\n", competence.nom, competence.name_img, strlen(competence.name_img), competence.desc);
    
    printf("Nombre comp preced : %d = {", competence.nb_prec);
    for(int j=0; j<competence.nb_prec; j++){
        printf(" %s ", competence.precedentes[j]->nom);
    }
    printf("}\n");
    printf("Nombre comp suiv : %d = {", competence.nb_suiv);
    for(int j=0; j<competence.nb_suiv; j++){
        printf(" %s ", competence.suivantes[j]->nom);
    }
    printf("}\n");

    printf("Buff :\n\t- Vie*%.2f\n\t- Att*%.2f\n\t- Vit_att*%.2f\n\t- Vit_depl*%.2f\n\t- bonus_perim_detect+%d\n", competence.buff.buff_vie, competence.buff.buff_degat, competence.buff.buff_vit_att, competence.buff.buff_vit_depl, competence.buff.perim_detect);

    printf("\n * Nécéssite :\n");
    for(int j=0; j<competence.taille_tab_obj_nec; j++){
        printf("\t- %s x %d\n", competence.obj_necessaires->objet[j].nom, competence.obj_necessaires->nb[j]);
    }
    
    printf("\n");
}
