
#include "Engine.h"
#include "SDL3/SDL.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "fmod.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <memory>
#include <random>
#include <fstream>

//Can use this to not have to type the namespace (like nu or std) every time. 
using namespace nu;


int main()
{




    //INITIALIZATION
    SetWorkingDirectory("assets");
   

    Engine::Get().Initialize();
  

    SpaceGame game;
    game.Initialize();

    //renderer test
    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("textures/Player.png", Engine::Get().GetRenderer());

   


    //handle events
    SDL_Event e;

    


    //MAIN LOOP
    bool quit = false;

    while (!quit) 
    {
        //UPDATE
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        //engine update
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();

        //Game
        game.Update(dt);
        //audio->update();

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            Engine::Get().GetAudio().PlaySound("test");
        }

        //RENDER
        Engine::Get().GetRenderer().SetColorFloat(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();


        game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    }
   
    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;

}

