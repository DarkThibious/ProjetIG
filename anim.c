#include "anim.h"

float t = 0.f;
float delta = 20.f;
float dt = 0;
float k = COEFF_WALK;

float l = 0.5f;

float position_X = position_Ini_X;
float position_Y = position_Ini_Y;

float sin_k_t = 0;

int Step = 0;
int latence = 4;

int direction_X = 0;
int direction_Y = 0;

int angleVisZ = 180;
int angleVisX = 0;

int prevDoing;
int doing = IDLE;

float vitesse = 0;

transition *first_Transi;

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
	switch(key) 
	{    
		case KEY_ESC:  
			exit(1);                    
			break; 
		case ' ':  
			if(doing != STOP)
			{
				prevDoing = doing;
				doing = STOP;
			}
			else
			{
				doing = prevDoing;
			}
			break;
		case 'r':
			prevDoing = doing;
			doing = RUN;
			k = COEFF_RUN;
			createTransition(&dt, 5, 0.01f);
			createTransition(&vitesse, VITESSE_RUN, 0.001f);
			break;
		case 'w':
			prevDoing = doing;
			doing = WALK;
			k = COEFF_WALK;
			createTransition(&dt, 0, 0.01f);
			createTransition(&vitesse, VITESSE_WALK, 0.001f);
			break;
		case 'i':
			doing = IDLE;
			break;
		case 'x':
			doing = SEAT;
			break;
		case '+':  
			delta *= 1.05;
			break; 
		case '-':  
			delta /= 1.05;
			break; 
		case 'z':
			direction_Y = 1;
			break;
		case 's': 
			direction_Y = -1;
			break;
		case 'd': 
			direction_X = 1;
			break;
		case 'q': 
			direction_X = -1;
			break;
	}     
}

GLvoid window_special_key(int key, int x, int y) 
{  
	switch (key) 
	{    
		case GLUT_KEY_LEFT:
			angleVisZ -= 1;
			break;
		case GLUT_KEY_RIGHT:
			angleVisZ += 1;
			break;
		case GLUT_KEY_UP:
			angleVisX += 1;
			break;
		case GLUT_KEY_DOWN:
			angleVisX -= 1;
			break;
	}     
}

GLvoid window_keyUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'z':
		case 's':
			direction_Y = 0;
			break;
		case 'q': 
		case 'd': 
			direction_X = 0;
			break;
	}
}

// fonction de call-back appelée régulièrement
GLvoid window_timer(int value) 
{
	if(doing != STOP)
	{
		t += delta;
		switch(doing)
		{
			case WALK:
				walkCalc();
				break;
			case RUN:
				runCalc();
				break;
			case IDLE:
				idleCalc();
				break;
			case SEAT:
				seatCalc();
		}
	}
	printf("posX : %f, dirX : %d, posY : %f, dirY : %d, vitesse : %f\n", position_X, direction_X, position_Y, direction_Y, vitesse);
	position_X += direction_X*vitesse;
	position_Y += direction_Y*vitesse;
	transitionnage();
	glutTimerFunc(latence,&window_timer,++Step);
	glutPostRedisplay();
}

void walkCalc()
{
	// On effectue une variation des angles de chaque membre
	// de l'amplitude associée et de la position médiane
	sin_k_t = sin(k*t);
	angle_Bras[Gauche] = med_Bras + amplitude_Bras * sin_k_t;
	angle_Bras[Droit] = med_Bras - amplitude_Bras * sin_k_t;
	angle_AvantBras[Gauche] = med_AvantBras + amplitude_AvantBras * sin_k_t;
	angle_AvantBras[Droit] = med_AvantBras - amplitude_AvantBras * sin_k_t;
	angle_Cuisse[Gauche] = med_Cuisse + amplitude_Cuisse * sin_k_t;
	angle_Cuisse[Droit] = med_Cuisse - amplitude_Cuisse * sin_k_t;
	angle_Mollet[Gauche] = med_Mollet + amplitude_Mollet * sin_k_t;
	angle_Mollet[Droit] = med_Mollet - amplitude_Mollet * sin_k_t;

	// On déplace la position de l'avatar pour qu'il avance
}

