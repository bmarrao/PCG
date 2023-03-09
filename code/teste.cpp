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

int camW,camL;
float alpha,betah,raio;
float lookAX, lookAY, lookAZ;
float camVX, camVY, camVZ;
float fov,near,far,pers;
std::vector<std::string> models ;


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
    std::cout << " " << camVX << " " << camVY  << " " <<camVZ << "\n " ;

    XMLElement *projection = camera->FirstChildElement("projection");
    fov = atof(projection->Attribute("fov"));
    near = atof(projection->Attribute("near"));
    far = atof(projection->Attribute("far"));
    pers = camW/camL;
    std::cout << " " << fov << " " << near  << " " <<far << " " << pers ;
    XMLElement *MODELS = xml.FirstChildElement("world")->FirstChildElement("group")->FirstChildElement("models");
    XMLElement *model = MODELS->FirstChildElement("model");
    while (model) 
    {
        std::string model_path = model->Attribute("file");
        std::cout << model_path;
        model = model->NextSiblingElement("model");
    }
}

int main(int argc, char **argv) {

    readXML("test_1_1.xml");
    for (auto i : models)
    {
        printf("%s\n",i);
		//render3D(i);
    }
}