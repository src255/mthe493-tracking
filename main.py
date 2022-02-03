import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as ani
import matplotlib.cm as cm
plt.rcParams['animation.ffmpeg_path'] ='C:/ffmpeg/bin/ffmpeg.exe'


# width = 101
N = 20
fraction = 1/8
INSIDE = 0.1
phi = np.full((N, N), -INSIDE)
for i in range(int(np.ceil(N*fraction)), int(np.floor(N*(1-fraction)))):
    for j in range(int(np.ceil(N*fraction)), int(np.floor(N*(1-fraction)))):
        phi[i][j] = INSIDE

fig = plt.figure()
ax = plt.axes(xlim=(0, N+1), ylim=(0, N+1))
ax.set_xticks(np.arange(0, N, 5))
ax.set_yticks(np.arange(0, N, 5))
ax.set_xticklabels([])
ax.set_yticklabels([])
ax.grid()
ax.set_aspect('equal')



# ax.contour(phi, 0, cmap=cm.inferno, linewidths=1)
# ax.plot(0, 0, 'k.', markersize=5)
# fig2 = plt.figure()
# ax2 = plt.axes(projection='3d')
# ax2.contour3D(X, Y, Z, 200, cmap=cm.winter)
# ax2.plot_surface(X, Y, Z2, color="grey")
# ax2.grid()


fps = 10
DT = round(1000/fps)
frames = 1_000
dt = 1
phi_x = np.zeros(np.shape(phi))
phi_y = np.zeros(np.shape(phi))
h = 1

def update(phi, epsilon, plot_points):
    global phi_x, phi_y, dt, h
    for i in range(N):
        for j in range(N):
            # compute phi_x
            if i == 0:
                phi_x[i][j] = (phi[i+1][j] - phi[i][j])/(2*h)
            elif i == N-1:
                phi_x[i][j] = (phi[i][j] - phi[i-1][j])/(2*h)
            else:
                phi_x[i][j] = (phi[i+1][j]-phi[i-1][j])/(2*h)

            # compute phi_y
            if j == 0:
                phi_y[i][j] = (phi[i][j+1] - phi[i][j])/(2*h)
            elif j == N-1:
                phi_y[i][j] = (phi[i][j] - phi[i][j-1])/(2*h)
            else:
                phi_y[i][j] = (phi[i][j+1]-phi[i][j-1])/(2*h)
    # phi_x, phi_y = np.gradient(phi)
    for i in range(N):
        for j in range(N):
            # compute phi_xx
            if i == 0:
                phi_xx = (phi_x[i+1][j] - phi_x[i][j])/(2*h)
            elif i == N-1:
                phi_xx = (phi_x[i][j] - phi_x[i-1][j])/(2*h)
            else:
                phi_xx = (phi_x[i+1][j]-phi_x[i-1][j])/(2*h)
            # compute phi_xy
            if j == 0:
                phi_xy = (phi_x[i][j+1] - phi_x[i][j])/(2*h)
            elif j == N-1:
                phi_xy = (phi_x[i][j] - phi_x[i][j-1])/(2*h)
            else:
                phi_xy = (phi_x[i][j+1]-phi_x[i][j-1])/(2*h)

            # compute phi_yy
            if j == 0:
                phi_yy = (phi_y[i][j+1] - phi_y[i][j])/(2*h)
            elif j == N-1:
                phi_yy = (phi_y[i][j] - phi_y[i][j-1])/(2*h)
            else:
                phi_yy = (phi_y[i][j+1]-phi_y[i][j-1])/(2*h)

            # print(f"PHI_xx{iteration}({i}, {j}) = {phi_xx})")
            # print(f"PHI_yy{iteration}({i}, {j}) = {phi_yy})")
            # compute K_n
            denominator = np.power(phi_x[i][j]**2 + phi_y[i][j]**2, 3/2) + 10e-6

            # deal with denominator = 0 case
            # if np.abs(denominator) == 0:
            #     # print(phi_x[i][j])
            #     # exit(1)
            #     K_n = 0
            # else:
            K_n = (phi_xx*phi_y[i][j]**2 - 2*phi_y[i][j]*phi_x[i][j]*phi_xy + phi_yy*phi_x[i][j]**2)/denominator
            phi[i][j] += dt*epsilon*K_n*np.sqrt((phi_x[i][j]**2 + phi_y[i][j]**2))
            # if K_n != 0:
            #     print(K_n)

            # clip phi to the range [-1000, 1000]
            if phi[i][j] >= 1000:
                phi[i][j] = 1000
            elif phi[i][j] <= -1000:
                phi[i][j] = -1000

            if plot_points:
                if phi[i][j] < 0:
                    ax.plot(i, j, 'r.')
    return phi


# for i in range(1):
#     phi = update(phi, 0.1)

# print(phi_x)


def pde(k):
    global phi
    ax.cla()
    ax.grid()
    phi = update(phi, 1, True)
    ax.contour(phi, 0, cmap=cm.plasma, linewidths=1)
    print(k)
# Writer = ani.writers['ffmpeg']
# writer = Writer(fps, metadata=dict(artist='Me'), bitrate=1800)

anim = ani.FuncAnimation(fig, pde, frames, interval=DT, repeat=False)
plt.show()

# anim.save('levelsetPDE.mp4', writer)
