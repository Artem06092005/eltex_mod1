#pragma once

#include <stdint.h>

typedef struct {
	int local_packets;
	int remote_packets;
	double local_percent;
	double remote_percent;
} NetStats;

NetStats simulate_network(const char* gw_ip, const char* net_mask, int n);

uint32_t ip_to_int(const char* ip_str);

int is_ip_in_subnet(uint32_t ip, uint32_t network_address, uint32_t mask);