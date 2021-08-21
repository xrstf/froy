#include "../include/config.h"
#include "stdio.h"

// Why grep the version from the config.h when we can
// just as easily have a tiny program doing it The Right Way(tm).

int main() {
	printf("%s\n", FROY_VERSION);
}
