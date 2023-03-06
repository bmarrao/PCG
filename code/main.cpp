
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
struct point {
    float x;
    float y;
	float z;
};
char * file = "cone.3d";
float alpha = M_PI/4, beta = M_PI/4,raio= sqrt(50);

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


void render3D(char * file)
{
    string line;
    //glBegin(GL_TRIANGLES);
    ifstream indata;
    indata.open(file);
    while ( getline (indata,line) )
    {
        std::string delimiter = ",";
        std::vector<std::string> v = split (line, delimiter);
		float point [3];
		int j = 0;
        for (auto i : v)
        {
			point[j] = atof(i.c_str());
			j = j + 1;
        }
		glBegin(GL_TRIANGLES);
		glVertex3f(point[0], point[1], point[2]);
        //cout << x << y << z;
    }
    indata.close();
}


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






void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
    /*
	gluLookAt(sin(alpha)*cos(beta)*raio,sin(beta)*raio,cos(alpha)*cos(beta)*raio, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
    */
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

    render3D(file);
	glEnd();
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
    /*
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
    */
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

