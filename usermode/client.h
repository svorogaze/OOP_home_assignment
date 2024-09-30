#pragma once
class Client {
public:

	Client();
	int get_time();

	int get_cost();

	void set_time(int x);

	void set_cost(int x);

	void set_number(int x);

	int get_number();

private:
	int cost = 0;
	int time = 0;
	int number = 0;
};