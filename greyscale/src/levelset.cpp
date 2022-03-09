#include "levelset.h"

void init(double phi[N][N], Image img)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            if (img[i][j] == 0)
            {
                phi[i][j] = INSIDE;
            }
            else
            {
                phi[i][j] = -INSIDE;
            }
        }
    }
}

void update(double phi[N][N], double a, double b, Image imgs[2])
{
    double phi_x[N][N] = {};
    double phi_y[N][N] = {};
    double xx{}, yy{}, xy{}, K{}, x2{}, y2{};
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // compute x partials
            if (i == 0)
            {
                phi_x[i][j] = (phi[i + 1][j] - phi[i][j]) / 2;
            }
            else if (i == N - 1)
            {
                phi_x[i][j] = (phi[i][j] - phi[i - 1][j]) / 2;
            }
            else
            {
                phi_x[i][j] = (phi[i + 1][j] - phi[i - 1][j]) / 2;
            }

            // compute y partials
            if (j == 0)
            {
                phi_y[i][j] = (phi[i][j + 1] - phi[i][j]) / 2;
            }
            else if (i == N - 1)
            {
                phi_y[i][j] = (phi[i][j] - phi[i][j - 1]) / 2;
            }
            else
            {
                phi_y[i][j] = (phi[i][j + 1] - phi[i][j - 1]) / 2;
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == 0)
            {
                xx = (phi_x[i + 1][j] - phi_x[i][j]) / 2;
            }
            else if (i == N - 1)
            {
                xx = (phi_x[i][j] - phi_x[i - 1][j]) / 2;
            }
            else
            {
                xx = (phi_x[i + 1][j] - phi_x[i - 1][j]) / 2;
            }
            if (j == 0)
            {
                yy = (phi_y[i][j + 1] - phi_y[i][j]) / 2;
                xy = (phi_x[i][j + 1] - phi_x[i][j]) / 2;
            }
            else if (j == N - 1)
            {
                yy = (phi_y[i][j] - phi_y[i][j - 1]) / 2;
                xy = (phi_x[i][j] - phi_x[i][j - 1]) / 2;
            }
            else
            {
                yy = (phi_y[i][j + 1] - phi_y[i][j - 1]) / 2;
                xy = (phi_x[i][j + 1] - phi_x[i][j - 1]) / 2;
            }
            x2 = pow(phi_x[i][j], 2); // x^2
            y2 = pow(phi_y[i][j], 2); // y^2
            // compute mean curvature
            K = (xx * y2 - 2 * phi_y[i][j] * phi_x[i][j] * xy + yy * x2) /
                (pow(x2 + y2, 3 / 2) + 1e-6);

            /**
             * D1 = D^{-x}_{ij}
             * D2 = D^{+x}_{ij}
             * D3 = D^{-y}_{ij}
             * D4 = D^{+y}_{ij}
             */
            double D1{}, D2{}, D3{}, D4{};
            if (i != 0)
            {
                D1 = phi[i][j] - phi[i - 1][j];
            }
            if (i != N - 1)
            {
                D2 = phi[i + 1][j] - phi[i][j];
            }
            if (j != 0)
            {
                D3 = phi[i][j] - phi[i][j - 1];
            }
            if (j != N - 1)
            {
                D4 = phi[i][j + 1] - phi[i][j];
            }
            double nabla_positive = sqrt(pow(std::max(D1, 0.0), 2) + pow(std::min(D2, 0.0), 2) + pow(std::max(D3, 0.0), 2) + pow(std::min(D4, 0.0), 2));
            double nabla_negative = sqrt(pow(std::max(D2, 0.0), 2) + pow(std::min(D1, 0.0), 2) + pow(std::max(D4, 0.0), 2) + pow(std::min(D3, 0.0), 2));

            // specify the functional F_0
            double F_0 = 2 * (b - a) * (imgs[1][i][j] - (a + b) / 2);

            // update phi
            phi[i][j] += -(std::max(F_0, 0.0) * nabla_positive + std::min(F_0, 0.0) * nabla_negative) + DT * EPSILON * K * sqrt(x2 + y2);

            // clip phi if magnitude is large
            if (phi[i][j] > 1000)
            {
                phi[i][j] = 1000;
            }
            else if (phi[i][j] < -1000)
            {
                phi[i][j] = -1000;
            }
        }
    }
}

void draw_region(Image img, double phi[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (phi[i][j] >= 0)
            {
                img[i][j] = 0;
            }
            else
            {
                img[i][j] = 255;
            }
        }
    }
}
