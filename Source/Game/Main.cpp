#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

#include <fmod.hpp>
#include <SDL3/SDL.h>
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
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    // initialize objects

    FMOD::Sound* sound = nullptr;
    std::vector<FMOD::Sound*> sounds;
    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
    audio->playSound(sound, 0, false, nullptr);

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
        audio->update();
        input.Update();

        // play drum sounds
        if (input.GetKeyPressed(SDL_SCANCODE_A)) audio->playSound(sounds[0], 0, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_S)) audio->playSound(sounds[1], 0, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_D)) audio->playSound(sounds[2], 0, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_F)) audio->playSound(sounds[3], 0, false, nullptr);
        if (input.GetKeyPressed(SDL_SCANCODE_G)) audio->playSound(sounds[4], 0, false, nullptr);

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

    return 0;
}

