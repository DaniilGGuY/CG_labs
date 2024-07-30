#include <math.h>

#include "vertex.h"

double to_radians(double degrees)
{
    return degrees * PI / 180;
}

proc_err_t read_vertex(vertex_t &vertex, FILE *f)
{
    if (!f || feof(f))
        return ERR_FILE;

    proc_err_t rc = OK;
    if (fscanf(f, "%lf %lf", &vertex.x, &vertex.y) != 2)
        rc = ERR_FILE_READ;

    return rc;
}

proc_err_t write_vertex(vertex_t &vertex, FILE *f)
{
    if (!f)
        return ERR_FILE;

    fprintf(f, "%lf %lf\n", vertex.x, vertex.y);

    return OK;
}

void transfer_vertex(vertex_t &vertex, const transfer_t transfer)
{
    vertex.x += transfer.dx;
    vertex.y += transfer.dy;
}

void scale_vertex(vertex_t &vertex, const vertex_t center, const scale_t scale)
{
    vertex.x = center.x + scale.kx * (vertex.x - center.x);
    vertex.y = center.y + scale.ky * (vertex.y - center.y);
}

static void rotate_around_z(vertex_t &vertex, const double angle)
{
    double rad_angle = to_radians(angle);
    double cos_angle = cos(rad_angle);
    double sin_angle = sin(rad_angle);

    double tmp = vertex.x;
    vertex.x = vertex.x * cos_angle - vertex.y * sin_angle;
    vertex.y = vertex.y * cos_angle + tmp * sin_angle;
}

void rotate_vertex(vertex_t &vertex, const vertex_t center, const rotate_t rotate)
{
    transfer_t forward = { -center.x, -center.y };
    transfer_t back = { center.x, center.y };

    transfer_vertex(vertex, forward);

    rotate_around_z(vertex, rotate.z_rot);

    transfer_vertex(vertex, back);
}
