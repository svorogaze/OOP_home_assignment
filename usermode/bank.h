#pragma once
#include <vector>
#include "client.h"
#include "clerk.h"
class Bank {
public:
	void add_client(Client c);

	void process_clients(int cur_time);

	int get_profits();

	int get_lost_profits();

private:
	std::vector<Clerk> clerks;
	std::vector<Client> clients_queue;
	int total_profits = 0;
	int processed_clients = 0;
	int lost_profits = 0;
};
