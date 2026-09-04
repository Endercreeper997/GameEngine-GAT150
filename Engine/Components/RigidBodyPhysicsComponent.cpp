#include "pch.h"
#include "RigidBodyPhysicsComponent.h"
#include "Core/Factory.h"
#include "Framework/Actor.h"


namespace nu
{
	FACTORY_REGISTER(RigidBodyPhysicsComponent)

	void RigidBodyPhysicsComponent::Update(float dt)
	{
	}

	void RigidBodyPhysicsComponent::ApplyForce(const Vector2& force)
	{
	}

	void RigidBodyPhysicsComponent::SetVelocity(const Vector2& velocity)
	{
	}

	Vector2 RigidBodyPhysicsComponent::GetVelocity()
	{
		return Vector2();
	}

	void RigidBodyPhysicsComponent::ApplyTorque(float torque)
	{
		m_angularAcceleration += torque;
	}

	void RigidBodyPhysicsComponent::SetAngularVelocity(float angularVelocity)
	{
		m_angularVelocity = angularVelocity;
	}

	float RigidBodyPhysicsComponent::GetAngularVelocity() const
	{
		return m_angularVelocity;
	}

	void RigidBodyPhysicsComponent::SetPosition(const Vector2& position)
	{
		GetOwner()->SetPosition(position);

	}

	Vector2 RigidBodyPhysicsComponent::GetPosition() const
	{
		return GetOwner()->GetTransform().position;
	}

	void RigidBodyPhysicsComponent::Read(const json::value_t& value)
	{
		PhysicsComponent::Read(value);

		JSON_READ_NAME(value, "velocity", m_velocity);
		JSON_READ_NAME(value, "angular_velocity", m_angularVelocity);
	}

}