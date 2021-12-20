#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef VECTORH
#define VECTORH
class Vector{
    public:
        void display();
        void setVec(float b1, float b2, float b3);
        void set_vec_comp(int pos, float value);
        float get_vec_comp(int pos);
        Vector operator+(Vector v);
        Vector operator-(Vector v);
        Vector operator*(float scalar);
        float dot_product(Vector v);
        Vector cross_product(Vector v);
        float length();
        void normalize();
        string data_out();
    private:
        float e1;
        float e2;
        float e3;
};
#endif