#pragma once

#include<fstream>
#include<vector>
#include<iostream>
#include<string>

class MapFileLoader
{
public:
	MapFileLoader() = default;
	void LoadLevel(const std::string& filename);
	std::vector<std::string>& GetLevelOneMap();

private:
	std::ifstream inputStream;
	std::vector<std::string> m_levelOneMap;
};