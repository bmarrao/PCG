
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>	
struct point {
    float x;
    float y;
	float z;
};

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCone(float radius, float height, int slices,int stacks	) 
{
    int i = 0;
    float j;
    float x;
    float ang = 2*M_PI / slices;
	float dify = height /stacks ;
	float difr = radius / stacks ;
	point ant ;
	point act ;	
	point aux1;
	point aux2;
    for (;i < slices; )
    {
        x = ang * i;
        i++;
        j = ang * i;
		//ant.x
		ant.x = radius*sin(x);
		//ant.z
		ant.y = 0;
		//z1
		ant.z = radius * cos(x);
		//act.x
		act.x = radius*sin(j);
		//y2
		act.y = 0;
		//z2
		act.z = radius * cos(j);
		glPolygonMode(GL_FRONT, GL_FILL);
        glBegin(GL_TRIANGLES);

		//Base Baixo
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(ant.x, 0.0f, ant.z);
        glVertex3f(act.x, 0.0f,act.z);
        glVertex3f(0.0f, 0.0f, 0.0f);     

		for (int l = 0; l < stacks-1; l++)
		{
			//FALTA DESCOBRIR O Q PRECISO APLICAR AQUI
			aux1.x = radius*sin(x);
			aux1.y = 0;
			aux1.z = radius * cos(x);
			aux2.x = radius*sin(j);
			aux2.y = 0;
			aux2.z = radius * cos(j);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(act.x, act.y, act.z);
			glVertex3f(ant.x, ant.y, ant.z);
			glVertex3f(aux2.x, aux2.y, aux2.z); 


			glVertex3f(aux2.x, aux2.y, aux.z);
			glVertex3f(aux1.x, aux1.y, aux1.z);
			glVertex3f(ant.x, ant.y, ant.z); 

		}
		
		//ultimo triang
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(ant.x, 0.0f, ant.z);
        glVertex3f(act.x, 0.0f, act.z);
        glVertex3f(0.0f, height, 0.0f); 
        glEnd();
		

        
    }
// put code to draw cylinder in here

}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	glBegin(GL_LINES);
	// X axis in red
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);

	glEnd();
	drawCone(1,2,10,0);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}


int main(int argc, char **argv) 
{

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

