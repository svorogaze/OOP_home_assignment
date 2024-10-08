#include "bank.h"
#include "globals.hpp"
#include "overlay/overlay.h"
#include <string>
#include <algorithm>
void Bank::add_client(const Client& c) {
	if (clients_queue.size() >= Globals::k) {
		lost_profits += c.get_cost();
	}
	else if (clients_queue.size() >= 7) {
		if (Globals::random() % 3) {
			clients_queue.push_back(c);
		}
		else {
			lost_profits += c.get_cost();
		}
	}
	else {
		clients_queue.push_back(c);
	}
}

void Bank::process_clients() {
	for (int i = 0; i < clerks.size() && !clients_queue.empty(); ++i) {
		if (clerks[i].is_finished(current_time)) {
			auto cur_client = clients_queue[0];
			total_profits += cur_client.get_cost();
			clerks[i].process_new_client(cur_client, current_time);
			processed_clients++;
			display.first = cur_client.get_number();
			display.second = i;
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

void Bank::do_one_step() {
	if (current_time <= (Globals::today < 5 ? 8 : (Globals::today == 5 ? 6 : 0)) * 60) {
		current_time++;
		if (next_client_time <= 0) {
			next_client_time = 0;
			while (next_client_time == 0) {
				add_client(Client());
				next_client_time = Globals::random() % 11;
			}
		}
		else {
			next_client_time--;
		}
		process_clients();
	}
	else if (not clients_queue.empty()) {
		current_time++;
		process_clients();
	}
	else {
		Globals::today = (Globals::today + 1) % 7;
		current_time = 0;
	}
}

void Bank::do_step(int amount) {
	while (amount--) {
		do_one_step();
	}
}

void Bank::draw() {
	int we = 70;
	for (int i = 0; i < clerks.size(); ++i) {
		int x1 = (i * 2) * we + we;
		int x2 = (i * 2 + 1) * we + we;
		int y1 = 100, y2 = 100 + we;
		ImGui::GetWindowDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(0, 0, 0));
		if (!clerks[i].is_finished(current_time)) {
			clerks[i].get_last_client().draw((x1 + x2) / 2, y2 + 30);
		}
	}
	int cx = 30, cy = 280;
	for (int i = 0; i < clients_queue.size(); ++i) {
		if (cx + 30 > 1280) cx = 30, cy += 60;
		clients_queue[i].draw(cx, cy);
		cx += 60;
	}
	std::string table = std::to_string(display.first);
	table += " to ";
	table += std::to_string(display.second);
	ImGui::GetWindowDrawList()->AddRect(ImVec2(600, 50), ImVec2(680, 62), ImColor(0, 0, 0));
	ImGui::GetWindowDrawList()->AddText(ImVec2(601, 49), ImColor(0, 0, 0), table.c_str());
}
