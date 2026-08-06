
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

//Can use this to not have to type the namespace (like nu or std) every time. 
using namespace nu;


class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }


    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }

};

uint32_t seed = 1234;

uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main()
{
    //rand && srand
    for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    std::cout << std::endl;
    
    seed = 1234;
    for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    std::cout << std::endl;
    

    //srand((unsigned int)time(NULL));
    SeedRandom((unsigned int)time(NULL));
    for (size_t i = 0; i < 10; i++) std::cout << rand() << " ";
    std::cout << std::endl;
    
    //random<>
    std::random_device randomDevice;
    std::cout << randomDevice.min() << std::endl;
    std::cout << randomDevice.max() << std::endl;
    std::cout << randomDevice.entropy() << std::endl;

    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<> dist(0, 20);
    for (size_t i = 0; i < 10; i++) std::cout << dist(generator) << " ";
    std::cout << std::endl; 


    std::uniform_real_distribution<float> distReal(-10.f, 20.0f);
    for (size_t i = 0; i < 10; i++) std::cout << distReal(generator) << " ";


    std::cout << "====================object=====================\n";
    {
        Object objectA;
        Object objectB = objectA;
        Object objectC;
        objectC = objectA;
    }
    std::cout << "====================raw pointers=====================\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;


        delete objectA;
        delete objectB;
        //delete objectC;
    }
    std::cout << "====================smart pointers=====================\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;

        objectB.reset();
    }

    std::cout << "====================shared pointers=====================\n";
    std::shared_ptr<Object> objectC;
    {
        auto objectA = std::make_shared<Object>();
        std::cout << objectA.get() << std::endl;
        std::cout << objectA.use_count() << std::endl;
        auto objectB = objectA;
        std::cout << objectB.get() << std::endl;
        std::cout << objectB.use_count() << std::endl;
        objectC = objectA;
        std::cout << objectC.get() << std::endl;
        std::cout << objectC.use_count() << std::endl;

    }
    std::cout << objectC.get() << std::endl;

    


    //return 0;

    //File Testing
    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt\n", "Hello, World!\n", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }
    


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

        //draw texture
        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("textures/Player.png", Engine::Get().GetRenderer()), 30, 30, 0.0f, 1.0f);

        game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    }
   
    //SHUTDOWN
    Engine::Get().Shutdown();

    return 0;

}

