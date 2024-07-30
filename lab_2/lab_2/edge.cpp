#include "edge.h"

proc_err_t read_edge(edge_t &edge, FILE *f)
{
    if (!f || feof(f))
        return ERR_FILE;

    proc_err_t rc = OK;
    if (fscanf(f, "%d %d", &edge.vertex1, &edge.vertex2) != 2)
        rc = ERR_FILE_READ;

    return rc;
}

proc_err_t write_edge(edge_t &edge, FILE *f)
{
    if (!f)
        return ERR_FILE;

    fprintf(f, "%d %d\n", edge.vertex1, edge.vertex2);

    return OK;
}
