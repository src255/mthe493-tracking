#include "imageIO.h"
#include "levelset.h"

int main(int argc, char **argv)
{
    /**
     * create an array of frames
     * 0 = frame
     * 1 = nextframe
     */
    Image images[2] = {};

    /**
     * create an array of marked-up frames
     * 0 = frame_markup
     * 1 = nextframe_markup
     */
    Image markups[2] = {};

    loadtxt("../test_images/frame.txt", images[0]);
    loadtxt("../test_images/nextframe.txt", images[1]);
    loadtxt("../test_images/frame_markup.txt", markups[0]);

    // initialize height function phi based on marked-up first frame
    double phi[N][N] = {};
    init(phi, markups[0]);

    /**
     * convert 0 to 255 unsigned char greyscale values to 0 to 1 double values
     * NOTE: This is to avoid overflow issues when summing these values over the
     * desired region
    */
    double normals[2][N][N] = {};
    normalize(images, normals);

    double sum[2]{}, area[2]{};
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (markups[0][i][j] == 0)
            {
                sum[0] += images[0][i][j];
                area[0] += 1.0;
            }
            else
            {
                sum[1] += images[0][i][j];
                area[1] += 1.0;
            }
        }
    }

    /**
     * a is the average pixel intensity of R_0 according to image[0]
     * b is the average pixel inesntiy of R_0^c according to image[0]
     */
    double a{}, b{};
    if (area[0] != 0.0)
    {
        a = sum[0]/area[0];
    }
    if (area[1] != 0.0)
    {
        b = sum[1]/area[1];
    }

    for (int i = 0; i < ITERATIONS; i++)
    {
        update(phi, a, b, images);
    }

    draw_region(markups[1], phi);

    writetxt("nextframe_markup.txt", markups[1]);

    return 0;
}