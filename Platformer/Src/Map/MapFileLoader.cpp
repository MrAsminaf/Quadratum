#include "MapFileLoader.h"

void MapFileLoader::LoadForeground(const std::string& foregroundFilename)
{
	if (!TryOpenFile(foregroundFilename))
		return;

	std::string tempLine; // temporary std::string object for reading each line in txt file
	int current_row = 0; // variables for tracking current row and column analyzed by loading process
	int current_column = 0; 
	while (std::getline(inputStream, tempLine))
	{
		for (auto& letter : tempLine) // loop through every letter in each line
		{
			if (letter == 'x') // if letter is equal to 'x' it means it's a spawning position of some enemy type 
			{
				m_enemyPositions.push_back(sf::Vector2i(current_column, current_row));
				letter = ' '; // after getting enemy position, reset the current letter to normal state
			}
			else if (letter != ' ')
			{
				m_maplevelOneForegroundMap.insert(std::make_pair(sf::Vector2i(current_column, current_row), 
					sf::FloatRect(sf::Vector2f(float(current_column), float(current_row)), sf::Vector2f(float(BlocksInfo::blockWidth), float(BlocksInfo::blockHeight)))));
			}
			++current_column;
		}
		m_levelOneForegroundMap.push_back(tempLine); // after processing each letter in line push the whole line to the vector
		++current_row;
		current_column = 0;
	}
	std::cout << "Successfully loaded " << foregroundFilename << std::endl;
	inputStream.close();
}

void MapFileLoader::LoadBackground(const std::string& backgroudFilename)
{
	if (!TryOpenFile(backgroudFilename))
		return;

	std::string tempLine;
	while (std::getline(inputStream, tempLine))
	{
		m_levelOneBackgroundMap.push_back(tempLine);
	}
	std::cout << "Successfully loaded " << backgroudFilename << std::endl;
	inputStream.close();
}

std::unordered_map<sf::Vector2i, sf::FloatRect>& MapFileLoader::GetMapForeground()
{
	return m_maplevelOneForegroundMap;
}

std::vector<std::string>& MapFileLoader::GetForeground()
{
	return m_levelOneForegroundMap;
}

std::vector<std::string>& MapFileLoader::GetBackground()
{
	return m_levelOneBackgroundMap;
}

std::vector<sf::Vector2i>& MapFileLoader::GetEnemyPositions()
{
	return m_enemyPositions;
}

bool MapFileLoader::TryOpenFile(const std::string & filename)
{
	inputStream.open("Maps/" + filename);
	if (!inputStream)
	{
		std::cerr << "Could not open " << filename << std::endl;
		return false;
	}
	else { return true; }
}