void runCalc()
{
	// On effectue une variation des angles de chaque membre
	// de l'amplitude associée et de la position médiane
	sin_k_t = sin(k*t);
	angle_Bras[Gauche] = med_Bras_R + amplitude_Bras_R * sin_k_t;
	angle_Bras[Droit] = med_Bras_R - amplitude_Bras_R * sin_k_t;
	angle_AvantBras[Gauche] = med_AvantBras_R + amplitude_AvantBras_R * sin_k_t;
	angle_AvantBras[Droit] = med_AvantBras_R - amplitude_AvantBras_R * sin_k_t;
	angle_Cuisse[Gauche] = med_Cuisse_R + amplitude_Cuisse_R * sin_k_t;
	angle_Cuisse[Droit] = med_Cuisse_R - amplitude_Cuisse_R * sin_k_t;
	angle_Mollet[Gauche] = med_Mollet_R + amplitude_Mollet_R * sin_k_t;
	angle_Mollet[Droit] = med_Mollet_R - amplitude_Mollet_R * sin_k_t;
}

void seatCalc()
{
	if(angle_Cuisse[Gauche] < 85)
	{
		angle_Cuisse[Gauche] += l;
	}
	if(angle_Cuisse[Droit] < 85)
	{
		angle_Cuisse[Droit] += l;
	}
	if(angle_Mollet[Gauche] < -85)
	{
		angle_Cuisse[Gauche] -= l;
	}
	if(angle_Mollet[Droit] < -85)
	{
		angle_Cuisse[Droit] -= l;
	}
}

void idleCalc()
{
		if(angle_Bras[Gauche] > 0)
		{
			angle_Bras[Gauche] -= l;
		}
		if(angle_Bras[Gauche] < 0)
		{
			angle_Bras[Gauche] += l;
		}
		if(angle_Bras[Droit] > 0)
		{
			angle_Bras[Droit] -= l;
		}
		if(angle_Bras[Droit] < 0)
		{
			angle_Bras[Droit] += l;
		}

		if(angle_AvantBras[Gauche] > 0)
		{
			angle_AvantBras[Gauche] -= 2*l;
		}
		if(angle_AvantBras[Gauche] < 0)
		{
			angle_AvantBras[Gauche] += 2*l;
		}
		if(angle_AvantBras[Droit] > 0)
		{
			angle_AvantBras[Droit] -= 2*l;
		}
		if(angle_AvantBras[Droit] < 0)
		{
			angle_AvantBras[Droit] += 2*l;
		}

		if(angle_Cuisse[Gauche] > 0)
		{
			angle_Cuisse[Gauche] -= 2*l;
		}
		if(angle_Cuisse[Gauche] < 0)
		{
			angle_Cuisse[Gauche] += 2*l;
		}
		if(angle_Cuisse[Droit] > 0)
		{
			angle_Cuisse[Droit] -= 2*l;
		}
		if(angle_Cuisse[Droit] < 0)
		{
			angle_Cuisse[Droit] += 2*l;
		}

		if(angle_Mollet[Gauche] > 0)
		{
			angle_Mollet[Gauche] -= 2*l;
		}
		if(angle_Mollet[Gauche] < 0)
		{
			angle_Mollet[Gauche] += 2*l;
		}
		if(angle_Mollet[Droit] > 0)
		{
			angle_Mollet[Droit] -= 2*l;
		}
		if(angle_Mollet[Droit] < 0)
		{
			angle_Mollet[Droit] += 2*l;
		}
}

transition *createTransition(float *var, float value, float increm)
{
	transition *T = first_Transi;
	if(T == NULL)
	{
		first_Transi = malloc(sizeof(transition));
		T = first_Transi;
	}
	else
	{
		while(T->next != NULL)
		{
			T = T->next;
		}
		T->next = malloc(sizeof(transition));
		T = T->next;
	}
	T->var = var;
	T->value = value;
	T->increm = increm;
	T->fini = false;
	T->next = NULL;
	return T;
}

void finTransition(transition *fini)
{
	transition *T = first_Transi;
	if(T == fini)
	{
		first_Transi = NULL;
	}
	else
	{
		while(T->next != fini)
		{
			T = T->next;
		}
		T->next = fini->next;
	}
	free(fini);
}


void transitionnage()
{
	transition *T = first_Transi;
	while(T != NULL)
	{
		if(!T->fini)
		{
			if(T->value - *(T->var) <= T->increm)
			{
				*(T->var) = T->value;
				T->fini = true;
			}
			else
			{
				if(*(T->var) > T->value && T->increm < 0)
				{
					*(T->var) += T->increm;
				}
				else if(*(T->var) > T->value && T->increm > 0)
				{
					*(T->var) -= T->increm;
				}
				else if(*(T->var) < T->value && T->increm > 0)
				{
					*(T->var) += T->increm;
				}
				else if(*(T->var) < T->value && T->increm < 0)
				{
					*(T->var) -= T->increm;
				}
			}
		}
		T = T->next;
	}
}
