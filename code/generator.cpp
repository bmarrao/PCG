#define _USE_MATH_DEFINES
#include <math.h>	
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
using std::ofstream;
using namespace std;

struct point 
{
    float x;
    float y;
	float z;
};
void drawSphere(float radius,int slices, int stacks,char const* file)
{

}

void drawCone(float radius, float height, int slices,int stacks, char const* file	) 
{
    ofstream MyFile;
    MyFile.open(file);

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
        MyFile << ponto1.x << ", " << ponto1.y << ", "<< ponto1.z << "\n";
        MyFile << ponto2.x << ", " << ponto2.y << ", "<< ponto2.z<< "\n";

        
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

void drawPlane(int comp, int slices, char const* file)
{
    ofstream MyFile;
    MyFile.open(file);

    int aresta = comp / slices; 
    int posicao = comp / 2;

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

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto1.z << "\n";

            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto1.z << "\n";
            MyFile << ponto1.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
            MyFile << ponto2.x << ", " << ponto1.y << ", " << ponto2.z << "\n";
        }
    }
}

void drawBox(int comp, int slices, char const* file)
{

}

int main (int argc, char const *argv[])
{
    cout << argc << argv[1];
    if (argc <=  1)
    {
          std::cout << "Invalid input";

    }
    else if (strcmp(argv[1],"sphere") && argc == 5 )
    {
        drawSphere(atof(argv[2]), atoi(argv[3]),atoi(argv[4]),argv[5]);
    }
    else if (!(strcmp(argv[1],"box")) && argc == 5 )
    {
        cout << "oi";
        drawBox(atoi(argv[2]), atoi(argv[3]),argv[4]);
    }
    else if (!(strcmp(argv[1],"cone")) && argc == 7 )
    {
        drawCone(atof(argv[2]), atof(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
    }
    else if (!(strcmp(argv[1],"plane")) && argc == 4 )
    {
        drawPlane(atoi(argv[2]), atoi(argv[3]),argv[4]);
    }
    

}


