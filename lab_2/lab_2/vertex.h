#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>

#include "processerror.h"

#define PI       3.141592653589

struct vertex_t
{
    double x;
    double y;
};

struct transfer_t
{
    double dx;
    double dy;
};

struct scale_t
{
    double kx;
    double ky;
};

struct rotate_t
{
    double z_rot;
};

double to_radians(double degrees);

proc_err_t read_vertex(vertex_t &vertex, FILE *f);

proc_err_t write_vertex(vertex_t &vertex, FILE *f);

void transfer_vertex(vertex_t &vertex, const transfer_t transfer);

void scale_vertex(vertex_t &vertex, const vertex_t center, const scale_t scale);

void rotate_vertex(vertex_t &vertex, const vertex_t center, const rotate_t rotate);

#endif // VERTEX_H
