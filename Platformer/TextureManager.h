#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>

class TextureManager
{
public:
	TextureManager() = default;
	void LoadTextures(const std::string& filename, const int size);
	std::vector<sf::Texture>& GetTextures();
	sf::RenderStates& GetRenderStates();

private:
	std::vector<sf::Texture>m_textures;
	sf::Texture m_rawTexture;
	sf::RenderStates m_renderStates;
};