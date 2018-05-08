#pragma once
#include "Paddle.h"

void Paddle::track(Ball ball, float dt)
{
	sf::Vector2f paddlepos = paddle.getPosition();
	sf::Vector2f ballpos = ball.getposition();
	if (ballpos.x > 400)
	{

		if (ballpos.y < 300)
		{
			ball.setfillcolor(sf::Color::Green);
			paddlepos.y -= paddlepos.y*dt;

			if (paddlepos.y <= 100)
			{
				paddle.setFillColor(sf::Color::Red);
				paddlepos.y = 100;
			}
			else
			{
				paddle.setFillColor(sf::Color::Cyan);
			}

			paddle.setPosition(paddlepos);
		}

		if (ballpos.y > 300)
		{
			{
				ball.setfillcolor(sf::Color::Blue);
				paddlepos.y += paddlepos.y*dt;

				if (paddlepos.y >= 500)
				{
					paddle.setFillColor(sf::Color::Yellow);
					paddlepos.y = 500;
				}
				else
				{
					paddle.setFillColor(sf::Color::Cyan);
				}

				paddle.setPosition(paddlepos);
			}
		}
	}
}

void Paddle::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		sf::Vector2f paddlepos = paddle.getPosition();
		paddlepos.y -= paddlepos.y*dt;

		if (paddlepos.y <= 100)
		{
			paddle.setFillColor(sf::Color::Red);
			paddlepos.y = 100;
		}
		else
		{
			paddle.setFillColor(sf::Color::Cyan);
		}

		paddle.setPosition(paddlepos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		sf::Vector2f paddlepos = paddle.getPosition();
		paddlepos.y += paddlepos.y*dt;

		if (paddlepos.y >= 500)
		{
			paddle.setFillColor(sf::Color::Yellow);
			paddlepos.y = 500;
		}
		else
		{
			paddle.setFillColor(sf::Color::Cyan);
		}

		paddle.setPosition(paddlepos);
	}

}

sf::Vector2f Paddle::getposition()
{
	return paddle.getPosition();
}

void Paddle::setposition(sf::Vector2f position)
{
	paddle.setPosition(position);
	this->position = position;
}

sf::Vector2f Paddle::getorigin()
{
	return paddle.getOrigin();
}

void Paddle::setorigin(sf::Vector2f origin)
{
	paddle.setOrigin(origin);
}

sf::Vector2f Paddle::getsize()
{
	return paddle.getSize();
}

void Paddle::setsize(sf::Vector2f size)
{
	paddle.setSize(size);
}

void Paddle::setfillcolor(sf::Color color)
{
	paddle.setFillColor(color);
}

sf::RectangleShape Paddle::getshape()
{
	return paddle;
}

void Paddle::setlose()
{
	lose = true;
}

void Paddle::setwin()
{
	win = true;
}

void Paddle::resetlose()
{
	lose = false;
}

void Paddle::resetwin()
{
	win = false;
}

bool Paddle::getlose()
{
	return lose;
}

bool Paddle::getwin()
{
	return win;
}
