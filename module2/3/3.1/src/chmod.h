#pragma once

#include <stdint.h>

uint16_t getBitMask(char *str);

int getStatString(char *filename, char *dest);

void printBinary(uint16_t mask);

uint16_t simulateChmod(char *mode_str, char *filename);