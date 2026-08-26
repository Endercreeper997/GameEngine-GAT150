#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Resources/ResourceManager.h"

class SpaceGame : public nu::Game
{
public:
	enum class GameState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver
	};

public:
	SpaceGame() = default;
	SpaceGame(nu::Scene* scene) :
		nu::Game{ scene }
	{ }

	bool Initialize() override;

	void Update(float dt) override;
	void Draw(class nu::Renderer& renderer) override;


	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }

private:
	void SpawnPlayer();
	void SpawnEnemy();
	void SpawnSpeedPickup();


private:
	int m_score{ 0 };
	int m_lives{ 0 };

	float m_spawnTimer = 0.0f;
	float m_spawnTime = 0.0f;
	float m_pickupTimer = 0.0f;
	float m_pickupTime = 0.0f;

	float m_stateTimer = 0.0f;

	int m_bossMarker = 3;
	int m_enemiesSpawned = 0;
	
	
	GameState m_gameState = GameState::Title;

	nu::res_t<nu::Font> m_titleFont;
	nu::res_t<nu::Font> m_gameFont;

	class nu::Text* m_titleText{ nullptr };

	class nu::Font* m_mediumFont{ nullptr };
	class nu::Text* m_gameOverText{ nullptr };


	class nu::Text* m_scoreText{ nullptr };
	class nu::Text* m_livesText{ nullptr };

};