#include "client.h"
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