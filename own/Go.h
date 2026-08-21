#pragma once
#ifndef WARP_URDAN_H
#define WARP_URDAN_H

#include "Go_Loadout.h"

class Go {
private:
	SDL_Window* sdl_window{ nullptr };
	SDL_Renderer* sdl_renderer{ nullptr };
	SDL_Texture* sdl_texture{ nullptr };

	Devise devise;
	UI ui;
	Style style;
public:
	// |<{<[<(< \/ >)>]>}>|
	// System

	SDL_AppResult System_Init_SDL();
	void System_Init_ImGui();

	void System_Render_Start();
	void System_Render_ImGui_End();
	void System_Render_SDL_End();

	void System_Quit_ImGui();
	void System_Quit_SDL();

	// |<{<[<(< \/ >)>]>}>|
	//UI
	void UI_Add_Widjet(Widjet_Type type, Int2 pos, Int2 size);

	void UI_Clear_SWindow();

	void UI_Draw_Main();

	// |<{<[<(< \/ >)>]>}>|
	// Events
	void Events_processing(SDL_Event* event);
	void Events_Mous_Press(SDL_Event* event);
	void Events_Mous_Motion(SDL_Event* event);
	SDL_AppResult Events_Keyboard_Press(SDL_Event* event);
};

#endif // WARP_URDAN_H