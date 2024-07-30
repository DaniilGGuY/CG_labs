#include <stdlib.h>

#include "edgearr.h"

edge_arr_t edge_arr_init(void)
{
    edge_arr_t tmp;

    tmp.data = NULL;
    tmp.size = 0;

    return tmp;
}

proc_err_t read_edge_count(edge_arr_t &edge, FILE *f)
{
    proc_err_t rc = OK;

    if (fscanf(f, "%d", &edge.size) != 1)
        rc = ERR_FILE;

    if (edge.size <= 0)
        rc = ERR_FILE_READ;

    return rc;
}

proc_err_t allocate_edge_arr(edge_arr_t &edge)
{
    edge_t *buf = (edge_t *)malloc(sizeof(edge_t) * edge.size);
    if (!buf)
        return ERR_MEM;

    edge.data = buf;

    return OK;
}

void free_edge_arr(edge_arr_t &edge)
{
    if (edge.data)
        free(edge.data);
}

proc_err_t read_edge_arr(edge_arr_t &edge, FILE *f)
{
    if (!f)
        return ERR_FILE;

    proc_err_t rc = read_edge_count(edge, f);
    if (!rc)
    {
        rc = allocate_edge_arr(edge);
        int i = 0;
        while (!rc && i < edge.size)
        {
            rc = read_edge(edge.data[i], f);
            ++i;
        }

        if (rc)
            free_edge_arr(edge);
    }

    return rc;
}

proc_err_t write_edge_arr(edge_arr_t &edge, FILE *f)
{
    if (!f)
        return ERR_FILE;

    fprintf(f, "%d\n", edge.size);
    for (int i = 0; i < edge.size; ++i)
        (void)write_edge(edge.data[i], f);

    return OK;
}

proc_err_t edges_arr_copy(edge_arr_t &edge, edge_arr_t tmp)
{
    if (tmp.size == 0)
        return ERR_MEM;

    edge.size = tmp.size;
    proc_err_t rc = allocate_edge_arr(edge);
    if (!rc)
    {
        for (int i = 0; i < tmp.size; ++i)
        {
            edge.data[i].vertex1 = tmp.data[i].vertex1;
            edge.data[i].vertex2 = tmp.data[i].vertex2;
        }
    }

    if (rc)
        free_edge_arr(edge);

    return rc;
}

proc_err_t check_edge_arr(edge_arr_t &edge, int max_num)
{
    for (int i = 0; i < edge.size; ++i)
        if (edge.data[i].vertex1 > max_num || edge.data[i].vertex2 > max_num)
            return ERR_FILE_READ;

    return OK;
}
