#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_main.h>

#include "Go.h"

static Go go;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	cout << "LAUNCH\n";

	go.System_Init_SDL();
	go.System_Init_ImGui();

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	cout << "START_GRAPHIC_LOOP\n";
	go.System_Render_Start();

	go.UI_Draw_Main();

	go.System_Render_ImGui_End();

	go.UI_Clear_SWindow();

	go.System_Render_SDL_End();
	cout << "END_GRAPHIC_LOOP\n";
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	cout << "START_EVENT_LOOP\n";
	SDL_AppResult result{SDL_APP_CONTINUE};

	go.Events_processing(event);

	switch (event->type) {
		case SDL_EVENT_KEY_DOWN: {
			result = go.Events_Keyboard_Press(event);
			if (result == SDL_APP_SUCCESS) { return SDL_APP_SUCCESS; }
			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN: {
			go.Events_Mous_Press(event);
			break;
		}
		case SDL_EVENT_MOUSE_MOTION: {
			go.Events_Mous_Motion(event);
			break;
		}
		default: {

			break;
		}
	}
	
	cout << "END_EVENT_LOOP\n";
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	cout << "SELF_DESTRUCTION";
	go.System_Quit_ImGui();
	go.System_Quit_SDL();
}