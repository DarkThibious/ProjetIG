#include "anim.h"

float t = 0.f;
float delta = 10.f;
float k = 0.001f;
float K = 0.002f;

float position = position_Ini;

float sin_k_t = 0;

int Step = 0;
int latence =4;

int prevDoing;
int doing = RUN;

// fonction de call-back pour la gestion des événements clavier
GLvoid window_key(unsigned char key, int x, int y) 
{  
	switch (key) 
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
		case '+':  
			delta *= 1.05;
			break; 
		case '-':  
			delta /= 1.05;
			break; 
		default:
			printf ("La touche %d n´est pas active.\n", key);
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
			case RUN:
				runCalc();
				break;
		}
	}
	glutTimerFunc(latence,&window_timer,++Step);
	glutPostRedisplay();
}

void runCalc()
{
	// On effecture une variation des angles de chaque membre
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
	position = K*t;
}

