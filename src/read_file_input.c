#include "hashcode.h"

t_info read_file_input(FILE *file_input)
{
    t_info info_file;
    fscanf(file_input, "%d%d%d%d%d", &info_file.duration_sim, &info_file.nb_intersections, &info_file.nb_street, &info_file.nb_cars, &info_file.bonus_point);

    return (info_file);
}

t_street *read_file_input_street(FILE *file_input, t_info info, t_hashtable **table)
{
    
    t_street *info_street;
    info_street = malloc(sizeof(t_street) * info.nb_street);

    for (int i = 0; i < info.nb_street; i++)
    {
        fscanf(file_input, "%d %d %s %d", &(info_street[i].street_begin), &(info_street[i].street_end), info_street[i].street_name, &(info_street[i].street_length));  
        info_street[i].id = i;
        info_street[i].weight = 0;
        info_street[i].weight_start = 0;
        t_entry *entry;
        if ((entry = insert_hashtable(table, create_entry(info_street[i].street_name))))
	    {
            entry->position = i;
	    }   
    }

    return info_street;
}


void weight_updater(t_info info, t_street * info_street, t_car * info_car)
{
    for (int i = 0; i < info.nb_cars; i++)
    {
        for (int j = 0; j <  info_car[i].nb_paths; j++)
        {
            int index = info_car[i].road_list[j];

            if (j == 0)
            {
               info_street[index].weight_start++;
               info_street[index].weight++;
            }
            
            else
            {
               info_street[index].weight++;
            }
        }
    }
}



t_car *read_file_input_car(FILE *file_input, t_info info, t_hashtable *table)
{

    t_car *info_car;
    info_car = malloc(sizeof(t_car) * info.nb_cars);

    for (int i = 0; i < info.nb_cars; i++)
    { 
        fscanf(file_input, "%d", &(info_car[i].nb_paths));
        info_car[i].road_list = malloc(sizeof(int) * info_car[i].nb_paths);
        for (int j = 0; j < info_car[i].nb_paths; j++)
        {
            char name[64];
            fscanf(file_input, "%s", name);
            t_entry *entry = hashtable_get(table, name);
            info_car[i].road_list[j] = entry->position;
        }
    } 

    return info_car;
}

void            add_road_to_intersection(t_intersection *info, int road_id)
{
    if (info->nb_linked_roads >= info->size)
    {
        info->size *= 2;
        info->linked_roads = realloc(info->linked_roads, sizeof(int) * info->size);
    }
    info->linked_roads[info->nb_linked_roads] = road_id;
    info->nb_linked_roads++;
}

t_intersection  *parse_intersection(t_info info, t_street *info_street)
{
    t_intersection *intersection_info;

    intersection_info = malloc(sizeof(t_intersection) * info.nb_intersections);
    for (int i = 0; i < info.nb_intersections ; i++)
    {
        intersection_info[i].size = 64;
        intersection_info[i].nb_linked_roads = 0;
        intersection_info[i].linked_roads = malloc(sizeof(int) * 64);
    }
    for (int i = 0; i < info.nb_street; i++)
    {
        int street_end = info_street[i].street_end;
        add_road_to_intersection(intersection_info + street_end, i);
    }
    

    return intersection_info;
}

