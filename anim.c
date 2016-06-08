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

float angle_Seat_Epaule = 10.0;
float angle_Seat_Coude = 75.0;
float angle_Seat_Genou = -90.0;
float angle_Seat_Cuisse = 90.0;
float angle_increm = 0.5f;

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
			makeRunning();
			break;
		case 'w':
			makeWalking();
			break;
		case 'i':
			makeIdle();
			break;
		case 'x':
			makeSeat();
			break;
		case '+':  
			delta *= 1.05;
			break; 
		case '-':  
			delta /= 1.05;
			break; 
		case 'z':
			direction_Y = 1;
			deterAngle();
			break;
		case 's': 
			direction_Y = -1;
			deterAngle();
			break;
		case 'd': 
			direction_X = 1;
			deterAngle();
			break;
		case 'q': 
			direction_X = -1;
			deterAngle();
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
				//walkCalc();
				//break;
			case RUN:
			//	runCalc();
				perCalc();
				break;
			case IDLE:
				idleCalc();
				break;
			case SEAT:
				seatCalc();
		}
	}
	homme.pos[X] += direction_X*vitesse;
	homme.pos[Y] += direction_Y*vitesse;
	collisionHommeChaise();
	transitionnage();
	glutTimerFunc(latence,&window_timer,++Step);
	glutPostRedisplay();
}

void perCalc()
{
	// On effectue une variation des angles de chaque membre
	// de l'amplitude associée et de la position médiane
	sin_k_t = sin(k*t);

	entity *e;

	e = &(homme.compo[EPAULE_GAUCHE]); // epaule gauche
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t; 
	e = e->compo->compo; // coude gauche
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t;

	e = &(homme.compo[EPAULE_DROITE]); // epaule droite
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t;
	e = e->compo->compo; // coude droit
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t;

	e = &(homme.compo[BASSIN].compo[DROITE]); // jambe droite
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t;
	e = e->compo;
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t;

	e = &(homme.compo[BASSIN].compo[GAUCHE]);//Jambe gauche
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t;
	e = e->compo;
	e->rotat[ANGLE] = 0.5*(e->angle_Ini[MIN] + e->angle_Ini[MAX]) +  0.5*(e->angle_Ini[MAX] - e->angle_Ini[MIN]) * sin_k_t;

	// On déplace la position de l'avatar pour qu'il avance
}

void runCalc()
{
	// On effectue une variation des angles de chaque membre
	// de l'amplitude associée et de la position médiane
	sin_k_t = sin(k*t);
	angle_Bras[GAUCHE] = med_Bras_R + amplitude_Bras_R * sin_k_t;
	angle_Bras[DROITE] = med_Bras_R - amplitude_Bras_R * sin_k_t;
	angle_AvantBras[GAUCHE] = med_AvantBras_R + amplitude_AvantBras_R * sin_k_t;
	angle_AvantBras[DROITE] = med_AvantBras_R - amplitude_AvantBras_R * sin_k_t;
	angle_Cuisse[GAUCHE] = med_Cuisse_R + amplitude_Cuisse_R * sin_k_t;
	angle_Cuisse[DROITE] = med_Cuisse_R - amplitude_Cuisse_R * sin_k_t;
	angle_Mollet[GAUCHE] = med_Mollet_R + amplitude_Mollet_R * sin_k_t;
	angle_Mollet[DROITE] = med_Mollet_R - amplitude_Mollet_R * sin_k_t;
}

void seatCalc()
{
	if(angle_Cuisse[GAUCHE] < 85)
	{
		angle_Cuisse[GAUCHE] += l;
	}
	if(angle_Cuisse[DROITE] < 85)
	{
		angle_Cuisse[DROITE] += l;
	}
	if(angle_Mollet[GAUCHE] < -85)
	{
		angle_Cuisse[GAUCHE] -= l;
	}
	if(angle_Mollet[DROITE] < -85)
	{
		angle_Cuisse[DROITE] -= l;
	}
}

