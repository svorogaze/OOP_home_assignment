#pragma once
#include <vector>
#include "client.h"
#include "clerk.h"
class Bank {
public:
	void add_client(Client c);

	void process_clients(int cur_time);

	

private:
	std::vector<Clerk> clerks;
	std::vector<Client> clients_queue;
	int total_profits = 0;
	int processed_clients = 0;
	int lost_clients = 0;
};
