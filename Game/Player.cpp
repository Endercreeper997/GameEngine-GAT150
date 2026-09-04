#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{
    //check for a boost
    if (m_speedBoost) {
        m_speed = 3000.0f;
        m_boostTimer--;
    }
    else {
        m_speed = 800.0f;
    }
    if (m_boostTimer <= 0) {
        m_speedBoost = false;
        m_boostTimer = 100;
    }
    
    //movement
    float thrust = 0.0f;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -40.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 40.f;

    nu::PhysicsComponent* physicsComponent = GetComponent<nu::PhysicsComponent>();
    if (physicsComponent)
    {
        nu::Vector2 forward{ 1, 0 };
        nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
        
        physicsComponent->ApplyForce(velocity);
        physicsComponent->ApplyTorque(rotate);

        nu::Vector2 position = physicsComponent->GetPosition();
        position.x = nu::Wrap(0.0f, 1280.0f, position.x);
        position.y = nu::Wrap(0.0f, 1024.0f, position.y);
        physicsComponent->SetPosition(position);
    }



    //AddVelocity(velocity * dt);

    //particle system
    if (thrust)
    {
        nu::Particle particle;

        nu::Vector2 offset{ -20.0f, 0.0f };
        offset = offset.Rotate(m_transform.rotation * nu::DegToRad);
        particle.position = m_transform.position;

        nu::Color colors[3] = { { 1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 1.0f} };
        particle.color = colors[nu::RandomInt(3)];
        particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
         particle.velocity = nu::Vector2{ nu::RandomFloat( -100.0f, -30.0f), 0.0f}.Rotate((m_transform.rotation + nu::RandomInt(-10, 10)) * nu::DegToRad);

        nu::Engine::Get().GetPS().AddParticle(particle);
    }

    //fire
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
    {
        nu::Engine::Get().GetAudio().PlaySound("duck");

        auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
        bullet->SetTransform(m_transform);
        bullet->SetScale(2.0f);
        bullet->SetTag("PlayerBullet");

        m_scene->AddActor(std::move(bullet));

        //BulletDesc desc;
        //desc.name = "Bullet";
        //desc.tag = "PlayerBullet";
        //desc.texture = nu::Resources().Get<nu::Texture>("textures/missile.png", nu::Engine::Get().GetRenderer());
        //desc.transform = m_transform;
        //desc.transform.scale = 0.8f;
        //desc.damping = 3.0f;
        //desc.speed = 400.0f;
        //desc.lifespan = 1.0f;

        ////create bullet burst
        //m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

        //desc.transform.rotation -= 20.0f;
        //m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

        //desc.transform.rotation += 20.0f;
        //m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));
    }

    //bullet time
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X))
    {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    return;
    if (other->GetTag() == "Enemy" || other->GetName() == "EnemyBoss")
    {
        SetDestroyed();

        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }
    if (other->GetName() == "Pickup")
    {
        other->SetDestroyed();
        m_speedBoost = true;
    }
}

void Player::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}




