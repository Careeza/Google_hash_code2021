#ifndef HASHCODE_H

# define HASHCODE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

/******PARSING*******/

typedef struct      s_info
{
    int             duration_sim;
    int             nb_intersections;
    int             nb_street;
    int             nb_cars;
    int             bonus_point;
}                   t_info;


typedef struct      s_street
{   
    int             id;
    int             street_begin;
    int             street_end;
    char            street_name[64];
    int             street_length;

    int             weight_start;
    int             weight;
}                   t_street;

//t_street  *all_street
//int index;
//t_entry entry = get(hash, nom_de_rue)
//all_street[entry.pos].weight++


typedef struct      s_car
{
    int             nb_paths;
    int             *road_list;
}                   t_car;


typedef struct      s_light_timing 
{
    int             id_road;
    int             wait;
}                   t_light_timing;

typedef struct      s_intersection
{
    int             nb_linked_roads;
    int             size;
    int             *linked_roads;
    int             intersection_id;
    t_light_timing  *light_timing;
}                   t_intersection;

extern t_street     *street_info;

/******HASHTABLE*******/

typedef struct	    s_entry
{
	char		    *key;
	uint64_t	    hash;
	uint64_t	    position;
}				    t_entry;

typedef struct	    s_hashtable
{
	size_t		    size;
	t_entry		    bucket[];
}				    t_hashtable;

t_hashtable		    *create_hashtable(size_t size);
t_entry			    create_entry(char *key);
t_entry			    *insert_hashtable(t_hashtable **table, t_entry entry);
t_entry			    *hashtable_get(t_hashtable *table, char *name);


t_info              read_file_input(FILE *file_input);
t_street            *read_file_input_street(FILE *file_input, t_info info, t_hashtable **table);
t_car               *read_file_input_car(FILE *file_input, t_info info, t_hashtable *table);
t_intersection      *parse_intersection(t_info info, t_street *info_street);
void                weight_updater(t_info info, t_street * info_street, t_car * info_car);
void                algo(t_info info, t_intersection *intersection_info, t_street *street_info);
void                write_output_file(const char *path_output, t_info info, t_intersection *intersection_info, t_street *street_info);


#endif

