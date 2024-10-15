#pragma once
#include <vector>
#include "client.h"
#include "clerk.h"
#include <algorithm>
class Bank {
public:

	Bank();

	void add_client(Client& c);

	void process_clients();

	int get_profits();

	int get_lost_profits();

	void draw();

	void do_one_step();

	void do_step(int amount);

	int get_day_length();

	void reset();

	std::vector<Clerk> clerks;
	int current_time = 0;
	int64_t sum_length = 0;
	int64_t sum_time = 0;
	int64_t max_queue_size = 0;
	int64_t sum_free_clerks = 0;
	struct Place {
		int x, y;
		bool free;
	};
	std::vector<Place> places;
private:
	
	std::vector<Client> clients_queue;
	int64_t total_profits = 0;
	int64_t processed_clients = 0;
	int64_t lost_profits = 0;
	std::pair<int, int> display;
	int next_client_time = 0;
};
