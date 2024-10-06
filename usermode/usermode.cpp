#include "imgui.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "overlay/overlay.h"
#include "bank.h"
#include "client.h"
#include "clerk.h"
#include "globals.hpp"
int main(int, char**) {
	Bank bank;
	bank.clerks.assign(Globals::n, Clerk());
	bank.clerks[0].set_finish_time(100);
	bank.clerks[0].set_last_client(Client());
	Globals::k = 25;
	for (int i = 0; i < 30; ++i) {
		bank.add_client(Client());
	}
	while (true) {
		overlay.draw();
		bank.draw();
		overlay.render(bank);
	}
}