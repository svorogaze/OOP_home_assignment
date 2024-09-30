#include "client.h"
#include "globals.hpp"

Client::Client() {
	time = (Globals::random() % (Globals::max_client_time - Globals::min_client_time + 1)) + Globals::min_client_time;
	cost = (Globals::random() % (Globals::max_client_cost - Globals::min_client_cost + 1)) + Globals::min_client_cost;
	number = ++Globals::created_clients;
}


int Client::get_time() {
	return time;
}

int Client::get_cost() {
	return cost;
}

void Client::set_time(int x) {
	time = x;
}

void Client::set_cost(int x) {
	cost = x;
}

void Client::set_number(int x) {
	number = x;
}

int Client::get_number() {
	return number;
}
