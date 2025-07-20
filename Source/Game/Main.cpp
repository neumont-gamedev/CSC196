#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Framework/Actor.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"

#include "Game/Player.h"

#include "Engine.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {

    // intialize engine
    viper::GetEngine().Initialize();

    viper::Time time;
    
    std::vector<viper::vec2> points{ 
        { -5, -5 },
        {  5, -5 },
        {  5,  5 },
        { -5,  5 },
        { -5, -5 },
    };

    std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(points, viper::vec3{ 0, 0, 1 });

    viper::Scene scene;

    for (int i = 0; i < 10; i++) {
        viper::Transform transform{ viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 }, 0, 10};
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        scene.AddActor(std::move(player));
    }

    // initialize sounds
    viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
    viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
    viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
    viper::GetEngine().GetAudio().AddSound("close-hat.wav", "close-hat");
    viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");

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

        // update engine
        viper::GetEngine().Update();
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        scene.Update(viper::GetEngine().GetTime().GetDeltaTime());

        // play drum sounds
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_A)) viper::GetEngine().GetAudio().PlaySound("bass");
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_S)) viper::GetEngine().GetAudio().PlaySound("snare");
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_D)) viper::GetEngine().GetAudio().PlaySound("clap");
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_F)) viper::GetEngine().GetAudio().PlaySound("close-hat");
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_G)) viper::GetEngine().GetAudio().PlaySound("open-hat");

        // draw
        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();
        
        scene.Draw(viper::GetEngine().GetRenderer());

        viper::vec2 speedz{ -140.0f, 0.0f };
        float length = speedz.Length();

        for (auto& star : stars) {
            star += speedz * time.GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }
        
        viper::GetEngine().GetRenderer().Present();
    }
    
    viper::GetEngine().Shutdown();

    return 0;
}

