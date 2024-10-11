#pragma once
class Client {
public:

	Client();
	int get_time() const;

	int get_cost() const;

	void set_time(int x);

	void set_cost(int x);

	void set_number(int x);

	int get_number() const;

	void draw() const;

	int position_x = 0, position_y = 0;

private:
	int cost = 0;
	int time = 0;
	int number = 0;
};