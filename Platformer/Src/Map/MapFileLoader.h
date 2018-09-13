#pragma once

#include<SFML/Graphics.hpp>
#include<fstream>
#include<vector>
#include<iostream>
#include<string>

#include <Texture/BlocksInfo.h>

class MapFileLoader
{
public:
	MapFileLoader() = default;
	void LoadLevel(const std::string& filename);
	std::vector<std::string>& GetLevelOneMap();
	std::vector<sf::Vector2i>& GetEnemyPositions();

private:
	std::ifstream inputStream;
	std::vector<std::string> m_levelOneMap;
	std::vector<sf::Vector2i> m_enemyPositions;
};