#pragma once
#include "Ball.h"

void Ball::track(Paddle player, Paddle computer)
{
	if (position.x < 0)
	{
		player.setlose();
		computer.setwin();
		++computerscore;
		setposition(sf::Vector2f(400, 300));
		velocity.x = 100;
		velocity.y = 300;
	}

	if (position.x > 800)
	{
		player.setwin();
		computer.setlose();
		++playerscore;
		setposition(sf::Vector2f(400, 300));
		velocity.x = 100;
		velocity.y = 300;
	}
}

void Ball::update(Paddle player, Paddle computer, float dt)
{
	position += velocity * dt;

	if (position.y > window.getSize().y && velocity.y > 0)
	{
		ball.setFillColor(sf::Color::White);
		velocity.y = -velocity.y;
		sound.play();
	}

	if (position.y < 0 && velocity.y < 0)
	{
		ball.setFillColor(sf::Color::White);
		velocity.y = -velocity.y;
		sound.play();
	}

	if (position.x >= player.getposition().x - 15 && position.x <= player.getposition().x + 15 && position.y <= player.getposition().y + 100 && position.y >= player.getposition().y - 100 && velocity.x < 0) //all edges of paddle player
	{
		int l = sqrt((position.x - player.getposition().x + 100)*(position.x - player.getposition().x + 100) + (position.y - player.getposition().y)*(position.y - player.getposition().y));
		sf::Vector2f dir(((position.x - player.getposition().x + 100) / l), ((position.y - player.getposition().y) / l));
		ball.setFillColor(sf::Color::Red);

		int velenght = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
		velocity.x = velenght*dir.x*1.3f;
		velocity.y = velenght*dir.y*1.3f;

		sound.play();
	}


	if (position.x >= computer.getposition().x - 15 && position.x <= computer.getposition().x + 15 && position.y <= computer.getposition().y + 100 && position.y >= computer.getposition().y - 100 && velocity.x > 0) //all edges of paddle computer
	{
		int l = sqrt((computer.getposition().x + 100 - position.x)*(computer.getposition().x + 100 - position.x) + (computer.getposition().y - position.y)*(computer.getposition().y - position.y));
		sf::Vector2f dir(((computer.getposition().x + 100 - position.x) / l), ((computer.getposition().y - position.y) / l));
		ball.setFillColor(sf::Color::Yellow);

		int velenght = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
		velocity.x = -velenght*dir.x*1.3f;
		velocity.y = -velenght*dir.y*1.3f;

		sound.play();
	}
	velocity.y += 5 * dt;
	ball.setPosition(position);
}

sf::Vector2f Ball::getposition()
{
	return ball.getPosition();
}

void Ball::setposition(sf::Vector2f position)
{
	ball.setPosition(position);
	this->position = position;
}

sf::Vector2f Ball::getorigin()
{
	return ball.getOrigin();
}

void Ball::setorigin(sf::Vector2f origin)
{
	ball.setOrigin(origin);
}

float Ball::getradius()
{
	return ball.getRadius();
}

void Ball::setradius(float radius)
{
	ball.setRadius(radius);
}

void Ball::setfillcolor(sf::Color color)
{
	ball.setFillColor(color);
}

sf::CircleShape Ball::getshape()
{
	return ball;
}
