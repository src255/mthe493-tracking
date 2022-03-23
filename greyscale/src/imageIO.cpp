#include "imageIO.h"

#include <cmath>
#include <fstream>
#include <iostream>

void loadtxt(std::string filename, Frame frame) {
    std::ifstream in(filename);
    double element{};

    if (in.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (in >> element) {
                    frame[i][j] = static_cast<double>(element) / 255.0;
                }
            }
        }
    }
    in.close();
}

void writetxt(std::string filename, Frame frame) {
    std::ofstream out(filename);
    if (out.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                out << static_cast<int>(frame[i][j]);
                if (j == N - 1) {
                    out << '\n';
                } else {
                    out << ' ';
                }
            }
        }
    }
    out.close();
}

void show(Frame frame) {
    std::cout << '[';
    for (int i = 0; i < N; i++) {
        std::cout << '[';
        for (int j = 0; j < N - 1; j++) {
            std::cout << +frame[i][j] << ", ";
        }
        std::cout << +frame[i][N - 1] << "]\n";
    }
    std::cout << ']';
}
