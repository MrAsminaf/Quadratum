#pragma once

#include<SFML/Graphics.hpp>
#include"MapFileLoader.h"
#include"TextureManager.h"
#include"MapRenderer.h"
#include"Player.h"
#include"Camera.h"
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
	void Input();
	void Update();

private:
	sf::RenderWindow m_gameWindow;
	MapFileLoader m_mapFileLoader;
	TextureManager m_textureManager;
	MapRenderer m_mapRenderer;
	Player m_player;
	Camera m_camera;
};