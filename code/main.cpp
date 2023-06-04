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
#include <tuple>
#include "tinyxml2.h"

#include <IL/il.h>

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


struct catmullRom{

    std::vector<tuple<float,float,float>> pontos;
    float time ;
    int align;
    int verticeCount;
    GLuint buffers[1];


};

struct Transformations{
    translate t;
    rotates r;
    scale s;
    catmullRom c;
    int escolha ;

};

struct Light{
    string type;
    int i;
    float posx;
    float posy;
    float posz;
    float dirx;
    float diry;
    float dirz;
    float cutoff;

};

struct modelos{
    string modelo;
    GLuint buffers[3];
    int verticeCount;
    float diffuse[4];
    float ambient[4];
    float specular[4];
    float emissive[4];
    float shininess;
    GLuint textura;
    int tem_textura;
    int light_components ;
};

struct Group{
    std::vector<struct Transformations> transformacoes;
    std::vector<Group> grupos;
    std::vector<modelos> models;
};

std::vector<Group> groups;


int camW,camL;
float alpha,betah,raio;
float lookAX, lookAY, lookAZ;
float camVX, camVY, camVZ;


float lookAXaux, lookAYaux, lookAZaux;
float fov,nears,fars,pers;
float dx,dz;
float camX, camY,camZ;
float camXaux, camYaux,camZaux;



int startX, startY, tracking = 0;
float a = 0;
GLuint indice, normals;
float transx ,transy,transz;
float rotx,roty,rotz;
float scax,scay,scaz;
float tglobal = 0;
std::vector<Light> Lights;
int lightindex = 1;


int loadTexture(std::string s) {

	unsigned int t,tw,th;
	unsigned char *texData;
	GLuint texID;

	ILboolean success;

	// Iniciar o DevIL
	ilInit();

	// Colocar a origem da textura no canto inferior esquerdo
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	// Carregar a textura para memóriadir
	ilGenImages(1,&t);
	ilBindImage(t);
	success = ilLoadImage((ILstring)s.c_str());
	if (success) {
        cout << "OIIII\n";
	}
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
    cout << tw << " " << th << "\n";
	// Assegurar que a textura se encontra em RGBA (Red, Green, Blue, Alpha) com um byte (0 -
	// 255) por componente
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	// Gerar a textura para a placa gráfica
	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	// Upload dos dados de imagem
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texID;

}


int Luz(int i){
    int luz;
    if(i == 0){
        luz = GL_LIGHT0;
    }
    else if( i == 1){
        luz = GL_LIGHT1;
    }
    else if( i == 2){
        luz = GL_LIGHT2;
    }
    else if( i == 3){
        luz = GL_LIGHT3;
    }
    else if( i == 4){
        luz = GL_LIGHT4;
    }
    else if( i == 5){
        luz = GL_LIGHT5;
    }
    else if( i == 6){
        luz = GL_LIGHT6;
    }
    else if( i == 7){
        luz = GL_LIGHT7;
    }
    return luz;
}

void spherical2Cartesian() {

	camX = raio * cos(betah) * sin(alpha);
	camY = raio * sin(betah);
	camZ = raio * cos(betah) * cos(alpha);
}

void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}


float length(float *v) {

	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;

}

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}


