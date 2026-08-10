
#include "SpaceGame.h"
#include "Engine.h"
#include "Assets.h"
#include "Player.h"
#include "Enemy.h"

#include <memory>


using namespace nu;

bool SpaceGame::Initialize()
{
	Game::Initialize();

	m_scene = new Scene();
	m_scene->SetGame(this);

	m_titleText = new Text(Resources().GetWithID<Font>("Game Font", "fonts/BreatheFireIii-PKLOB.ttf", 64));
	m_titleText->Create(Engine::Get().GetRenderer(), "Super Space Game 2", Color{ 1, 0, 1 });

	//m_gameFont = std::make_shared<Font>();
	//m_gameFont->Load("fonts/BreatheFireIii-PKLOB.ttf", 32);

	m_scoreText = new Text(Resources().Get<Font>("fonts/BreatheFireIii-PKLOB.ttf", 64));
	m_livesText = new Text(Resources().Get<Font>("fonts/BreatheFireIii-PKLOB.ttf", 64));
	
	Engine::Get().GetAudio().AddSound("test", "test.wav");
	Engine::Get().GetAudio().AddSound("duck", "duck-toy.mp3");
	Engine::Get().GetAudio().AddSound("oof", "oof.mp3");
	Engine::Get().GetAudio().AddSound("music", "gameMusic.mp3");
	Engine::Get().GetAudio().PlaySound("music");

	return true;
}



void SpaceGame::Update(float dt)
{
	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_gameState = GameState::StartGame;
		}
		break;
	case SpaceGame::GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_gameState = GameState::StartLevel;
		break;
	case SpaceGame::GameState::StartLevel:
	{
		m_spawnTimer = m_spawnTime;
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_gameState = GameState::Title;

			m_scene->RemoveAllActors();
			SpawnPlayer();
			m_spawnTime = 5.0f;
			m_pickupTime = 15.0f;
			m_gameState = GameState::Game;
		}
		break;
	}
	case SpaceGame::GameState::Game:
		
		m_spawnTimer -= dt;
		m_pickupTimer -= dt;
		if (m_spawnTimer <= 0.0f)
		{
			SpawnEnemy();
			m_spawnTimer = m_spawnTime;
		}
		if (m_pickupTimer <= 0.0f)
		{
			SpawnSpeedPickup();
			m_pickupTimer = m_pickupTime;
		}

		break;
	case SpaceGame::GameState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_gameState = GameState::Title;
			m_scene->RemoveAllActors();
		}
		break;
	default:
		break;

	}

	Game::Update(dt);
}
void SpaceGame::Draw(nu::Renderer& renderer)
{
	renderer.DrawTexture(*nu::Resources().Get<Texture>("textures/background.png", Engine::Get().GetRenderer()), 500, 500, 0.0f, 5.0f);
	
	m_scene->Draw(renderer);

	switch (m_gameState)
	{
	case SpaceGame::GameState::Title:
		//draw title
		m_titleText->Draw(renderer, 400, 400);
		break;
	case SpaceGame::GameState::StartGame:
		
		break;
	case SpaceGame::GameState::StartLevel:
	
		break;
	break;
	case SpaceGame::GameState::Game:
		//draw score / lives
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 20, 30);

		m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, 700, 30);

		
		break;
	case SpaceGame::GameState::GameOver:
		
		break;
	default:
		break;

	}
}

void SpaceGame::OnPlayerDead()
{
	m_lives--;
	if (m_lives <= 0) m_gameState = GameState::GameOver;
	else m_gameState = GameState::StartLevel;

}

void SpaceGame::SpawnPlayer()
{
	
	PlayerDesc playerDesc;
	playerDesc.name = "Player";
	//playerDesc.model = Assets::playerModel;
	playerDesc.texture = Resources().Get<Texture>("textures/Player.png", Engine::Get().GetRenderer());
	playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 0.2f };
	playerDesc.velocity = Vector2{ 0.0f, 0.0f };
	playerDesc.damping = 3.0f;
	playerDesc.speed = 2500.0f;

	std::unique_ptr<Player> player = std::make_unique<Player>( playerDesc );
	m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy()
{
	//boss spawning logic
	int enemyIndex = 0;

	if (m_enemiesSpawned < m_bossMarker)
	{
		enemyIndex = 0;
		m_enemiesSpawned++;
	}
	else {
		enemyIndex = 1;
		m_enemiesSpawned = 0;
	}
	

	if (enemyIndex == 0) {
		EnemyDesc enemyDesc;
		enemyDesc.name = "Enemy";
		//enemyDesc.model = Assets::enemyModel;
		enemyDesc.texture = Resources().Get<Texture>("textures/Enemy1.png", Engine::Get().GetRenderer());
		enemyDesc.transform = Transform{ Vector2{ RandomFloat(0, 1000.0f), RandomFloat(0, 800.f) }, 0.0f, 0.15f};
		enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
		enemyDesc.damping = 3.0f;
		enemyDesc.speed = 600.0f;

		m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
	}
	else if (enemyIndex == 1) {
		EnemyDesc enemyDesc2;
		enemyDesc2.name = "EnemyBoss";
		//enemyDesc2.model = Assets::enemyModel2;
		enemyDesc2.texture = Resources().Get<Texture>("textures/EnemyBoss.png", Engine::Get().GetRenderer());
		enemyDesc2.health = 7.0f;
		enemyDesc2.transform = Transform{ Vector2{ RandomFloat(0, 1000.0f), RandomFloat(0, 800.f) }, 0.0f, 0.30f };
		enemyDesc2.velocity = Vector2{ 0.0f, 0.0f };
		enemyDesc2.damping = 3.0f;
		enemyDesc2.speed = 700.0f;

		m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc2)));
	}
}


void SpaceGame::SpawnSpeedPickup()
{

	EnemyDesc pickupDesc;
	pickupDesc.name = "Pickup";
	//pickupDesc.model = Assets::pickupModel;
	pickupDesc.texture = Resources().Get<Texture>("textures/projectile02.png", Engine::Get().GetRenderer());
	pickupDesc.transform = Transform{ Vector2{ RandomFloat(0, 1000.0f), RandomFloat(0, 800.f) }, 0.0f, 1.4f };
	pickupDesc.velocity = Vector2{ 0.0f, 0.0f };
	pickupDesc.damping = 3.0f;
	pickupDesc.speed = 1200.0f;

	m_scene->AddActor(std::move(std::make_unique<Enemy>(pickupDesc)));
}