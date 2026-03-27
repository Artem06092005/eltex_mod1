#include <stdio.h>
#include <stdlib.h>

#include "network.h"

int main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("Использование: %s <IP шлюза> <Маска> <Кол-во пакетов>\n",
			   argv[0]);
		return 1;
	}

	const char* ip = argv[1];
	const char* mask = argv[2];
	int n = atoi(argv[3]);

	NetStats res = simulate_network(ip, mask, n);

	printf("Обработано пакетов: %d\n", n);
	printf("Своя подсеть:  %d шт. (%.2f%%)\n", res.local_packets,
		   res.local_percent);
	printf("Чужие сети:    %d шт. (%.2f%%)\n", res.remote_packets,
		   res.remote_percent);

	return 0;
}
