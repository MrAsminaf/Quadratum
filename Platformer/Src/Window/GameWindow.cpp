#include "GameWindow.h"

GameWindow::GameWindow()
	:
	GameWindow(sf::Vector2i(WindowWidth, WindowHeight), "Platformer")
{
	//InitEnemies();
}

GameWindow::GameWindow(const sf::Vector2i& size, const std::string& window_title)
	:
	m_gameWindow(sf::VideoMode(size.x, size.y), window_title),
	m_ui(&m_gameWindow, &m_player.GetPlayerObject()),
	m_player(&m_gameWindow),
	FPS_LIMIT(60),
	TICKS_TO_SKIP(1000 / FPS_LIMIT)
{
	m_mapFileLoader.LoadForeground("foreground_platformer.txt");
	m_mapFileLoader.LoadBackground("background_platformer.txt");
	m_textureManager.LoadTextures("tileset.png", 16);
	m_mapRenderer.InitMapForeground(m_mapFileLoader.GetForeground());
	m_mapRenderer.InitMapBackground(m_mapFileLoader.GetBackground());
}

void GameWindow::RunGameLoop()
{
	int next_tick = m_deltaTimeClock.getElapsedTime().asMilliseconds();
	int sleep_time = 0;
	while (m_gameWindow.isOpen())
	{
		HandleWindowEvents();
		Render();
		Input();
		Update();

		next_tick += TICKS_TO_SKIP;
		sleep_time = next_tick - m_deltaTimeClock.getElapsedTime().asMilliseconds();
		if (sleep_time >= 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
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
	m_gameWindow.clear(sf::Color(41, 41, 41));
	m_gameWindow.draw(m_background);
	m_gameWindow.draw(m_mapRenderer.GetBackgroundObject(), m_textureManager.GetRenderStates());
	m_gameWindow.draw(m_mapRenderer.GetForegroundObject(), m_textureManager.GetRenderStates());
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
	m_player.Update(m_mapFileLoader.GetForeground(), m_deltaTime, m_enemiesList, m_mapFileLoader.GetMapForeground());
	m_background.Update(m_gameWindow, m_player.GetHorizontalVeloity());

	m_camera.GetView().setCenter(m_player.GetPlayerObject().getPosition().x, 16*15);
	m_gameWindow.setView(m_camera.GetView());

	//for (auto& enemy : m_enemiesList)
	//	enemy.Update(m_mapFileLoader.GetForeground());

	m_ui.Update(m_mapFileLoader.GetMapForeground());
}

void GameWindow::InitEnemies()
{
	const auto number_of_enemies = m_mapFileLoader.GetEnemyPositions().size();
	std::cout << "Number of enemies: " << number_of_enemies << std::endl;

	for (const sf::Vector2i& enemy_position : m_mapFileLoader.GetEnemyPositions())
	{
		Enemy enemy_obj(enemy_position);
		m_enemiesList.push_back(enemy_obj);
	};
}
