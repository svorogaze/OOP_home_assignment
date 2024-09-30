#include "imgui.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "overlay/overlay.h"
#include "bank.h"
#include "client.h"
#include "clerk.h"
int main(int, char**) {
	while (true) {
		overlay.draw();
		overlay.render();
	}
}