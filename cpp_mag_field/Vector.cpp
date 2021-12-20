#include "Vector.h"
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

void Vector::display(){
    cout << "[" << e1 << ", " << e2 << ", " << e3 << "]"<< endl;
}

void Vector::setVec(float b1, float b2, float b3){
    e1 = b1;
    e2 = b2;
    e3 = b3;
}

void Vector::set_vec_comp(int pos, float value){
    switch(pos) {
        case 0:
            e1 = value;
            break;
        case 1:
            e2 = value;
            break;
        case 2:
            e3 = value;
            break;
        default:
            cout << "Not a valid component, not changing the vector" << endl;
        }
}

float Vector::get_vec_comp(int pos){
    float output = 0;
    switch(pos) {
        case 0:
            output = e1;
            break;
        case 1:
            output = e2;
            break;
        case 2:
            output = e3;
            break;
        default:
            cout << "Not a valid component, returning 0" << endl;
        }
        return output;
}


Vector Vector::operator+(Vector v){
    Vector new_vector;

    float n_e1 = v.get_vec_comp(0);
    float n_e2 = v.get_vec_comp(1);
    float n_e3 = v.get_vec_comp(2);

    new_vector.setVec(n_e1 + e1, n_e2 + e2, n_e3 + e3);
    return new_vector;
}

Vector Vector::operator-(Vector v){
    Vector new_vector;

    float n_e1 = v.get_vec_comp(0);
    float n_e2 = v.get_vec_comp(1);
    float n_e3 = v.get_vec_comp(2);

    new_vector.setVec(-n_e1 + e1, -n_e2 + e2, -n_e3 + e3);
    return new_vector;
}

Vector Vector::operator*(float scalar){
    Vector new_vector;

    new_vector.setVec(scalar*e1, scalar*e2, scalar*e3);
    return new_vector;
}

float Vector::dot_product(Vector v){
    float n_e1 = v.get_vec_comp(0);
    float n_e2 = v.get_vec_comp(1);
    float n_e3 = v.get_vec_comp(2);

    return e1*n_e1 + e2*n_e2 + e3*n_e3;
}

Vector Vector::cross_product(Vector v){
    float n_e1 = v.get_vec_comp(0);
    float n_e2 = v.get_vec_comp(1);
    float n_e3 = v.get_vec_comp(2);

    Vector new_vector;
    new_vector.setVec(e2*n_e3 - e3*n_e2, e3*n_e1 - e1*n_e3, e1*n_e2 -n_e1*e2);
    return new_vector;
}

float Vector::length(){
    float squared_total = e1*e1 + e2*e2 + e3*e3;
    return pow(squared_total,0.5);
}

void Vector::normalize(){
    float norm_factor = sqrt(e1*e1 + e2*e2 + e3*e3);
    e1 /= norm_factor;
    e2 /= norm_factor;
    e3 /= norm_factor;
}

string Vector::data_out(){
    std::ostringstream stream;
    stream << "[" << e1;
    stream << ", " << e2;
    stream << ", " << e3;
    stream << "]";
    string text = stream.str();
    return text;
}
