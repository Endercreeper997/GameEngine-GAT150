#pragma once
#include "Framework/Actor.h"
#include "Serialization/Json.h"

struct BulletDesc : public nu::ActorDesc
{
	float speed;
};

class Bullet : public nu::Actor
{
public:
	Bullet() = default;
	Bullet(const BulletDesc& BulletDesc) :
		Actor{ BulletDesc },
		m_speed{ BulletDesc.speed }
	{
	}
	
	CLASS_PROTOTYPE(Bullet)

	

	void Update(float dt) override;

	void Read(const nu::json::value_t& value);



private:
	float m_speed = 800.0f;
};