void idleCalc()
{
		if(angle_Bras[GAUCHE] > 0)
		{
			angle_Bras[GAUCHE] -= l;
		}
		if(angle_Bras[GAUCHE] < 0)
		{
			angle_Bras[GAUCHE] += l;
		}
		if(angle_Bras[DROITE] > 0)
		{
			angle_Bras[DROITE] -= l;
		}
		if(angle_Bras[DROITE] < 0)
		{
			angle_Bras[DROITE] += l;
		}

		if(angle_AvantBras[GAUCHE] > 0)
		{
			angle_AvantBras[GAUCHE] -= 2*l;
		}
		if(angle_AvantBras[GAUCHE] < 0)
		{
			angle_AvantBras[GAUCHE] += 2*l;
		}
		if(angle_AvantBras[DROITE] > 0)
		{
			angle_AvantBras[DROITE] -= 2*l;
		}
		if(angle_AvantBras[DROITE] < 0)
		{
			angle_AvantBras[DROITE] += 2*l;
		}

		if(angle_Cuisse[GAUCHE] > 0)
		{
			angle_Cuisse[GAUCHE] -= 2*l;
		}
		if(angle_Cuisse[GAUCHE] < 0)
		{
			angle_Cuisse[GAUCHE] += 2*l;
		}
		if(angle_Cuisse[DROITE] > 0)
		{
			angle_Cuisse[DROITE] -= 2*l;
		}
		if(angle_Cuisse[DROITE] < 0)
		{
			angle_Cuisse[DROITE] += 2*l;
		}

		if(angle_Mollet[GAUCHE] > 0)
		{
			angle_Mollet[GAUCHE] -= 2*l;
		}
		if(angle_Mollet[GAUCHE] < 0)
		{
			angle_Mollet[GAUCHE] += 2*l;
		}
		if(angle_Mollet[DROITE] > 0)
		{
			angle_Mollet[DROITE] -= 2*l;
		}
		if(angle_Mollet[DROITE] < 0)
		{
			angle_Mollet[DROITE] += 2*l;
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

transition *trouveTransition(float *var)
{
	transition *T = first_Transi;
	while(T != NULL)
	{
		if(T->var == var)
		{
			return T;
		}
		T = T->next;
	}
	return NULL;
}

void transitionnage()
{
	transition *T = first_Transi;
	while(T != NULL)
	{
		if(!T->fini)
		{
			if(abs(T->value - *(T->var)) <= abs(T->increm))
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

void deterAngle()
{
	int angle;
	if(direction_Y == 1)
	{
		switch(direction_X)
		{
			case 0 :
				angle = 0;
				break;
			case 1 :
				angle = 315;
				break;
			case -1 :
				angle = 45;
				break;
		}
	}
	else if(direction_Y == -1)
	{
		switch(direction_X)
		{
			case 0 :
				angle = 180;
				break;
			case 1 :
				angle = 225;
				break;
			case -1 :
				angle = 135;
				break;
		}
	}
	else
	{
		switch(direction_X)
		{
			case 0 :
				angle = 0;
				break;
			case 1 :
				angle = 270;
				break;
			case -1 :
				angle = 90;
				break;
		}
	}
	transition *T = trouveTransition(&(homme.rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	if(homme.rotat[ANGLE] > 180 && angle < 180)
	{
		angle += 360;
	}
	createTransition(&(homme.rotat[ANGLE]), angle, 5);
}

void makeRunning()
{
	transition *T;
	doing = RUN;
	k = COEFF_RUN;
	
	T = trouveTransition(&dt);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&dt, 5, 0.01f);

	T = trouveTransition(&vitesse);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&vitesse, VITESSE_RUN, 0.001f);

	// Epaule droite
	T = trouveTransition(&homme.compo[EPAULE_DROITE].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].angle_Ini[MIN]), angle_Bras_Ini_R[MIN], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_DROITE].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].angle_Ini[MAX]), angle_Bras_Ini_R[MAX], RUN_INCREM);

	// Coude droit
	T = trouveTransition(&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MIN]), angle_AvantBras_Ini_R[MIN], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MAX]), angle_AvantBras_Ini_R[MAX], RUN_INCREM);

	// Epaule gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].angle_Ini[MIN]), angle_Bras_Ini_R[MAX], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].angle_Ini[MAX]), angle_Bras_Ini_R[MIN], RUN_INCREM);

	// Coude gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MIN]), angle_AvantBras_Ini_R[MAX], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MAX]), angle_AvantBras_Ini_R[MIN], RUN_INCREM);

	// Cuisse Droite
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MIN]), angle_Cuisse_Ini_R[MIN], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MAX]), angle_Cuisse_Ini_R[MAX], RUN_INCREM);

	// Genou Droit
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MIN]), angle_Mollet_Ini_R[MIN], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MAX]), angle_Mollet_Ini_R[MAX], RUN_INCREM);


	// Cuisse Gauche 
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MIN]), angle_Cuisse_Ini_R[MAX], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MAX]), angle_Cuisse_Ini_R[MIN], RUN_INCREM);

	// Genou Droit
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MIN]), angle_Mollet_Ini_R[MAX], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MAX]), angle_Mollet_Ini_R[MIN], RUN_INCREM);

