#pragma once
#include "client.h"
class Clerk {
public:
	bool is_finished(int cur_time);

	void set_finish_time(int x);

	int get_finish_time();

	void set_last_client(Client c);

	Client get_last_client();

	void process_new_client(Client c, int cur_time);

private:
	int finish_time = -1;
	Client current_client;
};