import numpy as np
from PIL import Image, ImageOps

N = 100

img = np.loadtxt("final_region.txt")

nextframe = ImageOps.grayscale(Image.open("frame0.png"))
nextframe_markup = nextframe.copy()

# data = nextframe.getdata()
new_data = []

for i in range(N):
    for j in range(N):
        if img[i][j] == 0:
            new_data.append(0)
        else:
            new_data.append(255)

nextframe_markup.putdata(new_data)
nextframe_markup.save("frame259_final_region_browngreen_50iterations.png")
