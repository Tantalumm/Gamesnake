#include "GameScore.h"
#include "MainMenu.h"
#include "GamePlay.h"
#include "Score.h"
#include <SFML/Window/Event.hpp>

using namespace std;
GameScore::GameScore(std::shared_ptr<Context>& context)
	:m_context(context)
{
}

GameScore::~GameScore()
{

}

void GameScore::Init()//setpositon & string
{
	m_context->m_assets->AddFont(MAIN_FONT, "Pacifico-Regular.ttf");

	//Title
	m_scoreTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_scoreTitle.setString("Score");
	m_scoreTitle.setOrigin(m_scoreTitle.getLocalBounds().width / 2,
		m_scoreTitle.getLocalBounds().height / 2);
	m_scoreTitle.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2-300.f);

	m_backButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_backButton.setString("back");
	m_backButton.setOrigin(m_backButton.getLocalBounds().width / 2,
		m_backButton.getLocalBounds().height / 2);
	m_backButton.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 + 300.f);
	m_backButton.setCharacterSize(20);

	



	m_scoreboard.readFile();
	for (int i = 0; i < 5; i++)
	{
		m_showName[i].setCharacterSize(36);
		m_showName[i].setFillColor(sf::Color::White);
		m_showName[i].setFont(m_context->m_assets->GetFont(MAIN_FONT));
		m_showName[i].setString(m_scoreboard.getName()[i].second);

		m_showScore[i].setCharacterSize(36);
		m_showScore[i].setFillColor(sf::Color::White);
		m_showScore[i].setFont(m_context->m_assets->GetFont(MAIN_FONT));
		m_showScore[i].setString(std::to_string(m_scoreboard.getName()[i].first));

		m_showName[i].setPosition(m_context->m_window->getSize().x / 2 - 300.f, m_context->m_window->getSize().y / 2 - 180 + i * 50);
		m_showScore[i].setPosition(m_context->m_window->getSize().x / 2 + 200.f, m_context->m_window->getSize().y / 2 - 180 + i * 50);
	}
	m_scoreboard.clearScore();

	

}

void GameScore::ProcessInput() //keyborad
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Down:
			{
				if (!m_isBackButtonSelected)
				{
					m_isBackButtonSelected = true;
				}
				break;
			case sf::Keyboard::Return:
			{
				m_isBackButtonPressed = false;
				if (m_isBackButtonSelected)
				{
					m_isBackButtonPressed = true;
				}
			}
			default:
				break;
			}
			}


		}

	}
}

void GameScore::Update(sf::Time deltaTime)//update time to time
{
	if (m_isBackButtonSelected)
	{
		m_backButton.setFillColor(sf::Color::Yellow);
	}
	if (m_isBackButtonPressed)
	{
		m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
	}
}



void GameScore::Draw() //draw something
{
	m_context->m_window->clear(sf::Color::Black);
	m_context->m_window->draw(m_scoreTitle);
	m_context->m_window->draw(m_backButton);

	for (int i = 0; i < 5; i++)
	{
		m_context->m_window->draw(m_showName[i]);
		m_context->m_window->draw(m_showScore[i]);
	}

	m_context->m_window->display();
}


