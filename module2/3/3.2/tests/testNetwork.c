#include <string.h>

#include "../src/network.h"
#include "../unity/unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_ip_to_int(void) {
	uint32_t result = ip_to_int("255.255.255.255");
	TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, result);
	result = ip_to_int("255.192.0.0");
	TEST_ASSERT_EQUAL_HEX32(0xFFC00000, result);
	result = ip_to_int("0.0.0.0");
	TEST_ASSERT_EQUAL_HEX32(0x00000000, result);

	result = ip_to_int("256.1.1.1");
	TEST_ASSERT_EQUAL_HEX32(0, result);

	result = ip_to_int("192.168.1.256");
	TEST_ASSERT_EQUAL_HEX32(0, result);

	result = ip_to_int("192.168.1");
	TEST_ASSERT_EQUAL_HEX32(0, result);

	result = ip_to_int("abc.def.ghi.jkl");
	TEST_ASSERT_EQUAL_HEX32(0, result);

	result = ip_to_int("");
	TEST_ASSERT_EQUAL_HEX32(0, result);
}

void test_is_ip_in_subnet(void) {
	uint32_t network = ip_to_int("192.168.1.0");
	uint32_t mask = ip_to_int("255.255.255.0");

	TEST_ASSERT_TRUE(is_ip_in_subnet(ip_to_int("192.168.1.1"), network, mask));
	TEST_ASSERT_TRUE(
		is_ip_in_subnet(ip_to_int("192.168.1.100"), network, mask));
	TEST_ASSERT_TRUE(
		is_ip_in_subnet(ip_to_int("192.168.1.254"), network, mask));
	TEST_ASSERT_TRUE(is_ip_in_subnet(ip_to_int("192.168.1.0"), network, mask));
	TEST_ASSERT_TRUE(
		is_ip_in_subnet(ip_to_int("192.168.1.255"), network, mask));

	TEST_ASSERT_FALSE(is_ip_in_subnet(ip_to_int("192.168.0.1"), network, mask));
	TEST_ASSERT_FALSE(is_ip_in_subnet(ip_to_int("192.168.2.1"), network, mask));
	TEST_ASSERT_FALSE(is_ip_in_subnet(ip_to_int("10.0.0.1"), network, mask));
	TEST_ASSERT_FALSE(is_ip_in_subnet(ip_to_int("172.16.0.1"), network, mask));

	mask = ip_to_int("255.255.255.255");

	TEST_ASSERT_FALSE(is_ip_in_subnet(ip_to_int("192.168.1.1"), network, mask));
	TEST_ASSERT_FALSE(is_ip_in_subnet(ip_to_int("192.168.1.2"), network, mask));

	network = ip_to_int("0.0.0.0");
	mask = ip_to_int("0.0.0.0");
	TEST_ASSERT_TRUE(is_ip_in_subnet(ip_to_int("192.168.1.1"), network, mask));
	TEST_ASSERT_TRUE(is_ip_in_subnet(ip_to_int("10.0.0.1"), network, mask));
	TEST_ASSERT_TRUE(
		is_ip_in_subnet(ip_to_int("255.255.255.255"), network, mask));
}

void test_simulate_network(void) {
	NetStats stats =
		simulate_network("192.168.1.100", "255.255.255.255", 10000);
	TEST_ASSERT_EQUAL(0, stats.local_packets);
	TEST_ASSERT_EQUAL(10000, stats.remote_packets);
	TEST_ASSERT_EQUAL(0., stats.local_percent);
	TEST_ASSERT_EQUAL(100., stats.remote_percent);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ip_to_int);
	RUN_TEST(test_is_ip_in_subnet);
	RUN_TEST(test_simulate_network);
	return UNITY_END();
}