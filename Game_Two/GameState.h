#pragma once

#include "man.h"
#include "Image.h"

class GameState {
public:
	// Players
	Man man;
	Image image[100];

	// Images
	SDL_Texture* Image;
	SDL_Renderer* rend;
};