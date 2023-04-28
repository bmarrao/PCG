#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
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
    float time;

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


struct catmullRom
{

    std::vector<point> pontos;
    float time ;
    int align;

};

struct Transformations
{
    translate t;
    rotates r;
    scale s;
    catmullRom c;
    int escolha ;

};

struct modelos
{
    string modelo;
    int inicio ;
    int verticeCount;
};

struct Group
{
    std::vector<struct Transformations> transformacoes;
    std::vector<Group> grupos;
    std::vector<modelos> models;
};

std::vector<Group> groups;


int camW,camL;
float alpha,betah,raio;
float lookAX, lookAY, lookAZ;
float camVX, camVY, camVZ;
float fov,nears,fars,pers;
GLuint buffers[1];
float dx,dz;
float camX, camY,camZ;
std::vector<float> p;
int startX, startY, tracking = 0;
float a = 0;
GLuint indice;
float transx ,transy,transz;
float rotx,roty,rotz;
float scax,scay,scaz;

std::vector<std::string> split(std::string s, std::string delimiter) 
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) 
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token); "bezier_10.3d";
    }

    res.push_back (s.substr (pos_start));
    return res;
}


void printgroup(struct Group g){
    for(auto i :g.grupos){
        printgroup(i);
    }
    for(auto j: g.models){
        cout<<j.modelo<< " " << j.inicio << " " << j.verticeCount << "\n";

        for (int i = 0 ; i < (j.verticeCount * 3) - j.inicio; i++)
        {
            cout << p[i] << "\n";
        }

    }
    /*
    for(auto tran : g.transformacoes){
        cout << tran.escolha << "\n";
    }
     */
}

void createVBO(string file)
{
    std::string line;
    ifstream indata;
    indata.open(file);
    while ( getline (indata,line) )
    {

        std::string delimiter = ",";
        std::vector<std::string> v = split (line, delimiter);

        for (auto i : v)
        {
            p.push_back(atof(i.c_str()));
        }  
        indice++;



    }
    indata.close();
}

struct Group readGroup(XMLElement *group)
{


    XMLElement *trans = group-> FirstChildElement("transform");

    XMLElement *filho;
    struct Group grupo ;
    if (trans)
    {
        XMLElement *translate ;
        XMLElement *rotates ;
        XMLElement *scale;
        XMLElement *catmull;
        translate = trans-> FirstChildElement("translate");
        rotates = trans-> FirstChildElement("rotate");
        scale = trans-> FirstChildElement("scale");
        filho = trans->FirstChildElement();

        while (filho){
            string nome;
            nome = filho->Name();

            if (nome == "translate")
            {
                struct Transformations transformacao ;
                catmull = translate->FirstChildElement("point");
                if (catmull)
                {
                    catmullRom c ;
                    c.time = atof(translate->Attribute("time"));
                    point ponto ;
                    ponto.x = atof(translate->Attribute("x"));
                    ponto.y = atof(translate->Attribute("y"));
                    ponto.z = atof(translate->Attribute("z"));
                    c.pontos.push_back(ponto);
                    catmull = catmull->NextSiblingElement();
                    while(catmull)
                    {
                        ponto.x = atof(translate->Attribute("x"));
                        ponto.y = atof(translate->Attribute("y"));
                        ponto.z = atof(translate->Attribute("z"));
                        catmull = catmull->NextSiblingElement();
                        c.pontos.push_back(ponto);
                        transformacao.c = c;


                    }
                    transformacao.escolha =3 ;
                }
                else
                {
                    struct translate t;
                    t.transx = atof(translate->Attribute("x"));
                    t.transy = atof(translate->Attribute("y"));
                    t.transz = atof(translate->Attribute("z"));
                    transformacao.escolha = 0;
                    transformacao.t = t;

                }


                
                grupo.transformacoes.push_back(transformacao);
            }
            else if (nome == "rotate")
            {
                struct rotates r;
                r.rotx = atof(rotates->Attribute("x"));
                r.roty = atof(rotates->Attribute("y"));
                r.rotz = atof(rotates->Attribute("z"));
                if (rotates->Attribute("angle")){
                    r.ang = atof(rotates->Attribute("angle"));
                    r.time = 0.0f;
                }else{
                    r.time= atof(rotates->Attribute("time"));
                    r.ang = 0.0f;
                }
                struct Transformations transformacao ;
                transformacao.escolha = 1;
                transformacao.r = r;
                grupo.transformacoes.push_back(transformacao);
            }
            else if (nome == "scale")
            {
                struct scale s;
                s.scax = atof(scale->Attribute("x"));
                s.scay = atof(scale->Attribute("y"));
                s.scaz = atof(scale->Attribute("z"));
                struct Transformations transformacao ;
                transformacao.escolha = 2;
                transformacao.s = s;
                grupo.transformacoes.push_back(transformacao);
            }
            filho = filho->NextSiblingElement();
        }
    }
    XMLElement *MODELS = group->FirstChildElement("models");
    if(MODELS){
        XMLElement *model = MODELS->FirstChildElement("model");

        while (model)
        {

            std::string model_path = model->Attribute("file");

            modelos g ;
            g.modelo = "../../3d/" + model_path;
            g.inicio = indice;
            createVBO(g.modelo);
            g.verticeCount = indice - g.inicio;
            grupo.models.push_back(g);
            model = model->NextSiblingElement("model");

        }
    }


