#pragma once
#include<memory>
#include<array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"
#include "Snake.h"
#include "Score.h"


class GamePlay : public Engine::State
{
private:
	std::shared_ptr<Context>m_context;
	sf::Sprite m_grass;
	sf::Sprite m_food;
	sf::Sprite m_food2;
	sf::Sprite m_wallblock;
	sf::Sprite m_wallblock1;
	sf::Sprite m_wallblock2;
	sf::Sprite m_wallblock4;
	sf::Sprite m_wallblock5;
	sf::Sprite m_wallblock6;
	sf::Sprite m_wallblock7;
	sf::Sprite m_wallblock8;
	sf::Sprite m_wallblock9;

	std::array<sf::Sprite, 4> m_walls;
	Snake m_snake;

	sf::Vector2f m_snakeDirection;
	sf::Time m_elapsedTime;

	//score
	sf::Text m_scoreText;
	sf::Text m_Hp;

	int m_score;

	Score m_scoreboard;
	int m_hp;

	//bool m_isPaused;



public:
	GamePlay(std::shared_ptr<Context>& context);
	~GamePlay();
	

	void Init()override;
	void ProcessInput()override;
	void Update(sf::Time deltaTime)override;
	void Draw() override;

	//void Pause()override;
	//void Start()override;
};

