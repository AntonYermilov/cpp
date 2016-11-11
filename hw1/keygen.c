/* stupid random keygen */

#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv) {
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int len = atoi(argv[3]);
	
	FILE* fout = fopen(argv[4], "w");

	char color[] = {'B', 'G', 'R'};

	for (int i = 0; i < len * 5; i++) {
		int x = rand() % w;
		int y = rand() % h;
		int c = rand() % 3;
		fprintf(fout, "%d %d %c\n", x, y, color[c]);
	}
}
