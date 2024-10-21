#include "bank.h"
#include "globals.hpp"
#include "overlay/overlay.h"
#include <string>
#include <algorithm>
#include <iostream>

Bank::Bank() {
	places.resize(25);
	for (int i = 0; i < places.size(); ++i) {
		while (true) {
			int randx = Globals::random() % 600 + 100;
			int randy = Globals::random() % 300 + 250;
			int min_dist = 10000000;
			for (int j = 0; j < i; ++j) {
				min_dist = min(min_dist, (randx - places[j].x) * (randx - places[j].x) + (randy - places[j].y) * (randy - places[j].y));
			}
			if (min_dist < 4900) continue;
			places[i].x = randx, places[i].y = randy;
			places[i].free = true;
			break;
		}
	}
}

void Bank::add_client(Client& c) {
	if (clients_queue.size() >= Globals::k) {
		lost_profits += c.get_cost();
	}
	else if (clients_queue.size() < 7 || Globals::random() % 3) {
		total_profits += c.get_cost();
		int cnt = Globals::random() % places.size();
		int index = 0;
		while (true) {
			if (places[index].free) {
				cnt--;
				if (cnt <= 0) break;
			}
			index = (index + 1) % places.size();
		}
		places[index].free = false;
		c.position_x = places[index].x;
		c.position_y = places[index].y;
		clients_queue.push_back(c);
	}
	else {
		lost_profits += c.get_cost();
	}
}

void Bank::process_clients() {
	for (int i = 0; i < clerks.size() && !clients_queue.empty(); ++i) {
		if (clerks[i].is_finished(current_time)) {
			auto cur_client = clients_queue[0];
			for (auto& place : places) {
				if (place.x == cur_client.position_x && place.y == cur_client.position_y) {
					place.free = true;
					break;
				}
			}
			total_profits += cur_client.get_cost();
			clerks[i].process_new_client(cur_client, current_time);
			status[i].start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			status[i].end_time = status[i].start_time + std::chrono::milliseconds(Globals::step_time);
			status[i].start_x = cur_client.position_x;
			status[i].start_y = cur_client.position_y;
			int x1 = (i * 2) * Globals::clerk_width + Globals::clerk_width;
			int x2 = (i * 2 + 1) * Globals::clerk_width + Globals::clerk_width;
			int y2 = 100 + Globals::clerk_width + 30;
			status[i].end_x = (x1 + x2) / 2;
			status[i].end_y = y2;
			processed_clients++;
			display.first = cur_client.get_number();
			display.second = i + 1;
			clients_queue.erase(clients_queue.begin());
		}
	}
}

int Bank::get_profits() {
	return total_profits;
}

int Bank::get_lost_profits() {
	return lost_profits;
}

int Bank::get_day_length() {
	if (Globals::today < 5) {
		return 8 * 60;
	}
	if (Globals::today == 5) {
		return 6 * 60;
	}
	return -1;
}

void Bank::do_one_step() {
	if (current_time <= get_day_length()) {
		for (auto c : clerks) {
			if (c.get_finish_time() >= current_time) {
				sum_free_clerks += 1;
			}
		}
		sum_time++;
		sum_length += clients_queue.size();
		max_queue_size = max(max_queue_size, clients_queue.size());
		current_time++;
		if (next_client_time <= 0) {
			next_client_time = 0;
			while (next_client_time == 0) {
				Client new_client;
				new_client.set_number(++Globals::created_clients);
				add_client(new_client);
				double coef = std::abs(current_time - get_day_length() / 2) / (double)(get_day_length() / 2); // coefficent from 0 to 1, indicating how close we are to the middle day(0 is the closest)
				next_client_time = Globals::random() % (int)(Globals::middle_delay + (Globals::start_delay - Globals::middle_delay) * coef);
			}
		}
		else {
			next_client_time--;
		}
		process_clients();
	}
	else if (!clients_queue.empty()) {
		for (auto& c : clients_queue) {
			total_profits -= c.get_cost();
			lost_profits += c.get_cost();
		}
		clients_queue.clear();
		current_time++;
		process_clients();
	}
	else {
		total_profits -= 2000 * clerks.size();
		Globals::today = (Globals::today + 1) % 7;
		current_time = 0;
		Globals::created_clients = 0;
		for (int i = 0; i < places.size(); i++) {
			places[i].free = true;
		}
		std::fill(clerks.begin(), clerks.end(), Clerk());
	}
}

void Bank::do_step(int amount) {
	while (amount--) {
		do_one_step();
	}
}

void Bank::draw() {
	auto real_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	for (int i = 0; i < clerks.size(); ++i) {
		int x1 = (i * 2) * Globals::clerk_width + Globals::clerk_width;
		int x2 = (i * 2 + 1) * Globals::clerk_width + Globals::clerk_width;
		int y1 = 100, y2 = 100 + Globals::clerk_width;
		ImColor fill = ImColor(0, 255, 0);
		if (!clerks[i].is_finished(current_time)) {
			double coef = (double)(status[i].end_time - real_time).count() / (status[i].end_time - status[i].start_time).count();
			if (coef < 0) coef = 0;
			clerks[i].get_last_client().position_x = status[i].end_x - coef * (status[i].end_x - status[i].start_x);
			clerks[i].get_last_client().position_y = status[i].end_y - coef * (status[i].end_y - status[i].start_y);
			clerks[i].get_last_client().draw();
			fill = ImColor(255, 0, 0);
		}
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), fill);
	}
	for (int i = 0; i < clients_queue.size(); ++i) {
		clients_queue[i].draw();
	}
	std::string table = std::to_string(display.first);
	table += " to ";
	table += std::to_string(display.second);
	if (display.second == 0) {
		table = "";
	}
	ImGui::GetWindowDrawList()->AddRect(ImVec2(600, 50), ImVec2(680, 70), ImColor(0, 0, 0));
	ImGui::GetWindowDrawList()->AddText(ImVec2(601, 53), ImColor(0, 0, 0), table.c_str());
}

void Bank::reset() {
	clients_queue.clear();
	current_time = 0;
	sum_length = 0;
	sum_time = 0;
	max_queue_size = 0;
	sum_free_clerks = 0;
	clients_queue.clear();
	total_profits = 0;
	processed_clients = 0;
	lost_profits = 0;
	next_client_time = 0;
	display = { 0,0 };
	for (auto& i : clerks) {
		i.set_finish_time(0);
	}
}