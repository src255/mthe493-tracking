#ifndef LEVELSET_PDE_H
#define LEVELSET_PDE_H

#include "imageIO.h"

#define ITERATIONS 50
#define INSIDE 10.0
#define XI 3.0          // mean intensity coefficient
#define ETA 0.8         // nabla_I coefficient
#define EPSILON 2.0     // arclength coefficient
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

void init(double phi[N][N]);

void mean(double sum[2], double are[2], Frame frame, double phi[N][N]);

void update(double phi[N][N], double a, double b, Frame frame);

// void draw_region(Frame frame, double phi[N][N]);

#endif