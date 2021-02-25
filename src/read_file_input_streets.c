#include "hashcode.h"

typedef struct  s_info_streets
{
    int     inter_start;
    int     inter_end;
    char    street_name[64];
    int     street_time;

}   t_info_streets;

t_info_streets read_file_input(const char *path, )
{
    FILE *file_input = fopen(path, "r");
    t_info_streets info_street
    fscanf(file_input, "%d%d%d%d%d"


    fclose(file_input);

    return info_street;
}