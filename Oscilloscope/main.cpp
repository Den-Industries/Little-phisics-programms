#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>
#include <string>
#include "view.h"

using namespace sf;
using namespace std;

float evenly(float shit, int shit1)
{
	shit *= shit1;
	shit = nearbyint(shit);
	shit /= shit1;
	return shit;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int sw = 1366;
	int sh = 768;
	float stuffy = 0;
	float xmod1 = 0;
	float ymod1 = 0;
	float power1 = 5;
	float freq1 = 20;
	float powmod1 = 1;
	float xmod2 = 0;
	float ymod2 = 0;
	float power2 = 5;
	float freq2 = 20;
	float powmod2 = 1;
	float timemodif = 1;
	float viewmodif = 1;
	float culldown = 5;
	float alltime = 0;

	Font font;
	font.loadFromFile("font.ttf");
	Text text("", font, 40);
	text.setFillColor(Color(111, 185, 111));
	text.setStyle(sf::Text::Bold);

	Image exit_image;
	exit_image.loadFromFile("images/exitimage.png");
	exit_image.createMaskFromColor(Color(255, 255, 255));
	Texture exit_t;
	exit_t.loadFromImage(exit_image);
	Sprite s_exit;
	s_exit.setTexture(exit_t);

	Image bg_image;
	bg_image.loadFromFile("images/stuff2.png");
	bg_image.createMaskFromColor(Color(255, 255, 255));
	Texture bg_t;
	bg_t.loadFromImage(bg_image);
	Sprite s_bg;
	s_bg.setTexture(bg_t);

	Image fg_image;
	fg_image.loadFromFile("images/stuff1.png");
	fg_image.createMaskFromColor(Color(35, 71, 35));
	Texture fg_t;
	fg_t.loadFromImage(fg_image);
	Sprite s_fg;
	s_fg.setTexture(fg_t);

	Image ss_image;
	ss_image.loadFromFile("images/stuff.png");
	ss_image.createMaskFromColor(Color(255, 255, 255));
	Texture ss_t;
	ss_t.loadFromImage(ss_image);
	Sprite s_ss[2];
	s_ss[0].setTexture(ss_t);
	s_ss[1].setTexture(ss_t);
	s_ss[0].setTextureRect(IntRect(64, 0, 4, 4));
	s_ss[1].setTextureRect(IntRect(64, 0, 4, 4));
	s_ss[0].setPosition(553, 148);
	s_ss[1].setPosition(653, 148);

	Image stuff_image;
	stuff_image.loadFromFile("images/stuff.png");
	stuff_image.createMaskFromColor(Color(255, 255, 255));
	Texture stuff_t;
	stuff_t.loadFromImage(stuff_image);
	Sprite s_stuff[24];
	for (int i = 0; i < 24; i++)
	{
		s_stuff[i].setTexture(stuff_t);
		if (i % 2 == 0) s_stuff[i].setTextureRect(IntRect(0, 0, 32, 32)); 
		else s_stuff[i].setTextureRect(IntRect(32, 0, 32, 32));
	}

	//Координаты кнопок
	if (true)
	{
		s_stuff[0].setPosition(166, 120);
		s_stuff[1].setPosition(216, 120);

		s_stuff[2].setPosition(166, 159);
		s_stuff[3].setPosition(215, 159);

		s_stuff[4].setPosition(166, 198);
		s_stuff[5].setPosition(215, 198);

		s_stuff[6].setPosition(204, 639);
		s_stuff[7].setPosition(257, 639);

		s_stuff[8].setPosition(410, 639);
		s_stuff[9].setPosition(463, 639);

		s_stuff[10].setPosition(1242, 120);
		s_stuff[11].setPosition(1292, 120);

		s_stuff[12].setPosition(1242, 159);
		s_stuff[13].setPosition(1292, 159);

		s_stuff[14].setPosition(1242, 198);
		s_stuff[15].setPosition(1292, 198);

		s_stuff[16].setPosition(878, 639);
		s_stuff[17].setPosition(931, 639);

		s_stuff[18].setPosition(1082, 639);
		s_stuff[19].setPosition(1135, 639);

		s_stuff[20].setPosition(324, 403);
		s_stuff[21].setPosition(375, 403);

		s_stuff[22].setPosition(928, 403);
		s_stuff[23].setPosition(981, 403);
	}

	RenderWindow window(sf::VideoMode(sw, sh), "Oscilograf", Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, sw, sh));
	window.setPosition(Vector2i(0, 0));
	Clock clock;
	getplayercoordinateforview(int(sw / 2), int(sh / 2));

	while (window.isOpen())
	{
			float time = clock.getElapsedTime().asMilliseconds();
			clock.restart();
			alltime += time * timemodif;

			if (true)
			{
				float modif = 0.07;
				if (culldown < 5 && culldown + time * modif > 5)
					for (int i = 0; i < 24; i++) s_stuff[i].setColor(Color(255, 255, 255));

				if (culldown < 5) culldown += time * modif;
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				s_exit.setColor(Color::Green);
				window.draw(s_exit);
				window.display();
				Sleep(300);
				window.close();
			}

			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(pixelPos);
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
						if (true)
						{
							int pressedbut = -1;
							for (int i = 0; i < 24; i++)
								if (s_stuff[i].getGlobalBounds().contains(pos.x, pos.y))
									pressedbut = i;

							if (pressedbut == 0) xmod1 += 5;
							if (pressedbut == 1) xmod1 -= 5;
							if (pressedbut == 2) ymod1 -= 5;
							if (pressedbut == 3) ymod1 += 5;
							if (pressedbut == 4) powmod1 -= 0.01;
							if (pressedbut == 5) powmod1 += 0.01;
							if (pressedbut == 6 && power1 > 0.2) power1 -= 0.2;
							if (pressedbut == 7 && power1 < 12) power1 += 0.5;
							if (pressedbut == 8 && freq1 > 0) freq1 -= 2;
							if (pressedbut == 9 && freq1 < 50) freq1 += 2;

							if (pressedbut == 10) xmod2 += 5;
							if (pressedbut == 11) xmod2 -= 5;
							if (pressedbut == 12) ymod2 -= 5;
							if (pressedbut == 13) ymod2 += 5;
							if (pressedbut == 14) powmod2 -= 0.01;
							if (pressedbut == 15) powmod2 += 0.01;
							if (pressedbut == 16 && power2 > 0.2) power2 -= 0.2;
							if (pressedbut == 17 && power2 < 12) power2 += 0.5;
							if (pressedbut == 18 && freq2 > 0) freq2 -= 2;
							if (pressedbut == 19 && freq2 < 50) freq2 += 2;

							if (pressedbut == 20 && timemodif > 0.05) timemodif -= 0.05;
							if (pressedbut == 21 && timemodif < 2) timemodif += 0.05;

							if (pressedbut == 22 && viewmodif > 0.1) viewmodif -= 0.05;
							if (pressedbut == 23 && viewmodif < 2) viewmodif += 0.05;

							if (pressedbut != -1)
							{
								culldown = 0;
								s_stuff[pressedbut].setColor(Color(200, 200, 200));
							}

							if (power1 < 0.1) power1 = 0;
							if (power2 < 0.1) power2 = 0;

							power1 = evenly(power1, 10);
							power2 = evenly(power2, 10);
							timemodif = evenly(timemodif, 100);
							viewmodif = evenly(viewmodif, 100);
							powmod1 = evenly(powmod1, 100);
							powmod2 = evenly(powmod2, 100);

							if (viewmodif > 0.25)
							{
								s_ss[0].setScale(viewmodif, viewmodif);
								s_ss[1].setScale(viewmodif, viewmodif);
							}
							else
							{
								s_ss[0].setScale(0.25, 0.25);
								s_ss[1].setScale(0.25, 0.25);
							}
						}
					}
			}

			if (pos.y > 128)
			{
				if (stuffy > -42) stuffy -= 0.5 * time;
			}
			else
				if (stuffy < -1) stuffy += 0.5 * time;

			window.setView(view);
			window.clear();
			window.getSystemHandle();

			window.draw(s_bg);

			for (int i = 0; i < 3600 * (1 / viewmodif); i++)
			{
					int cords1[2];
					int cords2[2];

					cords1[0] = 268 + ymod1 + (i * viewmodif) - alltime * viewmodif;
					cords2[0] = 268 + ymod2 + (i * viewmodif) - alltime * viewmodif;

					cords1[1] = 175 + xmod1 + sin((i * freq1) * 0.0175) * power1 * 15 * powmod1 * viewmodif;
					cords2[1] = 175 + xmod2 + sin((i * freq2) * 0.0175) * power2 * 15 * powmod2 * viewmodif;

					s_ss[0].setPosition(cords1[0], cords1[1]);
					s_ss[1].setPosition(cords2[0], cords2[1]);

					window.draw(s_ss[0]);
					window.draw(s_ss[1]);

					for (int u = 0; u < freq1; u++)
					{
						int cords1[2];

						cords1[0] = 268 + ymod1 + i * viewmodif - alltime * viewmodif;

						cords1[1] = 175 + xmod1 + sin(((i * freq1) - u ) * 0.0175) * power1 * 15 * powmod1 * viewmodif;

						s_ss[0].setPosition(cords1[0], cords1[1]);

						window.draw(s_ss[0]);
					}

					for (int u = 0; u < freq2; u++)
					{
						int cords2[2];

						cords2[0] = 268 + ymod2 + i * viewmodif - alltime * viewmodif;

						cords2[1] = 175 + xmod2 + sin(((i * freq2) - u) * 0.0175) * power2 * 15 * powmod2 * viewmodif;

						s_ss[1].setPosition(cords2[0], cords2[1]);

						window.draw(s_ss[1]);
					}
			}

			if (alltime > 1440) alltime = 0;

			window.draw(s_fg);

			for (int i = 0; i < 24; i++) window.draw(s_stuff[i]);

			s_exit.setPosition(getviewx() + int(sw / 2) - 126, getviewy() - int(sh / 2) + stuffy);

			ostringstream thing;
			thing << power1;
			thing << " A   ";
			thing << freq1;
			thing << " Hz";
			text.setString(thing.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(282, 534);//задаем позицию текста, отступая от центра камеры
			window.draw(text);

			ostringstream thing1;
			thing1 << power2;
			thing1 << " A   ";
			thing1 << freq2;
			thing1 << " Hz";
			text.setString(thing1.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(952, 534);//задаем позицию текста, отступая от центра камеры
			window.draw(text);

			ostringstream thing3;
			thing3 << timemodif;
			text.setString(thing3.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(314, 316);//задаем позицию текста, отступая от центра камеры
			window.draw(text);

			ostringstream thing4;
			thing4 << viewmodif;
			text.setString(thing4.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(938, 316);//задаем позицию текста, отступая от центра камеры
			window.draw(text);

			window.draw(s_exit);
			window.display();
	}
	return 0;
}