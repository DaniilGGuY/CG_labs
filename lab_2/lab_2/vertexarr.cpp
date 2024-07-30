#include <stdlib.h>

#include "vertexarr.h"

vertex_arr_t vertex_arr_init(void)
{
    vertex_arr_t tmp;

    tmp.data = NULL;
    tmp.size = 0;

    return tmp;
}

proc_err_t read_vertex_count(vertex_arr_t &vertex, FILE *f)
{
    proc_err_t rc = OK;

    if (fscanf(f, "%d", &vertex.size) != 1)
        rc = ERR_FILE;

    if (vertex.size <= 0)
        rc = ERR_FILE_READ;

    return rc;
}

proc_err_t allocate_vertex_arr(vertex_arr_t &vertex)
{
    vertex_t *buf = (vertex_t *)malloc(sizeof(vertex_t) * vertex.size);
    if (!buf)
        return ERR_MEM;

    vertex.data = buf;

    return OK;
}

void free_vertex_arr(vertex_arr_t &vertex)
{
    if (vertex.data)
        free(vertex.data);
}

proc_err_t read_vertex_arr(vertex_arr_t &vertex, FILE *f)
{
    if (!f)
        return ERR_FILE;

    proc_err_t rc = read_vertex_count(vertex, f);
    if (!rc)
    {
        rc = allocate_vertex_arr(vertex);
        int i = 0;
        while (!rc && i < vertex.size)
        {
            rc = read_vertex(vertex.data[i], f);
            ++i;
        }

        if (rc)
            free_vertex_arr(vertex);
    }

    return rc;
}

proc_err_t write_vertex_arr(vertex_arr_t &vertex, FILE *f)
{
    if (!f)
        return ERR_FILE;

    fprintf(f, "%d\n", vertex.size);
    for (int i = 0; i < vertex.size; ++i)
        (void)write_vertex(vertex.data[i], f);

    return OK;
}

proc_err_t vertex_arr_copy(vertex_arr_t &vertex, vertex_arr_t tmp)
{
    if (tmp.size == 0)
        return ERR_MEM;

    vertex.size = tmp.size;
    proc_err_t rc = allocate_vertex_arr(vertex);
    if (!rc)
    {
        for (int i = 0; i < tmp.size; ++i)
        {
            vertex.data[i].x = tmp.data[i].x;
            vertex.data[i].y = tmp.data[i].y;
        }
    }

    if (rc)
        free_vertex_arr(vertex);

    return rc;
}

proc_err_t transfer_vertex_arr(vertex_arr_t &vertex, const transfer_t transfer)
{
    if (!vertex.data || vertex.size == 0)
        return ERR_TRANSFER;

    for (int i = 0; i < vertex.size; ++i)
        transfer_vertex(vertex.data[i], transfer);

    return OK;
}

proc_err_t scale_vertex_arr(vertex_arr_t &vertex, const vertex_t center, const scale_t scale)
{
    if (!vertex.data || vertex.size == 0)
        return ERR_SCALE;

    for (int i = 0; i < vertex.size; ++i)
        scale_vertex(vertex.data[i], center, scale);

    return OK;
}

proc_err_t rotate_vertex_arr(vertex_arr_t &vertex, const vertex_t center, const rotate_t rotate)
{
    if (!vertex.data || vertex.size == 0)
        return ERR_ROTATE;

    for (int i = 0; i < vertex.size; ++i)
        rotate_vertex(vertex.data[i], center, rotate);

    return OK;
}
