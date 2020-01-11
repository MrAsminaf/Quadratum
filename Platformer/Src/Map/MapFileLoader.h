#pragma once

#include<SFML/Graphics.hpp>
#include<fstream>
#include<vector>
#include<iostream>
#include<string>

#include "../Texture/BlocksInfo.h"

class MapFileLoader
{
public:
	MapFileLoader() = default;
	void LoadForeground(const std::string& foregroundFilename);
	void LoadBackground(const std::string& backgroudFilename);
	std::vector<std::string>& GetForeground();
	std::vector<std::string>& GetBackground();
	std::vector<sf::Vector2i>& GetEnemyPositions();
private:
	bool TryOpenFile(const std::string& filename);
private:
	std::ifstream inputStream;
	std::vector<std::string> m_levelOneForegroundMap;
	std::vector<std::string> m_levelOneBackgroundMap;
	std::vector<sf::Vector2i> m_enemyPositions;
};