    group = group->FirstChildElement("group");
    while (group)
    {
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

    camX = sin(alpha)*cos(betah)*raio;
    camY = sin(betah)*raio;
    camZ = cos(alpha)*cos(betah)*raio;

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
    nears = atof(projection->Attribute("near"));
    fars = atof(projection->Attribute("far"));
    pers = camW/camL;
    XMLElement *GROUP = xml.FirstChildElement("world")->FirstChildElement("group");
    XMLElement *group = GROUP;


    //glGenBuffers(1, buffers);
    while (group){
        groups.push_back(readGroup(group));
        group = group->NextSiblingElement("group");
    }

    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(
            GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
            sizeof(float) * p.size(), // tamanho do vector em bytes
            p.data(), // os dados do array associado ao vector
            GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)*/

    for (auto i : groups)
    {
        printgroup(i);
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
    gluPerspective(fov,pers,nears,fars);


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
            if (t.r.time == 0)
                glRotated(t.r.ang,t.r.rotx,t.r.roty,t.r.rotz);
            else{
                t.r.ang += 360/t.r.time;
                glRotated(t.r.ang,t.r.rotx,t.r.roty,t.r.rotz);
            }
        }
        else if (t.escolha == 2){
            glScaled(t.s.scax,t.s.scay,t.s.scaz);
        }
    }

}



