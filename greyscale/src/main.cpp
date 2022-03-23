#include <iostream>

#include "imageIO.h"
#include "levelset_PDE.h"

int main(int argc, char **argv) {
    /**
     * create an array of marked-up frames
     * 0 = frame_markup
     * 1 = nextframe_markup
     */
    auto markup{new Frame};
    loadtxt("../images/frame_markup.txt", markup);

    // initialize height function phi based on marked-up first frame
    double phi[N][N] = {};
    init(phi, markup);

    auto frame0{new Frame};
    loadtxt("../images/frame.txt", frame0);

    double sum[2]{}, area[2]{};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (markup[i][j] == 0.0) {
                sum[0] += frame0[i][j];
                area[0] += 1.0;
            } else {
                sum[1] += frame0[i][j];
                area[1] += 1.0;
            }
        }
    }
    delete[] markup;
    delete[] frame0;

    /**
     * a is the average pixel intensity of R_0 according to image[0]
     * b is the average pixel inesntiy of R_0^c according to image[0]
     */
    double a{}, b{};
    if (area[0] != 0.0) {
        a = sum[0] / area[0];
    }
    if (area[1] != 0.0) {
        b = sum[1] / area[1];
    }

    auto frame1{new Frame};
    loadtxt("../images/nextframe.txt", frame1);

    std::cout << "load images\n";

    for (int k = 0; k < ITERATIONS; k++) {
        // try
        // {
        //     if (update(phi, a, b, image1) != 1)
        //     {
        //         throw "error occurred in algorithm";
        //     }
        // }
        // catch(const char* exception)
        // {
        //     std::cerr << "Error: " << exception << '\n';
        // }
        update(phi, a, b, frame1);
        std::cout << "LOOP " << k << "\n\n";
    }

    delete[] frame1;

    auto markup1{new Frame};
    draw_region(markup1, phi);
    writetxt("../images/nextframe_markup.txt", markup1);
    std::cout << "draw region\n";
    delete[] markup1;

    return 0;
}