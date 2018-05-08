// main.cpp : Defines the entry point for the windows application.
// SFML Game: Pong
// Gameplay features: AI, Collision Detection, Vector Math, Score Calculation
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <cstring>
#include <cmath>

void update_state(float dt);
void render_frame();

sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
sf::Vector2f velocity(100, 300);

sf::Texture tex;

sf::SoundBuffer buf;
sf::Sound sound;

sf::Font font;

sf::RectangleShape background;

int playerscore = 0;
int computerscore = 0;
bool pause = false;

class Ball;

class Paddle
{
private:
	sf::Vector2f position;
	sf::Vector2f origin;
	sf::Vector2f size;
	sf::RectangleShape paddle;
	bool lose;
	bool win;
public:
	void track(Ball ball, float dt);
	void update(float dt);
	sf::Vector2f getposition();
	void setposition(sf::Vector2f position);
	sf::Vector2f getorigin();
	void setorigin(sf::Vector2f origin);
	sf::Vector2f getsize();
	void setsize(sf::Vector2f size);
	void setfillcolor(sf::Color color);
	sf::RectangleShape getshape();
	void setlose();
	void setwin();
	void resetlose();
	void resetwin();
	bool getlose();
	bool getwin();
};

class Ball
{
private:
	sf::Vector2f position;
	sf::Vector2f origin;
	sf::Vector2f radius;
	sf::CircleShape ball;


public:
	void track(Paddle paddle, Paddle computer);
	void trace(Paddle computer, float dt);
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

void Ball::trace(Paddle computer, float dt)
{


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

Paddle player;
Paddle computer;
Ball ball;
int winner = 0;
sf::Text text;
sf::Text playerscoretext;
sf::Text computerscoretext;
bool end = false;

int main()
{
	std::string score;
	sf::Clock clock;
	tex.loadFromFile("pongback.png");

	buf.loadFromFile("ball-hit.wav");
	sound.setBuffer(buf);

	font.loadFromFile("arial.TTF");

	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&tex);

	ball.setradius(20.f);
	ball.setorigin(sf::Vector2f(20, 20));
	ball.setposition(sf::Vector2f(400, 300));
	ball.setfillcolor(sf::Color::White);

	player.setsize(sf::Vector2f(30, 200));
	player.setorigin(sf::Vector2f(15, 100));
	player.setposition(sf::Vector2f(20, 300));
	player.setfillcolor(sf::Color::Cyan);

	computer.setsize(sf::Vector2f(30, 200));
	computer.setorigin(sf::Vector2f(15, 100));
	computer.setposition(sf::Vector2f(780, 300));
	computer.setfillcolor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			sound.play();

		text.setFont(font);
		text.setCharacterSize(50);
		score = "Pong Game";
		text.setString(score);
		text.setFillColor(sf::Color::Green);
		text.setPosition(300, 500);//player //text.setPosition(500, 100); computer 

		float dt = clock.restart().asSeconds();

		if (!pause)
		{
			update_state(dt);
			render_frame();
			window.display();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			pause = false;
			playerscore = 0;
			computerscore = 0;
			end = false;
			winner = 0;
		}
	}
	return 0;
}

void update_state(float dt)
{
	ball.update(player, computer, dt);
	ball.track(player, computer); // player lose condition
	computer.track(ball, dt);//computer AI
	player.update(dt);

	if (player.getlose()) //player lose
	{
		computer.setlose();
		computer.setwin();
		computer.setfillcolor(sf::Color::Blue);
	}
	else
		if (computer.getlose()) //computer lose
		{
			computer.resetlose();
			computer.resetwin();
			player.setfillcolor(sf::Color::Blue);
		}

	//Text playerscoretext;
	playerscoretext.setFont(font);
	playerscoretext.setCharacterSize(20);
	std::string s = "PLAYER SCORE: ";
	s += std::to_string(playerscore);
	playerscoretext.setString(s);
	playerscoretext.setFillColor(sf::Color::Yellow);
	playerscoretext.setPosition(50, 100);

	//Text computerscoretext;
	computerscoretext.setFont(font);
	computerscoretext.setCharacterSize(20);
	std::string sc = "COMPUTER SCORE: ";
	sc += std::to_string(computerscore);
	computerscoretext.setString(sc);
	computerscoretext.setFillColor(sf::Color::Yellow);
	computerscoretext.setPosition(500, 100);

	if (playerscore == 5 && computerscore < 5)
	{
		winner = 1;	//player
	}

	else
		if (computerscore == 5 && playerscore < 5)
		{
			winner = 2;	//computer
		}
		else
			if (computerscore == 5 && playerscore == 5)
			{
				winner = 3;	//tie
			}

	if (end)
	{
		pause = true;
	}
}

void render_frame()
{
	{
		window.clear();
		window.draw(background);
		window.draw(ball.getshape());
		window.draw(player.getshape());
		window.draw(computer.getshape());

		switch (winner)
		{
		case 1: text.setString("Winner: Player");
			end = true;
			break;
		case 2: text.setString("Winner: Computer");
			end = true;
			break;
		case 3: text.setString("Tie");
			end = true;
			break;
		}
		window.draw(playerscoretext);
		window.draw(computerscoretext);
		window.draw(text);
	}
}