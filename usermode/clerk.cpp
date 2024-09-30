#include "clerk.h"

bool Clerk::is_finished(int cur_time) {
	return cur_time >= finish_time;
}

void Clerk::set_finish_time(int x) {
	finish_time = x;
}

void Clerk::set_last_client(Client c) {
	current_client = c;
}

Client Clerk::get_last_client() {
	return current_client;
}

void Clerk::process_new_client(Client c, int cur_time) {
	set_finish_time(cur_time + c.get_time());
	set_last_client(c);
}


int Clerk::get_finish_time() {
	return finish_time;
}