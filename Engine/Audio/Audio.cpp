#pragma once
#include "pch.h"
#include "Audio.h"

#include <fmod_errors.h>

bool nu::Audio::Initialize()
{
	FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
	if (!CheckFMODResult(result))
		return false;

	void* extradriverdata = nullptr;
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (!CheckFMODResult(result))
		return false;

	return true;
}

void nu::Audio::Shutdown()
{
	CheckFMODResult(m_fmodSystem->release());
}

void nu::Audio::Update()
{
	CheckFMODResult(m_fmodSystem->update());
}

bool nu::Audio::AddSound(const std::string& name, const std::string& filename)
{
	// check if key exists in sounds map
	if (m_sounds.contains(name))
	{
		std::cerr << "Audio System : name already exists " << name << std::endl;
		return false;
	}

	// create sound from key
	FMOD::Sound* sound = nullptr;
	FMOD_RESULT result = m_fmodSystem->createSound(filename.data(), FMOD_DEFAULT, nullptr, &sound);
	if (!CheckFMODResult(result))
		return false;

	// insert sound into map
	//TODO: add sound to m_sounds using name as key
	m_sounds[name] = sound;

	return true;
}


bool nu::Audio::PlaySound(const std::string& name)
{
	// check if sound exists in sounds map
	if (!m_sounds.contains(name))
	{
		std::cerr << "Audio System : name doesn't exist " << name << std::endl;
		return false;
	}

	// play sound from key
	FMOD_RESULT result = m_fmodSystem->playSound(m_sounds.at(name), 0, false, nullptr);
	if (!CheckFMODResult(result))
		return false;

	return true;
}

bool nu::Audio::CheckFMODResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cerr << FMOD_ErrorString(result) << std::endl;
		return false;
	}

	return true;
}

