#include "chmod.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

uint16_t getBitMask(char *str) {
	uint16_t mask = 0;
	int len = strlen(str);

	if (str[0] >= '0' && str[0] <= '7') {
		if (len != 3) return 0xFFFF;
		for (int i = 0; i < 3; i++) {
			if (str[i] < '0' || str[i] > '7') return 0xFFFF;
		}
		unsigned int octal;
		sscanf(str, "%o", &octal);
		return (uint16_t)octal;
	}

	if (len != 9) return 0xFFFF;

	for (int i = 0; i < 9; i++) {
		if (str[i] == 'r')
			mask |= (1 << (8 - i));
		else if (str[i] == 'w')
			mask |= (1 << (8 - i));
		else if (str[i] == 'x')
			mask |= (1 << (8 - i));
		else if (str[i] != '-')
			return 0xFFFF;
	}
	return mask;
}

int getStatString(char *filename, char *dest) {
	struct stat fileStat;
	if (stat(filename, &fileStat) == -1) return -1;

	uint16_t mode = fileStat.st_mode & 0777;
	char rwx[10] = "---------";
	char comps[] = "rwxrwxrwx";

	for (int i = 0; i < 9; i++) {
		if (mode & (1 << (8 - i))) rwx[i] = comps[i];
	}

	if (dest) strcpy(dest, rwx);
	return (int)mode;
}

void printBinary(uint16_t mask) {
	printf("0b");
	for (int i = 8; i >= 0; i--) {
		printf("%d", (mask >> i) & 1);
		if (i % 3 == 0 && i != 0) printf("_");
	}
}

uint16_t simulateChmod(char *mode_str, char *filename) {
	struct stat fileStat;
	if (stat(filename, &fileStat) == -1) {
		return 0xFFFF;
	}

	uint16_t newMask = getBitMask(mode_str);
	if (newMask == 0xFFFF) {
		return 0xFFFF;
	}
	return newMask;
}