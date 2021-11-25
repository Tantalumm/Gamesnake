#include "GameName.h"



GameName::GameName(std::shared_ptr<Context>& context)
	: m_context(context)
{
}

GameName::~GameName()
{
}

void GameName::Init()
{

	//Title
	m_gameNameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameNameTitle.setString("YOUR NAME");
	m_gameNameTitle.setOrigin(m_gameNameTitle.getLocalBounds().width / 2,m_gameNameTitle.getLocalBounds().height / 2);
	m_gameNameTitle.setPosition(m_context->m_window->getSize().x / 2,m_context->m_window->getSize().y / 2 - 200.f);
	//Playbutton
	m_NextButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_NextButton.setString("Play");
	m_NextButton.setOrigin(m_NextButton.getLocalBounds().width / 2,m_NextButton.getLocalBounds().height / 2);
	m_NextButton.setPosition(m_context->m_window->getSize().x / 2,m_context->m_window->getSize().y / 2 + 200.f);
	m_NextButton.setCharacterSize(20);

	//Exitbutton
	m_BackButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_BackButton.setString("Back");
	m_BackButton.setOrigin(m_BackButton.getLocalBounds().width / 2,m_BackButton.getLocalBounds().height / 2);
	m_BackButton.setPosition(m_context->m_window->getSize().x / 2,m_context->m_window->getSize().y / 2 + 300.f);
	m_BackButton.setCharacterSize(20);

	name.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	name.setOrigin(m_BackButton.getLocalBounds().width / 2,name.getLocalBounds().height / 2);
	name.setPosition(m_context->m_window->getSize().x / 2,m_context->m_window->getSize().y / 2);
	name.setCharacterSize(60);
	
}

void GameName::ProcessInput()
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
				if (!m_isNextButtonSelected)
				{
					m_isNextButtonSelected = true;
					m_isbackkButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (!m_isbackkButtonSelected)
				{
					m_isNextButtonSelected = false;
					m_isbackkButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				m_isNextButtonPressed = false;
				m_isbackkButtonPressed = false;
				if (m_isNextButtonSelected)
				{
					m_isNextButtonPressed = true;
				}
				else
				{
					m_isbackkButtonPressed = true;
				}
				break;
			}
			default:
				break;
			}
		}
		else if (sf::Event::TextEntered)
		{
			KeyInput.push_back(event);
		}

	}
}

void GameName::Update(sf::Time deltaTime)
{
	
	if (m_isNextButtonSelected)
	{
		m_NextButton.setFillColor(sf::Color::Yellow);
		m_BackButton.setFillColor(sf::Color::White);
	}
	else
	{
		m_BackButton.setFillColor(sf::Color::Yellow);
		m_NextButton.setFillColor(sf::Color::White);
	}

	if (m_isNextButtonPressed)
	{
		m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
	}
	else if (m_isbackkButtonPressed)
	{
		m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
	}
	nameUpdate();
	
}


void GameName::nameUpdate()
{
	for (int i = 0; i < KeyInput.size(); i++)
	{
		if (KeyInput[i].type == sf::Event::TextEntered &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
		if (KeyInput[i].text.unicode == 32 && playerName.length() < 10)
			{
				playerName += static_cast<char>(95);
			}
		if (KeyInput[i].text.unicode == 8 && playerName.length() > 0)
			{
				playerName.erase(playerName.length() - 1);
			}
		else if (KeyInput[i].text.unicode < 128 && playerName.length() < 10 &&
			KeyInput[i].text.unicode != 8 && (KeyInput[i].text.unicode < 48 ||
				KeyInput[i].text.unicode > 57))
			{
				name.setFillColor(sf::Color::White);
				playerName += static_cast<char>(KeyInput[i].text.unicode);
			}
		}
	}
	KeyInput.clear();
	name.setString(playerName);
	name.setOrigin(name.getLocalBounds().width / 2, name.getLocalBounds().height / 2);

	
}


void GameName::Draw()
{
	m_context->m_window->clear(sf::Color::Black);
	m_context->m_window->draw(name);
	
	m_context->m_window->draw(m_gameNameTitle);
	m_context->m_window->draw(m_NextButton);
	m_context->m_window->draw(m_BackButton);
	m_context->m_window->display();
}

