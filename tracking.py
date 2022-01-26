import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as ani
# plt.rcParams['animation.ffmpeg_path'] = 'C:/ffmpeg/ffmpeg.exe'

# define constants
R = 1
PI = np.pi
N = 200
T = np.linspace(0, 2*PI, N)
speed = 1.0

fps = 30
dpi = 100
seconds = R/speed
total_frames = int(fps*seconds)
DT = 1000.0/fps


# create unit circle
circle = np.empty((2, N))
for j, t in enumerate(T):
    circle[0][j] = R*np.cos(t)
    circle[1][j] = R*np.sin(t)

fig = plt.figure()
# fig.canvas.manager.full_screen_toggle()
ax = plt.axes(xlim=(-3/2*R, 3/2*R), ylim=(-3/2*R, 3/2*R))
ax.set_aspect('equal')
ax.grid()
gamma, = ax.plot(circle[0], circle[1], 'k', linewidth=1)

def animate(i):
    for j, t in enumerate(T):
        if circle[0][j] != 0:
            circle[0][j] -= speed/fps*np.cos(t)
        if circle[1][j] != 0:
            circle[1][j] -= speed/fps*np.sin(t)
    gamma.set_data(circle[0], circle[1])
    return gamma,


anim = ani.FuncAnimation(fig, animate, frames=total_frames, interval=DT, blit=True, repeat=False)
plt.show()
Writer = ani.writers['ffmpeg']
writer = Writer(fps, metadata=dict(artist='Me'), bitrate=1800)
# anim.save('circle.mp4', writer)
# writer = ani.FFMpegWriter(fps=60, codec='vp9')
