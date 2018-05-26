#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

//globals
int num_vertBox = 30, num_horzBox = 30;
int size = 16; //number of pixels
int w = size * num_horzBox; //background number of pixels in width
int h = size * num_vertBox; //background number of pixels in height

int direction, directions, player2_length = 4, snake_length = 4;
float delay = .1;

//Maximum size of Snake
struct Snake
{
	int x, y;
}s[100];

struct Player2
{
	int a, b;
}p[100];

struct Fruit
{
	int x, y;
}food;

void Tick()
{
	//Move remaining pieces of snake s[1] - s[99]
	for (int i = snake_length; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	for (int i = player2_length; i > 0; --i)
	{
		p[i].a = p[i - 1].a;
		p[i].b = p[i - 1].b;
	}

	//Head of snake depends on direction of user s[0]
	//User Up
	if (direction == 3)
		s[0].y -= 1;
	//User Down
	if (direction == 0)
		s[0].y += 1;
	//User Left
	if (direction == 1)
		s[0].x -= 1;
	//User Right
	if (direction == 2)
		s[0].x += 1;

	//Player2 Up
	if (directions == 3)
		p[0].b -= 1;
	//Player2 Down
	if (directions == 0)
		p[0].b += 1;
	//Player2 Left
	if (directions == 1)
		p[0].a -= 1;
	//Player2 Right
	if (directions == 2)
		p[0].a += 1;

	//If Snake eats food it should grow
	if ((s[0].x == food.x) && (s[0].y == food.y))
	{
		snake_length++;
		
		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	if ((p[0].a == food.x) && (p[0].b == food.y))
	{
		player2_length++;

		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
	}

	//Boundary Checking screen loop back on other side
	if (s[0].x > num_horzBox)
		s[0].x = 0;
	if (s[0].x < 0)
		s[0].x = num_horzBox;

	if (s[0].y > num_vertBox)
		s[0].y = 0;
	if (s[0].y < 0)
		s[0].y = num_vertBox;

	if (p[0].a > num_horzBox)
		p[0].a = 0;
	if (p[0].a < 0)
		p[0].a = num_horzBox;

	if (p[0].b > num_vertBox)
		p[0].b = 0;
	if (p[0].b < 0)
		p[0].b = num_vertBox;

	//Check if go over snake
	for (int i = 1; i < snake_length; i++)
	{
		//Cut Snake in half from place eaten
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			snake_length = i;
		}
	}

	//Check if go over snake
	for (int i = 1; i < player2_length; i++)
	{
		//Cut Snake in half from place eaten
		if (p[0].a == p[i].a && p[0].b == p[i].b)
		{
			player2_length = i;
		}
	}
	float d = (snake_length + player2_length)/2;
	delay = (.1 / d) * 4;


}

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//textures
	Texture t1, t2, t3, t4;
	t1.loadFromFile("image/white.png");
	t2.loadFromFile("image/red.png");
	t3.loadFromFile("image/green.png");
	t4.loadFromFile("image/player2.png");

	//Sprite
	//Has physical dimensions
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);

	//player 2
	Sprite player2(t4);


	food.x = 10;
	food.y = 10;

	Clock clock;
	float timer = 0;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		//Allow us to check when a user does something
		Event e;

		//check when window is closed
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}

		//Controls for Snake Movement by User
		if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;

		if (Keyboard::isKeyPressed(Keyboard::W)) directions = 3;
		if (Keyboard::isKeyPressed(Keyboard::S)) directions = 0;
		if (Keyboard::isKeyPressed(Keyboard::A)) directions = 1;
		if (Keyboard::isKeyPressed(Keyboard::D)) directions = 2;

		if (timer > delay)
		{
			timer = 0;
			Tick();
		}
		//Draw
		window.clear();

		//Draw Background
		for (int i = 0; i < num_horzBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				sprite1.setPosition(i*size, j*size);
				window.draw(sprite1);
			}
		}

		//Draw Snake
		for (int i = 0; i < snake_length; i++)
		{
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);

		}

		for (int i = 0; i < player2_length; i++)
		{
			player2.setPosition(p[i].a*size, p[i].b*size);
			window.draw(player2);
		}

		//Draw Fruit
		sprite3.setPosition(food.x*size, food.y*size);
		window.draw(sprite3);

		window.display();
	}

	return 0;
}