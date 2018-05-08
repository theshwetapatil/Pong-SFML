#pragma once
#include "Paddle.h"

class Ball
{
	private:
		sf::Vector2f position;
		sf::Vector2f origin;
		sf::Vector2f radius;
		sf::CircleShape ball;

	public:
		void track(Paddle paddle, Paddle computer);
		void update(Paddle player, Paddle computer, float dt);
		sf::Vector2f getposition();
		void setposition(sf::Vector2f position);
		sf::Vector2f getorigin();
		void setorigin(sf::Vector2f origin);
		float getradius();
		void setradius(float radius);
		void setfillcolor(sf::Color color);
		sf::CircleShape getshape();
};

