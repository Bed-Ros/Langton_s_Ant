#include <SFML/Window.hpp>
#include "windows.h"

#include "TileMap.cpp"
#include "TileAnt.cpp"
#include "StepsAnt.cpp"

//Направление left right forward backward
//Цвет green blue red ...
//
//0 right	white
//1 left	red
//
//underfoot white => paint red => turn left
//underfoot red => paint white => turn right 


int main()
{
	//Размер окна
	const static int window_width = 1280;
	const static int window_height = 720;

	//Размер плитки
	static int tile_size = 61;

	//Размеры матрицы
	static int w_matrix_size = window_width/tile_size;
	static int h_matrix_size = window_height/tile_size;

	// Массив цветов плитки
	sf::Color **level_colors = new sf::Color* [h_matrix_size];
	for (int i = 0; i < h_matrix_size; ++i) {
		level_colors[i] = new sf::Color[w_matrix_size];
	}
	
	// Заливка белым цветом
	for (int i = 0; i < h_matrix_size; ++i) {
		for (int j = 0; j < w_matrix_size; ++j)
		level_colors[i][j] = sf::Color::White;
	}

	//Первоначальное положение муравья
	int ant_x = w_matrix_size / 2;
	int ant_y = h_matrix_size / 2;

	//Текстура муравья
	//std::string ant_texture = "ant.png";
	std::string ant_texture = "dot.png";	

	// Создать карту из массива уровня
	TileMap map;
	if (!map.load(sf::Vector2u(tile_size, tile_size), level_colors, w_matrix_size, h_matrix_size))
		return -1;
	//Создать муравья
	TileAnt ant;
	if (!ant.load(ant_texture, sf::Vector2u(tile_size, tile_size), sf::Vector2u(ant_x, ant_y)))
		return -1;
	//Шаги муравья
	StepsAnt steps;	
	steps.Add(sf::Color::White, "right");
	steps.Add(sf::Color::Red, "left");
	steps.LoopList();

	// Создание окна
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Langton's Ant");

	//Главный цикл
	while (window.isOpen())
	{
		bool walking = true;

		//Обработка событий
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Закрытие
			if (event.type == sf::Event::Closed)
				window.close();
			//Управление
			if (event.type == sf::Event::KeyPressed) {
				//Настройки
				if (event.key.code == sf::Keyboard::Escape)
					walking = false;
				//Ручное управление муравьем(на первое время)
				if (event.key.code == sf::Keyboard::W)
					ant.go_up();
				if (event.key.code == sf::Keyboard::S)
					ant.go_down();
				if (event.key.code == sf::Keyboard::A)
					ant.go_left();
				if (event.key.code == sf::Keyboard::D)
					ant.go_right();
			}
		}
		//Отрисовка
		window.clear();
		window.draw(map);
		window.draw(ant);
		window.display();

		//Алгоритм ходьбы
		if (walking) {
			//получить цвет плитки под муравьем
			sf::Color underfoot_color = map.colors[ant.y][ant.x];
			//узнать следующий шаг по цвету плитки
			step* next_step = steps.NextStep(underfoot_color);
			//заменить цвет плитки
			map.set_color(ant.x, ant.y, next_step->color);
			//сказать муравью повернуть
			ant.turn(next_step->turn);
		}
		
		Sleep(1000);
	}

	return 0;
}