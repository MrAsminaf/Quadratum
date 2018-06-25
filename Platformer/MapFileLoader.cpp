#include "MapFileLoader.h"

void MapFileLoader::LoadLevel(const std::string & filename)
{
	inputStream.open(filename);
	if (!inputStream)
		std::cerr << "Could not open " << filename << std::endl;

	std::string line;
	while (std::getline(inputStream, line))
		m_levelOneMap.push_back(line);

	std::cout << "Successfully loaded " << filename << std::endl;
}

std::vector<std::string>& MapFileLoader::GetLevelOneMap()
{
	return m_levelOneMap;
}
