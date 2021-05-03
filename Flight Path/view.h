#include <SFML/Graphics.hpp>
int viewX, viewY;
sf::View view;

void getplayercoordinateforview(float x, float y, int sw, int sh) { //функция для считывания координат игрока
	viewX = int(x); viewY = int(y);//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < int(sw / 2)) viewX = int(sw / 2);//убираем из вида левую сторону
	if (y < int(sh / 2)) viewY = int(sh / 2);
	if (x > 5000 - int(sw / 2)) viewX = 5000 - int(sw / 2);//убираем из вида левую сторону
	if (y > 3100 - int(sh / 2)) viewY = 3100 - int(sh / 2);//убираем из вида левую сторону

	view.setCenter(viewX, viewY); //следим за игроком, передавая его координаты камере. +100 - сместили камеру по иксу вправо. эксперементируйте
}
void setposview(float x, float y)
{
	viewX = int(x); viewY = int(y);
	view.setCenter(viewX, viewY);
}
int getviewx() { return(viewX); }
int getviewy() { return(viewY); }


