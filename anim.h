#ifndef  ANIM_INC
#define  ANIM_INC

#include "init.h"

#define KEY_ESC 27

enum action {STOP, IDLE, RUN, WALK};

extern float t;
extern float delta;
extern float k;
extern float K;

extern float position;

extern float sin_k_t;

extern int Step;
extern int latence;

extern int doing;

GLvoid window_key(unsigned char key, int x, int y); 
GLvoid window_timer(); 

void runCalc();

#endif
