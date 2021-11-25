#pragma once
#include "State.h"
#include "Game.h"
#include"GamePlay.h"

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "Score.h"

class GameScore : public Engine::State
{
private:
	std::shared_ptr<Context>m_context;
	sf::Text m_scoreTitle;
	sf::Text m_backButton;
	sf::Text n;

	sf::Text m_showScore[5];
	sf::Text m_showName[5];


	int playerScore;

	bool m_isBackButtonSelected;
	bool m_isBackButtonPressed;

	Score m_scoreboard;
public:
	GameScore(std::shared_ptr<Context>& context);
	~GameScore();

	inline void setScore(int score) { playerScore = score; }

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};
