#pragma once
#ifndef WU_LOADOUT_H
#define WU_LOADOUT_H

#include <SDL3/SDL.h>
#include <imgui.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;
using namespace ImGui;

// |<{<[<(< \/ >)>]>}>|
// Types

struct Int2 {
	int x{ 0 };
	int y{ 0 };

	Int2 operator* (int factor) {
		return Int2(x * factor, y * factor);
	}

	Int2 operator* (Int2& other) {
		return Int2(x * other.x, y * other.y);
	}

	ImVec2 T_ImVec2() {
		return ImVec2((float)x, (float)y);
	}
};

// Don't use analogs
struct Int4 {
	int x{ 0 };
	int y{ 0 };
	int z{ 0 };
	int q{ 0 };
};

struct Pixel {
	uint8_t r{ 0 };
	uint8_t g{ 0 };
	uint8_t b{ 0 };
	uint8_t a{ 0 };

	ImU32 T_ImU32() {
		return IM_COL32(r, g, b, a);
	}
};

class Vec {

};

class Grid {

};

// |<{<[<(< \/ >)>]>}>|
// Sub struct

enum Widjet_Type {
	EMPTY,
	BUTTON,
	COLOR_PICKER
};

struct Widjet {
	Widjet_Type type{ EMPTY };
	Int2 pos{ 0,0 }; // count in cell
	Int2 size{ 0,0 }; // count in cell

	Widjet(Widjet_Type giv_type, Int2 giv_pos, Int2 giv_size) {
		type = giv_type;
		pos = giv_pos;
		size = giv_size;
	}
};

// |<{<[<(< \/ >)>]>}>|
// Data structs

struct Style {
	Pixel sdl_WinBg{ 0,0,0,150 };

	Pixel CellDimond{ 200,200,200,100 };
	Pixel CellFrame{ 200,200,200,100 };

	Pixel WinBg{ 0,0,0,0 };
	Pixel WinBorder{ 0,0,0,0 };

	Pixel BottonUnHow{ 0,0,0,0 };
	Pixel BottonHow{ 0,0,0,0 };
	Pixel BottonPres{ 0,0,0,0 };

	Pixel SliderUnHow{ 0,0,0,0 };
	Pixel SliderHow{ 0,0,0,0 };
	Pixel SliderPress{ 0,0,0,0 };
};

struct UI {
	Int2 main_s{16,16};
	vector<Widjet> widjets;
};

struct Devise {
	Int2 monitor_s{ 0,0 };
};

#endif // WU_LOADOUT_H