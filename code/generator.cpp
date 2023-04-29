#define _USE_MATH_DEFINES
#include <math.h>	
#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
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

// Trata do ficheiro patch dado
void drawBezier(string patch, int tess, string file)
{
    ifstream patch_file("../" + patch);
    int n_patch, n_cpoints;
    char valor[2];
    vector<vector<float>> indices;
    vector<point> pontos_controlo;
    string line ;
    
    getline (patch_file,line);

    n_patch = atoi(line.c_str());
    //patch_file >> n_patch;

    cout << n_patch << " numero patches";
    
    for (int i = 0; i < n_patch; i++)
    {
        vector<float> auxiliar;
        getline (patch_file,line);
        std::vector<std::string> v = split (line, ",");
        for (auto a: v)
        {
            auxiliar.push_back(atoi(a.c_str()));
        }
        //string line;
        /*
        for (int j = 0; j < 16; j++)
        {
            string line ;
            getline (patch_file,line);
            std::vector<std::string> v = split (line, ",");

            // getline(patch_file,line);
            // string delimiter = ",";
            // auxiliar = split(line, delimiter);
            //patch_file.getline(valor, 256, ',');
            auxiliar.push_back(atoi(valor));
            cout << valor << " ";
            
        }
         */
        indices.push_back(auxiliar);
        //cout << i <<"\n";
    }

     for (auto i : indices)
     {
         for(auto j : i){
             cout << j << " " ;
        }
         cout <<"\n";
    }
    

    patch_file >> n_cpoints;
    // cout << "ola";
    // cout << n_cpoints;

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
            drawBezier(argv[2], atoi(argv[3]),argv[4]);
        }
      
    }
   
    

}





