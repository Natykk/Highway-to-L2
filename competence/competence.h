#include <stdio.h>
#include <stdlib.h>

#define NB_CPT 10
#define T_NOM 30
#define T_DESC 300

#define NO_IMPROVE 1
#define SMALL_IMPROVE 2         //améliore légèrement ...
#define MIDDLE_IMPROVE 3        //ameliore ...
#define BIG_IMPROVE 4           //améliore grandement ...
#define ULTRA_IMPROVE 5         //améliore énormémément ...

typedef enum {non_acquis, acquis} t_acquis;

typedef struct buff{
    int buff_vie;
    int buff_degat;
    int buff_vit_att;
    int buff_vit_depl;
    int perim_detect;
} t_buff;

typedef struct competence{
    t_acquis competence_acquise;
    char nom[T_NOM];
    char desc[T_DESC];
    t_buff buff_stat;
    struct competence *precedentes;
    int nb_prec;
    struct competence *suivantes;
    int nb_suiv;
} t_competence;


t_competence assassin[NB_CPT]={
    //étage1:
    {non_acquis, "Frappe rapide", "Cette compétence se concentre sur la rapidité d'attaque pour neutraliser rapidement la cible. Effet : Augmente la vitesse d'attaque.", {NO_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 2},
    //étage2:
    {non_acquis, "Cotte de maille", "Armure protégeant des petits dégats. Effet : Augmente les points de vie et légèrement la vitesse d'attaque.",  {MIDDLE_IMPROVE, NO_IMPROVE, SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 2},
    {non_acquis, "Cape d'invisibilité","L'assassin possède à présent une cape lui permettant d'améliorer sa discrétion. Effet : Réduit grandement le périmètre de détection des mobs.",{NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE}, NULL, 1, NULL, 2},
    //étage3:
    {non_acquis, "Coup perçant","L'assassin concentre son énergie dans la pointe de son arme pour assainer des dégats et aspirer de la vie à sa cible. Effet : Augmente les dégats, grandement la vitesse d'attaque et les points de vie.", {MIDDLE_IMPROVE, MIDDLE_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Entaille profonde","Cette compétence permet à l'assassin d'asséner des coup plus profond infligeant de gros dégats. Effet : Augmente grandement les dégats et la vitesse d'attaque.", {NO_IMPROVE, BIG_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Silence mortel", "Cette compétence améliore la capacité de l'assassin à se cacher ou à se dissimuler pour passer inaperçu. Effet : Réduit grandement le périmètre de détection des mobs, Augmente la vitesse de déplacement et légèrement la vitesse d'attaque.", {NO_IMPROVE,NO_IMPROVE,SMALL_IMPROVE,MIDDLE_IMPROVE,BIG_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Marche de l'ombre", "Cette compétence permet à l'assassin de se déplacer plus discrètement. Effet : Réduit grandement le périmètre de détection des mobs, Augmente la vitesse d'attaque et légèrement la vitesse de déplacement", {NO_IMPROVE,NO_IMPROVE,MIDDLE_IMPROVE,SMALL_IMPROVE,BIG_IMPROVE}, NULL, 1, NULL, 1},
    //étage4:
    {non_acquis, "Bottes de célérité","Cette compétence garantit à l'assassin une vitesse de déplacement supérieure. Effet : Augmente grandement la vitesse d'attaque et grandement la vitesse de déplacement.", {NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, BIG_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 1},
    {non_acquis, "Bottes de furtivité","L'assassin se chausse de bottes masquant le bruit de ses pas. Effet : Réduit énormement le périmètre de détection des mobs et Augmente la vitesse de déplacement.",{NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE, ULTRA_IMPROVE}, NULL, 2, NULL, 1},
    //étage5: Compétence ultime
    {non_acquis, "Chatiment fatal","L'assassin concentre toute son énergie dans son arme pour rendre chaque coup fatal. Effet : Augmente enormément les dégats, Augmente la furtivité et la vitesse d'attaque.",{NO_IMPROVE, ULTRA_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE}, NULL, 2, NULL, 0},
};


t_competence mage[NB_CPT]={
    //étage1:
    {non_acquis, "Bâton de l'apprentit", "Le mage possède à présent un bâton de magie. Effet : Augmente les dégats, Augmente légèrement la vitesse d'attaque.", {NO_IMPROVE, MIDDLE_IMPROVE, SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 2},
    //étage2:
    {non_acquis, "Baguette de Sureau", "Le mage troque son baton pour une baguette magique, plus maniable. Effet : Améliore énormément la vitesse d'attaque", {NO_IMPROVE, NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Bâton de l'Archimage", "Le mage est équipé de l'illustre bâton de l'Archimage. Effet : Augmente énormément les dégats.", {NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    //étage3:
    {non_acquis, "Bénédiction de l'Archange","Le personnage reçoit la bénédiction de l'Archange Gabriel. Effet : Augmente les points vie.",{MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 5},
    //étage4:
    {non_acquis, "Magie Ardente","Le mage transforme sa magie de base en une magie de feu. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Magie Aquatique","Le mage transforme sa magie de base en une magie de l'eau. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Magie Terrestre","Le mage transforme sa magie de base en une magie de terre. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Magie noire","Le mage transforme sa magie de base en une magie lugubre. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Magie céleste","Le mage transforme sa magie de base en une magie céleste. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    //étage5 : Compétence ultime
    {non_acquis, "Artéfact du Merlin", "Cette compétence permet au personnage d'obtenir un artéfact magique augmentant toutes les stats. Effet : Améliore toutes les statistiques", {MIDDLE_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE}, NULL, 5, NULL, 0}
};


t_competence guerrier[NB_CPT]={
    //étage1:
    {non_acquis, "Renforcement du Guerrier", "Cette compétence durcit le corps du Guerrier le redant impénétrable. Effet : Augmente grandement les points de vie.", {BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 4},
    //étage2:
    {non_acquis, "Katana","Le guerrier échange son épée de base contre un Katana. Effet : Augmente légèrement les dégats et grandement la vitesse d'attaque.", {NO_IMPROVE, SMALL_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Glaive et Bouclier","Le guerrier échange son épée de base contre un glaive et une petit bouclier. Effet : Augmente les points de vie et les dégats.", {MIDDLE_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Epée à 2 mains","Le guerrier échange son épée de base contre une epée à 2 main. Effet : Augmente énormément les dégats.", {NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Hache","Le guerrier échange son épée de base contre une Hache. Effet : Augmente légèrement la vitesse d'attaque et grandement les dégats.", {NO_IMPROVE, BIG_IMPROVE, SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    //étage3:
    {non_acquis, "Bénédiction de Neptune","Le dieu marin Neptune accorde sa bénédiction au Guerrier pour sa bravoure. Effet : Augmente les points de vies et légèrement la vitesse de déplacement", {MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, SMALL_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 2},
    {non_acquis, "Armure d'Hadès","Après avoir vaincu le dieu des Enfers, le Guerrier a conservé son armure. Effet : Augmente grandement les points de vies", {BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 2},
    //étage4:
    {non_acquis, "Bottes des géants", "Le guerrier s'équipe a présent de bottes donné en cadeau par des Géants au guerrier. Effet : Augmente grandement la vitesse de déplacement et Augmente légèrement les points de vie.", {SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 1},
    {non_acquis, "Bottes de sept lieues", "Le guerrier s'équipe a présent de bottes donné en cadeau par les Postillons au guerrier. Effet : Augmente grandement la vitesse de déplacement et Réduit légèrement le périmètre de détection des mobs.", {MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, SMALL_IMPROVE}, NULL, 2, NULL, 1},
    //étage5: Compétence ultime
    {non_acquis, "Rage du Berzerk", "Le guerrier debloque entièrement sa puissance pour détruire ses adversaire. Effet : Augmente énormémment la vitesse d'attaque, Augmente les dégats et la vitesse de déplacement.", {NO_IMPROVE, MIDDLE_IMPROVE, BIG_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 0}
};

t_competence archer[NB_CPT]={
    //étage1:
    {non_acquis, "Déplacement furtif", "L'archer est capable de se déplacer plus rapidement de manière discrète. Effet : Réduit légèrement le périmètre de détection. Augmente grandement la vitesse de déplacement", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, SMALL_IMPROVE}, NULL, 0, NULL, 3},
    //étage2:
    {non_acquis, "Arc Séraphin", "Arc légendaire donnée par la plus grande instance de la Hiérarchie Céleste. Effet : Augmente légèrement les points de vie et grandement les dégats.", {SMALL_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Arc d'Ether", "L'arc de l'Archer s'améliore en l'Arc d'Ether, léger et facile à manier. Effet : Augmente la vitesse de déplacement et la vitesse d'attaque.", {NO_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 2},
    {non_acquis, "Arc Sépulcral", "Arc sinistre obtenu dans le tombeau du pharaon Ramsès II. Effet : Augmente énormement les dégats.", {NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    //étage3:
    {non_acquis, "Manteau de la nuit", "Vêtement de l'archer permettant de réduire la distance de détection des mobs. Effet : Réduit grandement le périmètre de détection des mobs", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE}, NULL, 2, NULL, 2},
    {non_acquis, "Sandales d'Hermes", "Ces sandales accordent au jours une vitesse déplacement remarquable. Effet : Augmente grandement la vitesse de déplacement.", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 2},
    //étage4:
    {non_acquis, "Flèches perforantes", "Les flèches sont affutées pour atteindre plus facilement les ennemis et les transpercer. Effet : Augmente les dégats et légèrement la vitesse de déplacement.", {NO_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, SMALL_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    {non_acquis, "Flèche de Gungnir", "Flèches forgées à partir de la lance d'Odin : Gungnir. Effet : Augmente grandement la vitesse d'attaque", {NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 2, NULL, 1},
    {non_acquis, "Flèche vorace", "Flèches absorbant la vie de la cible. Effet : Augmente les dégats et légèrement les points de vie.",{SMALL_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 1, NULL, 1},
    //étage5: Compétence ultime
    {non_acquis, "Salve Ultime", "L'archer débloque son plein potentiel pour rendre ses flèches plus meurtrières. Effet : Augmente énormement la vitesse d'attaque et de déplacement.", {NO_IMPROVE, NO_IMPROVE, ULTRA_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE}, NULL, 3, NULL, 0},
};
