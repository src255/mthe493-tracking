import numpy as np
from PIL import Image, ImageOps

N = 100
FF = 259
# def savetxt(name, red, green, blue):
#     np.savetxt(name + '_' + "red.txt", red)
#     np.savetxt(name + '_' + "green.txt", green)
#     np.savetxt(name + '_' + "blue.txt", blue)

# def get_rgb_data(img):
#     return img.getdata(0), img.getdata(1), img.getdata(2)

frame_markup = ImageOps.grayscale(Image.open("frame0mask.png"))
data = frame_markup.getdata()
np.savetxt("frame0_markup.txt", data)

for i in range(FF):
    frame = ImageOps.grayscale(Image.open(f"frame{i}_noblack.png"))
    data = frame.getdata()
    np.savetxt(f"frame{i}.txt", data)

# frame = ImageOps.grayscale(Image.open("frame.png"))
# data = frame.getdata()
# np.savetxt("frame.txt", data)

# nextframe = ImageOps.grayscale(Image.open("nextframe.png"))
# data = nextframe.getdata()
# np.savetxt("nextframe.txt", data)

