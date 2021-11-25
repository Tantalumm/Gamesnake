#include "Game.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "MainMenu.h"
#include "GameScore.h"


Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(1280,720), "Snake Chikadoo", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}
Game::~Game()
{

}
void Game::Run()
{


    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();



        }
    }
}