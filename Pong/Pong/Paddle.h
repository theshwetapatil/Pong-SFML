#pragma once
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <cstring>
#include <cmath>

class Ball;

int playerscore = 0;
int computerscore = 0;

sf::Vector2f velocity = sf::Vector2f(100, 300);
sf::RenderWindow window{ sf::VideoMode(800, 600), "Pong" };

sf::SoundBuffer buf;
sf::Sound sound;

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
