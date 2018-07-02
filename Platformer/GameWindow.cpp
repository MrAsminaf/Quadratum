#include "GameWindow.h"

GameWindow::GameWindow()
	:
	GameWindow(sf::Vector2i(WindowWidth, WindowHeight), "Platformer")
{
	InitEnemies();
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
		//sf::Time delta_time = m_deltaTimeClock.restart();

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

	for (auto& enemy : m_enemiesList)
		m_gameWindow.draw(enemy.GetObject());

	m_gameWindow.draw(m_ui);

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

	m_camera.GetView().setCenter(m_player.GetPlayerObject().getPosition().x, 16*15);
	m_gameWindow.setView(m_camera.GetView());

	for (auto& enemy : m_enemiesList)
		enemy.Update(m_mapFileLoader.GetLevelOneMap());

	m_ui.Update(m_gameWindow);
}

void GameWindow::InitEnemies()
{
	const auto number_of_enemies = m_mapFileLoader.GetEnemyPositions().size();
	std::cout << "Number of enemies: " << number_of_enemies << std::endl;

	for (const sf::Vector2i& enemy_position : m_mapFileLoader.GetEnemyPositions())
	{
		Enemy enemy_obj(enemy_position);
		m_enemiesList.push_back(enemy_obj);
		std::cout << enemy_position.x  << " " << enemy_position.y << std::endl;
	};
}
