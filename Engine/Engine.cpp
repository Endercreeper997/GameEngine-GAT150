

#include "pch.h"
#include "framework.h"
#include "Engine.h"

#include <iostream>


namespace nu
{
#pragma once

	bool Engine::Initialize() 
	{
		m_renderer.Initialize("Game Engine", 1280, 1024);
		m_particleSystem.Initialize(5000);
		m_audio.Initialize();
		m_input.Initialize();


		return true;
	}
	void Engine::Shutdown()
	{
		m_input.Shutdown();
		m_audio.Shutdown();
		m_particleSystem.Shutdown();
		m_renderer.Shutdown();
		
	}

	void Engine::Update()
	{
		m_time.Tick();
		m_input.Update();
		m_audio.Update();
		m_particleSystem.Update(m_time.GetDeltaTime());
	}
}