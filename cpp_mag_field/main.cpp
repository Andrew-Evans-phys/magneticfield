#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include "Vector.h"
using namespace std;

Vector wire(float t){
    float x_coord = .5*cos(t);
    float y_coord = .5*sin(t);
    float z_coord = 0;
    Vector new_vector;
    new_vector.setVec(x_coord, y_coord, z_coord);
    return new_vector;
}

void data_out(string data){
    string filename("data.txt");
    ofstream file_out;

    file_out.open(filename, std::ios_base::app);
    file_out << data << endl;
}

Vector mag_field_calc(Vector magnetic_field_point, float upper_bound, float lower_bound, float grain, float current, float dl){
    Vector magnetic_field;
    magnetic_field.setVec(0,0,0);

    for(int i = 0; i < grain+1; i++){
        float step = lower_bound + dl*(i);
        float next_step = lower_bound + dl*(i+1);
        Vector path = wire(step);
        Vector next_path_pos = wire(next_step);
        Vector dl_vec = (next_path_pos - path)*current;
        Vector r = magnetic_field_point - path;
        Vector cross = dl_vec.cross_product(r);
        cross = cross*(1.0/(r.length()*r.length()));
        magnetic_field = magnetic_field + cross; 
    }
    return magnetic_field;
}

int main(){   
    //defining constants  
    float mu0 = .00000126;
    float pi = 3.1415;

    //setting run parameters
    float grain = 1000;
    float search_grain = 5;
    float search_upper_bound = 1;
    float search_lower_bound = -1;
    float upper_bound = 2*pi;
    float lower_bound = 0;
    float dl = ((upper_bound-lower_bound)/grain);
    float current = 1.0;

    //defining vectors
    Vector magnetic_field_point;
    Vector magnetic_field;
    Vector variation;

    //search  algorithm 
    for(int l = 0; l < search_grain+1; l++){
        float dx = (search_upper_bound-search_lower_bound)/search_grain;
        for(int k = 0; k < (search_grain+1); k++){ 
            float dz = (search_upper_bound-search_lower_bound)/search_grain;
            for(int j = 0; j < search_grain+1; j++){
                float dy = (search_upper_bound-search_lower_bound)/search_grain;
                magnetic_field_point = wire(dx*l);
                variation.setVec(search_lower_bound + dx*l, search_lower_bound + dy*j, search_lower_bound + dz*k);
                magnetic_field_point = magnetic_field_point + variation; 
                magnetic_field = mag_field_calc(magnetic_field_point, upper_bound, lower_bound, grain, current, dl);
                /*
                //For unit accurate measurements 
                double temp = mu0/(pi*4.0);
                float coeff = (float) temp;
                magnetic_field = magnetic_field*coeff;
                */
                //writing to file 
                string output_data = magnetic_field_point.data_out()+" "+magnetic_field.data_out();
                data_out(output_data);
            }
        }
    }
    return 0;
}