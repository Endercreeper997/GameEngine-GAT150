#pragma once
#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
    Player* player = m_scene->GetActorByName<Player>("PlayerPrototype");
    if (player)
    {
        
		nu::PhysicsComponent* physicsComponent = GetComponent<nu::PhysicsComponent>();
		if (physicsComponent)
		{
			nu::Vector2 forward{ 1, 0 };
			nu::Vector2 force = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;

			physicsComponent->ApplyForce(force);

			nu::Vector2 direction = player->GetTransform().position - m_transform.position;
			float rotation = direction.Angle();
			physicsComponent->SetRotation(rotation * nu::RadToDeg);
		}
    }



    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
	if (this->GetTag() == "Enemy" || this->GetName() == "EnemyBoss") {
		if (other->GetTag() == "PlayerBullet")
		{
			other->SetDestroyed();

			m_health -= 1.0f;

			if (m_health <= 0) {
				SetDestroyed();
				other->SetDestroyed();

				((SpaceGame*)m_scene->GetGame())->AddPoints(100);

				//add audio for explosion death
				nu::Engine::Get().GetAudio().PlaySound("oof");

				// create particle explosion
				for (int i = 0; i < 100; i++)
				{
					nu::Particle particle;
					particle.position = m_transform.position;
					particle.color = { nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat() };
					particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
					particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

					nu::Engine::Get().GetPS().AddParticle(particle);
				}
			}
		}
	}
}


void Enemy::Read(const nu::json::value_t& value)
{
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);
	//JSON_READ_NAME(value, "points", m_points);
	JSON_READ_NAME(value, "health", m_health);
}