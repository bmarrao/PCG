
#include <math.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
using std::ofstream;
using namespace std;



#include <iostream>
#include <sstream>
#include <vector>

// for string delimiter
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


void render3D(char * file)
{
    string line;
    //glBegin(GL_TRIANGLES);
    ifstream indata;
    indata.open(file);
    while ( getline (indata,line) )
    {
        std::string delimiter = ",";
        std::vector<std::string> v = split (line, delimiter);

        float point [3];
		int j = 0;
        for (auto i : v)
        {
			point[j] = atof(i.c_str());
			j = j + 1;
        }
		//glVertex3f(point[0], point[1], point[2]);
        cout << point[0] << " " << point[1] << " " <<  point[2];
        cout << "\n";
        //cout << x << y << z;
    }
    indata.close();
}



int main ()
{
    render3D("box.3d");
    return 1;
}