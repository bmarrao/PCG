
#include <iostream>
#include <string.h>
#include <cstdlib>

void drawSphere(float radius,int slices, int stacks,char const* file)
{

}

void drawCone(float radius, float height, int slices,int stacks, char const* file	) 
{

}

void drawPlane(int comp, int slices, char const* file)
{

}

void drawCube(int comp, int slices, char const* file)
{

}

int main (int argc, char const *argv[])
{
    if (argc <=  1)
    {
          std::cout << "Invalid input";

    }
    else if (strcmp(argv[1],"sphere") && argc == 5 )
    {
        drawSphere(atof(argv[2]), atoi(argv[3]),atoi(argv[4]),argv[5]);
    }
    else if (strcmp(argv[1],"box") && argc == 4 )
    {
        drawBox(atoi(argv[2]), atoi(argv[3]),argv[4]);
    }
    

}


