#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include "Go.h"

// |<{<[<(< \/ >)>]>}>|
// System

// Init
SDL_AppResult Go::System_Init_SDL() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		cout << "Can't initialize video!";
		return SDL_APP_FAILURE;
	}

	if (SDL_CreateWindowAndRenderer("Pixel Golium", ui.main_s.x*32, ui.main_s.y*32
		, SDL_WINDOW_BORDERLESS
		| SDL_WINDOW_TRANSPARENT
		, &sdl_window, &sdl_renderer)) {
		cout << "\n Can't create window and renderer!";
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;
}

void Go::System_Init_ImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = GetIO(); (void)io;

	StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(sdl_window, sdl_renderer);
	ImGui_ImplSDLRenderer3_Init(sdl_renderer);
}

//Render
void Go::System_Render_Start() {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
}

void Go::System_Render_ImGui_End() {
	Render();
}

void Go::System_Render_SDL_End() {
	ImGui_ImplSDLRenderer3_RenderDrawData(GetDrawData(), sdl_renderer);
	SDL_RenderPresent(sdl_renderer);
}

//Quit
void Go::System_Quit_ImGui() {
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	DestroyContext();
}

void Go::System_Quit_SDL() {
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_DestroyTexture(sdl_texture);
}



// |<{<[<(< \/ >)>]>}>|
// Ui

void Go::UI_Add_Widjet(Widjet_Type type, Int2 pos, Int2 size) {
	ui.widjets.push_back(Widjet(type, pos, size));
}

void Go::UI_Clear_SWindow() {
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
	SDL_RenderClear(sdl_renderer);
}

void Go::UI_Draw_Main() {
	Int2 win_s_pix{ ui.main_s.x * 32,ui.main_s.y * 32 };

	SetNextWindowPos({ 0,0 });
	SetNextWindowSize(win_s_pix.T_ImVec2());
	PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f,0.0f });
	PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f,0.0f });
	Begin("Main", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	int cells{ ui.main_s.x + ui.main_s.y };
	float cell_s{ 32 };
	ImVec2 points[4]{ {0.5f,0.25f}, {0.75f,0.5f}, {0.5f,0.75f}, {0.25f,0.5f} };
	for (int i{ 0 };i < 4;i++) {
		points[i].x *= cell_s;
		points[i].y *= cell_s;
	}

	sdl_texture = SDL_CreateTexture(
		sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		(int)cell_s, (int)cell_s );
	SDL_SetRenderTarget(sdl_renderer, sdl_texture);
	UI_Clear_SWindow();

	Pixel col = style.CellFrame;
	SDL_SetRenderDrawColor(sdl_renderer, col.r, col.g, col.b, col.a);
	SDL_FRect rect{ 0.0f, 0.0f, cell_s, cell_s };
	SDL_RenderRect(sdl_renderer, &rect );

	SDL_SetRenderTarget(sdl_renderer, NULL);
	ImTextureID tex = (ImTextureID)sdl_texture;

	for (int i{ 0 };i < ui.main_s.y;i++) {
		for (int j{ 0 };j < ui.main_s.x;j++) {
			Image(tex, { cell_s,cell_s });
			if (j != (ui.main_s.x - 1)) {
				SameLine();
			}
		}
	}

	End();
	PopStyleVar(2);
}



// |<{<[<(< \/ >)>]>}>|
// Events

void Go::Events_processing(SDL_Event* event) {
	ImGui_ImplSDL3_ProcessEvent(event);
}
void Go::Events_Mous_Press(SDL_Event* event) {

}
void Go::Events_Mous_Motion(SDL_Event* event) {

}
SDL_AppResult Go::Events_Keyboard_Press(SDL_Event* event) {
	switch (event->key.key) {
	case SDLK_ESCAPE: {
		return SDL_APP_SUCCESS;
		break;
	}
	default: {
		return SDL_APP_CONTINUE;
		break;
	}
	} // END of Switch
}