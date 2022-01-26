import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as ani
from matplotlib import cm

def f(x, y):
    return 1 - x**2 - y**2
F = np.vectorize(f)

# def u(x, y):

# U = np.vectorize(u)
a = 1.5
x = np.linspace(-a, a, 300)
y = np.linspace(-a, a, 300)
X, Y = np.meshgrid(x, y)
phi = F(X, Y)
# print(Z)

fig = plt.figure()
# fig.canvas.manager.full_screen_toggle()
ax = plt.axes(xlim=(-a, a), ylim=(-a, a))
ax.grid()
ax.set_aspect('equal')
# ax.plot(0, 0, 'k.', markersize=5)
# fig2 = plt.figure()
# ax2 = plt.axes(projection='3d')
# ax2.contour3D(X, Y, Z, 200, cmap=cm.winter)
# ax2.plot_surface(X, Y, Z2, color="grey")
# ax2.grid()


runtime = 10.0
fps = 60
frames = int(runtime*fps)
dt = 1/fps

# for i in range(it):
#     dphi = np.gradient(phi)
#     dphi_norm = np.sqrt(np.sum(np.power(dphi, 2), axis=0))

#     phi = phi + dt*F*dphi_norm

#     plt.contour(phi, 0)
#     plt.show()
kappa = []
nabla_phi = []

def pde(i, X, Y, phi, ax):
    global kappa, nabla_phi
    ax.cla()
    ax.grid()
    nabla_phi = np.gradient(phi)
    norm_nabla_phi = np.sqrt(np.sum(np.power(nabla_phi, 2), axis=0))
    kappa = np.gradient(nabla_phi[0])[0] + np.gradient(nabla_phi[1])[1]
    nabla_pos = np.power(np.power(np.fmax(-nabla_phi[0], 0), 2) + np.power(np.fmin(nabla_phi[0], 0), 2) + np.power(np.fmax(-nabla_phi[1], 0), 2) + np.power(np.fmin(nabla_phi[1], 0), 2), 1/2)
    nabla_neg = np.power(np.power(np.fmax(nabla_phi[0], 0), 2) + np.power(np.fmin(-nabla_phi[0], 0), 2) + np.power(np.fmax(nabla_phi[1], 0), 2) + np.power(np.fmin(-nabla_phi[1], 0), 2), 1/2)
    phi -= dt*(np.fmax(kappa, 0) @ nabla_pos + np.fmin(kappa, 0) @ nabla_neg)
    # phi -= dt*(np.fmax(kappa, 0) + np.fmin(kappa, 0))
    # phi -= dt*30*norm_nabla_phi
    ax.contour(X, Y, phi, 0, linewidths=1, cmap=cm.plasma)

anim = ani.FuncAnimation(fig, pde, frames, fargs=(X, Y, phi, ax), interval=1000*dt, repeat=False)
plt.show()
