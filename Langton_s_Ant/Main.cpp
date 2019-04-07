#include <SFML/Window.hpp>
#include "windows.h"

#include "TileMap.cpp"
#include "TileAnt.cpp"
#include "StepsAnt.cpp"

//����������� left right forward backward
//���� green blue red ...
//
//0 right	white
//1 left	red
//
//underfoot white => paint red => turn left
//underfoot red => paint white => turn right 


int main()
{
	//������ ����
	const static int window_width = 1280;
	const static int window_height = 720;

	//������ ������
	static int tile_size = 61;

	//������� �������
	static int w_matrix_size = window_width/tile_size;
	static int h_matrix_size = window_height/tile_size;

	// ������ ������ ������
	sf::Color **level_colors = new sf::Color* [h_matrix_size];
	for (int i = 0; i < h_matrix_size; ++i) {
		level_colors[i] = new sf::Color[w_matrix_size];
	}
	
	// ������� ����� ������
	for (int i = 0; i < h_matrix_size; ++i) {
		for (int j = 0; j < w_matrix_size; ++j)
		level_colors[i][j] = sf::Color::White;
	}

	//�������������� ��������� �������
	int ant_x = w_matrix_size / 2;
	int ant_y = h_matrix_size / 2;

	//�������� �������
	//std::string ant_texture = "ant.png";
	std::string ant_texture = "dot.png";	

	// ������� ����� �� ������� ������
	TileMap map;
	if (!map.load(sf::Vector2u(tile_size, tile_size), level_colors, w_matrix_size, h_matrix_size))
		return -1;
	//������� �������
	TileAnt ant;
	if (!ant.load(ant_texture, sf::Vector2u(tile_size, tile_size), sf::Vector2u(ant_x, ant_y)))
		return -1;
	//���� �������
	StepsAnt steps;	
	steps.Add(sf::Color::White, "right");
	steps.Add(sf::Color::Red, "left");
	steps.LoopList();

	// �������� ����
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Langton's Ant");

	//������� ����
	while (window.isOpen())
	{
		bool walking = true;

		//��������� �������
		sf::Event event;
		while (window.pollEvent(event))
		{
			//��������
			if (event.type == sf::Event::Closed)
				window.close();
			//����������
			if (event.type == sf::Event::KeyPressed) {
				//���������
				if (event.key.code == sf::Keyboard::Escape)
					walking = false;
				//������ ���������� ��������(�� ������ �����)
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
		//���������
		window.clear();
		window.draw(map);
		window.draw(ant);
		window.display();

		//�������� ������
		if (walking) {
			//�������� ���� ������ ��� ��������
			sf::Color underfoot_color = map.colors[ant.y][ant.x];
			//������ ��������� ��� �� ����� ������
			step* next_step = steps.NextStep(underfoot_color);
			//�������� ���� ������
			map.set_color(ant.x, ant.y, next_step->color);
			//������� ������� ���������
			ant.turn(next_step->turn);
		}
		
		Sleep(1000);
	}

	return 0;
}