#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    // intialize engine systems
    viper::Time time;

    viper::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Viper Engine", 1280, 1024);

    viper::InputSystem input;
    input.Initialize();

    // create audio system
    viper::AudioSystem audio;
    audio.Initialize();

    // initialize sounds
    audio.AddSound("bass.wav", "bass");
    audio.AddSound("snare.wav", "snare");
    audio.AddSound("clap.wav", "clap");
    audio.AddSound("close-hat.wav", "close-hat");
    audio.AddSound("open-hat.wav", "open-hat");

    // create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280 , viper::random::getRandomFloat() * 1024 });
    }
    
    SDL_Event e;
    bool quit = false;

    // MAIN LOOP
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // update engine systems
        audio.Update();
        input.Update();

        // play drum sounds
        if (input.GetKeyPressed(SDL_SCANCODE_A)) audio.PlaySound("bass");
        if (input.GetKeyPressed(SDL_SCANCODE_S)) audio.PlaySound("snare");
        if (input.GetKeyPressed(SDL_SCANCODE_D)) audio.PlaySound("clap");
        if (input.GetKeyPressed(SDL_SCANCODE_F)) audio.PlaySound("close-hat");
        if (input.GetKeyPressed(SDL_SCANCODE_G)) audio.PlaySound("open-hat");

        // draw
        renderer.SetColor(0, 0, 0);
        renderer.Clear();
        
        viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }
        
        renderer.Present();
    }

    renderer.Shutdown();
    audio.Shutdown();

    return 0;
}

