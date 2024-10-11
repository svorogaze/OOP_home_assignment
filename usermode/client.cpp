#include "client.h"
#include "globals.hpp"
#include "overlay/overlay.h"
#include <string>
Client::Client() {
	time = (Globals::random() % (Globals::max_client_time - Globals::min_client_time + 1)) + Globals::min_client_time;
	cost = (Globals::random() % (Globals::max_client_cost - Globals::min_client_cost + 1)) + Globals::min_client_cost;
}

void Client::draw() const {
	ImGui::GetWindowDrawList()->AddCircle(ImVec2(position_x, position_y), 20.f, ImColor(0, 0, 0));
	std::string number_string = std::to_string(number);
	ImGui::GetWindowDrawList()->AddText(ImVec2(position_x - 6, position_y - 4), ImColor(0, 0, 0), number_string.c_str());
}


int Client::get_time() const {
	return time;
}

int Client::get_cost() const {
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

int Client::get_number() const {
	return number;
}
