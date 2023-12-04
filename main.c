
#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

int main(/*int argc, char *argv[]*/)
{
	char *map[] = {
		"1111\0",
		"1C01\0",
		"1PE1\0",
		"1111\0",
		NULL}; // TO DO MUST BE NULL TERMINATED
	char *file_path = "maps/valid_map1";

	map_validation_response *a = get_map(file_path, map);

	if (a->valid == false)
		printf("%s\n", a->reason);
	else
		printf("ok, map is valid\n");

	free(a);//Necessario per non avere memory leak con il valgrind nei test
}
