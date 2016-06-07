#ifndef STRUCT
#define STRUCT

#define NB_ACTS 5
#define NB_ENTITIES 2
#define NB_MB_MAN 6

typedef struct s_entity entity;

enum coor {X = 0, Y, Z, ANGLE};
enum extre {MIN = 0, MAX};
enum color {R = 0, G, B};
enum bodyPart {TETE = 0, EPAULE_DROITE, EPAULE_GAUCHE, PAPILLON, BASSIN};

struct s_entity
{
	float color[3];
	float pos[3];
	float rotat[4];
	float angle_Ini[2];
	int listeDessin;
	int nbCompo;
	entity *compo;
};

extern entity entities[NB_ENTITIES];

#endif
