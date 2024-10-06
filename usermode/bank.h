#pragma once
#include <vector>
#include "client.h"
#include "clerk.h"
#include <algorithm>
class Bank {
public:
	void add_client(const Client& c);

	void process_clients();

	int get_profits();

	int get_lost_profits();

	void draw();

	void do_one_step();

	void do_step(int amount);

	std::vector<Clerk> clerks;
	int current_time = 0;
private:
	
	std::vector<Client> clients_queue;
	int total_profits = 0;
	int processed_clients = 0;
	int lost_profits = 0;
	std::pair<int, int> display;
};
