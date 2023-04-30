#define _USE_MATH_DEFINES
#include <math.h>	
#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
//#include <bits/stdc++.h>
using std::ofstream;
using namespace std;

string path = "../3d/";
struct point 
{
    float x;
    float y;
	float z;
};

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
void drawSphere(float radius,int slices, int stacks,string file)
{
	float al = 0;
	float be = -M_PI/2;
	
    ofstream MyFile;
    MyFile.open(path + file);
	for(int j = 0;j!= stacks;j++)
    {
		for(int i = 0;i!= slices;i++)
        {
			MyFile << radius*cos(be)*sin(al) << ", "  << radius*sin(be) << ", "<< radius*cos(be)*cos(al) << '\n';
            MyFile << radius*cos(be)*sin(al+2*M_PI/stacks) << ", " << radius*sin(be) << ", "<< radius*cos(be)*cos(al+2*M_PI/stacks) << '\n';
            MyFile << radius*cos(be+M_PI/slices)*sin(al) << ", "<< radius*sin(be+M_PI/slices) << ", "<< radius*cos(be+M_PI/slices)*cos(al) << '\n';

            MyFile << radius*cos(be)*sin(al+2*M_PI/stacks) << ", " << radius*sin(be) << ", "<< radius*cos(be)*cos(al+2*M_PI/stacks) << '\n';
            MyFile << radius*cos(be+M_PI/slices)*sin(al+2*M_PI/stacks) << ", " << radius*sin(be+M_PI/slices) << ", "<<  radius*cos(be+M_PI/slices)*cos(al+2*M_PI/stacks) << '\n';
            MyFile << radius*cos(be+M_PI/slices)*sin(al) << ", "<< radius*sin(be+M_PI/slices) << ", "<< radius*cos(be+M_PI/slices)*cos(al) << '\n';

			al += 2*M_PI/stacks;
			
		}
		be += M_PI/slices;
	}
    MyFile.close();

}

void drawCone(float radius, float height, int slices,int stacks, string file	) 
{
    ofstream MyFile;
    MyFile.open(path + file);

    float ang = 0;
    float draio = radius/stacks;
    float alt = 0;
    float r = radius;
    for(int i = 0;i!= slices;i++){
        point ponto1;
        point ponto2;
        point ponto3;
        point ponto4;
        ponto1.x =sin(ang)*r;
        ponto1.y = 0;
        ponto1.z = cos(ang)*r;

        ponto2.x =sin(ang+(M_PI*2/slices))*r;
        ponto2.y = 0;
        ponto2.z = cos(ang+(M_PI*2/slices))*r;
        MyFile << 0.0 << ", " << 0.0 << ", "<< 0.0 << "\n";
        MyFile << ponto2.x << ", " << ponto2.y << ", "<< ponto2.z<< "\n";
        MyFile << ponto1.x << ", " << ponto1.y << ", "<< ponto1.z << "\n";

        
        for (int j = 0;j != stacks;j++)
        {
            ponto1.x =sin(ang)*r;
            ponto1.y = alt;
            ponto1.z = cos(ang)*r;

            ponto2.x =sin(ang+(M_PI*2/slices))*r;
            ponto2.y = alt;
            ponto2.z = cos(ang+(M_PI*2/slices))*r;
            

            ponto3.x =sin(ang)*(r-draio);
            ponto3.y = alt+ height/stacks;
            ponto3.z = cos(ang)*(r-draio);

            ponto4.x =sin(ang+(M_PI*2/slices))*(r-draio);
            ponto4.y = alt+ height/stacks;
            ponto4.z = cos(ang+(M_PI*2/slices))*(r-draio);

            MyFile << ponto1.x << ", " << ponto1.y << ", "<< ponto1.z<< "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", "<< ponto2.z<< "\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", "<< ponto3.z<< "\n";

            MyFile << ponto2.x << ", " << ponto2.y << ", "<< ponto2.z<< "\n";
            MyFile << ponto4.x << ", " << ponto4.y << ", "<< ponto4.z<< "\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", "<< ponto3.z<< "\n";
            
            r -= draio;
            alt += height/stacks;

            
        }
        alt = 0;
        r = radius;
        ang += 2*M_PI/slices;

    }
    
    MyFile.close();


}

void drawPlane(float comp, int slices, string file)
{
    ofstream MyFile;
    MyFile.open(path + file);

    float aresta = comp / slices; 
    float posicao = comp / 2;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {
            point ponto1;
            point ponto2;

            ponto1.x = i * aresta - posicao;
            ponto1.y = 0;
            ponto1.z = j * aresta - posicao;

            ponto2.x = (i + 1) * aresta - posicao;
            ponto2.y = 0;
            ponto2.z = (j + 1) * aresta - posicao;

            // Vista de Cima
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto1.z << "\n";

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";

            // Vista de baixo
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
        }
    }
}

