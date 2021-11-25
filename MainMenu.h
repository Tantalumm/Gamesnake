#pragma once

#include"State.h"
#include"Game.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include<array>
#include<memory>

#define MAX_ITEMS 3

class MainMenu : public Engine::State
{
private:
	std::shared_ptr<Context>m_context;
	sf::Text m_gameTitle;
	sf::Text m_playButton;
	sf::Text m_exitButton;
	sf::Text m_scoreButton;
	sf::Text m_myname;
	sf::Text m_mynum;
	sf::Sprite m_bg;


	bool m_isPlayButtonSelected;
	bool m_isPlayButtonPressed;

	bool m_isScoreButtonSelected;
	bool m_isScoreButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;
	


public:
	MainMenu(std::shared_ptr<Context>& Context);
	~MainMenu();



	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

	
};
