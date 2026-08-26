#pragma once

#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Math/MathUtils.h"
#include "Core/StringUtils.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"
#include "Serialization/Json.h"

#include "Core/Factory.h"
#include "Physics/Physics.h"

//Systems
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Core/GameTime.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/ParticleSystem.h"
#include "fmod.hpp"
#include "Core/File.h"
#include "Audio/Audio.h"



#define ENGINE			Engine::Get()



namespace nu
{
	class Engine
	{
	public:

		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particleSystem; }

		Physics& GetPhysics() { return m_physics; }

		Audio& GetAudio() { return m_audio; }



	private:
		Engine() = default;

	private:
		Input m_input;
		Renderer m_renderer;
		ParticleSystem m_particleSystem;
		Audio m_audio;
		Physics m_physics;

		Time m_time;
	};

}