void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
			
	
	float a[4] ={0.0f,0.0f,0.0f,0.0f};
	float taux[4] = {powf(t,3),powf(t,2),t,1};
	
	float tauxd[4] = {3*powf(t,2),2*t,1,0};
	// Compute A = M * P
	for(int i = 0;i <3; i++){
		float auxp[4] = {p0[i],p1[i],p2[i],p3[i]};
		multMatrixVector((float*)m,auxp,a);
		// Compute pos = T * A
		pos[i] = (taux[0]*a[0]) +(taux[1]*a[1]) +(taux[2]*a[2]) +(taux[3]*a[3]);
		// compute deriv = T' * A
		deriv[i] = (tauxd[0]*a[0]) +(tauxd[1]*a[1]) +(tauxd[2]*a[2]) +(tauxd[3]*a[3]);
		
		
	}
	
}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt ,float *pos, float *deriv,struct catmullRom cat) {
    int POINT_COUNT = cat.pontos.size();
	float t = gt * cat.pontos.size(); // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment
	// indices store the points
	int indices[4]; 
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;	
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT; 
	indices[3] = (indices[2]+1)%POINT_COUNT;

    float p1[3] = {get<0>(cat.pontos[indices[0]]),get<1>(cat.pontos[indices[0]]),get<2>(cat.pontos[indices[0]])};
    float p2[3] = {get<0>(cat.pontos[indices[1]]),get<1>(cat.pontos[indices[1]]),get<2>(cat.pontos[indices[1]])};
    float p3[3] = {get<0>(cat.pontos[indices[2]]),get<1>(cat.pontos[indices[2]]),get<2>(cat.pontos[indices[2]])};
    float p4[3] = {get<0>(cat.pontos[indices[3]]),get<1>(cat.pontos[indices[3]]),get<2>(cat.pontos[indices[3]])};


	getCatmullRomPoint(t, p1, p2, p3, p4, pos, deriv);
}

void vboCatmullRomCurve(catmullRom *c,float line_segments){
    std::vector<float>points;
    float pos[3], deriv[3];
    for (int i = 0; i < line_segments; i++){
        getGlobalCatmullRomPoint(1/line_segments * i, pos, deriv,*c);
        points.push_back(pos[0]);
        points.push_back(pos[1]);
        points.push_back(pos[2]);
    }
    glGenBuffers(1, c->buffers);
    glBindBuffer(GL_ARRAY_BUFFER,c->buffers[0]);
    glBufferData(
            GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
            sizeof(float) * points.size(), // tamanho do vector em bytes
            points.data(), // os dados do array associado ao vector
            GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)*/

    c->verticeCount = points.size()/3;
    

}


std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void createVBO(string file ,modelos* g){
    std::vector<float>points;
    std::vector<float> normals;
    std::vector<float> textures;
    std::string line;
    ifstream indata;
    indata.open(file);
    int j = 0;
    while ( getline (indata,line) ){

        std::string delimiter = ",";
        std::vector<std::string> v = split (line, delimiter);
        
        for (auto i : v){
            if (j >2){
                if (j >5){
                    textures.push_back(atof(i.c_str()));
                }
                else{
                    normals.push_back(atof(i.c_str()));
                }
            }
            else{
                points.push_back(atof(i.c_str()));   
            }
            j++;
        }  
        j=0;

    }
    glGenBuffers(3, g->buffers);
    glBindBuffer(GL_ARRAY_BUFFER,g->buffers[0]);
    glBufferData(
        GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
        sizeof(float) * points.size(), // tamanho do vector em bytes
        points.data(), // os dados do array associado ao vector
        GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)*/
    g->verticeCount = points.size()/3;
    glBindBuffer(GL_ARRAY_BUFFER,g->buffers[1]);
    glBufferData(
        GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
        sizeof(float) * points.size(), // tamanho do vector em bytes
        normals.data(), // os dados do array associado ao vector
        GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)*/
    /*
    for (auto w : textures)
    {
        cout << w << " \n";
    }
    */
    glBindBuffer(GL_ARRAY_BUFFER,g->buffers[2]);
    glBufferData(
        GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
        sizeof(float) * textures.size(), // tamanho do vector em bytes
        textures.data(), // os dados do array associado ao vector
        GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)

}

struct Group readGroup(XMLElement *group){

    XMLElement *trans = group-> FirstChildElement("transform");

