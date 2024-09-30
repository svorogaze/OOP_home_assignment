#include "bank.h"
void Bank::add_client(Client c) {
	clients_queue.push_back(c);
}

void Bank::process_clients(int cur_time) {
	for (auto& clerk : clerks) {
		if (clerk.is_finished(cur_time)) {
			if (!clients_queue.empty()) {
				auto cur_client = clients_queue[0];
				total_profits += cur_client.get_cost();
				clerk.process_new_client(cur_client, cur_time);
				processed_clients++;
				clients_queue.erase(clients_queue.begin());
			}
		}
	}
}
