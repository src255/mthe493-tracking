#include "imageIO.h"

#include <fstream>
#include <iostream>

void loadtxt(std::string filename, Image img)
{
    std::ifstream in(filename);
    uchar element{};

    if (in.is_open())
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (in >> element)
                {
                    img[i][j] = element;
                }
            }
        }
    }
    in.close();
}

void writetxt(std::string filename, Image img)
{
    std::ofstream out(filename);
    if (out.is_open())
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                out << +img[i][j];
                if (j == N - 1)
                {
                    out << '\n';
                }
                else
                {
                    out << ' ';
                }
            }
        }
    }
    out.close();
}

void normalize(Image imgs[2], double normals[2][N][N])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                normals[i][j][k] = imgs[i][j][k]/255.0;
            }
        }
    }
}

void show(Image img)
{
    std::cout << '[';
    for (int i = 0; i < N; i++)
    {
        std::cout << '[';
        for (int j = 0; j < N - 1; j++)
        {
            std::cout << +img[i][j] << ", ";
        }
        std::cout << +img[i][N - 1] << "]\n";
    }
    std::cout << ']';
}

void show(double array[N][N])
{
    std::cout << '[';
    for (int i = 0; i < N; i++)
    {
        std::cout << '[';
        for (int j = 0; j < N - 1; j++)
        {
            std::cout << array[i][j] << ", ";
        }
        std::cout << array[i][N - 1] << "]\n";
    }
    std::cout << ']';
}
