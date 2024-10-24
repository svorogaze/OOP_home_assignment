#include <cstdint>
#include <random>
#include "bank.h"
namespace Globals {
	extern int n, k;
	extern int step;
	extern int min_client_cost;
	extern int max_client_cost;
	extern int min_client_time;
	extern int max_client_time;
	extern int created_clients;
	extern int start_delay;
	extern int middle_delay;
	extern int step_time;
	extern int clerk_width;
	extern std::mt19937 random;
	extern Bank bank;
	extern int today;
}