void drawBox(float comp, int slices, string file)
{
    ofstream MyFile;
    MyFile.open(path + file);

    float aresta = comp / slices;
    float posicao = comp / 2;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {
            point ponto1;
            point ponto2;

            ponto1.x = i * aresta - posicao;
            ponto1.y = posicao;
            ponto1.z = j * aresta - posicao;

            ponto2.x = (i + 1) * aresta - posicao;
            ponto2.y = -posicao;
            ponto2.z = (j + 1) * aresta - posicao;

            // Face de cima
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto1.z << "\n";

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";

            // Face de baixo
            MyFile << ponto1.x << ", " << ponto2.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto2.z << "\n";

            MyFile << ponto1.x << ", " << ponto2.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto2.z << "\n";
            MyFile << ponto1.x << ", " << ponto2.y << ", " << ponto2.z << "\n";

            // Face de X constante negativo
            MyFile << ponto2.y << ", " << ponto1.x << ", " << ponto1.z << "\n";
            MyFile << ponto2.y << ", " << ponto2.x << ", " << ponto2.z << "\n";
            MyFile << ponto2.y << ", " << ponto2.x << ", " << ponto1.z << "\n";

            MyFile << ponto2.y << ", " << ponto1.x << ", " << ponto1.z << "\n";
            MyFile << ponto2.y << ", " << ponto1.x << ", " << ponto2.z << "\n";
            MyFile << ponto2.y << ", " << ponto2.x << ", " << ponto2.z << "\n";

            // Face de X constante positivo
            MyFile << ponto1.y << ", " << ponto1.x << ", " << ponto1.z << "\n";
            MyFile << ponto1.y << ", " << ponto2.x << ", " << ponto1.z << "\n";
            MyFile << ponto1.y << ", " << ponto2.x << ", " << ponto2.z << "\n";

            MyFile << ponto1.y << ", " << ponto1.x << ", " << ponto1.z << "\n";
            MyFile << ponto1.y << ", " << ponto2.x << ", " << ponto2.z << "\n";
            MyFile << ponto1.y << ", " << ponto1.x << ", " << ponto2.z << "\n";

            // Face de Z constante negativo
            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto2.y << "\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto2.y << "\n";
            MyFile << ponto2.x << ", " << ponto1.z << ", " << ponto2.y << "\n";

            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto2.y << "\n";
            MyFile << ponto1.x << ", " << ponto2.z << ", " << ponto2.y << "\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto2.y << "\n";

            // Face de Z constante positivo
            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto1.y << "\n";
            MyFile << ponto2.x << ", " << ponto1.z << ", " << ponto1.y << "\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto1.y << "\n";

            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto1.y << "\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto1.y << "\n";
            MyFile << ponto1.x << ", " << ponto2.z << ", " << ponto1.y << "\n";
        }
    }
}

void multMatrix(float m[4][4], float v[4][4], float res[4][4]) {

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; ++j) {
		    res[i][j] = 0;                  // inicializacao
		    for (int k = 0; k < 4; ++k) {   // percorre linha * coluna
			    res[i][j] += v[i][k] * m[k][j];
		    }
	    }
    }   
}

void multMatrixVector(float m[4][4], float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }

}

// Função para calcular P(U,V) = U * M * pontos[indices] * M * V      Mt = M
float UbezierV(float u, float calculado[4][4], float v){ 
    float V[4] = { powf(v, 3.0) , powf(v, 2.0) + v + 1 };
    float temp[4];
    float res;
    // temp = M * pontos[indices] * M * V
    multMatrixVector(calculado,V,temp);
    // res = U * temp
    res = powf(u, 3.0) * temp[0] + powf(u, 2.0) * temp[1] + u * temp[2] + temp[3];

    return res;
}

