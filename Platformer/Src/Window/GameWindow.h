#pragma once

#include <SFML/Graphics.hpp>
#include "Window_info.h"
#include "../Map/MapFileLoader.h"
#include "../Texture/TerrainTextureManager.h"
#include "../Map/MapRenderer.h"
#include "../Player/Player.h"
#include "../GUI/Camera.h"
#include "../Enemies/Enemy.h"
#include "../GUI/UI.h"
#include "../Background/Background.h"
#include <vector>
#define DEBUG

class GameWindow
{
public:
	GameWindow();
	GameWindow(const sf::Vector2i& size, const std::string& window_title);
	void RunGameLoop();

private:
	void HandleWindowEvents();
	void Render();
	void Input(const sf::Time& delta_time);
	void Update();
	void InitEnemies();

private:
	sf::RenderWindow m_gameWindow;
	sf::Clock m_deltaTimeClock;
	MapFileLoader m_mapFileLoader;
	TerrainTextureManager m_textureManager;
	MapRenderer m_mapRenderer;
	Player m_player;
	Camera m_camera;
	UI m_ui;
	Background m_background;
	sf::Time m_deltaTime;
	std::vector<Enemy> m_enemiesList;
};