/*	angle Perso
	T = trouveTransition(&(homme.rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.rotat[ANGLE]), RUN_ANGLE, RUN_INCREM);
	*/
}

void makeWalking()
{
	transition *T;
	doing = WALK;
	k = COEFF_WALK;
	
	T = trouveTransition(&dt);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&dt, 0, 0.01f);

	T = trouveTransition(&vitesse);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&vitesse, VITESSE_WALK, 0.001f);

	// Epaule droite
	T = trouveTransition(&homme.compo[EPAULE_DROITE].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].angle_Ini[MIN]), angle_Bras_Ini[MIN], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_DROITE].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].angle_Ini[MAX]), angle_Bras_Ini[MAX], RUN_INCREM);

	// Coude droit
	T = trouveTransition(&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MIN]), angle_AvantBras_Ini[MIN], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MAX]), angle_AvantBras_Ini[MAX], RUN_INCREM);

	// Epaule gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].angle_Ini[MIN]), angle_Bras_Ini[MAX], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].angle_Ini[MAX]), angle_Bras_Ini[MIN], RUN_INCREM);

	// Coude gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MIN]), angle_AvantBras_Ini[MAX], RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MAX]), angle_AvantBras_Ini[MIN], RUN_INCREM);

	// Cuisse Droite
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MIN]), angle_Cuisse_Ini[MIN], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MAX]), angle_Cuisse_Ini[MAX], RUN_INCREM);

	// Genou Droit
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MIN]), angle_Mollet_Ini[MIN], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MAX]), angle_Mollet_Ini[MAX], RUN_INCREM);


	// Cuisse Gauche 
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MIN]), angle_Cuisse_Ini[MAX], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MAX]), angle_Cuisse_Ini[MIN], RUN_INCREM);

	// Genou Droit
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MIN]), angle_Mollet_Ini[MAX], RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MAX]), angle_Mollet_Ini[MIN], RUN_INCREM);

/*	angle Perso
	T = trouveTransition(&(homme.rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.rotat[ANGLE]), RUN_ANGLE, RUN_INCREM);
	*/
}