// Calcular os pontos
void drawBezier(float xCoords[4][4], float yCoords[4][4], float zCoords[4][4], int tess, string file){
    ofstream MyFile;
    MyFile.open(path + file);

    float delta = 1.0 / tess;

    for (float i = 0; i < 1; i+=delta)
    {
        for (float j = 0; j < 1; j+=delta)
        {
            // percorre a tesselacao, 4 pontos
            point ponto;
            point ponto1;
            point ponto2;
            point ponto3;

            ponto.x = UbezierV(i,xCoords,j);
            ponto.y = UbezierV(i,yCoords,j);
            ponto.z = UbezierV(i,zCoords,j);

            ponto1.x = UbezierV(i+delta,xCoords,j);
            ponto1.y = UbezierV(i+delta,yCoords,j);
            ponto1.z = UbezierV(i+delta,zCoords,j);

            ponto2.x = UbezierV(i+delta,xCoords,j+delta);
            ponto2.y = UbezierV(i+delta,yCoords,j+delta);
            ponto2.z = UbezierV(i+delta,zCoords,j+delta);

            ponto3.x = UbezierV(i,xCoords,j+delta);
            ponto3.y = UbezierV(i,yCoords,j+delta);
            ponto3.z = UbezierV(i,zCoords,j+delta);

            // passar para o ficheiro o "quadrado"
            // triangulo 1
            MyFile << ponto.x << ", " << ponto.y << ", " << ponto.z << "\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", " << ponto3.z << "\n";

            // triangulo 2
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto2.z << "\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", " << ponto3.z << "\n";
        }
        
    }
    
}

// Trata do ficheiro patch dado
void readPatch(string patch, int tess, string file)
{
    ifstream patch_file("../" + patch);
    int n_patch, n_cpoints;
    char valor[2];
    vector<vector<float>> indices;
    vector<point> pontos_controlo;
    string line ;
    float xCoords[4][4];
    float yCoords[4][4];
    float zCoords[4][4];
    float m[4][4] = {	{-1.0f,  3.0f, -3.0f,  1.0f},   // Matriz de Bezier
						{ 3.0f, -6.0f,  3.0f,  0.0f},
						{-3.0f,  3.0f,  0.5f,  0.0f},
						{ 1.0f,  1.0f,  0.0f,  0.0f}};
    
    getline(patch_file,line);

    n_patch = atoi(line.c_str());

    cout << n_patch << " numero patches";
    
    // Guardar os indices
    for (int i = 0; i < n_patch; i++)
    {
        vector<float> auxiliar;
        getline (patch_file,line);
        std::vector<std::string> v = split (line, ",");
        for (auto a: v)
        {
            auxiliar.push_back(atoi(a.c_str()));
        }
        indices.push_back(auxiliar);
    }
    

    getline(patch_file,line);

    n_cpoints = atoi(line.c_str());
    // cout << "ola";
    // cout << n_cpoints;

    // Guardar os pontos de controlo
    for (int i = 0; i < n_cpoints; i++)
    {
        point ponto;
        string lixo;
        patch_file >> ponto.x;
        patch_file >> lixo;
        patch_file >> ponto.y;
        patch_file >> lixo;
        patch_file >> ponto.z;
        pontos_controlo.push_back(ponto);
    }

    // Guardar os pontos de controlo de x,y,z nas respetivas matrizes dadas pelos indices
    for(auto ind : indices){
        for(int i=0; i<4; i++){
            for(int j = 0; j<4; j++){
                int index = ind[i * 4 + j];
                xCoords[j][i] = pontos_controlo[index].x;
                yCoords[j][i] = pontos_controlo[index].y;
                zCoords[j][i] = pontos_controlo[index].z;
            }
        }
    }
    float temp[4][4];

    //  M * pontos[indices] * M para x,y,z que podem ser pré calculados
    multMatrix(m,xCoords,temp);
    multMatrix(temp,m,xCoords); 

    multMatrix(m,yCoords,temp);
    multMatrix(temp,m,yCoords);

    multMatrix(m,zCoords,temp);
    multMatrix(temp,m,zCoords);

    drawBezier(xCoords,yCoords,zCoords,tess,file);

}

int main (int argc, char const *argv[])
{  
    if (argc <=  1)
    {
          std::cout << "Invalid input";

    }
    else
    {
        if (!(strcmp(argv[1],"sphere")) && argc == 6 )
        {
            drawSphere(atof(argv[2]), atoi(argv[3]),atoi(argv[4]),argv[5]);
        }
        else if (!(strcmp(argv[1],"box")) && argc == 5 )
        {
            drawBox(atoi(argv[2]), atoi(argv[3]),argv[4]);
        }
        else if (!(strcmp(argv[1],"cone")) && argc == 7 )
        { 
            drawCone(atof(argv[2]), atof(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
        }
        else if (!(strcmp(argv[1],"plane")) && argc == 5 )
        {
            drawPlane(atoi(argv[2]), atoi(argv[3]),argv[4]);
        }
        else if (!(strcmp(argv[1],"patch")) && argc == 5 )
        {
            readPatch(argv[2], atoi(argv[3]),argv[4]);
        }
      
    }
   
    

}





