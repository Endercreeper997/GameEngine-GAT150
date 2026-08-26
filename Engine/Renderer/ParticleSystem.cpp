#pragma once
#include "pch.h"
#include "ParticleSystem.h"

namespace nu
{
	bool ParticleSystem::Initialize(Renderer& renderer, size_t size)
	{
		// reserve # particles in container
		m_particles.resize(size);
		m_texture = Resources().Get<Texture>("textures/projectile02.png", renderer);

		return true;
	}

	void ParticleSystem::Shutdown()
	{
		// clear all particles
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt)
	{
		// update active particles
		for (auto& particle : m_particles)
		{
			if (!particle.active) continue;

			// reduce particle.lifespan by subtracting delta time
			particle.lifespan -= dt;

			// set active if (particle.lifespan > 0);
			if (particle.lifespan > 0) {
				particle.active;
			}
			else {
				particle.active = false;
			}

			// update position with velocity (multiply by dt)
			//TODO: update position += with particle velocity * delta time
			particle.position += particle.velocity * dt;
		}
	}

	void ParticleSystem::Draw(const Renderer& renderer)
	{
		// draw all active particlee
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				// set particle color and draw point at current position
				renderer.SetColorFloat(particle.color.r, particle.color.g, particle.color.b, 1);
				//renderer.DrawPoint(particle.position.x, particle.position.y);
				renderer.DrawTexture(*m_texture, particle.position.x, particle.position.y, 0.0f, 1.0f);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		// get free particle
		Particle* freeParticle = GetFreeParticle();
		// check if free particle is not nullptr
		if (freeParticle)
		{
			// set free particle object with particle
			*freeParticle = particle;
			// set particle active
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		// find and return inactive particle 
		for (auto& particle : m_particles)
		{
			// return pointer to inactive particle
			if (!particle.active)
				return &particle;
		}

		// no free particles, return nullptr
		return nullptr;
	}

}