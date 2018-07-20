#pragma once

#include "Texture/BlocksInfo.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MapRenderer
{
public:
	MapRenderer();
	void CreateRenderObject(const std::vector<std::string>& textMapFile);
	sf::VertexArray& GetMapObject();
private:
	sf::VertexArray m_mapObject;
};