#ifndef LEVELSET_H
#define LEVELSET_H

#include "imageIO.h"

#define ITERATIONS 5
#define INSIDE 0.5
#define EPSILON 1.0
#define DT 0.01

/**
 * @brief Initialize the height function according to a
 * marked-up image. The image specifies a region with pure
 * black pixels, that is intensity = 0.
 *
 * @param phi: height function
 * @param frame: marked-up Image
 */
void init(double phi[N][N], Frame frame);

void update(double phi[N][N], double a, double b, Frame frame);

void draw_region(Frame frame, double phi[N][N]);

#endif