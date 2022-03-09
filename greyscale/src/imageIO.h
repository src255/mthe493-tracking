#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <string>

#define N 200

using uchar = unsigned char;

using Image = uchar[N][N];

/**
 * @brief Load a .txt file representation of an N by N array into an unsigned char
 * array where the text file separates each column with a space and each row
 * with a newline.
 *
 * @param filename: string of text file in current directory
 * @param array: N by N integer array
 */
void loadtxt(std::string filename, Image img);

void writetxt(std::string filename, Image img);


/**
 * @brief Convert greyscale image to double array with values in
 * [0, 1].
 *
 * @param img: Image (unsigned char[N][N])
 * @param grey: output double array
 */
void normalize(Image imgs[2], double normals[2][N][N]);

/**
 * @brief Print an N by N integer array to the terminal.
 *
 * @param array
 */
void show(Image img);
/**
 * @brief Print an N by N double array to the terminal.
 *
 * @param array
 */
void show(double array[N][N]);

#endif
