
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

//class Animal
//{
//public:
//    virtual void speak() { std::cout << "???"; }
//};
//
//class Cat : public Animal
//{
//    void speak() override { std::cout << "meow"; }
//
//};
//class Dog : public Animal
//{
//    void speak() override { std::cout << "woof"; }
//
//};
//class Bird : public Animal
//{
//    void speak() override { std::cout << "chirp"; }
//
//};
/*
enum class Type
{
    Cat = 1,
    Dog,
    Bird
};

Animal* AnimalFactory(Type id)
{
    Animal* animal = nullptr;

    switch (id)
    {
    case Type::Cat: 
        animal = new Cat;
        break;
    case Type::Dog:
        animal = new Dog;
        break;
    case Type::Bird:
        animal = new Bird;
        break;
    }

    return animal;
}*/

//Animal* AnimalFactory(const std::string& id)
//{
//    Animal* animal = nullptr;
//
//    if (nu::ToLower(id) == "cat") animal = new Cat;
//    else if (nu::EqualsIgnoreCase(id, "Dog")) animal = new Dog;
//    else if (id == "bird") animal = new Bird;
//
//    return animal;
//};

/*
class ICreator
{
public:
    virtual ~ICreator() = default;
    virtual std::unique_ptr<Animal> Create() = 0;
};

template <typename T>
class Creator : public ICreator
{
public:
    std::unique_ptr<Animal> Create() override { return std::make_unique<T>(); }
};

std::map<std::string, std::unique_ptr<ICreator>> registry;
*/

int main()
{
  /*  Factory::Instance().Register<Actor>("Actor");
    auto actor = Factory::Instance().Create("Actor");
    std::cout << actor->IsActive() << std::endl;*/



   /* registry["Cat"] = std::make_unique<Creator<Cat>>();
    registry["Dog"] = std::make_unique <Creator<Dog>>();

    {
        auto animal = registry["Cat"]->Create();
        auto animal2 = registry["Dog"]->Create();
        animal->speak();
        animal2->speak();
    }*/


   /* int selection;
    std::cout << "Select Animal: ";
    std::cin >> selection;

    auto animal = AnimalFactory(1);
    animal->speak();*/

    //return 0;

    //INITIALIZATION
    SetWorkingDirectory("assets");


    // Jsoning
    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("data/data.json", document))
        {
            // read/show the data from the json file
            std::string name;
            int age;
            float speed;
            bool isAwake;
            nu::Vector2 position;
            nu::Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;


        }
    }









   

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

