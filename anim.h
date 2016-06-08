#ifndef  ANIM_INC
#define  ANIM_INC

#include "init.h"

#define KEY_ESC 27
#define VITESSE_WALK 0.1f
#define VITESSE_RUN 0.2f

#define COEFF_WALK 0.0035f
#define COEFF_RUN 0.005f

#define RUN_INCREM 0.25f
#define RUN_ANGLE 12.5f

extern float t;
extern float delta;
extern float k;
extern float K;

extern float position_X;
extern float position_Y;

extern float sin_k_t;

extern int Step;
extern int latence;

extern int direction_X;
extern int direction_Y;

extern int angleVisZ;
extern int angleVisX;

extern int doing;
extern int prevDoing;

extern float vitesse;

typedef struct trans transition;

extern transition *first_Transi;

extern float angle_Seat_Epaule;
extern float angle_Seat_Coude;
extern float angle_Seat_Genou;
extern float angle_Seat_Cuisse;
extern float angle_increm;

struct trans
{
	float *var;
	float value;
	float increm;
	bool fini;
	transition *next;
};

GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_special_key(int key, int x, int y);
GLvoid window_keyUp(unsigned char key, int x, int y);
GLvoid window_timer(int value); 

void walkCalc();
void runCalc();
void seatCalc();
void idleCalc();
void transitionnage();
transition *createTransition(float *var, float value, float increm);
transition *trouveTransition(float *var);
void finTransition(transition *fini);
#endif
