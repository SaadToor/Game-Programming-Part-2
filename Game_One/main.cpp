#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_Image.h> 

#include "man.h"
#include "global_variables.h"

int processEvents(SDL_Window* window, Man* man) {
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
		man->x--;
	if (state[SDL_SCANCODE_RIGHT])
		man->x++;
	if (state[SDL_SCANCODE_UP])
		man->y--;
	if (state[SDL_SCANCODE_DOWN])
		man->y++;
	if (state[SDL_SCANCODE_A])
		man->x--;
	if (state[SDL_SCANCODE_D])
		man->x++;
	if (state[SDL_SCANCODE_W])
		man->y--;
	if (state[SDL_SCANCODE_S])
		man->y++;

return done;
}

void doRender(SDL_Renderer* renderer, Man* man) {
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
	SDL_Rect rect = { man->x, man->y, 200, 200 };

	// Draw the filled rectangle
	SDL_RenderFillRect(renderer, &rect);

	// Finished drawing, result will show on the screen
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {

	std::cout << "Hows that?\n\nMy first ever game program\n\nIts not much, but a decent start\n\nI made it so when you"
		<< "press the \nESC button or close at the top right then it will close\n\n" 
		<< "You can move the box with the (wsad) and (UP DOWN LEFT RIGTH) keys\n\n:)\n\n";

	//Declare a window
	SDL_Window* window;

	//Declare a renderer
	SDL_Renderer* renderer;

	// Initialize SDL2
	SDL_Init(SDL_INIT_VIDEO);

	//Declare a man
	Man man;
	man.x = 220;
	man.y = 140;

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
		SDL_RENDERER_ACCELERATED				// This is using a graphics card to render the output
		);

	// The window is open, need to Event Loop
	//Create a flag
	int done = 0;

	// Event Loop
	while (!done) {
		// Check of events
		done = processEvents(window, &man);

		// Look at function
		doRender(renderer, &man);

		// Wait a few sconds before closing, Don't burn up the CPU
		SDL_Delay(100 /* MillaSeconds(ms) */);
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	// Memory Allocation
	SDL_Quit();

	std::cout << "It's Awsome!!!!!!\n\nYEAH\n";
	return 0;
}