void makeSeat()
{
	transition *T;
	doing = SEAT;
	
	vitesse = 0;
	dt=0;

	// Epaule droite
	T = trouveTransition(&homme.compo[EPAULE_DROITE].rotat[ANGLE]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].rotat[ANGLE]), angle_Seat_Epaule, angle_increm);

	// Epaule gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].rotat[ANGLE]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].rotat[ANGLE]), angle_Seat_Epaule, angle_increm);

	// Coude droit
	T = trouveTransition(&homme.compo[EPAULE_DROITE].compo[0].compo[0].rotat[ANGLE]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].compo[0].compo[0].rotat[ANGLE]), angle_Seat_Coude, angle_increm);

	// Coude gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].rotat[ANGLE]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].rotat[ANGLE]), angle_Seat_Coude, angle_increm);

	// Cuisse Droite
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].rotat[ANGLE]), angle_Seat_Cuisse, angle_increm);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].rotat[ANGLE]), angle_Seat_Cuisse, angle_increm);

	// Genou Droit
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].rotat[ANGLE]), angle_Seat_Genou, angle_increm);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].rotat[ANGLE]), angle_Seat_Genou, angle_increm);

	T = trouveTransition(&(homme.rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.rotat[ANGLE]), 180, 5);	

	T = trouveTransition(&(homme.pos[X]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.pos[X]), chaise.pos[X], 0.01);	

	T = trouveTransition(&(homme.pos[Y]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.pos[Y]), chaise.pos[Y], 0.01);	

	T = trouveTransition(&(homme.pos[Z]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.pos[Z]), chaise.pos[Z]+8, 0.01);	
}

void collisionHommeChaise()
{
	float homme_X = TRONC_R*sin(homme.rotat[ANGLE])+homme.pos[X];
	float homme_Y = TRONC_R*TRONC_SCL_Y*cos(homme.rotat[ANGLE])+homme.pos[Y];
	float chaise_min_x = -3.575 + chaise.pos[X];
	float chaise_max_x = 3.575 + chaise.pos[X];
	float chaise_min_y = -3.575 + chaise.pos[Y];
	float chaise_max_y = 3.575 + chaise.pos[Y]+vitesse/0.1;

	fprintf(stderr, "%f %f %f %f %f %f\n", homme_X, homme_Y, chaise_min_x, chaise_max_x, chaise_min_y, chaise_max_y);

	if(homme_X > chaise_min_x && homme_X < chaise_max_x && homme_Y > chaise_min_y && homme_Y < chaise_max_y)
	{
		if(direction_Y != -1)
		{
			doing = SEAT;
			makeSeat();
		}
		else
		{
			doing = IDLE;
			makeIdle();
		}
	}
}

void makeIdle()
{
	transition *T;
	doing = IDLE;
	k = COEFF_WALK;
	
	T = trouveTransition(&dt);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&dt, 0, 0.01f);

	T = trouveTransition(&vitesse);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&vitesse, 0, 0.1f);

	// Epaule droite
	T = trouveTransition(&homme.compo[EPAULE_DROITE].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].angle_Ini[MIN]), 0, RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_DROITE].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].angle_Ini[MAX]), 0, RUN_INCREM);

	// Coude droit
	T = trouveTransition(&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MIN]), 0, RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_DROITE].compo[0].compo[0].angle_Ini[MAX]), 0, RUN_INCREM);

	// Epaule gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].angle_Ini[MIN]), 0, RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].angle_Ini[MAX]), 0, RUN_INCREM);

	// Coude gauche
	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MIN]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MIN]), 0, RUN_INCREM);

	T = trouveTransition(&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MAX]);
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition((&homme.compo[EPAULE_GAUCHE].compo[0].compo[0].angle_Ini[MAX]), 0, RUN_INCREM);

	// Cuisse Droite
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MIN]), 0, RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].angle_Ini[MAX]), 0, RUN_INCREM);

	// Genou Droit
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MIN]), 0, RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[DROITE].compo[0].angle_Ini[MAX]), 0, RUN_INCREM);


	// Cuisse Gauche 
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MIN]), 0, RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].angle_Ini[MAX]), 0, RUN_INCREM);

	// Genou Droit
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MIN]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MIN]), 0, RUN_INCREM);
	
	T = trouveTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MAX]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.compo[BASSIN].compo[GAUCHE].compo[0].angle_Ini[MAX]), 0, RUN_INCREM);

/*	angle Perso
	T = trouveTransition(&(homme.rotat[ANGLE]));
	if(T != NULL)
	{
		finTransition(T);
	}
	createTransition(&(homme.rotat[ANGLE]), RUN_ANGLE, RUN_INCREM);
	*/
}
