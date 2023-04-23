#include <stdio.h>
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
using namespace std;

float alfa = 0.0f, betah = 0.0f, radius = 5.0f;
float camX, camY, camZ;
GLuint vertices[1];
std::vector<float> p;
int triangles1 ;
int triangles2;
int inicio;
int indice = 0;

//GLuint indice = 0;

void spherical2Cartesian() {

    camX = radius * cos(betah) * sin(alfa);
    camY = radius * sin(betah);
    camZ = radius * cos(betah) * cos(alfa);
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

void createVBO(string file,string file2)
{
    cout << file << "\n";
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
            indice++;
        }


    }


    indata.close();

    triangles1 = indice;

    indata.open(file2);
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

    triangles2 = indice - triangles1;
    indata.close();
    glGenBuffers(1, vertices);

    // copiar o vector para a memória gráfica
    glBindBuffer(GL_ARRAY_BUFFER, vertices[0]);
    glBufferData(
            GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
            sizeof(float) * p.size(), // tamanho do vector em bytes
            p.data(), // os dados do array associado ao vector
            GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)
}




void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glBindBuffer(GL_ARRAY_BUFFER, vertices[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, triangles1);

    
    glDrawArrays(GL_TRIANGLES, triangles1, triangles2);

    //cylinder(1,2,10);
    //drawvbo();


    // End of frame
    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {


}


void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

    printf("\nUse Arrows to move the camera up/down and left/right\n");
    printf("Page Up and Page Down control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");



// Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    // init GLEW
#ifndef __APPLE__
    glewInit();
#endif


//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT, GL_LINE);



    printInfo();

    spherical2Cartesian();
    createVBO("../../3d/cone_1_2_4_3.3d"  ,"../../3d/box_2_3.3d");
    for (int i = 0; i < 84* 3 ; i++)
    {
        cout << p[i] << "\n";
    }
// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}








































