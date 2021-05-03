#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <string>
#include "view.h"
using namespace sf;
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	float ITISTIMETOSTOP[3];
	ITISTIMETOSTOP[0] = -1;
	ITISTIMETOSTOP[1] = -1;
	ITISTIMETOSTOP[2] = -1;
	int angle = 0;
	int actualss = 0;
	int needit = 0;
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	int x = 0, y = 0;
	float stopx = 0;
	bool baba = false;
	bool stop = false;
	bool stop1 = true;
	bool stops[3];
	stops[0] = true;
	stops[1] = true;
	stops[2] = true;
	char m;
	float falltime = 0;
	float alltime = 0;
	float timemodif = 1;
	float bollx = 158, bolly = 2999;
	float  vx = 0, vy = 0, ax = 0, ay = 0, v, a;
	ITISTIMETOSTOP[0] = 0;
	stops[0] = false;

	Font font;
	font.loadFromFile("font.ttf");
	Text text("", font, 24);
	text.setFillColor(Color(255, 0, 0));
	text.setStyle(sf::Text::Bold);

	CircleShape shape(4.5);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(int(bollx), int(bolly));
	shape.setOrigin(6, 6);

	CircleShape shapeshow[20];
	for (int i = 0; i < 20; i++)
	{
		shapeshow[i].setRadius(1.5);
		shapeshow[i].setFillColor(sf::Color::Red);
		shapeshow[i].setOrigin(2, 2);
		shapeshow[i].setPosition(-100, -100);
	}

	Image exit_image;
	exit_image.loadFromFile("images/exitimage.png");
	exit_image.createMaskFromColor(Color(255, 255, 255));
	Texture exit_t;
	exit_t.loadFromImage(exit_image);
	Sprite s_exit;
	s_exit.setTexture(exit_t);
	s_exit.setPosition(0, 0);
	
	Image background_image;
	background_image.loadFromFile("images/background.png");
	background_image.createMaskFromColor(Color(255, 255, 255));
	Texture background_t;
	background_t.loadFromImage(background_image);
	Sprite s_background;
	s_background.setTexture(background_t);
	s_background.setPosition(0, 0);
	bollx = 158;
	bolly = 3000;
	string lang;
	cout << "Choose language Выберите язык (eng / rus) \n";
	cin >> lang;
	while (lang != "eng" && lang != "rus")
	{
		cout << "\n";
		cin >> lang;
	}
	cout << "\n";
	if (lang == "rus")
	{
		cout << "Введите скорость в метрах в секунду\n";
		cin >> v;
		cout << "Введите ускорение в метрах на секунду в квадрате\n";
		cin >> a;
		cout << "Введите угол наклона относительно горизонта\n";
		cin >> angle;
	}
	else
	{
		cout << "Enter speed in m/s\n";
		cin >> v;
		cout << "Enter speedup in m/s^2\n";
		cin >> a;
		cout << "Enter angle in\n";
		cin >> angle;
	}
		vy = (v * sin(angle * 0.0175));
		vx = (v * cos(angle * 0.0175));
		ay = (a * sin(angle * 0.0175));
		ax = (a * cos(angle * 0.0175));
		if (lang == "rus")
	cout << "Задайте скорость воспроизведения\n";
		else
			cout << "Enter speed of viewing\n";
	cin >> timemodif;
	RenderWindow window(sf::VideoMode(sw, sh), "Fisics programm", Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, sw, sh));
	window.setPosition(Vector2i(0, 0));
	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time * timemodif;
		for (int i = 0; i < 3; i++) if (alltime > ITISTIMETOSTOP[i] && stops[i] == false) {
			stop1 = true; stops[i] = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter)) stop1 = false;
		if (stop1 == false) alltime += time / 1000;
		//Данные положения курсора//
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		//Работа с событиями(нажатия мыши, выход из проги и т.д.)//
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) {//а именно левая
					if (s_exit.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
					{
						s_exit.setColor(Color::Green);
						window.draw(s_exit);
						window.display();
						Sleep(300);
						window.close();
					}
				}
		}
		
		if (stop1 == false)
		{
			if (bolly > 3000)
			{
				bolly = 3001;
				if (stop == false) { stop = true; stopx = bollx; falltime = alltime; }
				bollx = stopx;
				vx = 0;
				vy = 0;
			}
			else
			{
				if (alltime > (timemodif * (needit + 1))) 
				{
					shapeshow[actualss].setPosition(int(bollx), int(bolly));
					needit++;
					actualss++;
					if (actualss == 20) actualss = 0;
				}
				float uknow = ((0.4441 * 1.2754 * 0.5 * 0.2 * vx * vx) / 0.4) * time / 1000;
				bollx += (vx * 100 * time) / 1000;
				vx += ax * time / 1000;
				if (vx > 0) vx -= uknow;
				else if (vx < 0) vx += uknow;
				bolly -= (vy * 100 * time) / 1000;
				vy += ay * (time / 1000);
				vy -= 9.80665 * (time / 1000);
			}
		}
		shape.setPosition(int(bollx), int(bolly));
		getplayercoordinateforview(bollx, bolly, sw, sh);
		window.setView(view);
		window.clear();
		window.getSystemHandle();
		window.draw(s_background);
		s_exit.setPosition(getviewx() + int(sw / 2) - 126, getviewy() - int(sh / 2));
		for (int i = 0; i < 20; i++) window.draw(shapeshow[i]);
		window.draw(s_exit);
		window.draw(shape);

		std::ostringstream thing;
		thing << "x ";
		thing << (bollx - 158) / 100;
		thing << " m";
		text.setString(thing.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 28);//задаем позицию текста, отступая от центра камеры
		window.draw(text);

		std::ostringstream thing1;
		thing1 << "y ";
		thing1 << (3000 - bolly + 1) / 100;
		thing1 << " m";
		text.setString(thing1.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 56);//задаем позицию текста, отступая от центра камеры
		window.draw(text);

		std::ostringstream thing2;
		thing2 << "Vx ";
		thing2 << vx;
		thing2 << " m/c";
		text.setString(thing2.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 84);//задаем позицию текста, отступая от центра камеры
		window.draw(text);

		std::ostringstream thing3;
		thing3 << "Vy ";
		thing3 << vy;
		thing3 << " m/c";
		text.setString(thing3.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 112);//задаем позицию текста, отступая от центра камеры
		window.draw(text);

		std::ostringstream thing6;
		thing6 << "V ";
		thing6 << sqrt((vx*vx) + (vy * vy));
		thing6 << " m/c";
		text.setString(thing6.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 140);//задаем позицию текста, отступая от центра камеры
		window.draw(text);

		std::ostringstream thing4;
		thing4 << "time ";
		if (true)
		{
			float uknow = alltime;
			thing4 << uknow;
		}
		thing4 << " c";
		text.setString(thing4.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 3);//задаем позицию текста, отступая от центра камеры
		window.draw(text);

		if (stop == true)
		{
			std::ostringstream thing7;
			thing7 << "falltime ";
			if (true)
			{
				float uknow = falltime;
				thing7 << uknow;
			}
			thing7 << " c";
			text.setString(thing7.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 168);//задаем позицию текста, отступая от центра камеры
			window.draw(text);
		}

		if (stop1 == true)
		{
			std::ostringstream thing5;
			thing5 << "Press enter";
			text.setString(thing5.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2) + 196);//задаем позицию текста, отступая от центра камеры
			window.draw(text);
		}

		window.display();
	}

	return 0;
}