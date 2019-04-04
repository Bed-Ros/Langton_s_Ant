#include <SFML/Window.hpp>

#include "TileMap.cpp"
#include "TileAnt.cpp"

int main()
{
	//������� �������
	const static int w_matrix_size = 20;
	const static int h_matrix_size = 10;

	// ������ ������ ������
	sf::Color level_colors[w_matrix_size*h_matrix_size];
	// ������� ����� ������
	for (int i = 0; i < w_matrix_size*h_matrix_size; ++i) {
		level_colors[i] = sf::Color::White;
	}

	static int tile_size = 64;
	static int texture_size = 380;

	static int window_width = tile_size * w_matrix_size;
	static int window_height = tile_size * h_matrix_size;

	int ant_x = w_matrix_size / 2;
	int ant_y = h_matrix_size / 2;

	std::string ant_texture = "ant.png";

	// �������� ����
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Langton's Ant");

	// ������� ����� �� ������� ������
	TileMap map;
	if (!map.load(sf::Vector2u(tile_size, tile_size), level_colors, w_matrix_size, h_matrix_size))
		return -1;
	//������� �������
	TileAnt ant;
	if (!ant.load(ant_texture, sf::Vector2u(texture_size, texture_size), sf::Vector2u(tile_size, tile_size), sf::Vector2u(ant_x, ant_y)))
		return -1;

	// ������� ����
	while (window.isOpen())
	{
		// ��������� �������
		sf::Event event;
		while (window.pollEvent(event))
		{
			// ��������
			if (event.type == sf::Event::Closed)
				window.close();
			//����������
			if (event.type == sf::Event::KeyPressed) {
				//���������
				if (event.key.code == sf::Keyboard::Escape);
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
	}

	return 0;
}