#pragma once

#include"State.h"
#include"Game.h"
#include "Score.h"
#include "GamePlay.h"
#include "MainMenu.h"

#include <SFML/Window/Event.hpp>
#include<memory>
#include<SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class GameName : public Engine::State
{
private:
	std::shared_ptr<Context>m_context;
	sf::Text m_gameNameTitle;
	sf::Text m_NextButton;
	sf::Text m_BackButton;
	std::vector<sf::Event> KeyInput;

	bool m_isNextButtonSelected;
	bool m_isNextButtonPressed;

	bool m_isbackkButtonSelected;
	bool m_isbackkButtonPressed;

	sf::RenderWindow* window;


	int m_score;
	Score m_scoreboard;

	sf::Text name;
	sf::Text cursor;
	sf::Sprite m_BGname;

	int states;
	int events;


public:
	GameName(std::shared_ptr<Context>& Context);
	~GameName();
	
	void nameUpdate();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};
