#include "disp.h"


int main(int argc, char **argv) 
{  
	// initialisation  des param�tres de GLUT en fonction
	// des arguments sur la ligne de commande
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// d�finition et cr�ation de la fen�tre graphique
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Avatar anim�");

	// initialisation de OpenGL et de la sc�ne
	initGL();  
	init_scene();

	// choix des proc�dures de callback pour 
	// le trac� graphique
	glutDisplayFunc(&window_display);
	// le redimensionnement de la fen�tre
	glutReshapeFunc(&window_reshape);
	// la gestion des �v�nements clavier
	glutKeyboardFunc(&window_key);
	// fonction appel�e r�guli�rement entre deux gestions d��v�nements
	glutTimerFunc(latence,&window_timer,Step);

	// la boucle prinicipale de gestion des �v�nements utilisateur
	glutMainLoop();  

	return 1;
}
