#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include "Vector.h"
using namespace std;

//defined  globals
float mu0 = .00000126;
float pi = 3.1415;

Vector wire(float t){
    float x_coord = 0.5*cos(t);
    float y_coord = 0.5*sin(t);
    float z_coord = t;
    Vector new_vector;
    new_vector.setVec(x_coord, y_coord, z_coord);
    return new_vector;
}

void data_out(string data, string file){
    string filename(file);
    ofstream file_out;

    file_out.open(filename, std::ios_base::app);
    file_out << data << endl;
}

void data_delete(string file){
  ofstream MyFile(file);
  MyFile << "";
  MyFile.close();
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

void search_field(float wire_grain, float search_grain, float upper_bound, float lower_bound, float int_grain, float current, int start_layer, int end_layer ){
    Vector magnetic_field_point;
    Vector magnetic_field;

    //defining small change in wire, the search radius, and a small change in angle
    float dwire = (upper_bound-lower_bound)/int_grain;

    float dtheta = (2*pi)/search_grain;
    for(int k = 1; k <= end_layer; k++){   
        float base_search_radius = .2*k; //need to iterate! use start_layer nd end_layer with if for layer control
        if(k >= start_layer){
            for(int i = 0; i < wire_grain; i++){
            float step = (upper_bound-lower_bound)/wire_grain;
            
            //defining tangent path vectors and normalizing 
            Vector dl = wire(step*(i+0.001)+lower_bound)- wire(step*(i)+lower_bound);
            Vector dlprime = wire(step*(i+0.0002)+lower_bound)- wire(step*(i+0.0001)+lower_bound);
            dl.normalize();
            dlprime.normalize();
            


            //Calculating acceleration vector and normalizing  
            Vector dn = dlprime-dl;
            dn.normalize();

            //checking for the straght line case
            if(dn.get_vec_comp(0) == 0 && dn.get_vec_comp(1) == 0 && dn.get_vec_comp(2) == 0){
                Vector dl = wire(step*(i+0.001)*step*(i+0.001)+lower_bound) - wire(step*i*step*i+lower_bound);
                dl.normalize();
                }
            
            //finding B
            Vector B = dl.cross_product(dn);
            B.normalize();
            

            for(int j = 0; j < search_grain+1; j++){
                Vector variation = dn*sin(dtheta*j) + B*cos(dtheta*j);
                //variation = variation*base_search_radius;
                Vector search_point = wire(step*i+lower_bound) + variation*base_search_radius;
                magnetic_field = mag_field_calc(search_point, upper_bound, lower_bound, int_grain, current, dwire);
                string output_data = search_point.data_out()+" "+magnetic_field.data_out(); //string output_data = search_point.data_out()+" "+magnetic_field.data_out()
                data_out(output_data, "data.txt");
                }
            }
        }
        
    }
    

}

int main(){   
    //setting run parameters
    float wire_grain = 10;
    float search_grain = 10;
    float int_grain = 10000;
    float upper_bound = pi;
    float lower_bound = -1*pi;
    float current = 1.0;
    int start_layer = 1;
    int end_layer = 2;

    //Clearing old data 
    data_delete("data.txt");

    //Searching points on a unit circle around wire
    search_field(wire_grain, search_grain, upper_bound, lower_bound, int_grain, current, start_layer, end_layer);

    return 0;
}