
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

using namespace tinyxml2;
using namespace std;
struct point {
    float x;
    float y;
	float z;
};

struct rotates{

    float rotx;
    float roty;
    float rotz;
    float ang;
    
};

struct translate{

    float transx;
    float transy;
    float transz;
    
};

struct scale{

    float scax;
    float scay;
    float scaz;
};

struct Transformations 
{
    translate t;
    rotates r;
    scale s;
    int escolha ;

};
struct Group 
{
    std::vector<struct Transformations> transformacoes;
    int trans = 0;
    int rota = 0;
    int sca = 0;
    std::vector<Group> grupos;
    std::vector<string> models;
};


/*
class Group{    
    public:
        
        std::vector<Group> grupos;
        std::vector<string> models;
        
        void transacoes() {  
            if (trans == 1){
                glTranslated(t.transx,t.transy,t.transz);
            }
            if (rota == 1){
                glrotatesd(r.ang,r.rotx,r.roty,r.rotz);
            }
            if (sca == 1){
                glScaled(s.scax,s.scay,s.scaz);
            }

        }
};
*/
//string file = "box.3d";

std::vector<Group> groups;


int once = 0;

int camW,camL;
float alpha,betah,raio;
float lookAX, lookAY, lookAZ;
float camVX, camVY, camVZ;
float fov,near,far,pers;

float transx ,transy,transz;
float rotx,roty,rotz;
float scax,scay,scaz;

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




void render3D(string file)
{
    string line;
    //glBegin(GL_TRIANGLES);
    ifstream indata;
    indata.open(file);
    glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);

    while ( getline (indata,line) ){

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
/*
void printgroup(struct Group g){
    for(auto i :g.grupos){
        printgroup(i);
    }
    for(auto j: g.models){
        cout<<j<<"\n";
    }
    printf("%f %f %f\n", g.t.transx,g.t.transy,g.t.transz);
    printf("%f %f %f %f\n", g.r.ang,g.r.rotx,g.r.roty,g.r.rotz);
    printf("%f %f %f\n", g.s.scax,g.s.scay,g.s.scaz);
}
*/

struct Group readGroup(XMLElement *group){

    
    XMLElement *trans = group-> FirstChildElement("transform");
    XMLElement *translate = trans-> FirstChildElement("translate");
    XMLElement *rotates = trans-> FirstChildElement("rotate");
    XMLElement *scale = trans-> FirstChildElement("scale");
    struct translate t;
    struct rotates r;
    struct scale s;
    struct Group grupo ;
    
    if (trans){
        if (translate){
            t.transx = atof(translate->Attribute("x"));
            t.transy = atof(translate->Attribute("y"));
            t.transz = atof(translate->Attribute("z"));
            struct Transformations transformacao ;
            transformacao.escolha = 0;
            transformacao.t = t;
            grupo.transformacoes.push_back(transformacao);
        }
        if (rotates)
        {
            r.rotx = atof(rotates->Attribute("x"));
            r.roty = atof(rotates->Attribute("y"));
            r.rotz = atof(rotates->Attribute("z"));
            r.ang = atof(rotates->Attribute("angle"));
            struct Transformations transformacao ;
            transformacao.escolha = 1;
            transformacao.r = r;
            grupo.transformacoes.push_back(transformacao);
        }
        if (scale)
        {
            s.scax = atof(scale->Attribute("x"));
            s.scay = atof(scale->Attribute("y"));
            s.scaz = atof(scale->Attribute("z"));
            struct Transformations transformacao ;
            transformacao.escolha = 2;
            transformacao.s = s;
            grupo.transformacoes.push_back(transformacao);
        }
    }
    
    XMLElement *MODELS = group->FirstChildElement("models");
    if(MODELS){
        XMLElement *model = MODELS->FirstChildElement("model");
    
        while (model) {
            
            std::string model_path = model->Attribute("file");
            
            grupo.models.push_back("../../3d/" + model_path);
            
            //mod.models.push_back(mod);
            //models.push_back ("../../3d/" + model_path);
            //render3D(aux);
            model = model->NextSiblingElement("model");
            
        }
    }
    //printgroup(grupo);
    group = group->FirstChildElement("group");
    while (group){
        grupo.grupos.push_back(readGroup(group));
        group = group->NextSiblingElement("group");
    }
   
    return grupo;
}

void readXML(std::string source){
    
    source = "../../test_files/" + source;
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
    XMLElement *GROUP = xml.FirstChildElement("world")->FirstChildElement("group");
    XMLElement *group = GROUP;
    
    while (group){
        
        groups.push_back(readGroup(group));
        group = group->NextSiblingElement("group");
    }
    /*
    for(auto i: groups){
        printgroup(i);
    }
    */
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

void transacoes(struct Group g)
{
    for(auto t : g.transformacoes)
    {
        if (t.escolha == 0){
            glTranslated(t.t.transx,t.t.transy,t.t.transz);
        }
        else if (t.escolha == 1){
            glRotated(t.r.ang,t.r.rotx,t.r.roty,t.r.rotz);
        }
        else if (t.escolha == 2){
            glScaled(t.s.scax,t.s.scay,t.s.scaz);
        }
    }
    
}


void recFilhos(struct Group g){


    glPushMatrix();
    transacoes(g);
    for (auto j: g.models){
        render3D(j);
    }
        
    for (auto j : g.grupos) 
        recFilhos(j);    
    glPopMatrix();
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

    int last = 0;
    for (auto i : groups){
        recFilhos(i);
        
    }
	glutSwapBuffers();
}
/*
void recursiva(translate , rotates, scale , model)
{

    recursiva(translate,rotates,scale,model);
}
*/
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
    readXML("test_2_4.xml");
    /*
    if (argc > 1)
    {
        readXML(argv[1]);
    }
    */
    

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
