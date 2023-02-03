#define NB_CPT 8

#define NO_IMPROVE 1
#define SMALL_IMPROVE 1.25
#define MIDDLE_IMPROVE 1.5
#define BIG_IMPROVE 1.75
#define ULTRA_IMPROVE 2

typedef struct buff{
    int buff_vie;
    float buff_degat;
    float buff_vit_att;
    float buff_vit_depl;
} t_buff;

typedef struct competence{
    char nom[20];
    t_buff buff_stat;
    struct competence **precedentes;
    int nb_prec;
    struct competence **suivantes;
    int nb_suiv;
} t_competence;

t_competence assassin[NB_CPT]={
    {"Dague", {NO_IMPROVE,NO_IMPROVE,SMALL_IMPROVE,SMALL_IMPROVE}, NULL, 0, NULL, 0},
    {"Dague sanguine", {NO_IMPROVE,NO_IMPROVE,MIDDLE_IMPROVE,MIDDLE_IMPROVE}, NULL, 0, NULL, 0},
    {"Dague ténébreuse", {NO_IMPROVE,NO_IMPROVE,MIDDLE_IMPROVE,MIDDLE_IMPROVE}, NULL, 0, NULL, 0},
    {},
    {},
    {},
    {},
    {}
};

t_competence mage[NB_CPT]={
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};


t_competence guerrier[NB_CPT]={
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};

t_competence archer[NB_CPT]={
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};

