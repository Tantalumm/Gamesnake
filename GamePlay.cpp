#include "GamePlay.h"
#include "GameOver.h"
#include <SFML/Window/Event.hpp>
#include "Score.h"
#include "GameName.h"

#include <stdlib.h>
#include <time.h>

using namespace std;


GamePlay::GamePlay(std::shared_ptr<Context>& context)
	:m_context(context), 
	 m_snakeDirection({16.f,0.f}), 
	 m_elapsedTime(sf::Time::Zero),
	 m_score(0)
	
{
	srand(time(nullptr));
	
}

GamePlay::~GamePlay()
{

}

void GamePlay::Init()
{
	m_context->m_assets->AddTexture(GRASS, "din.png", true);
	m_context->m_assets->AddTexture(FOOD, "food.png");
	m_context->m_assets->AddTexture(WALL, "wall.png", true);
	m_context->m_assets->AddTexture(SNAKE, "snake.png");
	m_context->m_assets->AddTexture(FOOD2, "orange.png");
	m_context->m_assets->AddTexture(STONE, "stone.png");


	m_grass.setTexture(m_context->m_assets->GetTextture(GRASS));
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	for (auto& wall : m_walls)
	{
		wall.setTexture(m_context->m_assets->GetTextture(WALL));
	}
	//Wall top down
	m_walls[0].setTextureRect({0, 0, (int)m_context->m_window->getSize().x, 16 });
	m_walls[1].setTextureRect({ 0, 0,(int)m_context->m_window->getSize().x, 16 });
	m_walls[1].setPosition(0, m_context->m_window->getSize().y - 16);
	//wall left right
	m_walls[2].setTextureRect({ 0, 0, 16, (int)m_context->m_window->getSize().y });
	m_walls[3].setTextureRect({ 0, 0, 16, (int)m_context->m_window->getSize().y });
	m_walls[3].setPosition(m_context->m_window->getSize().x - 16, 0);


	//apple
	m_food.setTexture(m_context->m_assets->GetTextture(FOOD));
	m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

	m_food2.setTexture(m_context->m_assets->GetTextture(FOOD2));



	//STONE
	m_wallblock.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock1.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock2.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock4.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock5.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock6.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock7.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock8.setTexture(m_context->m_assets->GetTextture(STONE));
	m_wallblock9.setTexture(m_context->m_assets->GetTextture(STONE));

	
	//snake
	m_snake.Init(m_context->m_assets->GetTextture(SNAKE));

	//SHOW SCORE N HP
	m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_scoreText.setString("Score : " + std::to_string(m_score));
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition(0,0);
	m_scoreText.setCharacterSize(15);

	m_Hp.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_Hp.setString("HP : " + std::to_string(m_hp));
	m_Hp.setFillColor(sf::Color::White);
	m_Hp.setPosition(80,0);
	m_Hp.setCharacterSize(15);

}


void GamePlay::ProcessInput()
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
			sf::Vector2f newDirection = m_snakeDirection;
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				newDirection = { 0.f, -16.f };
				break;
			case sf::Keyboard::Down:
				newDirection = { 0.f,  16.f };
				break;
			case sf::Keyboard::Left:
				newDirection = { -16.f, 0.f };
				break;
			case sf::Keyboard::Right:
				newDirection = {  16.f, 0.f };
				break;
			case sf::Keyboard::M:
				m_context->m_states->Add(std::make_unique<GameOver>(m_context));
				break;
			case sf::Keyboard::Escape:
				m_context->m_window->close();
				break;

			default:
				break;
			}

			if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
				std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
			{
				m_snakeDirection = newDirection;
			}

		}
	}
}



