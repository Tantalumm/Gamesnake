#pragma once

#include<SFML/System/Time.hpp>
#include<string>

namespace Engine
{
	class State
	{
	public:
		State() {};
		virtual ~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(sf::Time deltaTime) = 0;
		virtual void Draw() {};

		virtual void Pause() {};
		virtual void Start() {};

	};
}

extern std::string playerName;