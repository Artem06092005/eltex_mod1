#include "network.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint32_t ip_to_int(const char* ip_str) {
	unsigned int a, b, c, d;
	if (sscanf(ip_str, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) return 0;

	if (a > 255 || b > 255 || c > 255 || d > 255) return 0;

	return (uint32_t)((a << 24) | (b << 16) | (c << 8) | d);
}

int is_ip_in_subnet(uint32_t ip, uint32_t network_address, uint32_t mask) {
	return (ip & mask) == network_address;
}

NetStats simulate_network(const char* gw_ip, const char* net_mask, int n) {
	NetStats stats = {0, 0, 0.0, 0.0};

	uint32_t gateway = ip_to_int(gw_ip);
	uint32_t mask = ip_to_int(net_mask);

	if (gateway == 0 || mask == 0) {
		fprintf(stderr, "Ошибка: некорректный IP-адрес или маска\n");
		return stats;
	}

	uint32_t network_address = gateway & mask;

	printf("Параметры подсети:\n");
	printf("Шлюз: %s\n", gw_ip);
	printf("Маска: %s\n", net_mask);
	printf("Адрес подсети: %u.%u.%u.%u\n", (network_address >> 24) & 0xFF,
		   (network_address >> 16) & 0xFF, (network_address >> 8) & 0xFF,
		   network_address & 0xFF);
	printf("------------------------\n");

	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		uint32_t random_ip = 0;
		for (int j = 0; j < 4; j++) {
			random_ip = (random_ip << 8) | (rand() % 256);
		}

		if ((random_ip & mask) == network_address) {
			stats.local_packets++;
		} else {
			stats.remote_packets++;
		}
	}

	if (n > 0) {
		stats.local_percent = (double)stats.local_packets / n * 100.0;
		stats.remote_percent = (double)stats.remote_packets / n * 100.0;
	}

	return stats;
}