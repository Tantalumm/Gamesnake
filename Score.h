#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>


class Score
{
private:
	std::FILE* fp;
	sf::RenderWindow* window;
	sf::View view;
	sf::Font font;

	std::string name[6];

	char temp[255];
	int score[6];
	std::vector<std::pair<int, std::string>> scorePair;

public:
	Score();
	static bool sortDes(const std::pair<int, std::string>& a,
		const std::pair<int, std::string>& b);
	inline const std::vector<std::pair<int, std::string>> getName() { return scorePair; }
	void clearScore();
	void readFile();
	void writeFile(std::string playerName, int playerScore);
};