void GamePlay::Update(sf::Time deltaTime)
{
	   float i = 0.1;
	   if (m_score >= 10)
	   {
		   i -= 0.02;
	   }
	   if (m_score >= 20)
	   {
		   i -= 0.02;
	   }
	   if (m_score >= 30)
	   {
		   i -= 0.02;
	   }
	   if (m_score >= 40)
	   {
		   i -= 0.02;
	   }
	   if (m_score >= 50)
	   {
		   i -= 0.01;
	   }


		m_elapsedTime += deltaTime;

		

		if (m_elapsedTime.asSeconds() > i) //speed play
		{
			//check when hit block & walls
			for (auto& wall : m_walls)
			{
				if (m_snake.IsOn(wall))
				{
					m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
					m_scoreboard.writeFile(playerName, m_score);
					m_scoreboard.clearScore();
					break;
				}
			}

			//when eat food & glow
			if (m_snake.IsOn(m_food))
			{
				m_snake.Grow(m_snakeDirection);

				int x = 0, y = 0;
				x = rand() % m_context->m_window->getSize().x*0.8 + m_context->m_window->getSize().x*0.1;
				y = rand() % m_context->m_window->getSize().y*0.8 + m_context->m_window->getSize().y*0.1;
			    m_food.setPosition(x, y);
				m_score += 1;
				/*if (m_score >= 2 && m_score % 2 == 0)
				{
					m_hp += 0;
					m_Hp.setString("HP : " + std::to_string(m_hp));
				}*/
				m_scoreText.setString("Score : " + std::to_string(m_score));



				if (m_score >= 10 && m_score % 10 == 0)
				{
					int x = 0, y = 0;
					x = rand() % m_context->m_window->getSize().x * 0.8 + m_context->m_window->getSize().x * 0.1;
					y = rand() % m_context->m_window->getSize().y * 0.8 + m_context->m_window->getSize().y * 0.1;
					m_food2.setPosition(x,y);
				}
				else
				{
					int x = 0, y = 0;
					x = rand() % m_context->m_window->getSize().x + 2000.f + m_context->m_window->getSize().x + 2000.f;
					y = rand() % m_context->m_window->getSize().y * 2000.f + m_context->m_window->getSize().y + 2000.f;
					m_food2.setPosition(x, y);
				}
				if (m_score == 10)
				{
					int x = 0, y = 0;
					x = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					y = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;
					m_wallblock.setPosition(x, y);
				}
				if (m_score == 20)
				{
					int x = 0, y = 0;
					x = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					y = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;
					m_wallblock1.setPosition(x, y);
				}
				if (m_score == 30)
				{
					int x = 0, y = 0;
					x = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					y = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;
					m_wallblock2.setPosition(x, y);
				}
				if (m_score == 40)
				{
					int x = 0, y = 0,a = 0 ,b = 0;
					x = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					y = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;

					a = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					b = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;
					m_wallblock4.setPosition(x, y);
					m_wallblock5.setPosition(a, b);
				}
				if (m_score == 50)
				{
					int x = 0, y = 0, a = 0, b = 0;
					x = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					y = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;

					a = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					b = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;
					m_wallblock6.setPosition(x, y);
					m_wallblock7.setPosition(a, b);
				}
				if (m_score == 60)
				{
					int x = 0, y = 0, a = 0, b = 0;
					x = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					y = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;

					a = rand() % m_context->m_window->getSize().x * 0.7 + m_context->m_window->getSize().x * 0.1;
					b = rand() % m_context->m_window->getSize().y * 0.7 + m_context->m_window->getSize().y * 0.1;

					m_wallblock8.setPosition(x, y);
					m_wallblock9.setPosition(a, b);
				}
				
				
			}
			if (m_snake.IsOn(m_food2))
			{
				m_snake.Grow(m_snakeDirection);

					int x = 0, y = 0;
					x = rand() % m_context->m_window->getSize().x +2000.f + m_context->m_window->getSize().x +2000.f;
					y = rand() % m_context->m_window->getSize().y +2000.f + m_context->m_window->getSize().y +2000.f;
					m_food2.setPosition(x, y);

				m_score += 2;
				m_hp += 1;

				m_scoreText.setString("Score : " + std::to_string(m_score));
				m_Hp.setString("HP : " + std::to_string(m_hp));
			}
			else
			{
				m_snake.Move(m_snakeDirection);
			}

	

			//check when hit body
			if (m_snake.IsSelfIntersecting()){
			
				m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
				m_scoreboard.writeFile(playerName, m_score);
				m_scoreboard.clearScore();
			}
			//spaw wall
			if (m_snake.IsOn(m_wallblock))
			{
				int a = 0,b = 0;
				a = rand() % m_context->m_window->getSize().x * 0.8 + m_context->m_window->getSize().x * 0.1;
				b = rand() % m_context->m_window->getSize().y * 0.8 + m_context->m_window->getSize().y * 0.1;
				m_wallblock.setPosition(a, b);

				m_hp -= 1;
				m_Hp.setString("HP : " + std::to_string(m_hp));
			}

			if (m_snake.IsOn(m_wallblock1))
			{
				int  c = 0, d = 0;
				c = rand() % m_context->m_window->getSize().x * 0.8 + m_context->m_window->getSize().x * 0.1;
				d = rand() % m_context->m_window->getSize().y * 0.8 + m_context->m_window->getSize().y * 0.1;
				m_wallblock1.setPosition(c, d);		
				m_hp -= 1;
				m_Hp.setString("HP : " + std::to_string(m_hp));
			}

			if (m_snake.IsOn(m_wallblock2))
			{
				int  e = 0, f = 0;
				e = rand() % m_context->m_window->getSize().x * 0.8 + m_context->m_window->getSize().x * 0.1;
				f = rand() % m_context->m_window->getSize().y * 0.8 + m_context->m_window->getSize().y * 0.1;
				m_wallblock2.setPosition(e, f);
				m_hp -= 1;
				m_Hp.setString("HP : " + std::to_string(m_hp));
			}

			if (m_hp < 0)
			{
				m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
				m_scoreboard.writeFile(playerName, m_score);
				m_scoreboard.clearScore();
			}

			m_elapsedTime = sf::Time::Zero;
		}


	
}



void GamePlay::Draw()
{
	m_context->m_window->clear();
	
	m_context->m_window->draw(m_grass);
	
	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);
	}
	m_context->m_window->draw(m_scoreText);
	m_context->m_window->draw(m_food);

	//draw orange
	if (m_score >= 10 && m_score % 10 == 0)
	{
		m_context->m_window->draw(m_food2);
	}

	m_context->m_window->draw(m_snake);
	m_context->m_window->draw(m_Hp);
	//draw stone
	if(m_score >= 10)
	{
		m_context->m_window->draw(m_wallblock);
	}
	if (m_score >= 20)
	{
		m_context->m_window->draw(m_wallblock1);
	}
	if (m_score >= 30)
	{
		m_context->m_window->draw(m_wallblock2);
	}
	
	if (m_score >= 40)
	{
		m_context->m_window->draw(m_wallblock4);
		m_context->m_window->draw(m_wallblock5);
	}

	if (m_score >= 50)
	{
		m_context->m_window->draw(m_wallblock6);
		m_context->m_window->draw(m_wallblock7);
	}
	
	if (m_score >= 60)
	{
		m_context->m_window->draw(m_wallblock8);
		m_context->m_window->draw(m_wallblock9);
	}




	m_context->m_window->display();
}


