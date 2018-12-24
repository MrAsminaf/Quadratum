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
		for (auto& letter : tempLine) // loop tharough every letter in each line
		{
			if (letter == 'x') // if letter is equal to 'x' it means it's a spawning position of some enemy type 
			{
				m_enemyPositions.push_back(sf::Vector2i(current_column, current_row));
				letter = ' '; // after getting enemy position, reset the current letter to normal state
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

void MapFileLoader::LoadBackground(const std::string & backgroudFilename)
{
	if (!TryOpenFile(backgroudFilename))
		return;

	std::string tempLine;
	int current_row = 0;
	int current_column = 0;
	while (std::getline(inputStream, tempLine))
	{
		for (auto& letter : tempLine)
			m_levelOneBackgroundMap.push_back(tempLine);
	}
	std::cout << "Successfully loaded " << backgroudFilename << std::endl;
	inputStream.close();

}

std::vector<std::string>& MapFileLoader::GetLevelOneMap()
{
	return m_levelOneForegroundMap;
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
