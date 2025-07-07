#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Renderer/Renderer.h"

#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    viper::Renderer renderer;

    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    vec2 v(30, 40);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        renderer.Clear();
        
        for (int i = 0; i < 100; i++) {
            //renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            //renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);



            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(v.x, v.y);
            //renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
        }
        
        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}

