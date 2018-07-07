#pragma once

#include<SFML/Graphics.hpp>
#include"Window_info.h"
#include"MapFileLoader.h"
#include"TerrainTextureManager.h"
#include"MapRenderer.h"
#include"Player.h"
#include"Camera.h"
#include"Enemy.h"
#include"UI.h"
#include<vector>
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
	sf::Time m_deltaTime;
	std::vector<Enemy> m_enemiesList;
};