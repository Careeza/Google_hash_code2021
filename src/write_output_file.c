#include "hashcode.h"

void write_output_file(const char *path_output, t_info info, t_intersection *intersection_info, t_street *street_info)
{
    FILE *file_output = fopen(path_output, "w");

    fprintf(file_output, "%d\n", info.nb_intersections);

    for (int i = 0; i < info.nb_intersections; i++)
    {
        fprintf(file_output, "%d\n", i);
        fprintf(file_output, "%d\n", intersection_info[i].nb_linked_roads);
        for (int j = 0; j < intersection_info[i].nb_linked_roads; j++)
        {
            int index = intersection_info[i].light_timing[j].id_road;
            fprintf(file_output, "%s %d\n", street_info[index].street_name,  intersection_info[i].light_timing[j].wait);
        }   
    }
    fclose(file_output);
}