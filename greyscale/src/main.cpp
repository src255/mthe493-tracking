#include <iostream>

#include "imageIO.h"
#include "levelset_PDE.h"

#define FF 259

int main(int argc, char **argv) {
    /**
     * create an array of marked-up frames
     * 0 = frame_markup
     * 1 = nextframe_markup
     */
    auto markup{new Frame};
    loadtxt("../images/frame0_markup.txt", markup);

    // initialize height function phi based on marked-up first frame
    double phi[N][N] = {};
    init(phi, markup);

    auto frame0{new Frame};
    loadtxt("../images/frame0.txt", frame0);

    double sum[2]{}, area[2]{};
    mean(sum, area, frame0, phi);
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
    loadtxt("../images/frame1.txt", frame1);

    std::cout << "load images\n";

    for (int k = 0; k < ITERATIONS; k++) {
        update(phi, a, b, frame1);
        // std::cout << "LOOP " << k << "\n\n";
    }

    // writetxt("../images/nextframe1_markup.txt", markup1);
    for (int i = 1; i < FF; i++) {
        // std::string path{"../images/frame" + std::to_string(i+1) + ".txt"};
        auto frame{new Frame};
        copy(frame1, frame);

        std::string path{"../images/frame" + std::to_string(i + 1) + ".txt"};
        loadtxt(path, frame1);

        init(phi);

        mean(sum, area, frame, phi);
        if (area[0] != 0.0) {
            a = sum[0] / area[0];
        }
        if (area[1] != 0.0) {
            b = sum[1] / area[1];
        }

        for (int k = 0; k < ITERATIONS; k++) {
            update(phi, a, b, frame1);
            // std::cout << "LOOP " << k << "\n\n";
        }
    }
    writetxt("../images/final_region.txt", phi);
    std::cout << "write to text file\n";
    return 0;
}