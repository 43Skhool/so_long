
#include "so_long.h"

// gcc *.c *.h -Lminilibx-linux -lmlx_Linux -lX11 -lXext
// gcc *.c *.h

int main(int argc, char *argv[])
{
	char *map[] = {
		"ABCD",
		"EFGH",
		"IJKL"};

	map_validation_response *a = validate_map(map);
	
	if (a->valid == false)
		printf("%s\n", a->reason);

	free(a);//Necessario per non avere memory leak con il valgrind nei test
}
