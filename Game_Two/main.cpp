#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <SDL.h>
#include <SDL_Image.h>

#include "GameState.h"
#include "global_variables.h"

int processEvents(SDL_Window* window, GameState* gameState) {
	//Create a flag
	int done = 0;
	// Create a event
	SDL_Event event;

	// Process all the events waiting in the events system
	while (SDL_PollEvent(&event)) {				// Return true if there is a event waiting to be prossed
												// Check the event type
		switch (event.type) {
		case SDL_WINDOWEVENT_CLOSE: {
			if (window) {
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				done = 1;
				break;
			}
		}
		break;
		case SDL_QUIT:
			// quit out of the game
			done = 1;
			break;
		}
	}

	// Make the keys faster and less lag
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If the key is pressed, it will return true for the whole frame
	if (state[SDL_SCANCODE_LEFT])
		gameState->man.x -= 10;
	if (state[SDL_SCANCODE_RIGHT])
		gameState->man.x += 10;
	if (state[SDL_SCANCODE_UP])
		gameState->man.y -= 10;
	if (state[SDL_SCANCODE_DOWN])
		gameState->man.y += 10;
	if (state[SDL_SCANCODE_A])
		gameState->man.x -= 10;
	if (state[SDL_SCANCODE_D])
		gameState->man.x += 10;
	if (state[SDL_SCANCODE_W])
		gameState->man.y -= 10;
	if (state[SDL_SCANCODE_S])
		gameState->man.y += 10;

return done;
}

void doRender(SDL_Renderer* renderer, GameState* gameState) {
	// Set a background color
	SDL_SetRenderDrawColor(renderer,			// Renderer created above
		0,										// Color Red
		0,										// Color Green
		255,									// Color Blue
		255										// Opaque or translucent
		);

	// Clear the renderer screen (to blue)
	SDL_RenderClear(renderer);

	// Set the drawing color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Create the object
	SDL_Rect rect = { gameState->man.x, gameState->man.y, 80, 80 };

	// Draw the filled rectangle
	SDL_RenderFillRect(renderer, &rect);

	// Draw the image
	for (int i = 0; i < 100; i++) {
		SDL_Rect imgRect = { gameState->image[i].x, gameState->image[i].y, 64, 64 };
		// Copy or draw the sdl render passed in onto the screen
		SDL_RenderCopy(renderer, gameState->Image, NULL, &imgRect);
	}
	// Finished drawing, result will show on the screen
	SDL_RenderPresent(renderer);
}

void loadGame(GameState* gameState, std::string path) {
	// Declare a GameState	
	gameState->man.x = 320 - 40;
	gameState->man.y = 240 - 40;

	//Declare a source image to create a texture
	SDL_Surface* imageSurface = NULL;

	// Load the images and create rendering textures from them
	imageSurface = IMG_Load(path.c_str());
	// Make sure the image has been loaded
	if (imageSurface == NULL) {
		std::cerr << "Cannot find soccerball.png, Due to: \n" << IMG_GetError() << "\n\n";
		SDL_Quit();
		exit(1);
	}

	// Store into the game state, by create a texture of the surface
	gameState->Image = SDL_CreateTextureFromSurface(gameState->rend, imageSurface);

	// Free the surface
	SDL_FreeSurface(imageSurface);

	// initialize the images
	for (int i = 0; i < 100; i++) {
		gameState->image[i].x = rand()%640;
			gameState->image[i].y = rand()%480;
	}
}

int main(int argc, char* argv[]) {

	GameState gameState;

	//Declare a window
	SDL_Window* window = NULL;

	//Declare a renderer
	SDL_Renderer* renderer = NULL;

	// Initialize SDL2
	SDL_Init(SDL_INIT_VIDEO);
	
	// Create a Window with the following settings
	window = SDL_CreateWindow("Firt Game",		// Window title
		SDL_WINDOWPOS_UNDEFINED,                // Iinitalize x position
		SDL_WINDOWPOS_UNDEFINED,				// Iinitalize y position
		WIDTH,									// Set the width in pixels
		HEIGHT,									// Set the heigth in pixels
		0										// Flags
		);

	// Create a new Renderer 
	renderer = SDL_CreateRenderer(window,		// Window that was created above
		-1,										// Index
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  
		// This is using a graphics card to render the output
		// Vsync allows more smoother and faster response, dont need the SDL_Delay();
		);

	gameState.rend = renderer;

	// Load the game using the load function created above

	loadGame(&gameState, argv[1]);
	

	// The window is open, need to Event Loop
	//Create a flag
	int done = 0;

	// Event Loop
	while (!done) {
		// Check of events
		done = processEvents(window, &gameState);

		// Look at function
		doRender(renderer, &gameState);

		// Wait a few sconds before closing, Don't burn up the CPU
		//SDL_Delay(10  MillaSeconds(ms) );
	}

	// Shutdown game and unload all memory
	SDL_DestroyTexture(gameState.Image);

	// Close and destroy the window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	// Memory Allocation
	SDL_Quit();

	return 0;
}