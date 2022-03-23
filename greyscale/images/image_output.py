import numpy as np
from PIL import Image, ImageOps

N = 100

img = np.loadtxt("nextframe_markup.txt")

nextframe = ImageOps.grayscale(Image.open("nextframe.png"))
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
nextframe_markup.save("nextframe_markup.png")
