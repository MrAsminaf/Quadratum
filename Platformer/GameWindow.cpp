#include "GameWindow.h"

GameWindow::GameWindow()
	:
	GameWindow(sf::Vector2i(1200, 700), "Platformer")
{
}

GameWindow::GameWindow(const sf::Vector2i& size, const std::string & window_title)
	:
	m_gameWindow(sf::VideoMode(size.x, size.y), window_title)
{
	m_mapFileLoader.LoadLevel("platformer.txt");
	m_textureManager.LoadTextures("tileset.png", 16);
	m_mapRenderer.CreateRenderObject(m_mapFileLoader.GetLevelOneMap());
}

void GameWindow::RunGameLoop()
{
	while (m_gameWindow.isOpen())
	{
		HandleWindowEvents();
		Render();
		Input();
		Update();
	}
}

void GameWindow::HandleWindowEvents()
{
	sf::Event event;
	while (m_gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_gameWindow.close();
	}
}

void GameWindow::Render()
{
	m_gameWindow.clear();
	m_gameWindow.draw(m_mapRenderer.GetMapObject(), m_textureManager.GetRenderStates());
	m_gameWindow.draw(m_player);
	m_gameWindow.display();
}

void GameWindow::Input()
{
	m_player.Controls();
}

void GameWindow::Update()
{
	m_player.UpdateGravity();
	m_player.Collision(m_mapFileLoader.GetLevelOneMap());

	m_camera.GetView().setCenter(m_player.GetPlayerObject().getPosition().x, 16*16+8);
	m_gameWindow.setView(m_camera.GetView());
}
