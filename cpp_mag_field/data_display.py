import matplotlib.pyplot as plt
import numpy as np

#checking total data
f = open("data.txt", "r")
line_count = 0
for line in f:
    if line != "\n":
        line_count += 1
f.close()

#data extraction 
data = []
f = open("data.txt", "r")
for i in range(line_count):
     data.append(f.readline()[:-1])
f.close()

#separating position argument from magnetic field argument 
position = []
magnetic_field = []

for i in data:
     split_data = i.split("[")
     position.append(split_data[1][:-2])
     magnetic_field.append(split_data[2][:-1])

for i in range(len(position)):
     position[i] = position[i].split(",")
     magnetic_field[i] = magnetic_field[i].split(",")

pos_x = []
pos_y = []
pos_z = []
mag_x = []
mag_y = []
mag_z = []
for i in position:
     pos_x.append(float(i[0]))
     pos_y.append(float(i[1]))
     pos_z.append(float(i[2]))
for i in magnetic_field:  
     mag_x.append(float(i[0]))
     mag_y.append(float(i[1]))
     mag_z.append(float(i[2]))

strength = []
for i in range(len(mag_x)):
     strength.append(np.sqrt(mag_x[i]**2+mag_y[i]**2+mag_z[i]**2))


fig = plt.figure()
ax = fig.add_subplot(projection='3d')


s = 1
ax.quiver(pos_x, pos_y, pos_z, mag_x, mag_y, mag_z, length=.4, lw=2, normalize=True)#, colors = strength
ax.scatter([1,1,1,-1], [1,-1,1,-1], [1,1,-1,-1])
#xline = []
#yline = []
#zline = []
#ax.plot3D(xline, yline, zline, 'gray') #This needs data

plt.show()