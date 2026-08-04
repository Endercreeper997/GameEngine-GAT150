#include "Assets.h"
#include "Random.h"
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
    Model playerModel{ std::vector<Mesh>{ playerMesh } };

    Mesh bulletMesh{
    {
      Vector2{ -1, -1 },
      Vector2{ 1, 0 },
      Vector2{ -1, 1 },
      Vector2{ -1, -1 },
    },
    Color{ 1.0f, 0.0f, 0.0f }
    };
    Model bulletModel{ std::vector<Mesh>{ bulletMesh } };

    Mesh enemyMesh{
    {
      Vector2{ -1, -1 },
      Vector2{ 1, 0 },
      Vector2{ -1, 1 },
      Vector2{ -1, -1 },
    },
    Color{ 0.0f, 1.0f, 0.0f }
    };
    Model enemyModel{ std::vector<Mesh>{ enemyMesh } };

    Mesh enemyMesh2{
    {
      Vector2{ -1, -1 },
      Vector2{ 1, 0 },
      Vector2{ -1, 1 },
      Vector2{ -1, -1 },
    },
    Color{ 1.0f, 1.0f, 0.0f }
    };
    Model enemyModel2{ std::vector<Mesh>{ enemyMesh2 } };


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
    Model pickupModel{ std::vector<Mesh>{ pickupMesh } };

}