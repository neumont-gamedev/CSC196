#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Game/Actor.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Game/Scene.h"

#include "Game/Player.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {

    // intialize engine systems
    viper::Time time;

    std::unique_ptr<viper::Renderer> renderer = std::make_unique<viper::Renderer>();
    renderer->Initialize();
    renderer->CreateWindow("Viper Engine", 1280, 1024);

    std::unique_ptr<viper::InputSystem> input = std::make_unique<viper::InputSystem>();
    input->Initialize();

    // create audio system
    std::unique_ptr<viper::AudioSystem> audio = std::make_unique<viper::AudioSystem>();
    audio->Initialize();
    
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
    audio->AddSound("bass.wav", "bass");
    audio->AddSound("snare.wav", "snare");
    audio->AddSound("clap.wav", "clap");
    audio->AddSound("close-hat.wav", "close-hat");
    audio->AddSound("open-hat.wav", "open-hat");

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


        if (input->GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // update engine systems
        audio->Update();
        input->Update();

        // play drum sounds
        //if (input.GetKeyPressed(SDL_SCANCODE_A)) audio.PlaySound("bass");
        //if (input.GetKeyPressed(SDL_SCANCODE_S)) audio.PlaySound("snare");
        //if (input.GetKeyPressed(SDL_SCANCODE_D)) audio.PlaySound("clap");
        //if (input.GetKeyPressed(SDL_SCANCODE_F)) audio.PlaySound("close-hat");
        //if (input.GetKeyPressed(SDL_SCANCODE_G)) audio.PlaySound("open-hat");

        //if (input.GetKeyDown(SDL_SCANCODE_A)) transform.rotation -= viper::math::degToRad(90 * time.GetDeltaTime());
        //if (input.GetKeyDown(SDL_SCANCODE_D)) transform.rotation += viper::math::degToRad(90 * time.GetDeltaTime());

        float speed = 200;

        viper::vec2 direction{ 0, 0 };
        if (input->GetKeyDown(SDL_SCANCODE_W)) direction.y = -1; // speed* time.GetDeltaTime();
        if (input->GetKeyDown(SDL_SCANCODE_S)) direction.y =  1; // speed* time.GetDeltaTime();
        if (input->GetKeyDown(SDL_SCANCODE_A)) direction.x = -1; // speed* time.GetDeltaTime();
        if (input->GetKeyDown(SDL_SCANCODE_D)) direction.x =  1; //speed * time.GetDeltaTime();

        if (direction.LengthSqr() > 0) {
            direction = direction.Normalized();
            //for (auto& actor : actors) {
            //    actor->GetTransform().position += (direction * speed) * time.GetDeltaTime();
            //}
            //actor.GetTransform().position += (direction * speed) * time.GetDeltaTime();
        }

        // draw
        viper::vec3 color{ 0, 0, 0 };

        renderer->SetColor(color.r, color.g, color.b);
        renderer->Clear();
        
        //model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10.0f);
        //model.Draw(renderer, transform);
        scene.Draw(*renderer);

        viper::vec2 speedz{ -140.0f, 0.0f };
        float length = speedz.Length();

        for (auto& star : stars) {
            star += speedz * time.GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            renderer->SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer->DrawPoint(star.x, star.y);
        }
        
        renderer->Present();
    }
    
    renderer->Shutdown();
    audio->Shutdown();
    input->Shutdown();

    return 0;
}