    XMLElement *filho;
    struct Group grupo ;
    if (trans){
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

            if (nome == "translate"){
                struct Transformations transformacao ;
                catmull = translate->FirstChildElement("point");
                if (catmull){
                    
                    catmullRom c ;
                    c.time = atof(translate->Attribute("time"));
                    string str = translate->Attribute("align");
                    if(str == "true") c.align = 1;
                    else c.align = 0;
                    c.pontos.push_back( tuple<float, float, float>(atof(catmull->Attribute("x")),atof(catmull->Attribute("y")),atof(catmull->Attribute("z"))) );
                    catmull = catmull->NextSiblingElement();
                    
                    while(catmull){

                        c.pontos.push_back( tuple<float, float, float>(atof(catmull->Attribute("x")),atof(catmull->Attribute("y")),atof(catmull->Attribute("z"))) );
                        catmull = catmull->NextSiblingElement();
                        
                        


                    }
                    
                    vboCatmullRomCurve(&c,100);
                    transformacao.c = c;
                    transformacao.escolha =3 ;
                    
                }
                else{
                    struct translate t;
                    t.transx = atof(translate->Attribute("x"));
                    t.transy = atof(translate->Attribute("y"));
                    t.transz = atof(translate->Attribute("z"));
                    transformacao.escolha = 0;
                    transformacao.t = t;

                }


                
                grupo.transformacoes.push_back(transformacao);
            }
            else if (nome == "rotate"){
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
            else if (nome == "scale"){

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
        XMLElement *textura_name ;
        XMLElement *color ;
        XMLElement *diffuse ;
        XMLElement *ambient ;
        XMLElement *specular ;
        XMLElement *emissive ;
        XMLElement *shininess ;


        while (model){
            modelos g ;
            textura_name = model->FirstChildElement("texture");
            if (textura_name){
                g.tem_textura = 1;
                string x = textura_name->Attribute("file");
                cout << "../../texturas/" + x  << " \n";
                g.textura = loadTexture("../../texturas/" + x);
                cout << g.textura << "\n";
                color = textura_name->NextSiblingElement();
            }
            else 
            {
                g.tem_textura = 0;
            }

            color = model->FirstChildElement("color");

            if (color){
                g.light_components =1 ;
                diffuse = color->FirstChildElement("diffuse");
                g.diffuse[0]=atof(diffuse->Attribute("R"))/255;
                g.diffuse[1] =atof(diffuse->Attribute("G"))/255;
                g.diffuse[2]= atof(diffuse->Attribute("B"))/255;
                g.diffuse[3]= 1;
                ambient = diffuse->NextSiblingElement("ambient");
                g.ambient[0] = atof(ambient->Attribute("R"))/255;
                g.ambient[1] =atof(ambient->Attribute("G"))/255;
                g.ambient[2] = atof(ambient->Attribute("B"))/255;
                g.ambient[3] =1;
                specular = ambient->NextSiblingElement("specular");
                g.specular[0] = atof(specular->Attribute("R"))/255;
                g.specular[1] = atof (specular->Attribute("G"))/255;
                g.specular[2] =  atof(specular->Attribute("B"))/255;
                g.specular[3]= 1;
                emissive = specular->NextSiblingElement("emissive");
                g.emissive[0] = atof(emissive->Attribute("R"))/255;
                g.emissive[1] = atof(emissive->Attribute("G"))/255;
                g.emissive[2] =atof(emissive->Attribute("B"))/255;
                g.emissive[3] =1;
                shininess = emissive->NextSiblingElement("shininess");
                g.shininess = atof(shininess->Attribute("value"));
            }
            else{
                g.light_components =0 ;

            }
            //"
            std::string model_path = model->Attribute("file");
            g.modelo = "../../3d/" + model_path;
            //g.inicio = indice;
            
            g.verticeCount=0;
            createVBO(g.modelo,&g);
    
            //g.verticeCount = points.size();
            grupo.models.push_back(g);
            model = model->NextSiblingElement("model");

        }
    }


    group = group->FirstChildElement("group");
    while (group){
        grupo.grupos.push_back(readGroup(group));
        group = group->NextSiblingElement("group");
    }
    return grupo;
}
void readWD(std::string source){
    source = "../../test_files/" + source;
    XMLDocument xml;
    xml.LoadFile(source.data());

    XMLElement *window = xml.FirstChildElement("world")->FirstChildElement("window");

    camW = atoi(window->Attribute("width"));
    camL = atoi(window->Attribute("height"));
}

void readXML(std::string source){
    
    source = "../../test_files/" + source;
    XMLDocument xml;
    xml.LoadFile(source.data());

    XMLElement *window = xml.FirstChildElement("world")->FirstChildElement("window");


    XMLElement *camera = xml.FirstChildElement("world")->FirstChildElement("camera");

    XMLElement *position = camera->FirstChildElement("position");
    camX = atof(position->Attribute("x"));
    camY = atof(position->Attribute("y"));
    camZ = atof(position->Attribute("z"));
    
    raio = sqrt(camX*camX + camY*camY + camZ*camZ);
    betah = asin(camY / raio);
    alpha = asin(camX / (raio * cos(betah)));

    //Possivel erro de alterarmos o camX ...  e o posX ...
    camXaux = camX;
    camYaux = camY;
    camZaux = camZ;

    XMLElement *lookAt = camera->FirstChildElement("lookAt");
    lookAX = atof(lookAt->Attribute("x"));
    lookAY = atof(lookAt->Attribute("y"));
    lookAZ = atof(lookAt->Attribute("z"));
    lookAXaux = lookAX;
    lookAYaux = lookAY;
    lookAZaux = lookAZ;

    XMLElement *up = camera->FirstChildElement("up");
    camVX = atof(up->Attribute("x"));
    camVY = atof(up->Attribute("y"));
    camVZ = atof(up->Attribute("z"));

    XMLElement *projection = camera->FirstChildElement("projection");
    fov = atof(projection->Attribute("fov"));
    nears = atof(projection->Attribute("near"));
    fars = atof(projection->Attribute("far"));
    pers = camW/camL;

    XMLElement *lights =  xml.FirstChildElement("world")->FirstChildElement("lights");
    
    if (lights){
        XMLElement *light = lights ->FirstChildElement("light");
        while (light){
            struct Light l;
            
            l.type = light->Attribute("type");
            
            if(l.type == "point"){
                l.posx = atof(light->Attribute("posx"));
                l.posy = atof(light->Attribute("posy"));
                l.posz = atof(light->Attribute("posz"));
                l.dirx = 0;
                l.diry = 0;
                l.dirz = 0;
                l.cutoff = 0;
                l.i = Luz(lightindex);
            }
            else if(l.type == "spot"){
                l.posx = atof(light->Attribute("posx"));
                l.posy = atof(light->Attribute("posy"));
                l.posz = atof(light->Attribute("posz"));
                l.dirx = atof(light->Attribute("dirx"));
                l.diry = atof(light->Attribute("diry"));
                l.dirz = atof(light->Attribute("dirz"));
                l.cutoff = atof(light->Attribute("cutoff"));
                l.i = Luz(lightindex);
                
            }
            else{
                l.dirx = atof(light->Attribute("dirx"));
                l.diry = atof(light->Attribute("diry"));
                l.dirz = atof(light->Attribute("dirz"));
                l.posx = 0;
                l.posy = 0;
                l.posz = 0;
                l.cutoff = 0;
                l.i = Luz(lightindex);
            }
            lightindex++;
            Lights.push_back(l);
            light = light->NextSiblingElement("light");
        }
    }
    XMLElement *GROUP = xml.FirstChildElement("world")->FirstChildElement("group");
    XMLElement *group = GROUP;


    while (group){
        groups.push_back(readGroup(group));
        group = group->NextSiblingElement("group");
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

void transacoes(struct Group g){
    
    for(auto t : g.transformacoes){
        if (t.escolha == 0){
            glTranslated(t.t.transx,t.t.transy,t.t.transz);
        }
        else if (t.escolha == 1){
            if (t.r.time == 0)
                glRotated(t.r.ang,t.r.rotx,t.r.roty,t.r.rotz);
            else{
                t.r.ang = 360*(tglobal/1000)/t.r.time;
                
                glRotatef(t.r.ang,t.r.rotx,t.r.roty,t.r.rotz);
            }
        }
        else if (t.escolha == 2){
            glScaled(t.s.scax,t.s.scay,t.s.scaz);
        }
        else if (t.escolha == 3){
            glBindBuffer(GL_ARRAY_BUFFER, t.c.buffers[0]);
	        glVertexPointer(3, GL_FLOAT, 0, 0);
            glDrawArrays(GL_LINE_LOOP, 0, t.c.verticeCount);

            if(t.c.align == 1){

                float pos[3];
                float deriv[3];


                static float *x = deriv;
                static float y0[3] = {0.0f,1.0f,0.0f};
                static float y1[3] = {0.0f,1.0f,0.0f};
                static float z[3] = {0.0f,0.0f,0.0f};

                static float tempo = 0.0f;
                static float tempoaux = 0.0f;
                if(tempo>= 1){
                    tempoaux += 1;

                    tempo = ((tglobal/1000)/t.c.time) -tempoaux;
                }
                else{
                    tempo = ((tglobal/1000)/t.c.time) - tempoaux;
                }

                getGlobalCatmullRomPoint(tempo,pos,deriv,t.c);

                x = deriv;
                normalize(x);
                cross(x,y0,z);
                normalize(z);
                cross(z,x,y1);
                normalize(y1);
                for( int i = 0; i<3;i++){
                    y0[i] = y1[i];
                }

                glTranslatef(pos[0],pos[1],pos[2]);

                float matrix[16];

                buildRotMatrix(x,y1,z,matrix);

                glMultMatrixf(matrix);

            }
            else{

                float pos[3];
                float deriv[3];
                static float *x = deriv;
                static float y0[3] = {0.0f,1.0f,0.0f};
                static float y1[3] = {0.0f,1.0f,0.0f};
                static float z[3] = {0.0f,0.0f,0.0f};
                static float tempo = 0.0f;
                static float tempoaux = 0.0f;
                if(tempo>= 1){
                    tempoaux += 1;

                    tempo = ((tglobal/1000)/t.c.time) -tempoaux;
                }
                else{
                    tempo = ((tglobal/1000)/t.c.time) - tempoaux;
                }
                getGlobalCatmullRomPoint(tempo,pos,deriv,t.c);
                glTranslatef(pos[0],pos[1],pos[2]);

            }

        }
    }

}



void recFilhos(struct Group g){

    glPushMatrix();
    transacoes(g);
    for (auto j: g.models)
    {
        
        
        
        if (j.light_components == 1){
            
            glMaterialfv(GL_FRONT, GL_DIFFUSE,j.diffuse);
            glMaterialfv(GL_FRONT, GL_AMBIENT,j.ambient);
            glMaterialfv(GL_FRONT, GL_EMISSION,j.emissive);
            glMaterialfv(GL_FRONT, GL_SPECULAR, j.specular);
            glMaterialf(GL_FRONT, GL_SHININESS, j.shininess);   
        }
        

        glBindBuffer(GL_ARRAY_BUFFER, j.buffers[0]);
	    glVertexPointer(3, GL_FLOAT, 0, 0);

	    glBindBuffer(GL_ARRAY_BUFFER, j.buffers[1]);
	    glNormalPointer(GL_FLOAT, 0, 0);

        if (j.tem_textura = 1){
            glBindTexture(GL_TEXTURE_2D,j.textura);
        }

	    glBindBuffer(GL_ARRAY_BUFFER, j.buffers[2]);
	    glTexCoordPointer(2, GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, j.verticeCount);
        

        if (j.tem_textura == 1)
        {
            glBindTexture(GL_TEXTURE_2D,0);
        }

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


    glDisable(GL_LIGHTING);
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
    glColor3f(1.0f,1.0f,1.0f);
    glEnable(GL_LIGHTING);

    //SPOTLIGHT - DIRECTION 
    for(auto l : Lights){
        if (l.type== "point"){
            
            float pos[4] =  {l.posx,l.posy,l.posz,1.0f};
            glLightfv(l.i, GL_POSITION,pos);
        }
        else if (l.type == "spot"){
            float pos[4] =  {l.posx,l.posy,l.posz,1.0f};
            float posDirec[4] =  {l.dirx,l.diry,l.dirz,0.0f};
            float posCutoff  = l.cutoff;
            //cout << pos << " " << posDirec << " " << posCutoff << "\n";
            glLightfv(l.i, GL_POSITION,pos);
            glLightfv(l.i, GL_SPOT_DIRECTION, posDirec);
            glLightfv(l.i, GL_SPOT_CUTOFF, &posCutoff);
        }
        else{
            float posDirec[4] =  {l.dirx,l.diry,l.dirz,0.0f};
            //out << l.dirx << " " << l.diry << " " << l.dirz << "\n";
            glLightfv(l.i, GL_POSITION, posDirec);	
        }
    }

    for (auto i : groups){
        recFilhos(i);

    }

    tglobal = glutGet(GLUT_ELAPSED_TIME);

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

        case 'f':
            a = 0;
            camX = 0.0f;
            camZ = 0.0f;
            camY = 0.0f;
            lookAX = camX + sin(a);
            lookAZ = camZ + cos(a);
            lookAY = camY;
            break;
        case 'o':
            a += M_PI/32;

            lookAX = camX + sin(a);
            lookAZ = camZ + cos(a);
            lookAY = camY;
            break;
        case 'p':
            a -= M_PI/32;

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
            camX -= 1;

            lookAX = camX + sin(a);
            lookAZ = camZ + cos(a);
            lookAY = camY;
            break;
        case 'r':
            camX =camXaux;
            camY = camYaux;
            camZ = camZaux;
            lookAX = lookAXaux;
            lookAY = lookAYaux;
            lookAZ = lookAZaux;
            break;
        }

        glutPostRedisplay();
    }

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
    
void processSpecialKeys(int key, int xx, int yy) {

    // put code to process special keys in here

}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nuhjk are wasd \n");
	printf("z to zoom and x to unzoom\n");
    printf("press f to change to fps came and set pos to 0,0,0\n");
    printf("and wasd to move around and o and p to change camera direction\n");
    printf("r to reset to original position\n");
    printf("only use mouse look arround when camera is at original position\n");



}
 


int main(int argc, char **argv){

    if (argc > 1){
        readWD(argv[1]);
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
    glutIdleFunc(renderScene);
// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);
    
    glewInit(); // after glutCreateWindow and before calling any OpenGL function



//  OpenGL settings
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_RESCALE_NORMAL);
    float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    spherical2Cartesian();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    

    
    //ISSO AQUIÉ ISSO ?
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    if (argc > 1){
        readXML(argv[1]);
    }
    
    if(Lights.size()>0){
        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
        float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        //glEnable(GL_TEXTURE_2D);

        // LER AS CORES DO XML
       
        // light colors
        for(Light l : Lights){
            cout << "teste\n";
            glEnable(l.i);
            glLightfv(l.i, GL_AMBIENT, dark);
            glLightfv(l.i, GL_DIFFUSE, white);
            glLightfv(l.i, GL_SPECULAR, white);
            
        }

        // controls global ambient light
    }
    
    


    
    printInfo();
    glutMainLoop();


    
    return 1;
}