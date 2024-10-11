#include <cstdint>
#include <random>
#include "bank.h"
namespace Globals {
	int n = 5, k = 10;
	int step = 10;
	int min_client_cost = 3000;
	int max_client_cost = 50000;
	int min_client_time = 2;
	int max_client_time = 30;
	int created_clients = 0;
	int start_delay = 5;
	int middle_delay = 20;
	std::mt19937 random(1337);
	Bank bank;

	int today = 0; // 0 for Monday, 6 for Sunday
}