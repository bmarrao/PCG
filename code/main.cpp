
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

float alpha = M_PI/4, beta = M_PI/4,raio= sqrt(50);

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
	/*
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
	float radius1;
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
        glBegin(GL_TRIANGLES);

		//Base Baixo
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(ant.x, 0.0f, ant.z);
		glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(act.x, 0.0f,act.z);


		radius1 = (radius -  difr );
		aux1.y = 0;
		aux2.y = 0;

		for (int l = 0; l < stacks; l++)
		{
			//FALTA DESCOBRIR O Q PRECISO APLICAR AQUI
			
			
			
			glColor3f(0.5, 1.0, 0.0);

			glVertex3f(ant.x, ant.y, ant.z);
			glVertex3f(act.x, act.y, act.z);
			glVertex3f(aux2.x, aux2.y, aux2.z); 

			glColor3f(0.0, 1.0, 0.5);


			glVertex3f(aux2.x, aux2.y, aux2.z);
			glVertex3f(aux1.x, aux1.y, aux1.z);
			glVertex3f(ant.x, ant.y, ant.z); 

			//ACT E ANT VIRAM AUX1 e AUX2
			ant = aux1;
			act = aux2;
			
	
		}

		
		glEnd();
		*/
		//Base Baixo
		
		float ang = 0;
		float draio = radius/stacks;
		float alt = 0;
		float r = radius;
		glBegin(GL_TRIANGLES);
		for(int i = 0;i!= slices;i++){
		
        	glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f, 0, 0.0f);
			glVertex3f(sin(ang)*r, 0, cos(ang)*r);
			glVertex3f(sin(ang+(M_PI*2/slices))*r, 0, cos(ang+(M_PI*2/slices))*r);
			
			for (int j = 0;j != stacks;j++){
				
				glVertex3f(sin(ang)*r,alt, cos(ang)*r);
				glVertex3f(sin(ang+(M_PI*2/slices))*r, alt, cos(ang+(M_PI*2/slices))*r);
				glVertex3f(sin(ang)*(r-draio),alt+ height/stacks, cos(ang)*(r-draio));

				
				glVertex3f(sin(ang+(M_PI*2/slices))*r, alt, cos(ang+(M_PI*2/slices))*r);
				glVertex3f(sin(ang+(M_PI*2/slices))*(r-draio), alt+ height/stacks, cos(ang+(M_PI*2/slices))*(r-draio));
				glVertex3f(sin(ang)*(r-draio), alt + height/stacks, cos(ang)*(r-draio));
				
				r -= draio;
				alt += height/stacks;

				
			}
			alt = 0;
			r = radius;
			ang += 2*M_PI/slices;

		}
		
		glEnd();
	
	
}
// put code to draw cylinder in here



void drawSphere(float radius, int slices,int stacks) {
	float al = 0;
	float be = -M_PI/2;
	

	for(int j = 0;j!= stacks;j++){
		for(int i = 0;i!= slices;i++){
			glBegin(GL_TRIANGLES);
			glColor3f(0.0,1.0,0.0);
			glVertex3f(radius*cos(be)*sin(al), radius*sin(be), radius*cos(be)*cos(al));
			glVertex3f(radius*cos(be)*sin(al+2*M_PI/stacks), radius*sin(be), radius*cos(be)*cos(al+2*M_PI/stacks));
			glVertex3f(radius*cos(be+M_PI/slices)*sin(al), radius*sin(be+M_PI/slices), radius*cos(be+M_PI/slices)*cos(al));
			glEnd();

			glBegin(GL_TRIANGLES);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(radius*cos(be)*sin(al+2*M_PI/stacks), radius*sin(be), radius*cos(be)*cos(al+2*M_PI/stacks));
			glVertex3f(radius*cos(be+M_PI/slices)*sin(al+2*M_PI/stacks), radius*sin(be+M_PI/slices), radius*cos(be+M_PI/slices)*cos(al+2*M_PI/stacks));
			glVertex3f(radius*cos(be+M_PI/slices)*sin(al), radius*sin(be+M_PI/slices), radius*cos(be+M_PI/slices)*cos(al));
			glEnd();
			al += 2*M_PI/stacks;
			
		}
		be += M_PI/slices;
	}

}

void drawPlane(int comp, int slices) {
	glColor3f(0.0f, 1.0f, 0.0f);
	int aresta = comp / slices; // comprimento do triangulo
	int posicao = comp / 2;	 // posicionar corretamente no centro do eixo
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {
			glBegin(GL_TRIANGLES);

			glVertex3f(i * aresta - posicao, 0, j * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, 0, (j + 1) * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, 0, j * aresta - posicao);

			glVertex3f(i * aresta - posicao, 0, j * aresta - posicao);
			glVertex3f(i * aresta - posicao, 0, (j + 1) * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, 0, (j + 1) * aresta - posicao);
			glEnd();
		}
	}
}

