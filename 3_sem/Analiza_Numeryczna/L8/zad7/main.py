import matplotlib.pyplot as plt
import nifs_data_2 as data
from nifs import NIFS3

x = data.x
t = data.t
y = data.y
u = data.u_lst

x_2 = data.x_2
t_2 = data.t_2
y_2 = data.y_2
u_2 = data.u_lst_2

ax = NIFS3(t, x)
ay = NIFS3(t, y)

ax_2 = NIFS3(t_2, x_2)
ay_2 = NIFS3(t_2, y_2)

sx = ax.result()
sy = ay.result()

sx_2 = ax_2.result()
sy_2 = ay_2.result()

fig, ax = plt.subplots()
# plt.plot(x, y)
plt.plot([sx(k) for k in u], [sy(k) for k in u])
plt.plot([sx_2(k) for k in u_2], [sy_2(k) for k in u_2])
plt.show()