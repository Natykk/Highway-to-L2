#define NB_CPT 8
#define T_NOM 30
#define T_DESC 200

#define NO_IMPROVE 1
#define SMALL_IMPROVE 1.25
#define MIDDLE_IMPROVE 1.5
#define BIG_IMPROVE 1.75
#define ULTRA_IMPROVE 2

typedef enum {non_acquis, acquis} t_acquis;

typedef struct buff{
    int buff_vie;
    float buff_degat;
    float buff_vit_att;
    float buff_vit_depl;
    int perim_detect;
} t_buff;

typedef struct competence{
    t_acquis est_acquise;
    char nom[T_NOM];
    char desc[T_DESC];
    t_buff buff_stat;
    struct competence **precedentes;
    int nb_prec;
    struct competence **suivantes;
    int nb_suiv;
} t_competence;

t_competence assassin[NB_CPT]={
    {non_acquis, "Silence mortel", "Cette compétence permet à l'assassin de se déplacer plus discrètement. Effet : Réduit légèrement le périmètre de détection des mobs.", {NO_IMPROVE,NO_IMPROVE,NO_IMPROVE,NO_IMPROVE,SMALL_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Frappe rapide", "Cette compétence se concentre sur la rapidité d'attaque pour neutraliser rapidement la cible. Effet : Augmente la vitesse d'attaque.", {NO_IMPROVE,NO_IMPROVE,MIDDLE_IMPROVE,NO_IMPROVE,NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Cotte légère", "Armure protégeant des petits dégats. Effet : Augmente légèrement les points de vie",  {SMALL_IMPROVE,NO_IMPROVE,NO_IMPROVE,NO_IMPROVE,NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Marche de l'ombre", "Cette compétence implique la capacité à l'assassin de se cacher ou à se dissimuler pour passer inaperçu. Effet : Réduit le périmètre de détection des mobs, Augmente légèrement la vitesse de déplacement.", {NO_IMPROVE,NO_IMPROVE,NO_IMPROVE,SMALL_IMPROVE,MIDDLE_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Coup perçant","L'assassin concentre son énergie dans la pointe de son arme pour assainer des dégats importants. Effet : Augmente les dégats", {NO_IMPROVE,MIDDLE_IMPROVE,NO_IMPROVE,NO_IMPROVE,NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Bottes de célérité","Cette compétence garantit à l'assassin une vitesse de déplacement supérieure. Effet : Augmente grandement la vitesse de déplacement", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Entaille profonde","Cette compétence permet à l'assassin d'asséner des coup plus profond. Effet : Augmente grandement les dégats.", {NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Chatiment fatal","L'assassin concentre toute son énergie dans son arme pour rendre chaque coup fatal. Effet : Augmente enormément les dégats, Augmente grandement la vitesse d'attaque."{NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0}
};

t_competence mage[NB_CPT]={
    {non_acquis, "Bâton supérieur de l'apprentit", "Le mage possède à présent un bâton de magie supérieure. Effet : Augmente les dégats, Augmente légèrement la vitesse d'attaque.", {NO_IMPROVE, MIDDLE_IMPROVE, SMALL_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Artéfact du Merlin", "Cette compétence permet au personnage d'obtenir un artéfact magique augmentant toutes les stats. Effet : Augmente légèrement toutes les stats", {SMALL_IMPROVE, SMALL_IMPROVE, SMALL_IMPROVE, SMALL_IMPROVE, SMALL_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Magie du feu","Le mage transforme sa magie de base en une magie de feu. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Magie aquatique","Le mage transforme sa magie de base en une magie de l'eau. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Magie électrique","Le mage transforme sa magie de base en une magie de l'électricité. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Magie noire","Le mage transforme sa magie de base en une magie lugubre. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Bénédiction de l'Archange","Le personnage reçoit la bénédiction de l'Archange Gabriel. Effet : Augmente les points vie.",{MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Bâton de l'Archimage", "Le mage est équipé de l'illustre bâton de l'Archimage. Effet : Augmente énormément les dégats.", {NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0}
};


t_competence guerrier[NB_CPT]={
    {non_acquis, "Bénédiction de Mars","Le dieux romain Mars accorde sa bénédiction au guerrier. Effet : Augmente grandement les points de vie.", {BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Excalibur","Le guerrier est équipé de l'épée divine Excalibur. Effet : Augmente grandement les dégats.", {NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Bouclier d'Achille", "Bouclier robuste légué au guerrier par le héros Achille. Augmente les points de vie.", {MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Rage du Berzerk", "Le guerrier debloque entièrement sa puissance pour détruire ses adversaire. Effet : Augmente énormémment la vitesse d'attaque, Augmente les dégats, Augmente la vitesse de déplacement.", {NO_IMPROVE, MIDDLE_IMPROVE, BIG_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Bottes des géants", "Le guerrier s'équipe a présent de bottes donné en cadeau au guerrier pour sa bravoure. Effet : Augmente légèrement la vitesse de déplacement, Augmente les points de vie.", {MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, SMALL_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Renforcement", "Cette compétence durcit le corps du Guerrier le redant impénétrable. Effet : Augmente grandement les points de vie.", {BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Katana Masamune", "Sabre Japonnais délivré par le grand Maitre Masamune. Effet : Augmente légèrement les dégats. Augmente énormement la vitesse d'attaque.", {NO_IMPROVE, SMALL_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Armure d'Hadès", "Après la mort du dieux des Enfers, Zeus a offert cette armure au Guerrier. Effet : Augmente énormément les points de vie.", {ULTRA_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0}
};

t_competence archer[NB_CPT]={
    {non_acquis, "Déplacement furtif", "L'archer est capable de se déplacer plus rapidement de manière discrète. Effet : Réduit légèrement le périmètre de détection. Augmente grandement la vitesse de déplacement", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, SMALL_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Arc d'Ebène", "L'arc de l'Archer s'améliore en l'Arc d'Ebène. Effet : Augmente les dégats et la vitesse d'attaque.", {NO_IMPROVE, MIDDLE_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Bottes d'Hermes", "Ces bottes accordent au jours une vitesse déplacement remarquable. Effet : Augmente énormement la vitesse de déplacement.", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Flèche de Gungnir", "Flèches forgées à partir de la lance d'Odin : Gungnir. Effet : Augmente grandement la vitesse d'attaque", {NO_IMPROVE, NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Manteau de la nuit", "Vêtement de l'archer permettant de réduire la distance de détection des mobs. Effet : Réduit le périmètre de détection", {NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE, MIDDLE_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Arc de Séraphin", "Arc légendaire donnée par la plus grande instance de la Hiérarchie Céleste. Effet : Augmente énormement les dégats, la vitesse d'attaque et la vitesse de déplacement.", {NO_IMPROVE, ULTRA_IMPROVE, ULTRA_IMPROVE, ULTRA_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Flèche vorace", "Flèches absorbant la vie de la cible. Effet : Augmente grandement les dégats.",{NO_IMPROVE, BIG_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0},
    {non_acquis, "Flèches perforantes", "Les flèches sont affutées pour atteindre plus facilement les ennemis et les transpercer. Effet : Augmente les dégats.", {NO_IMPROVE, MIDDLE_IMPROVE, NO_IMPROVE, NO_IMPROVE, NO_IMPROVE}, NULL, 0, NULL, 0}
};

