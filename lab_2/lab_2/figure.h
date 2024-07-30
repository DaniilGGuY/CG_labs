#ifndef FIGURE_H
#define FIGURE_H

#include "vertexarr.h"
#include "edgearr.h"
#include "processerror.h"

struct figure_t
{
    vertex_arr_t vertexes;
    edge_arr_t edges;
};

figure_t figure_init(void);

proc_err_t deep_copy_figure(figure_t &figure, figure_t &tmp);

void copy_figure(figure_t &figure, figure_t &tmp);

proc_err_t read_figure(figure_t &figure, const char *filename);

proc_err_t write_figure(figure_t &figure, const char *filename);

proc_err_t figure_transfer(figure_t &figure, const transfer_t transfer);

proc_err_t figure_scale(figure_t &figure, vertex_t center, const scale_t scale);

proc_err_t figure_rotate(figure_t &figure, vertex_t center, const rotate_t rotate);

void free_figure(figure_t &figure);

#endif // FIGURE_H
