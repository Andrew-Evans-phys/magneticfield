#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <typeinfo>

using namespace std;

class Vector{
    public:
        void display(){
            cout << "[" << e1 << ", " << e2 << ", " << e3 << "]"<< endl;
        }

        void setVec(float b1, float b2, float b3){
            e1 = b1;
            e2 = b2;
            e3 = b3;
        }

        void set_vec_comp(int pos, float value){
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

        float get_vec_comp(int pos){
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


        Vector operator+(Vector v){
            Vector new_vector;
            float o_e1 = this->e1;
            float o_e2 = this->e2;
            float o_e3 = this->e3;

            float n_e1 = v.get_vec_comp(0);
            float n_e2 = v.get_vec_comp(1);
            float n_e3 = v.get_vec_comp(2);

            new_vector.setVec(n_e1 + o_e1, n_e2 + o_e2, n_e3 + o_e3);
            return new_vector;
        }

        Vector operator-(Vector v){
            Vector new_vector;
            float o_e1 = this->e1;
            float o_e2 = this->e2;
            float o_e3 = this->e3;

            float n_e1 = v.get_vec_comp(0);
            float n_e2 = v.get_vec_comp(1);
            float n_e3 = v.get_vec_comp(2);

            new_vector.setVec(-n_e1 + o_e1, -n_e2 + o_e2, -n_e3 + o_e3);
            return new_vector;
        }

        Vector operator*(float scalar){
            Vector new_vector;
            float o_e1 = this->e1;
            float o_e2 = this->e2;
            float o_e3 = this->e3;

            new_vector.setVec(scalar*o_e1, scalar*o_e2, scalar*o_e3);
            return new_vector;
        }

        float dot_product(Vector v){
            float o_e1 = this->e1;
            float o_e2 = this->e2;
            float o_e3 = this->e3;  
            float n_e1 = v.get_vec_comp(0);
            float n_e2 = v.get_vec_comp(1);
            float n_e3 = v.get_vec_comp(2);

            return o_e1*n_e1 + o_e2*n_e2 + o_e3*n_e3;
        }

        Vector cross_product(Vector v){
            float o_e1 = this->e1;
            float o_e2 = this->e2;
            float o_e3 = this->e3;  
            float n_e1 = v.get_vec_comp(0);
            float n_e2 = v.get_vec_comp(1);
            float n_e3 = v.get_vec_comp(2);

            Vector new_vector;
            new_vector.setVec(o_e2*n_e3 - o_e3*n_e2, o_e3*n_e1 - o_e1*n_e3, o_e1*n_e2 -n_e1*o_e2);
            return new_vector;
        }

        float length(){
            float o_e1 = this->e1;
            float o_e2 = this->e2;
            float o_e3 = this->e3;  

            float squared_total = o_e1*o_e1 + o_e2*o_e2 + o_e3*o_e3;
            return pow(squared_total,0.5);
        }

        string data_out(){
            std::ostringstream stream;
            stream << "[" << e1;
            stream << ", " << e2;
            stream << ", " << e3;
            stream << "]";
            string text = stream.str();
            return text;
        }


    private:
        float e1;
        float e2;
        float e3;
};


Vector wire(float t){
    float x_coord = .5*cos(t);
    float y_coord = .5*sin(t);
    float z_coord = 0;
    Vector new_vector;
    new_vector.setVec(x_coord, y_coord, z_coord);
    return new_vector;
}

int main(){   
    //opening file
    float mu0 = .00000126;
    float pi = 3.1415;
    ofstream MyFile("data.txt"); 
    float grain = 10000;
    float search_grain = 10;
    float search_upper_bound = 2;
    float search_lower_bound = -2;
    float upper_bound = 2*pi;
    float lower_bound = 0;
    float dl = ((upper_bound-lower_bound)/grain);
    float current = 1.0;

    Vector magnetic_field_point;
    Vector magnetic_field;
    Vector dl_vec;
    Vector path;
    Vector next_path_pos;
    Vector r;
    Vector cross;

for(int l = 0; l < search_grain+1; l++){
    float dx = (search_upper_bound-search_lower_bound)/search_grain;
    for(int k = 0; k < (search_grain+1); k++){ //
        float dz = (search_upper_bound-search_lower_bound)/search_grain;

        for(int j = 0; j < search_grain+1; j++){
            float dy = (search_upper_bound-search_lower_bound)/search_grain;
            magnetic_field.setVec(0,0,0);
            magnetic_field_point.setVec(search_lower_bound + dx*l, search_lower_bound + dy*j, search_lower_bound+dz*k);
            
            for(int i = 0; i < grain+1; i++){
                float step = lower_bound + dl*(i);
                float next_step = lower_bound + dl*(i+1);
                path = wire(step);
                next_path_pos = wire(next_step);
                dl_vec = (next_path_pos - path)*current;
                r = magnetic_field_point - path;
                cross = dl_vec.cross_product(r);
                cross = cross*(1.0/(r.length()*r.length()));
                magnetic_field = magnetic_field + cross; 
            }
            /*
            //For unit accurate measurements 
            double temp = mu0/(pi*4.0);
            float coeff = (float) temp;
            magnetic_field = magnetic_field*coeff;
            */
            //writing to file 
            MyFile << magnetic_field_point.data_out()+" "+magnetic_field.data_out() + "\n";
        }
    }
}

    

    // Closing the file
    MyFile.close();
    return 0;
}