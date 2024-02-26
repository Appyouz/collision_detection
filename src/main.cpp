#include <SDL2/SDL.h>
#include <iostream>

int main() {
  SDL_Window *window{nullptr};
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Video failed to load." << SDL_GetError() << '\n';
  } else {
    std::cout << "SDL Video is ready to go.\n";
  }

  window =
      SDL_CreateWindow("Collison Detection", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1024, 720, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer{nullptr};
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Rect player{100, 100, 100, 100};
  // Draws at center
  SDL_Rect obstacle{462, 334, 100, 100};

  bool gameIsRunning{true};
  while (gameIsRunning) {
    SDL_Event event;


    // Get mouse state x and y position
    int mouseX{};
    int mouseY{};
    Uint32 buttons {SDL_GetMouseState(&mouseX, &mouseY)};

    // start event loop
    while (SDL_PollEvent(&event)) {
      const Uint8 *state{SDL_GetKeyboardState(NULL)};
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        gameIsRunning = false;
        std::cout << "Escape key pressed.\n";
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Do drawing here
    //
    // Draw player
    SDL_SetRenderDrawColor(renderer, 0, 0, 139, 255);
    player.x = mouseX;
    player.y = mouseY;
    SDL_RenderFillRect(renderer, &player);


    // Draw obstacle
    SDL_SetRenderDrawColor(renderer, 139,0,0,255);
    SDL_RenderFillRect(renderer, &obstacle);

    SDL_RenderPresent(renderer);
  }

  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