void drawCube(int comp, int slices) {
	glColor3f(0.0f, 1.0f, 0.0f);
	int aresta = comp / slices; // comprimento do triangulo
	int posicao = comp / 2;	 // posicionar corretamente no centro do eixo
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {
			glBegin(GL_TRIANGLES);

			// Face de cima
			glVertex3f(i * aresta - posicao, comp / 2, j * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, comp / 2, (j + 1) * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, comp / 2, j * aresta - posicao);

			glVertex3f(i * aresta - posicao, comp / 2, j * aresta - posicao);
			glVertex3f(i * aresta - posicao, comp / 2, (j + 1) * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, comp / 2, (j + 1) * aresta - posicao);

			// Face de baixo
			glVertex3f(i * aresta - posicao, -comp / 2, j * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, -comp / 2, (j + 1) * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, -comp / 2, j * aresta - posicao);

			glVertex3f(i * aresta - posicao, -comp / 2, j * aresta - posicao);
			glVertex3f(i * aresta - posicao, -comp / 2, (j + 1) * aresta - posicao);
			glVertex3f((i + 1) * aresta - posicao, -comp / 2, (j + 1) * aresta - posicao);


			// Face de X constante negativo
			glVertex3f(-comp / 2, i * aresta - posicao, j * aresta - posicao);
			glVertex3f(-comp / 2, (i + 1) * aresta - posicao, (j + 1) * aresta - posicao);
			glVertex3f(-comp / 2, (i + 1) * aresta - posicao, j * aresta - posicao);

			glVertex3f(-comp / 2, i * aresta - posicao, j * aresta - posicao);
			glVertex3f(-comp / 2, i * aresta - posicao, (j + 1) * aresta - posicao);
			glVertex3f(-comp / 2, (i + 1) * aresta - posicao, (j + 1) * aresta - posicao);

			// Face de X constante positivo
			glVertex3f(comp / 2, i * aresta - posicao, j * aresta - posicao);
			glVertex3f(comp / 2, (i + 1) * aresta - posicao, (j + 1) * aresta - posicao);
			glVertex3f(comp / 2, (i + 1) * aresta - posicao, j * aresta - posicao);

			glVertex3f(comp / 2, i * aresta - posicao, j * aresta - posicao);
			glVertex3f(comp / 2, i * aresta - posicao, (j + 1) * aresta - posicao);
			glVertex3f(comp / 2, (i + 1) * aresta - posicao, (j + 1) * aresta - posicao);

			// Face de Z constante negativo
			glVertex3f(i * aresta - posicao, j * aresta - posicao, -comp / 2);
			glVertex3f((i + 1) * aresta - posicao, (j + 1) * aresta - posicao, -comp / 2);
			glVertex3f((i + 1) * aresta - posicao, j * aresta - posicao, -comp / 2);

			glVertex3f(i * aresta - posicao, j * aresta - posicao, -comp / 2);
			glVertex3f(i * aresta - posicao, (j + 1) * aresta - posicao, -comp / 2);
			glVertex3f((i + 1) * aresta - posicao, (j + 1) * aresta - posicao, -comp / 2);

			// Face de Z constante positivo
			glVertex3f(i * aresta - posicao, j * aresta - posicao, comp / 2);
			glVertex3f((i + 1) * aresta - posicao, (j + 1) * aresta - posicao, comp / 2);
			glVertex3f((i + 1) * aresta - posicao, j * aresta - posicao, comp / 2);

			glVertex3f(i * aresta - posicao, j * aresta - posicao, comp / 2);
			glVertex3f(i * aresta - posicao, (j + 1) * aresta - posicao, comp / 2);
			glVertex3f((i + 1) * aresta - posicao, (j + 1) * aresta - posicao, comp / 2);

			glEnd();
		}
	}
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(sin(alpha)*cos(beta)*raio,sin(beta)*raio,cos(alpha)*cos(beta)*raio, 
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
	drawCube(4, 4);
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
	
	switch(key){
		case 'a':
			alpha -= M_PI/16;
			break;
		case 'd':
			alpha += M_PI/16;
			break;
		case 'w':
			if(!(beta+M_PI/16>M_PI/2)){
				beta += M_PI/16;
			}
			break;
		case 's':
			if(!(beta-M_PI/16<-M_PI/2)){
				beta -= M_PI/16;
			}
			break;
		case 'z':
			raio += 1;
			break;
		case 'x':
			raio -= 1;
			break;
	}
	glutPostRedisplay();
	
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

