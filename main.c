#include "disp.h"


int main(int argc, char **argv) 
{  
	// initialisation  des paramètres de GLUT en fonction
	// des arguments sur la ligne de commande
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// définition et création de la fenêtre graphique
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Avatar animé");

	// initialisation de OpenGL et de la scène
	initGL();  
	init_scene();

	// choix des procédures de callback pour 
	// le tracé graphique
	glutDisplayFunc(&window_display);
	// le redimensionnement de la fenêtre
	glutReshapeFunc(&window_reshape);
	// la gestion des événements clavier
	glutKeyboardFunc(&window_key);
	// fonction appelée régulièrement entre deux gestions d´événements
	glutTimerFunc(latence,&window_timer,Step);

	// la boucle prinicipale de gestion des événements utilisateur
	glutMainLoop();  

	return 1;
}
