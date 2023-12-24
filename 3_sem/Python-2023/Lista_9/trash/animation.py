import matplotlib.pyplot as plt
import matplotlib.animation as animation
import math
import numpy as np
def init():
    line.set_data([], [])
    return line,
def animate(i):
    t = 0.01*i
    x = math.sin(a * t + math.pi / 2.0)
    y = math.sin(b*t)
    xdata.append(x)
    ydata.append(y)
    line.set_data(xdata, ydata)
    return line,
def animate_1(i):
    global xdata, ydata
    t = 0.01*i
    x = math.sin(a * t + np.pi / 2.0)
    y = math.sin(b*t)
    xdata.append(x)
    xdata = xdata[-50:]
    ydata.append(y)
    ydata = ydata[-50:]
    line.set_data(xdata, ydata)
    return line,
a, b = 9, 8
fig = plt.figure()
ax = plt.axes(xlim=(-2, 2), ylim=(-2, 2))
xdata, ydata = [], []
line, = ax.plot([], [])


ani = animation.FuncAnimation(fig, animate_1,
init_func=init, frames=500,
interval=50, blit=True)
plt.show()