void recFilhos(struct Group g)
{

    glPushMatrix();
    transacoes(g);
    for (auto j: g.models)
    {
        //printgroup(g)
        glDrawArrays(GL_TRIANGLES, j.inicio, j.verticeCount);
    }

    //glEnd();
    for (auto j : g.grupos)
        recFilhos(j);
    glPopMatrix();
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    gluLookAt(camX,camY,camZ,
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
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    
    for (auto i : groups)
    {
        recFilhos(i);

    }


    glutSwapBuffers();
}
void processKeys(unsigned char key, int xx, int yy) {
    switch(key){
        case 'h':
            alpha -= M_PI/16;
            camX = sin(alpha)*cos(betah)*raio;
            camY = sin(betah)*raio;
            camZ = cos(alpha)*cos(betah)*raio;
            break;
        case 'k':
            alpha += M_PI/16;
            camX = sin(alpha)*cos(betah)*raio;
            camY = sin(betah)*raio;
            camZ = cos(alpha)*cos(betah)*raio;
            break;
        case 'u':
            if(!(betah+M_PI/16>M_PI/2)){
                betah += M_PI/16;
            }
            camX = sin(alpha)*cos(betah)*raio;
            camY = sin(betah)*raio;
            camZ = cos(alpha)*cos(betah)*raio;
            break;
        case 'j':
            if(!(betah-M_PI/16<-M_PI/2)){
                betah -= M_PI/16;
            }
            camX = sin(alpha)*cos(betah)*raio;
            camY = sin(betah)*raio;
            camZ = cos(alpha)*cos(betah)*raio;
            break;
        case 'z':
            raio += 1;
            camX = sin(alpha)*cos(betah)*raio;
            camY = sin(betah)*raio;
            camZ = cos(alpha)*cos(betah)*raio;
            break;
        case 'x':
            raio -= 1;
            camX = sin(alpha)*cos(betah)*raio;
            camY = sin(betah)*raio;
            camZ = cos(alpha)*cos(betah)*raio;
            break;

        case 'p':
            a = 0;
            camX = 0.0f;
            camZ = 0.0f;
            camY = 0.0f;
            lookAX = camX + sin(a);
            lookAZ = camZ + cos(a);
            lookAY = camY;
            break;
        case 'i':
            a += M_PI/16;

            lookAX = camX + sin(a);
            lookAZ = camZ + cos(a);
            lookAY = camY;
            break;
        case 'o':
            a -= M_PI/16;

            lookAX = camX + sin(a);
            lookAZ = camZ + cos(a);
            lookAY = camY;
            break;
        case 'w':

            dx = (lookAX-camX)*3;
            dz = (lookAZ-camZ)*3;
            camX = camX + dx;
            camZ = camZ + dz;
            lookAX = lookAX +  dx;
            lookAZ = lookAZ +  dz;
            lookAY = camY;
            //lookY = camY;
            break;
        case 's':

                dx = (lookAX-camX)*3;
                dz = (lookAZ-camZ)*3;
                camX = camX - dx;
                camZ = camZ - dz;
                lookAX = lookAX -  dx;
                lookAZ = lookAZ -  dz;
                lookAY = camY;

                break;
            case 'a':

                camX += 1;
                lookAX = camX + sin(a);
                lookAZ = camZ + cos(a);
                lookAY = camY;
                break;
            case 'd':

                camX -= 1;

                lookAX = camX + sin(a);
                lookAZ = camZ + cos(a);
                lookAY = camY;
                break;


        }

        glutPostRedisplay();
    }

    /*
    void processMouseButtons(int button, int state, int xx, int yy) {

        if (state == GLUT_DOWN)  {
            startX = xx;
            startY = yy;
            if (button == GLUT_LEFT_BUTTON)
                tracking = 1;
            else if (button == GLUT_RIGHT_BUTTON)
                tracking = 2;
            else
                tracking = 0;
        }
        else if (state == GLUT_UP) {
            if (tracking == 1) {
                alpha += (xx - startX);
                betah += (yy - startY);
            }
            else if (tracking == 2) {

                raio -= yy - startY;
                if (raio < 3)
                    raio = 3.0;
            }
            tracking = 0;
        }
    }

    void processMouseMotion(int xx, int yy) {

        int deltaX, deltaY;
        int alphaAux, betaAux;
        int rAux;

        if (!tracking)
            return;

        deltaX = xx - startX;
        deltaY = yy - startY;

        if (tracking == 1) {


            alphaAux = alpha + deltaX;
            betaAux = betah + deltaY;

            if (betaAux > 85.0)
                betaAux = 85.0;
            else if (betaAux < -85.0)
                betaAux = -85.0;

            rAux = raio;
        }
        else if (tracking == 2) {

            alphaAux = alpha;
            betaAux = betah;
            rAux = raio - deltaY;
            if (rAux < 3)
                rAux = 3;
        }
        camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
        camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
        camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
    }
    */
    void processSpecialKeys(int key, int xx, int yy) {

    // put code to process special keys in here

    }


    int main(int argc, char **argv)
    {
        //readXML("test_2_4.xml");



    // init GLUT and the window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(camW,camL);
        glutCreateWindow("CG@DI-UM");

    // Required callback registry
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);

    // Callback registration for keyboard processing
        glutKeyboardFunc(processKeys);
        glutSpecialFunc(processSpecialKeys);
        glewInit(); // after glutCreateWindow and before calling any OpenGL function

    //  OpenGL settings
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnableClientState(GL_VERTEX_ARRAY);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);




        if (argc > 1)
        {
            readXML(argv[1]);
        }
    // enter GLUT's main cycle
        glutMainLoop();
        

        return 1;
    }