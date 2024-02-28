#include <SDL2/SDL.h>
#include <iostream>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Video failed to load: " << SDL_GetError() << '\n';
        return 1;
    }

    // Create window and renderer
    SDL_Window *window = SDL_CreateWindow("Collision Detection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 720, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Game objects
    SDL_Rect player = {100, 100, 100, 100};
    SDL_Rect obstacle = {462, 334, 100, 100};

    bool gameIsRunning = true;
    while (gameIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
      const Uint8 *state{SDL_GetKeyboardState(NULL)};
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
        gameIsRunning = false;
        std::cout << "Escape key pressed.\n";
      }
        }

        // Move player with mouse
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
  // we do player.h /2 and player.w/2 to move x and yo to wards center instead of top left edge
        player.y = mouseY - player.h / 2;
        player.x = mouseX - player.w / 2;

        // Check for collision
        if (player.x < obstacle.x + obstacle.w &&
            player.x + player.w > obstacle.x &&
            player.y < obstacle.y + obstacle.h &&
            player.y + player.h > obstacle.y) {
            // Collision detected, resolve
            int playerRight = player.x + player.w;
            int playerBottom = player.y + player.h;
            int obstacleRight = obstacle.x + obstacle.w;
            int obstacleBottom = obstacle.y + obstacle.h;

      // Represents the both player and obstacle left and right edge
      // min() -> for right and max()-> for left
            int overlapX = std::min(playerRight, obstacleRight) - std::max(player.x, obstacle.x);
      // Represents the both player and obstacle bottom and top edge
      // min()-> for bottom and max() -> for top
            int overlapY = std::min(playerBottom, obstacleBottom) - std::max(player.y, obstacle.y);


      // Who ever has less distance it is better to push to that axis
            if (overlapX < overlapY) {
                // Resolve X-axis collision
        // This checks if player is moving towards left to right 
                if (playerRight < obstacleRight) {
                    player.x -= overlapX;
                } else {
          // This check if players is moving from right to left
                    player.x += overlapX;
                }
            } else {
             // This checks if the player is moving from bottom to top
if (playerBottom < obstacleBottom) {
    // If the player's bottom edge is below the obstacle's bottom edge:
    // Resolve Y-axis collision by moving the player upwards
    player.y -= overlapY; // Adjust player's y-coordinate to move it away from the obstacle
} else {
    // If the player's bottom edge is above or overlapping with the obstacle's bottom edge:
    // Resolve Y-axis collision by moving the player downwards
    player.y += overlapY; // Adjust player's y-coordinate to move it away from the obstacle
}   // Resolve Y-axis collision
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render objects
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue color for player
        SDL_RenderFillRect(renderer, &player);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red color for obstacle
        SDL_RenderFillRect(renderer, &obstacle);

        // Present renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
