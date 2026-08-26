#include "Assets.h"
#include "Core/Random.h"
using namespace nu;

namespace Assets
{
    Mesh playerMesh{ 
        {
        // Connected Lines
        { 2, 2 },
        { 5, 0 },
        { 2, -2 },
        { -3, -4 },
        { -3, -3 },
        { 1, -1 },
        { -3, 0 },
        { 1, 1 },
        { -3, 3 },
        { -3, 4 },
        { 2, 2 },
            },
            Color{ 0.0f, 0.0f, 1.0f } 
    };
    std::shared_ptr<Model> playerModel = std::make_shared<Model>( std::vector<Mesh>{ playerMesh } );

    Mesh bulletMesh{
    {
      Vector2{ -1, -1 },
      Vector2{ 1, 0 },
      Vector2{ -1, 1 },
      Vector2{ -1, -1 },
    },
    Color{ 1.0f, 0.0f, 0.0f }
    };
    std::shared_ptr<Model> bulletModel = std::make_shared<Model>(std::vector<Mesh>{ bulletMesh });

    Mesh enemyMesh{
    {
      Vector2{ -1, -1 },
      Vector2{ 1, 0 },
      Vector2{ -1, 1 },
      Vector2{ -1, -1 },
    },
    Color{ 0.0f, 1.0f, 0.0f }
    };
    std::shared_ptr<Model> enemyModel = std::make_shared<Model>(std::vector<Mesh>{ enemyMesh });

    Mesh enemyMesh2{
    {
      Vector2{ -1, -1 },
      Vector2{ 1, 0 },
      Vector2{ -1, 1 },
      Vector2{ -1, -1 },
    },
    Color{ 1.0f, 1.0f, 0.0f }
    };
    std::shared_ptr<Model> enemyModel2 = std::make_shared<Model>(std::vector<Mesh>{ enemyMesh2 });


    Mesh pickupMesh{
       {
            // Connected Lines
            { 2, 2 },
            { 5, 0 },
            { 2, -2 },
            { -3, -4 },
            { -3, -3 },
            { 1, -1 },
            { -3, 0 },
            { 1, 1 },
            { -3, 3 },
            { -3, 4 },
            { 2, 2 },
                },
                Color{ nu::RandomFloat(1.0f), nu::RandomFloat(1.0f), nu::RandomFloat(1.0f)}
    };
    std::shared_ptr<Model> pickupModel = std::make_shared<Model>(std::vector<Mesh>{ pickupMesh });

}