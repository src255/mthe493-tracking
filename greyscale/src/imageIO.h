#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <string>

#define N 100

using Frame = double[N][N];

/**
 * @brief Load a .txt file representation of an N by N array into a double
 * array where the text file separates each column with a space and each row
 * with a newline.
 *
 * @param filename: string of text file in current directory
 * @param frame: N by N double array
 */
void loadtxt(std::string filename, Frame frame);

void writetxt(std::string filename, Frame frame);

/**
 * @brief Print an N by N double array to the terminal.
 *
 * @param frame
 */
void show(Frame frame);

#endif
