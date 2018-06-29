#include "MapFileLoader.h"

void MapFileLoader::LoadLevel(const std::string & filename)
{
	inputStream.open(filename);
	if (!inputStream)
		std::cerr << "Could not open " << filename << std::endl;

	std::string line; // temporary std::string object for reading each line in txt file
	int current_row = 0; // variables for tracking current row and column analyzed by loading process
	int current_column = 0; 

	while (std::getline(inputStream, line))
	{
		for (auto& letter : line) // loop tharough every letter in each line
		{
			if (letter == 'x') // if letter is equal to 'x' it means it's a spawning position of some enemy type 
			{
				m_enemyPositions.push_back(sf::Vector2i(current_column, current_row));
				letter = ' '; // after getting enemy position, reset the current letter to normal state
			}
			++current_column;
		}
		m_levelOneMap.push_back(line); // after processing each letter in line push the whole line to the vector
		++current_row;
		current_column = 0;
	}
	std::cout << "Successfully loaded " << filename << std::endl;
}

std::vector<std::string>& MapFileLoader::GetLevelOneMap()
{
	return m_levelOneMap;
}

std::vector<sf::Vector2i>& MapFileLoader::GetEnemyPositions()
{
	return m_enemyPositions;
}
