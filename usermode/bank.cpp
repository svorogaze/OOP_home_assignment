#include "bank.h"
#include "globals.hpp"
void Bank::add_client(Client c) {
	if (clients_queue.size() >= Globals::k) {
		lost_profits += c.get_cost();
	}
	else {
		clients_queue.push_back(c);
	}
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

int Bank::get_profits() {
	return total_profits;
}

int Bank::get_lost_profits() {
	return lost_profits;
}
