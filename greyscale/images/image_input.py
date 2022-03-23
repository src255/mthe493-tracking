import numpy as np
from PIL import Image, ImageOps

N = 100
# def savetxt(name, red, green, blue):
#     np.savetxt(name + '_' + "red.txt", red)
#     np.savetxt(name + '_' + "green.txt", green)
#     np.savetxt(name + '_' + "blue.txt", blue)

# def get_rgb_data(img):
#     return img.getdata(0), img.getdata(1), img.getdata(2)

frame_markup = ImageOps.grayscale(Image.open("frame_markup.png"))
data = frame_markup.getdata()
np.savetxt("frame_markup.txt", data)

frame = ImageOps.grayscale(Image.open("frame.png"))
data = frame.getdata()
np.savetxt("frame.txt", data)

nextframe = ImageOps.grayscale(Image.open("nextframe.png"))
data = nextframe.getdata()
np.savetxt("nextframe.txt", data)
