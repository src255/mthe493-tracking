#ifndef LEVELSET_H
#define LEVELSET_H

#include "imageIO.h"
#include <cmath>
#include <algorithm>

#define ITERATIONS 10
#define INSIDE 1.0
#define EPSILON 1.0
#define DT 0.1

/**
 * @brief Initialize the height function according to a
 * marked-up image. The image specifies a region with pure
 * red pixels, that is rgb(255, 0, 0).
 *
 * @param phi: height function
 * @param img: marked-up Image
 */
void init(double phi[N][N], Image img);

void update(double phi[N][N], double a, double b, Image imgs[2]);

void draw_region(Image img, double phi[N][N]);

#endif