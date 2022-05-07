#include "levelset_PDE.h"

#include <algorithm>
#include <cmath>
#include <iostream>

void init(double phi[N][N], Frame frame) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (frame[i][j] < 0.003) {
                phi[i][j] = INSIDE;
            } else {
                phi[i][j] = -INSIDE;
            }
        }
    }
}

void init(double phi[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (phi[i][j] >= 0) {
                phi[i][j] = INSIDE;
            } else {
                phi[i][j] = -INSIDE;
            }
        }
    }
}

void mean(double sum[2], double area[2], Frame frame, double phi[N][N]) {
    for (int i = 0; i < 2; i++) {
        sum[i] = 0;
        area[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (phi[i][j] >= 0) {
                sum[0] += frame[i][j];
                area[0]++;
            } else {
                sum[1] += frame[i][j];
                area[1]++;
            }
        }
    }
}

void update(double phi[N][N], double a, double b, Frame frame) {
    double x{}, y{}, I_x{}, I_y{}, nabla_I{}, xx{}, yy{}, xy{}, xL{}, xR{},
        yD{}, yU{}, x_squared{}, y_squared{}, K{};
    // std::cout << "initialize doubles\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // compute x partials
            if (i == 0) {
                x = (phi[i + 1][j] - phi[i][j]) / 2;
                I_x = (frame[i + 1][j] - frame[i][j]) / 2;
            } else if (i == N - 1) {
                x = (phi[i][j] - phi[i - 1][j]) / 2;
                I_x = (frame[i][j] - frame[i - 1][j]) / 2;
            } else {
                x = (phi[i + 1][j] - phi[i - 1][j]) / 2;
                I_x = (frame[i + 1][j] - frame[i - 1][j]) / 2;
            }

            // compute y partials
            if (j == 0) {
                y = (phi[i][j + 1] - phi[i][j]) / 2;
                I_y = (frame[i][j + 1] - frame[i][j]) / 2;
            } else if (i == N - 1) {
                y = (phi[i][j] - phi[i][j - 1]) / 2;
                I_y = (frame[i][j] - frame[i][j - 1]) / 2;
            } else {
                y = (phi[i][j + 1] - phi[i][j - 1]) / 2;
                I_y = (frame[i][j + 1] - frame[i][j - 1]) / 2;
            }
            // std::cout << "first order partials\n";

            // compute second partials
            if (i == 0) {
                xL = 0;
                xR = (phi[i + 2][j] - phi[i][j]) / 2;
            } else if (i == 1) {
                xL = (phi[i][j] - phi[i - 1][j]) / 2;
                xR = (phi[i + 2][j] - phi[i][j]) / 2;
            } else if (i == N - 2) {
                xL = (phi[i][j] - phi[i - 2][j]) / 2;
                xR = (phi[i + 1][j] - phi[i][j]) / 2;
            } else if (i == N - 1) {
                xL = (phi[i][j] - phi[i - 2][j]) / 2;
                xR = 0;
            } else {
                xL = (phi[i][j] - phi[i - 2][j]) / 2;
                xR = (phi[i + 2][j] - phi[i][j]) / 2;
            }
            xx = (xR - xL) / 2;
            if (j == 0) {
                yD = 0;
                yU = (phi[i][j + 2] - phi[i][j]) / 2;
            } else if (j == 1) {
                yD = (phi[i][j] - phi[i][j - 1]) / 2;
                yU = (phi[i][j + 2] - phi[i][j]) / 2;
            } else if (j == N - 2) {
                yD = (phi[i][j] - phi[i][j - 2]) / 2;
                yU = (phi[i][j + 1] - phi[i][j]) / 2;
            } else if (j == N - 1) {
                yD = (phi[i][j] - phi[i][j - 2]) / 2;
                yU = 0;
            } else {
                xL = (phi[i][j] - phi[i - 2][j]) / 2;
                yU = (phi[i + 2][j] - phi[i][j]) / 2;
            }
            yy = (yU - yD) / 2;

            if (i == 0 && j == 0) {  // bottom left
                xy = (phi[i + 1][j + 1] - phi[i][j + 1] - phi[i + 1][j] +
                      phi[i][j]) /
                     4;
            } else if (i == 0 && j > 0 && j < N - 1) {  // left wall
                xy = (phi[i + 1][j + 1] - phi[i][j + 1] - phi[i + 1][j - 1] +
                      phi[i][j - 1]) /
                     4;
            } else if (i == 0 && j == N - 1) {  // top left
                xy = (phi[i + 1][j] - phi[i][j] - phi[i + 1][j - 1] +
                      phi[i][j - 1]) /
                     4;
            } else if (i > 0 && i < N - 1 && j == N - 1) {  // top wall
                xy = (phi[i + 1][j] - phi[i - 1][j] - phi[i + 1][j - 1] +
                      phi[i - 1][j - 1]) /
                     4;
            } else if (i == N - 1 && j == N - 1) {  // top right
                xy = (phi[i][j] - phi[i - 1][j] - phi[i][j - 1] +
                      phi[i - 1][j - 1]) /
                     4;
            } else if (i == N - 1 && j > 0 && j < N - 1) {  // right
                xy = (phi[i][j + 1] - phi[i - 1][j + 1] - phi[i][j - 1] +
                      phi[i - 1][j - 1]) /
                     4;
            } else if (i == N - 1 && j == 0) {  // bottom right
                xy = (phi[i][j + 1] - phi[i - 1][j + 1] - phi[i][j] +
                      phi[i - 1][j]) /
                     4;
            } else if (0 < i && i < N - 1 && j == 0) {  // bottom
                xy = (phi[i + 1][j + 1] - phi[i - 1][j + 1] - phi[i + 1][j] +
                      phi[i - 1][j]) /
                     4;
            } else {
                xy = (phi[i + 1][j + 1] - phi[i - 1][j + 1] -
                      phi[i + 1][j - 1] + phi[i - 1][j - 1]) /
                     4;
            }
            // std::cout << "second order partials\n";

            x_squared = pow(x, 2);
            y_squared = pow(y, 2);
            // compute mean curvature
            K = (xx * y_squared - 2 * y * x * xy + yy * x_squared) /
                (pow(x_squared + y_squared, 3 / 2) + 1e-6);
            // std::cout << "kappa\n";

            /**
             * D1 = D^{-x}_{ij}
             * D2 = D^{+x}_{ij}
             * D3 = D^{-y}_{ij}
             * D4 = D^{+y}_{ij}
             */
            double D1{}, D2{}, D3{}, D4{};
            if (i != 0) {
                D1 = phi[i][j] - phi[i - 1][j];
            }
            if (i != N - 1) {
                D2 = phi[i + 1][j] - phi[i][j];
            }
            if (j != 0) {
                D3 = phi[i][j] - phi[i][j - 1];
            }
            if (j != N - 1) {
                D4 = phi[i][j + 1] - phi[i][j];
            }
            double nabla_positive =
                sqrt(pow(std::max(D1, 0.0), 2) + pow(std::min(D2, 0.0), 2) +
                     pow(std::max(D3, 0.0), 2) + pow(std::min(D4, 0.0), 2));
            double nabla_negative =
                sqrt(pow(std::max(D2, 0.0), 2) + pow(std::min(D1, 0.0), 2) +
                     pow(std::max(D4, 0.0), 2) + pow(std::min(D3, 0.0), 2));

            // compute gradient I
            nabla_I = sqrt(pow(I_x, 2) + pow(I_y, 2));

            // specify the functional F_0
            double F_0 =
                XI * 2 * (b - a) * (frame[i][j] - (a + b) / 2) - ETA * nabla_I;
            // std::cout << "average intensity functional\n";

            // update phi
            phi[i][j] += -(std::max(F_0, 0.0) * nabla_positive +
                           std::min(F_0, 0.0) * nabla_negative) +
                         DT * EPSILON * K * sqrt(x_squared + y_squared);
            // std::cout << "update phi\n";

            // clip phi if magnitude is large
            if (phi[i][j] > 100) {
                phi[i][j] = 100;
            } else if (phi[i][j] < -100) {
                phi[i][j] = -100;
            }
            // std::cout << "LOOP: (" << i << ", " << j << ")\n";
        }
        // std::cout << "LOOP: " << i << '\n';
    }
}

// void draw_region(Frame frame, double phi[N][N]) {
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             if (phi[i][j] >= 0) {
//                 frame[i][j] = 0.0;
//             } else {
//                 frame[i][j] = 255.0;
//             }
//         }
//     }
// }
