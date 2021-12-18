import matplotlib as mpl 
import matplotlib.pyplot as plt
from numpy import arange,meshgrid,sqrt

u,v = arange(-50,51,10),arange(-50,51,10)
print(u)
u,v = meshgrid(u,v)
print(u)
M = sqrt(u*u+v*v) # magnitude
print(M)
x,y = u,v
qq=plt.quiver(x,y,u,v,M,cmap=plt.cm.jet)
plt.colorbar(qq, cmap=plt.cm.jet)
plt.show()