#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *f = fopen("c_data", "rb");
	unsigned char *c = (unsigned char*)malloc(150*sizeof(unsigned char));
	fread(c, 1, 150, f);
	printf("%s\n", c);
	return 0;
}
