#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <Windows.h>
#include <utility>
#include <CommCtrl.h>
#include "../bank.h"
#pragma comment(lib, "d3d11.lib") 

class Overlay {
public:
	ID3D11Device* g_pd3dDevice = nullptr;
	ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
	IDXGISwapChain* g_pSwapChain = nullptr;
	bool                     g_SwapChainOccluded = false;
	ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	int windowstate = 0;
	bool done = false;
	bool menu = true;
	bool one_step_pressed = false;
	bool all_steps_pressed = false;
	bool revert_step_pressed = false;
	bool active = false;
	int page = 0;
	int max_depth = 0;
	ImVec4 clear_color;
	ImColor fractal_color;
	HWND hwnd;
	WNDCLASSEXW wc;
	UINT ResizeWidth = 0, ResizeHeight = 0;
	void draw();
	void render(Bank& bank);
	Overlay();
	~Overlay();
	ImDrawList* getdrawlist();
	ID3D11ShaderResourceView* textures[50];
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
};
static bool mainmenu = true;
extern Overlay overlay;
