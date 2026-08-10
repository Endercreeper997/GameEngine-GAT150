
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
    {

        //read file (input file)
        std::ifstream file("data/text.txt");
        if (file.is_open()) 
        {
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
        }
        else
        {
            std::cout << "couldnt load de ting: data/text.txt\n" << std::endl;

        }
        file.close();
    }

    {
        //write file (output file)
        std::ofstream file("data/text.txt", std::ios::app);
        if (file.is_open())
        {
            file << "hajve a gooud dayy. \n";
        }
    }

    {
        // read / write (input / output file)
        std::fstream file("data/text.txt", std::ios::in | std::ios::out | std::ios::app);
        if (file.is_open())
        {
            //input
            file << "add de line. \n";
            file.seekg(0);
            //output
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
        }
    }

    {
        std::string name;
        int score;
        bool isAlive;

        bool save = true;
        if (save)
        {
            name = "Mr Cheese";
            score = 1234;
            isAlive = true;

            //save game data
            std::fstream file("data/game.txt", std::ios::in | std::ios::out | std::ios::app);
            if (file.is_open())
            {
                file << name << "\n";
                file << score << "\n";
                file << isAlive << "\n";

            }
        }

        // load game data
        bool load = true;
        if (load)
        {
            // read file (input file)
            std::ifstream file("data/game.txt");
            if (file.is_open())
            {
                std::getline(file, name);

                std::string str;
                std::getline(file, str);

                score = std::stoi(str);
                //file >> score;
                file >> std::boolalpha >> isAlive;

            }
        }

        //display game data
        std::cout << name << std::endl;
        std::cout << score << std::endl;
        std::cout << isAlive << std::endl;
    }

    return 0;






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

