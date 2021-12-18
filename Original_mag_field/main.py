import scipy.integrate as integrate
import scipy.special as special
import math as m
import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt

def path_func(x,y,z):
    return np.array([m.cos(15*z),m.sin(15*z),z])

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
    

#line direction must be a unit vector
def descrete_integral(steps,start,end,function,position,curve):
    out = 0
    for i in range(1,steps+1):
        out += function(position, curve(0,0,start+(end-start)/steps*i+.01)-curve(0,0,start+(end-start)/steps*i), curve(0,0,start+(end-start)/steps*i)) #wrong
    return out

#ignore this class for now
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



#p1 = Particle(1, 1, np.array([1.,0.,0.]), np.array([0.,0.,0.]))



bound_range = 4

output_vectors = []
for i in range(1,bound_range):
    for j in range(bound_range-3):
        for k in range(bound_range+4):
            start_point = [i-3,j,k-3]
            output_vectors.append(vector_correct(start_point, descrete_integral(100, 0., 2*m.pi, Bfield, start_point, path_func)))


fig = plt.figure()

# draw vector
soa = np.array(output_vectors)

X, Y, Z, U, V, W = zip(*soa)
ax = fig.gca(projection='3d')

zline = np.linspace(0, 2*m.pi, 500)
yline = np.sin(15*zline)
xline = np.cos(15*zline)


ax.plot3D(xline, yline, zline, 'gray')

ax.quiver(X, Y, Z, U, V, W, length=.75, normalize=True)
ax.set_xlim([-50, 50])
ax.set_ylim([-50, 50])
ax.set_zlim([-50, 50])
ax.set_title("Magnetic field of a solenoid")

p1 = Particle(1,1,np.array([-10.,0.,0.]),np.array([1.,0.,0.]))
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

#fig = plt.figure()
#ax = plt.axes(projection='3d')
#ax.scatter3D(xpos, ypos, zpos,c=xpos, cmap='Greens')
#plt.show()



