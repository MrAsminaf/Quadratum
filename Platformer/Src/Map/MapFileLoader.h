#pragma once

#include "../Texture/BlocksInfo.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

namespace std
{
	template <class T>
	struct hash<sf::Vector2<T>>
	{
		std::size_t operator()(const sf::Vector2<T>& v) const
		{
			using std::hash;

			// Compute individual hash values for first
			// and second. Combine them using the Boost-func

			std::size_t tmp0 = hash<T>()(v.x);
			std::size_t tmp1 = hash<T>()(v.y);

			tmp0 ^= tmp1 + 0x9e3779b9 + (tmp0 << 6) + (tmp0 >> 2);
			return tmp0;
		}
	};
}

class MapFileLoader
{
public:
	MapFileLoader() = default;
	void LoadForeground(const std::string& foregroundFilename);
	void LoadBackground(const std::string& backgroudFilename);
	std::unordered_map<sf::Vector2i, sf::FloatRect>& GetMapForeground();
	std::vector<std::string>& GetForeground();
	std::vector<std::string>& GetBackground();
	std::vector<sf::Vector2i>& GetEnemyPositions();
private:
	bool TryOpenFile(const std::string& filename);
private:
	std::ifstream inputStream;
	std::unordered_map<sf::Vector2i, sf::FloatRect> m_maplevelOneForegroundMap;
	std::vector<std::string> m_levelOneForegroundMap;
	std::vector<std::string> m_levelOneBackgroundMap;
	std::vector<sf::Vector2i> m_enemyPositions;
};