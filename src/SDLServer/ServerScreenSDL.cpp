#include "ServerScreenSDL.h"
void ServerScreenSDL::populateRandom(int num){
	int width;
	int height;
	SDL_GetWindowSize(win, &width, &height);
	for (int i = 0; i < num; i++){
		ServerWindowSDL* newWin = new ServerWindowSDL(
			{rand() % width, rand() % height, 200, 300},
			{(Uint8) rand(), (Uint8) rand(), (Uint8) rand(), 0xFF});
		windows.insert(newWin);
		idWindowMap[newWin->windowID] = newWin;
	}

}
ServerScreenSDL::ServerScreenSDL(std::string name, Area area) : visible(true){
	win = SDL_CreateWindow(name.c_str(), area.x, area.y, area.width, area.height, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, 0);
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
		area.width, area.height);

	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);

	windowID = SDL_GetWindowID(win);


	windows = std::set<ServerWindowSDL*, ServerWindowSDL>(ServerWindowSDL());

	populateRandom(10);
}

void ServerScreenSDL::handleEvent(SDL_Event& e) {
	if(e.window.windowID == windowID){
		if(e.type == SDL_WINDOWEVENT){
			std::cout << "ServerScreenSDL::handleEvent: " << e.window.event << std::endl;
			switch (e.window.event){
				case SDL_WINDOWEVENT_CLOSE:
				SDL_HideWindow(win);
				break;

				case SDL_WINDOWEVENT_HIDDEN:
				visible = false;
				break;

				case SDL_WINDOWEVENT_SHOWN:
				visible = true;
				break;

				case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(ren);
				break;
			}
		} else { //must be a key event

		}
		render();
	}
}

void ServerScreenSDL::render(){
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(ren);


	for (auto& w : windows){
		w->render(ren);
	}

	SDL_RenderPresent(ren);
}

bool ServerScreenSDL::isVisible(){
	return visible;
}

bool ServerScreenSDL::hasWindow(long windowID){
	return idWindowMap.count(windowID);
}

ServerScreenSDL::~ServerScreenSDL() {



	SDL_DestroyRenderer(ren);
	SDL_DestroyTexture(tex);
	SDL_DestroyWindow(win);
}


