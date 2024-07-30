#include "figure.h"
#include <QDebug>

figure_t figure_init(void)
{
    figure_t tmp;

    tmp.edges = edge_arr_init();
    tmp.vertexes = vertex_arr_init();

    return tmp;
}

proc_err_t deep_copy_figure(figure_t &figure, figure_t &tmp)
{
    proc_err_t rc = vertex_arr_copy(figure.vertexes, tmp.vertexes);
    if (!rc)
        rc = edges_arr_copy(figure.edges, tmp.edges);

    return rc;
}

void copy_figure(figure_t &figure, figure_t &tmp)
{
    figure.edges.size = tmp.edges.size;
    figure.edges.data = tmp.edges.data;
    figure.vertexes.size = tmp.vertexes.size;
    figure.vertexes.data = tmp.vertexes.data;
}

proc_err_t read_figure(figure_t &figure, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return ERR_FILE;

    figure_t tmp = figure_init();

    proc_err_t rc = read_vertex_arr(tmp.vertexes, f);
    if (!rc)
    {
        rc = read_edge_arr(tmp.edges, f);
        if (!rc)
            rc = check_edge_arr(tmp.edges, tmp.vertexes.size);

        if (rc)
            free_figure(tmp);
    }

    if (!rc)
    {
        free_figure(figure);
        figure = figure_init();
        copy_figure(figure, tmp);
    }

    fclose(f);

    return rc;
}

proc_err_t write_figure(figure_t &figure, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return ERR_FILE;

    proc_err_t rc = write_vertex_arr(figure.vertexes, f);
    if (!rc)
        rc = write_edge_arr(figure.edges, f);

    fclose(f);

    return rc;
}

proc_err_t figure_transfer(figure_t &figure, const transfer_t transfer)
{
    return transfer_vertex_arr(figure.vertexes, transfer);
}

proc_err_t figure_scale(figure_t &figure, vertex_t center, const scale_t scale)
{
    return scale_vertex_arr(figure.vertexes, center, scale);
}

proc_err_t figure_rotate(figure_t &figure, vertex_t center, const rotate_t rotate)
{
    return rotate_vertex_arr(figure.vertexes, center, rotate);
}

void free_figure(figure_t &figure)
{
    free_edge_arr(figure.edges);
    free_vertex_arr(figure.vertexes);
}
