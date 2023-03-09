
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
#include "tinyxml2.h"

using namespace std;
struct point {
    float x;
    float y;
	float z;
};
//string file = "box.3d";

std::vector<std::string> models ;


int camW,camL;
float alpha,betah,raio;
float lookAX, lookAY, lookAZ;
float camVX, camVY, camVZ;
float fov,near,far,pers;

std::vector<std::string> split(std::string s, std::string delimiter) 
{
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




void render3D(string file)
{
    string line;
    //glBegin(GL_TRIANGLES);
    ifstream indata;
    indata.open(file);
    glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

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
		glVertex3f(point[0], point[1], point[2]);
    }
    glEnd();
    indata.close();
}

void readXML(std::string source)
{
    using namespace tinyxml2;
    
    XMLDocument xml;
    xml.LoadFile(source.data());

    XMLElement *window = xml.FirstChildElement("world")->FirstChildElement("window");

    camW = atoi(window->Attribute("width"));
    camL = atoi(window->Attribute("height"));

    XMLElement *camera = xml.FirstChildElement("world")->FirstChildElement("camera");

    XMLElement *position = camera->FirstChildElement("position");
    float posx = atof(position->Attribute("x"));
    float posy = atof(position->Attribute("y"));
    float posz = atof(position->Attribute("z"));

    raio = sqrt(posx*posx + posy*posy + posz*posz);
    betah = asin(posy / raio);
    alpha = asin(posx / (raio * cos(betah)));


    XMLElement *lookAt = camera->FirstChildElement("lookAt");
    lookAX = atof(lookAt->Attribute("x"));
    lookAY = atof(lookAt->Attribute("y"));
    lookAZ = atof(lookAt->Attribute("z"));

    XMLElement *up = camera->FirstChildElement("up");
    camVX = atof(up->Attribute("x"));
    camVY = atof(up->Attribute("y"));
    camVZ = atof(up->Attribute("z"));

    XMLElement *projection = camera->FirstChildElement("projection");
    fov = atof(projection->Attribute("fov"));
    near = atof(projection->Attribute("near"));
    far = atof(projection->Attribute("far"));
    pers = camW/camL;
    XMLElement *MODELS = xml.FirstChildElement("world")->FirstChildElement("group")->FirstChildElement("models");
    XMLElement *model = MODELS->FirstChildElement("model");
    while (model) 
    {
        std::string model_path = model->Attribute("file");
        models.push_back ("../" + model_path);
        //render3D( model_path);
        model = model->NextSiblingElement("model");
    }
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
	gluPerspective(fov,pers,near,far);


	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}






void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	gluLookAt(sin(alpha)*cos(betah)*raio,sin(betah)*raio,cos(alpha)*cos(betah)*raio, 
		      lookAX, lookAY, lookAZ,
			  camVX, camVY, camVZ);

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

    for (auto i : models)
    {
        //printf("%s\n",i);
		render3D(i);
    }
    //render3D("../plane.3d");
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
            if(!(betah+M_PI/16>M_PI/2)){
                betah += M_PI/16;
            }
            break;
        case 's':
            if(!(betah-M_PI/16<-M_PI/2)){
                betah -= M_PI/16;
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

    if (argc > 1)
    {
        readXML(argv[1]);
    }
    

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(camW,camL);
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
