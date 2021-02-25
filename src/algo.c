#include "hashcode.h"


int gcd(int a, int b)
{
    int temp;
    if (a || b == 0) {
        if (a != 0)
            return (a);
        if (b != 0)
            return (b);
        return (1);
    }
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

int     gcd_list(t_intersection intersection_info, t_street *street_info) {
    int index1 = intersection_info.linked_roads[0];
    if (intersection_info.nb_linked_roads == 1)
        return (street_info[index1].weight == 0 ? 1 : street_info[index1].weight);
    int gcd_value = street_info[index1].weight;
    for (int j = 1; j < intersection_info.nb_linked_roads; j++) {
        int index2 = intersection_info.linked_roads[j];
        gcd_value = gcd(gcd_value, street_info[index2].weight);
    }
    return (gcd_value);
}

int     comp(const void *elem1, const void *elem2) {
    int     *street1 = (int *)elem1;
    int     *street2 = (int *)elem2;

    if (street_info[*street1].weight_start > street_info[*street2].weight_start)
        return (1);
    if (street_info[*street1].weight_start < street_info[*street2].weight_start)
        return (-1);
    return (0);
}

void    algo(t_info info, t_intersection *intersection_info, t_street *street_info) {
    for (int i = 0; i < info.nb_intersections; i++) {
        int tot = 1;
        qsort(intersection_info[i].linked_roads, intersection_info[i].nb_linked_roads, sizeof(int), comp);
        intersection_info[i].light_timing = malloc(sizeof(t_light_timing) * intersection_info[i].nb_linked_roads);
        for (int j = 0; j < intersection_info[i].nb_linked_roads; j++) {
            int index = intersection_info[i].linked_roads[j];
            intersection_info[i].light_timing[j].id_road = street_info[index].id;
            tot += street_info[index].weight;
            //intersection_info[i].light_timing[j].wait = street_info[index].weight / gcd_value;
        }

        for (int j = 0; j < intersection_info[i].nb_linked_roads; j++) {
            int index = intersection_info[i].linked_roads[j];
            intersection_info[i].light_timing[j].wait = (street_info[index].weight * info.duration_sim) / tot;
            if (intersection_info[i].light_timing[j].wait == 0)
                intersection_info[i].light_timing[j].wait = 1;
            if (intersection_info[i].light_timing[j].wait > info.duration_sim)
                intersection_info[i].light_timing[j].wait = info.duration_sim - 1;
        }
    }
}