import scipy.integrate as integrate
import scipy.special as special
import math as m
import numpy as np
import matplotlib as mpl 
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
from matplotlib import cm


def path_func(x,y,z):
    return np.array([m.cos(z),m.sin(z),0*z])

def vector_correct(position, input_vector):
    corrected_vector = []
    for i in position:
        corrected_vector.append(i)
    for j in input_vector:
        corrected_vector.append(j)
    return corrected_vector

def Bfield(position, line_direction, line_position):
    current = 1
    return current*np.cross(line_direction/np.linalg.norm(line_direction),((position-line_position)/np.linalg.norm(position-line_position)))/np.linalg.norm(position-line_position)**2
    
def descrete_integral(steps,start,end,function,position,curve):
    out = 0
    for i in range(1,steps+1):
        out += function(position, curve(0,0,start+(end-start)/steps*i+.01)-curve(0,0,start+(end-start)/steps*i), curve(0,0,start+(end-start)/steps*i)) #wrong
    return out

class Particle:
    def __init__(self, mass, charge, position, velocity):
        self.mass = mass
        self.charge = charge
        self.position = position
        self.velocity = velocity
        
    def MagneticForce(self, angle, Bfield): #should be deleted
        return self.charge*self.velocity*Bfield*m.sin(angle)
    
    def update(self, force, timestep):
        accel = force/self.mass
        self.velocity += accel*timestep
        self.position += self.velocity*timestep+.5*accel*timestep**2 

bound_range = 3
vector_list = []
output_vectors = []
for i in range(1,bound_range):
    for j in range(1,bound_range):
        for k in range(1,bound_range):
            start_point = [i-3,j-3,k-3]
            magnetic_field_vector = descrete_integral(100, 0., 2*m.pi, Bfield, start_point, path_func)
            vector_list.append(list(magnetic_field_vector))
            output_vectors.append(vector_correct(start_point, magnetic_field_vector))
print(vector_list)
fig = plt.figure()
# draw vector
soa = np.array(output_vectors)
X, Y, Z, U, V, W = zip(*soa)
ax = fig.gca(projection='3d')


#need to make this line write the vector magnitude into some stupid fucking impossible to understand/ communicate form, seriously am I the first person to ever want this????
M = []
for i in vector_list:
    M.append([np.sqrt(i[0]*i[0]+i[1]*i[1]+i[2]*i[2])])


#curve
zline = np.linspace(0, 2*m.pi, 500)
yline = np.sin(zline)
xline = np.cos(zline)
ax.plot3D(xline, yline, 0*zline, 'gray')

#vector setup

cmap = plt.get_cmap()
ax.quiver(X, Y, Z, U, V, W, M, cmap=plt.cm.jet, length=0.5, color = cmap(M))
ax.set_xlim([-50, 50])
ax.set_ylim([-50, 50])
ax.set_zlim([-50, 50])
ax.set_title("Magnetic field of a solenoid")

p1 = Particle(20,1,np.array([-2.,0.,0.]),np.array([0.,.1,0.]))
path_of_particle_x = []
path_of_particle_y = []
path_of_particle_z = []

for counter in range(1000):
    path_of_particle_x.append(p1.position[0])
    path_of_particle_y.append(p1.position[1])
    path_of_particle_z.append(p1.position[2])
    p1.update(descrete_integral(100, 0., 2*m.pi, Bfield, p1.position, path_func),.01)

ax.scatter3D(path_of_particle_x,path_of_particle_y,path_of_particle_z, color = "red")

plt.show()





