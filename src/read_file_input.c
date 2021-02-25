#include "hashcode.h"

t_info read_file_input(const char *path)
{
    FILE *file_input = fopen(path, "r");

    t_info info_file;
    fscanf(file_input, "%d%d%d%d%d", &info_file.duration_sim, &info_file.nb_intersections, &info_file.nb_street, &info_file.nb_cars, &info_file.bonus_point);

    return info_file;
}