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
	while (true) {
		int to_sz = Globals::n;
		while (bank.clerks.size() > to_sz) bank.clerks.pop_back();
		while (bank.clerks.size() < to_sz) bank.clerks.push_back(Clerk());
		overlay.draw();
		bank.draw();
		overlay.render(bank);
	}
}