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
struct catmullRom{

    std::vector<tuple<float,float,float>> pontos;
    int align;
    int verticeCount;


};
void normalize(float *a){

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}


vector<vector<float>> indices;
vector<point> pontos_controlo;

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
void drawSphere(float radius,int slices, int stacks,string file){
	float al = 0;
	float be = -M_PI/2;
	
    ofstream MyFile;
    MyFile.open(path + file);
	for(int j = 0;j!= stacks;j++){
		for(int i = 0;i!= slices;i++){
            float n1[3] = {radius*cos(be)*sin(al) , radius*sin(be), radius*cos(be)*cos(al)};
            normalize(n1);
			MyFile << radius*cos(be)*sin(al) << ", "  << radius*sin(be) << ", "<< radius*cos(be)*cos(al) << ", "<< n1[0] << ", " << n1[1] << ", " <<n1[2] << ", "<< (float)i/slices << ", " << (float)j/stacks << '\n';
            
            float n2[3] = {radius*cos(be)*sin(al+2*M_PI/stacks), radius*sin(be), radius*cos(be)*cos(al+2*M_PI/stacks)};
            normalize(n2);
            MyFile << radius*cos(be)*sin(al+2*M_PI/stacks) << ", " << radius*sin(be) << ", "<< radius*cos(be)*cos(al+2*M_PI/stacks) << ", " << n2[0] << ", "<< n2[1] << ", "<< n2[2]<<", "<< (float)(i+1)/slices << ", " << (float)j/stacks <<'\n';
            
            float n3[3] = {radius*cos(be+M_PI/slices)*sin(al),  radius*sin(be+M_PI/slices), radius*cos(be+M_PI/slices)*cos(al)};
            normalize(n3);
            MyFile << radius*cos(be+M_PI/slices)*sin(al) << ", "<< radius*sin(be+M_PI/slices) << ", "<< radius*cos(be+M_PI/slices)*cos(al) << ", "<< n3[0] << ", "<< n3[1] << ", "<< n3[2]<<", "<< (float)i/slices << ", " << (float)(j+1)/stacks <<'\n';

            float n4[3] = {radius*cos(be)*sin(al+2*M_PI/stacks), radius*sin(be), radius*cos(be)*cos(al+2*M_PI/stacks)};
            normalize(n4);
            MyFile << radius*cos(be)*sin(al+2*M_PI/stacks) << ", " << radius*sin(be) << ", "<< radius*cos(be)*cos(al+2*M_PI/stacks) <<", "<< n4[0] << ", " << n4[1] << ", "<< n4[2] <<", "<< (float)(i+1)/slices << ", " << (float)j/stacks<<'\n';

                      
            float n5[3] = {radius*cos(be+M_PI/slices)*sin(al+2*M_PI/stacks) , radius*sin(be+M_PI/slices) , radius*cos(be+M_PI/slices)*cos(al+2*M_PI/stacks)};
            normalize(n5);
            MyFile << radius*cos(be+M_PI/slices)*sin(al+2*M_PI/stacks) << ", " << radius*sin(be+M_PI/slices) << ", "<<  radius*cos(be+M_PI/slices)*cos(al+2*M_PI/stacks)<<", " << n5[0] << ", " << n5[1] << ", "<<  n5[2] << ", "<< (float)(i+1)/slices << ", " << (float)(j+1)/stacks<<'\n';
            
            float n6[3] = {radius*cos(be+M_PI/slices)*sin(al) ,  radius*sin(be+M_PI/slices) ,  radius*cos(be+M_PI/slices)*cos(al)};
            MyFile << radius*cos(be+M_PI/slices)*sin(al) << ", "<< radius*sin(be+M_PI/slices) << ", "<< radius*cos(be+M_PI/slices)*cos(al) << ", "<< n6[0] << ", "<< n6[1] << ", " << n6[2] <<", "<< (float)i/slices << ", " << (float)(j+1)/stacks<<'\n';

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
    float nx ;
    float ny ;
    float nz;
    float n[3];
    for(int i = 0;i!= slices;i++){
        point ponto1;
        point ponto2;
        point ponto3;
        point ponto4;
        point normal1;
        point normal2;
        ponto1.x =sin(ang)*r;
        ponto1.y = 0;
        ponto1.z = cos(ang)*r;

        ponto2.x =sin(ang+(M_PI*2/slices))*r;
        ponto2.y = 0;
        ponto2.z = cos(ang+(M_PI*2/slices))*r;

    
        MyFile << 0.0 << ", " << 0.0 << ", "<< 0.0 << ", " << 0.0 << ", " << -1.0 << ", "<< 0.0 << ", "<<(float)0.5<< ", "<<(float)0.5<<"\n";
        MyFile << ponto2.x << ", " << ponto2.y << ", "<< ponto2.z<<  ", " << 0.0 << ", " << -1.0 << ", "<< 0.0 << ", "<<0.5*sin(ang+(M_PI*2/slices))<< ", "<<0.5*cos(ang+(M_PI*2/slices))<<"\n";
        MyFile << ponto1.x << ", " << ponto1.y << ", "<< ponto1.z << ", " << 0.0 << ", " << -1.0 << ", "<< 0.0  << ", "<<0.5*sin(ang)<< ", "<<0.5*cos(ang)<<"\n";

        nx=0;
        ny= height;
        nz=0;
        
        n[0]=(ponto2.x-ponto1.x)*(nx-ponto1.x);
        n[1]=(ponto2.y-ponto1.y) *(ny-ponto1.y);
        n[2]=(ponto2.z-ponto1.z)*(nz-ponto1.z);
        normalize(n);
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

            MyFile << ponto1.x << ", " << ponto1.y << ", "<< ponto1.z<<  ", " << n[0] << ", " << n[1] << ", "<< n[2] <<", "<<(float)i/slices << ", "<<(float)j/stacks<< "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", "<< ponto2.z<< ", " << n[0] << ", " << n[1] << ", "<< n[2] <<", "<<(float)(i+1)/slices << ", "<<(float)j/stacks<<"\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", "<< ponto3.z<< ", " << n[0] << ", " << n[1] << ", "<< n[2]<<", "<<(float)i/slices << ", "<<(float)(j+1)/stacks <<"\n";

            MyFile << ponto2.x << ", " << ponto2.y << ", "<< ponto2.z<< ", " << n[0] << ", " << n[1] << ", "<< n[2] << ", "<<(float)(i+1)/slices << ", "<<(float)j/stacks<<"\n";
            MyFile << ponto4.x << ", " << ponto4.y << ", "<< ponto4.z<< ", " << n[0] << ", " << n[1] << ", "<< n[2] <<", "<<(float)(i+1)/slices << ", "<<(float)(j+1)/stacks <<"\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", "<< ponto3.z<< ", " << n[0] << ", " << n[1] << ", "<< n[2] <<", "<<(float)i/slices << ", "<<(float)(j+1)/stacks <<"\n";
            
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

    for (int i = 0; i < slices; i++) 
    {
        for (int j = 0; j < slices; j++) 
        {
            point ponto1;
            point ponto2;
            point normal1;
            point normal2;
            ponto1.x = i * aresta - posicao;
            ponto1.y = 0;
            ponto1.z = j * aresta - posicao;

            ponto2.x = (i + 1) * aresta - posicao;
            ponto2.y = 0;
            ponto2.z = (j + 1) * aresta - posicao;


            // Vista de cima
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << 1 << ", " << 0 << ", " << (ponto1.x+comp/2)/comp   << ", " << (ponto1.z+comp/2)/comp << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << 1 << ", " << 0 << ", " << (ponto2.x+comp/2)/comp  << ", " << (ponto2.z+comp/2)/comp << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << 1 << ", " << 0 << ", " << (ponto2.x+comp/2)/comp  << ", " << (ponto1.z+comp/2)/comp << "\n";

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << 1 << ", " << 0 << ", " << ponto1.x/comp +0.5 << ", " << ponto1.z/comp +0.5 << "\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << 1 << ", " << 0 << ", " << ponto1.x/comp +0.5  << ", " << ponto2.z/comp +0.5 << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << 1 << ", " << 0 << ", " << ponto2.x/comp +0.5  << ", " << ponto2.z/comp +0.5 << "\n";
            
            

            // Vista de baixo
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << -1 << ", " << 0 << ", " << ponto1.x/comp +0.5  << ", " << ponto1.z/comp +0.5 << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << -1 << ", " << 0 << ", " << ponto2.x/comp +0.5  << ", " << ponto1.z/comp+0.5  << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << -1 << ", " << 0 << ", " << ponto2.x/comp +0.5  << ", " << ponto2.z/comp +0.5 << "\n";

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << -1 << ", " << 0 << ", " << ponto1.x/comp +0.5  << ", " << ponto1.z/comp +0.5 << "\n";;
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << -1 << ", " << 0 << ", " << ponto2.x/comp +0.5 << ", " << ponto2.z/comp+0.5  << "\n";;
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << -1 << ", " << 0 << ", " << ponto1.x/comp +0.5  << ", " << ponto2.z/comp+0.5  << "\n";;
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
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << 1 << ", " << 0 << ", "<<ponto1.x/comp+0.5  << ", "<<ponto1.z/comp+0.5 << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << 1 << ", " << 0 <<", "<<ponto2.x/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << 1 << ", " << 0 <<", "<<ponto2.x/comp +0.5 << ", "<<ponto1.z/comp+0.5 << "\n";

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << ", " << 0 << ", " << 1 << ", " << 0 << ", "<<ponto1.x/comp +0.5 << ", "<<ponto1.z/comp+0.5 <<"\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << 1 << ", " << 0 << ", "<<ponto1.x/comp +0.5 << ", "<<ponto2.z/comp+0.5 <<"\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << ", " << 0 << ", " << 1 << ", " << 0 <<", "<<ponto2.x/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";

            // Face de baixo
            MyFile << ponto1.x << ", " << ponto2.y << ", " << ponto1.z << ", " << 0 << ", " << -1 << ", " << 0 << ", "<<ponto1.x/comp+0.5  << ", "<<ponto1.z/comp+0.5 <<"\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto1.z << ", " << 0 << ", " << -1 << ", " << 0 << ", "<<ponto2.x/comp +0.5 << ", "<<ponto1.z/comp+0.5 <<"\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto2.z << ", " << 0 << ", " << -1 << ", " << 0 <<", "<<ponto2.x/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";

            MyFile << ponto1.x << ", " << ponto2.y << ", " << ponto1.z << ", " << 0 << ", " << -1 << ", " << 0 <<", "<<ponto1.x/comp +0.5 << ", "<<ponto1.z/comp+0.5 << "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto2.z << ", " << 0 << ", " << -1 << ", " << 0 << ", "<<ponto2.x/comp +0.5 << ", "<<ponto2.z/comp+0.5 <<"\n";
            MyFile << ponto1.x << ", " << ponto2.y << ", " << ponto2.z << ", " << 0 << ", " << -1 << ", " << 0 <<", "<<ponto1.x/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";

            // Face de X constante negativo
            MyFile << ponto2.y << ", " << ponto1.x << ", " << ponto1.z << ", " << -1 << ", " << 0 << ", " << 0 <<", "<<ponto2.y/comp +0.5 << ", "<<ponto1.z/comp+0.5 << "\n";
            MyFile << ponto2.y << ", " << ponto2.x << ", " << ponto2.z << ", " << -1 << ", " << 0 << ", " << 0 << ", "<<ponto2.y/comp +0.5 << ", "<<ponto2.z/comp+0.5 <<"\n";
            MyFile << ponto2.y << ", " << ponto2.x << ", " << ponto1.z << ", " << -1 << ", " << 0 << ", " << 0 << ", "<<ponto2.y/comp +0.5 << ", "<<ponto1.z/comp+0.5 <<"\n";

            MyFile << ponto2.y << ", " << ponto1.x << ", " << ponto1.z << ", " << -1 << ", " << 0 << ", " << 0 << ", "<<ponto2.y/comp +0.5 << ", "<<ponto1.z/comp+0.5 <<"\n";
            MyFile << ponto2.y << ", " << ponto1.x << ", " << ponto2.z << ", " << -1 << ", " << 0 << ", " << 0 <<", "<<ponto2.y/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";
            MyFile << ponto2.y << ", " << ponto2.x << ", " << ponto2.z << ", " << -1 << ", " << 0 << ", " << 0 <<", "<<ponto2.y/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";

            // Face de X constante positivo
            MyFile << ponto1.y << ", " << ponto1.x << ", " << ponto1.z << ", " << 1 << ", " << 0 << ", " << 0 <<", "<<ponto1.y/comp +0.5 << ", "<<ponto1.z/comp+0.5 << "\n";
            MyFile << ponto1.y << ", " << ponto2.x << ", " << ponto1.z << ", " << 1 << ", " << 0 << ", " << 0 << ", "<<ponto1.y/comp +0.5 << ", "<<ponto1.z/comp+0.5 <<"\n";
            MyFile << ponto1.y << ", " << ponto2.x << ", " << ponto2.z << ", " << 1 << ", " << 0 << ", " << 0 <<", "<<ponto1.x/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";

            MyFile << ponto1.y << ", " << ponto1.x << ", " << ponto1.z << ", " << 1 << ", " << 0 << ", " << 0 << ", "<<ponto1.y/comp +0.5 << ", "<<ponto1.z/comp+0.5 <<"\n";
            MyFile << ponto1.y << ", " << ponto2.x << ", " << ponto2.z << ", " << 1 << ", " << 0 << ", " << 0 <<", "<<ponto1.y/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";
            MyFile << ponto1.y << ", " << ponto1.x << ", " << ponto2.z << ", " << 1 << ", " << 0 << ", " << 0 <<", "<<ponto1.y/comp +0.5 << ", "<<ponto2.z/comp+0.5 << "\n";

            // Face de Z constante negativo
            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto2.y << ", " << 0 << ", " << 0 << ", " << -1 << ", "<<ponto1.x/comp +0.5 << ", "<<ponto2.y/comp+0.5 <<"\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto2.y << ", " << 0 << ", " << 0 << ", " << -1 << ", "<<ponto2.x/comp +0.5 << ", "<<ponto2.y/comp+0.5 <<"\n";
            MyFile << ponto2.x << ", " << ponto1.z << ", " << ponto2.y << ", " << 0 << ", " << 0 << ", " << -1 << ", "<<ponto2.x/comp +0.5 << ", "<<ponto2.y/comp+0.5 <<"\n";

            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto2.y << ", " << 0 << ", " << 0 << ", " << -1 <<", "<<ponto1.x/comp +0.5 << ", "<<ponto2.y/comp+0.5 << "\n";
            MyFile << ponto1.x << ", " << ponto2.z << ", " << ponto2.y << ", " << 0 << ", " << 0 << ", " << -1 <<", "<<ponto1.x/comp +0.5 << ", "<<ponto2.y/comp+0.5 << "\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto2.y << ", " << 0 << ", " << 0 << ", " << -1 <<", "<<ponto2.x/comp +0.5 << ", "<<ponto2.y/comp+0.5 << "\n";

            // Face de Z constante positivo
            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto1.y << ", " << 0 << ", " << 0 << ", " << 1 << ", "<<ponto1.x/comp +0.5 << ", "<<ponto1.y/comp+0.5 <<"\n";
            MyFile << ponto2.x << ", " << ponto1.z << ", " << ponto1.y << ", " << 0 << ", " << 0 << ", " << 1 <<", "<<ponto2.x/comp +0.5 << ", "<<ponto1.y/comp+0.5 << "\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto1.y << ", " << 0 << ", " << 0 << ", " << 1 << ", "<<ponto2.x/comp +0.5 << ", "<<ponto1.y/comp+0.5 <<"\n";

            MyFile << ponto1.x << ", " << ponto1.z << ", " << ponto1.y << ", " << 0 << ", " << 0 << ", " << 1 << ", "<<ponto1.x/comp +0.5 << ", "<<ponto1.y/comp+0.5 <<"\n";
            MyFile << ponto2.x << ", " << ponto2.z << ", " << ponto1.y << ", " << 0 << ", " << 0 << ", " << 1 << ", "<<ponto2.x/comp +0.5 << ", "<<ponto1.y/comp+0.5 <<"\n";
            MyFile << ponto1.x << ", " << ponto2.z << ", " << ponto1.y << ", " << 0 << ", " << 0 << ", " << 1 << ", "<<ponto1.x/comp +0.5 << ", "<<ponto1.y/comp+0.5 <<"\n";
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
    float V[4] = { powf(v, 3.0) , powf(v, 2.0), v, 1 };
    float temp[4];
    float res;
    // temp = M * pontos[indices] * M * V
    multMatrixVector(calculado,V,temp);
    // res = U * temp
    res = powf(u, 3.0) * temp[0] + powf(u, 2.0) * temp[1] + u * temp[2] + temp[3];
    
    return res;
}
void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}



void drawBezier(float xCoords[4][4], float yCoords[4][4], float zCoords[4][4], int tess, string file){
    ofstream MyFile;
    MyFile.open(path + file,std::ios_base::app);

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

            float aux1[3] = {ponto1.x-ponto.x,ponto1.y-ponto.y,ponto1.z-ponto.z};
            float aux2[3] = {ponto3.x-ponto.x,ponto3.y-ponto.y,ponto3.z-ponto.z};
            float res1[3];
            cross(aux1,aux2,res1);
            normalize(res1);
            MyFile << ponto.x << ", " << ponto.y << ", " << ponto.z << ", "<< res1[0] <<", "<< res1[1] <<", "<< res1[2] << "\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z <<", "<< res1[0] <<", "<< res1[1] << ", "<< res1[2] <<"\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", " << ponto3.z << ", "<< res1[0] <<", "<< res1[1] <<", "<< res1[2] <<"\n";

            float aux3[3] = {ponto2.x-ponto1.x,ponto2.y-ponto1.y,ponto2.z-ponto1.z};
            float aux4[3] = {ponto3.x-ponto1.x,ponto3.y-ponto1.y,ponto3.z-ponto1.z};
            float res2[3];
            cross(aux3,aux4,res2);
            normalize(res2);

            // triangulo 2
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z <<", "<< res2[0] <<", "<< res2[1] << ", "<< res2[2]<< "\n";
            MyFile << ponto2.x << ", " << ponto2.y << ", " << ponto2.z <<", "<< res2[0] <<", "<< res2[1] << ", "<< res2[2] <<"\n";
            MyFile << ponto3.x << ", " << ponto3.y << ", " << ponto3.z <<", "<< res2[0] <<", "<< res2[1] << ", "<< res2[2] << "\n";
        }
        
    }
    
}

void construcaoMatrizes(int tess, string file)
{
    float xCoords[4][4];
    float yCoords[4][4];
    float zCoords[4][4];
    float m[4][4] = {	{-1.0f,  3.0f, -3.0f,  1.0f},   // Matriz de Bezier
						{ 3.0f, -6.0f,  3.0f,  0.0f},
						{-3.0f,  3.0f,  0.0f,  0.0f},
						{ 1.0f,  0.0f,  0.0f,  0.0f}};
    
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
}

// Trata do ficheiro patch dado
void readPatch(string patch, int tess, string file)
{
    ifstream patch_file("../" + patch);
    int n_patch, n_cpoints;
    char valor[2];

    string line ;

    getline(patch_file,line);   
    std::ofstream outfile;
    outfile.open(path+file);

    n_patch = atoi(line.c_str());

    //cout << n_patch << " numero patches";
    
    // Guardar os indices
    for (int i = 0; i < n_patch; i++)
    {
        vector<float> auxiliar;
        getline (patch_file,line);
        std::vector<std::string> v = split (line, ", ");
        for (auto a: v)
        {
            auxiliar.push_back(atoi(a.c_str()));
        }
        indices.push_back(auxiliar);
    }
    

    getline(patch_file,line);

    n_cpoints = atoi(line.c_str());


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

    construcaoMatrizes(tess,file);

    
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





