#ifndef EDGEARR_H
#define EDGEARR_H

#include "edge.h"

struct edge_arr_t
{
    edge_t *data;
    int size;
};

edge_arr_t edge_arr_init(void);

proc_err_t read_edge_count(int &count, FILE *f);

proc_err_t allocate_edge_arr(edge_arr_t &edge);

void free_edge_arr(edge_arr_t &edge);

proc_err_t read_edge_arr(edge_arr_t &edge, FILE *f);

proc_err_t write_edge_arr(edge_arr_t &edge, FILE *f);

proc_err_t edges_arr_copy(edge_arr_t &edge, edge_arr_t tmp);

proc_err_t check_edge_arr(edge_arr_t &edge, int max_num);

#endif // EDGEARR_H
