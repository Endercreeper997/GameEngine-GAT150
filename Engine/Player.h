#pragma once
#include "Actor.h"


struct PlayerDesc : public nu::ActorDesc
{
	float speed;

};

class Player : public nu::Actor
{
public:
	Player() = default;
	Player(const PlayerDesc playerDesc) :
		Actor{ playerDesc },
		m_speed{ playerDesc.speed }

	{
	}
	
	CLASS_PROTOTYPE(Player)


	void Update(float dt) override;	
	//void Draw(const nu::Renderer& renderer) const override;
	void OnCollision(Actor* other);

	float GetSpeed() const { return m_speed; }

	void Read(const nu::json::value_t& value) override;

	


private:
	int m_ammo = 0;
	float m_speed = 0.0f;
	bool m_speedBoost = false;
	int m_boostTimer = 300;

};