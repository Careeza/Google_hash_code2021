#include "hashcode.h"

void    test_t_info(t_info info_file) {
    printf("%d %d %d %d %d\n", info_file.duration_sim, info_file.nb_intersections, info_file.nb_street, info_file.nb_cars, info_file.bonus_point);
}

t_street 		*street_info = NULL;

int		main(int argc, char **argv)
{

	t_info			info_file;
	t_hashtable		*table;
	t_car			*info_cars;
	t_intersection 	*intersection_info;

	if (argc < 3) {
		printf("need a least two args\n");
		return (1);
	}
    FILE *file = fopen(argv[1], "r");
	info_file = read_file_input(file);

	table = create_hashtable(4096);
	street_info = read_file_input_street(file, info_file, &table);
	info_cars = read_file_input_car(file, info_file, table);
	intersection_info = parse_intersection(info_file, street_info);
	weight_updater(info_file, street_info, info_cars);
	algo(info_file, intersection_info, street_info);
	write_output_file(argv[2], info_file, intersection_info, street_info);

	return (0);
}
