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

private:
	std::vector<sf::Texture>m_textures;
};