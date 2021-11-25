#include "MainMenu.h"
#include "GamePlay.h"
#include "GameScore.h"
#include "GameName.h"
#include <stdlib.h>

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context)
	: m_context(context), 
	m_isPlayButtonSelected(true),
	m_isPlayButtonPressed(false),

	m_isExitButtonSelected(false),
	m_isExitButtonPressed(false),
	
	m_isScoreButtonSelected(true),
	m_isScoreButtonPressed(false)
{
}
MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	m_context->m_assets->AddFont(MAIN_FONT, "Pacifico-Regular.ttf");

	//BG
	m_context->m_assets->AddTexture(BG, "sn1.png");
	m_bg.setTexture(m_context->m_assets->GetTextture(BG));




	//Title
	m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameTitle.setString("Snake	Chikadoo");
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2	,m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2 	,m_context->m_window->getSize().y / 2 - 200.f);
	m_playButton.setCharacterSize(100);

	//Playbutton
	m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_playButton.setString("Play");
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2	,m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x / 2 + 75.f	,m_context->m_window->getSize().y / 2 + 25.f);
	m_playButton.setCharacterSize(40);

	//Scorebutton
	m_scoreButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_scoreButton.setString("Score");
	m_scoreButton.setOrigin(m_scoreButton.getLocalBounds().width / 2,m_scoreButton.getLocalBounds().height / 2);
	m_scoreButton.setPosition(m_context->m_window->getSize().x / 2	,m_context->m_window->getSize().y / 2  + 100.f);
	m_scoreButton.setCharacterSize(40);

	//Exitbutton
	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2	,m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2	,m_context->m_window->getSize().y / 2 + 200.f);
	m_exitButton.setCharacterSize(40); 

	m_myname.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_myname.setString("Wattikorn Charoenkan");
	m_myname.setPosition(m_context->m_window->getSize().x / 2 - 600.f, m_context->m_window->getSize().y / 2 + 250.f);
	m_myname.setCharacterSize(30);

	m_mynum.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_mynum.setString("64010801");
	m_mynum.setPosition(m_context->m_window->getSize().x / 2 - 500.f, m_context->m_window->getSize().y / 2 + 300.f);
	m_mynum.setCharacterSize(30);


}

void MainMenu::ProcessInput()
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
			case sf::Keyboard::Up:
			{
				if (!m_isPlayButtonSelected)
				{
					m_isPlayButtonSelected = true;
					m_isScoreButtonSelected = false;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (!m_isScoreButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isScoreButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				
				else if (!m_isExitButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isScoreButtonSelected = false;
					m_isExitButtonSelected = true;
				}

				break;
			}
			case sf::Keyboard::Return:
			{
				m_isPlayButtonPressed = false;
				m_isExitButtonPressed = false;
				m_isScoreButtonPressed = false;

				if (m_isPlayButtonSelected)
				{
					m_isPlayButtonPressed = true;
				}
				else if (m_isScoreButtonSelected) 
				{
					m_isScoreButtonPressed = true;
				}
				else if (m_isExitButtonSelected)
				{
					m_isExitButtonPressed = true;
				}

				break;
			}
			default:
				break;
			}
		}


	}
}

void MainMenu::Update(sf::Time deltaTime)
{
	if (m_isPlayButtonSelected)
	{
		m_scoreButton.setFillColor(sf::Color::White);
		m_playButton.setFillColor(sf::Color::Yellow);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else if (m_isScoreButtonSelected)
	{
		m_scoreButton.setFillColor(sf::Color::Yellow);
		m_playButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else if (m_isExitButtonSelected)
	{
		m_scoreButton.setFillColor(sf::Color::White);
		m_playButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color::Yellow);
	}
	if (m_isPlayButtonPressed)
	{
		m_context->m_states->Add(std::make_unique<GameName>(m_context),true);
	}
	if (m_isScoreButtonPressed)
	{
		m_context->m_states->Add(std::make_unique<GameScore>(m_context),true);
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
	
}


void MainMenu::Draw()
{
	//m_context->m_window->clear(sf::Color::Black);
	m_context->m_window->draw(m_bg);
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->draw(m_scoreButton);
	m_context->m_window->draw(m_myname);
	m_context->m_window->draw(m_mynum);




	m_context->m_window->display();
}				

