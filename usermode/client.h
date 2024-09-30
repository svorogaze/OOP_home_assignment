#pragma once
class Client {
public:
	int get_time();

	int get_cost();

	void set_time(int x);

	void set_cost(int x);

private:
	int cost = 0;
	int time = 0;
	int number = 0;
};