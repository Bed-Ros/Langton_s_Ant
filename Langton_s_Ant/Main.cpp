#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include "windows.h"

#include "TileMap.cpp"
#include "TileAnt.cpp"
#include "StepsAnt.cpp"

//Размер окна
const static int window_width = 1280;
const static int window_height = 720;

//Размер плитки
static int tile_size = 32;

//Размеры матрицы
static int w_matrix_size = window_width / tile_size + 1;
static int h_matrix_size = window_height / tile_size + 1;

//Вектор цветов плитки с заливкой белым цветом
std::vector<std::vector<sf::Color>> level_colors(w_matrix_size, std::vector<sf::Color>(h_matrix_size, sf::Color::White));

//Первоначальное положение муравья
int ant_x = w_matrix_size / 2;
int ant_y = h_matrix_size / 2;

//Текстура муравья
//std::string ant_texture = "ant.png";
std::string ant_texture = "dot.png";

//Создать карту из массива уровня
TileMap map(sf::Vector2u(tile_size, tile_size), level_colors);

//Создать муравья
TileAnt ant(ant_texture, sf::Vector2u(tile_size, tile_size), sf::Vector2u(ant_x, ant_y));

int walking = 0;

StepsAnt steps;

void stop_btn_foo() {
	walking = 0;
	TileAnt result_ant(ant_texture, sf::Vector2u(tile_size, tile_size), sf::Vector2u(ant_x, ant_y));
	ant = result_ant;
	TileMap result_map(sf::Vector2u(tile_size, tile_size), level_colors);
	map = result_map;	
}

void settings_btn_foo() {
	walking = 0;

}

void about_btn_foo() {
	
}

void settings_win_exit_btn_foo(tgui::ChildWindow::Ptr settings_win) {

	settings_win->setVisible(false);
}

void loadWidgets(tgui::Gui& gui) {
	int bar_height = 30;
	//Play
	auto play_btn = tgui::BitmapButton::create();
	play_btn->setImage(tgui::Texture::Texture("./play.png"));
	play_btn->setSize(bar_height, bar_height);
	play_btn->setImageScaling(1);
	play_btn->connect("pressed", [=]() { walking = 10; });
	gui.add(play_btn);
	//Pause
	auto pause_btn = tgui::BitmapButton::create();
	pause_btn->setImage(tgui::Texture::Texture("./pause.png"));
	pause_btn->setSize(bar_height, bar_height);
	pause_btn->setImageScaling(1);
	pause_btn->setPosition(bar_height, 0);
	pause_btn->connect("pressed", [=]() { walking = 0; });
	gui.add(pause_btn);
	//Шаг вперед
	auto arrow_btn = tgui::BitmapButton::create();
	arrow_btn->setImage(tgui::Texture::Texture("./arrow.png"));
	arrow_btn->setSize(bar_height, bar_height);
	arrow_btn->setImageScaling(1);
	arrow_btn->setPosition(bar_height * 2, 0);
	arrow_btn->connect("pressed", [=]() { walking = 1; });
	gui.add(arrow_btn);
	//Стоп
	auto stop_btn = tgui::BitmapButton::create();
	stop_btn->setImage(tgui::Texture::Texture("./stop.png"));
	stop_btn->setSize(bar_height, bar_height);
	stop_btn->setImageScaling(1);
	stop_btn->setPosition(bar_height * 3, 0);
	stop_btn->connect("pressed", stop_btn_foo);
	gui.add(stop_btn);
	//Настройки????????????
	auto settings_win = tgui::ChildWindow::create(L"Настройки",0);
	settings_win->setVisible(false);
	gui.add(settings_win);

	auto settings_win_exit_btn = tgui::Button::create(L"Сохранить");
	settings_win_exit_btn->setPosition(20, 30);
	settings_win_exit_btn->connect("pressed", settings_win_exit_btn_foo, settings_win);
	settings_win->add(settings_win_exit_btn);

	auto settings_btn = tgui::Button::create(L"Настройки");
	settings_btn->setPosition(bar_height * 4, 0);
	settings_btn->setSize(80, 30);
	settings_btn->connect("pressed", [=]() {walking = 0; settings_win->setVisible(true); });
	gui.add(settings_btn);
	//О программе????????????
	auto about_win = tgui::ChildWindow::create(L"О программе", 0);
	about_win->setSize(100, 50);
	about_win->setVisible(false);
	about_win->setKeepInParent(true);
	gui.add(about_win);

	auto about_win_exit_btn = tgui::Button::create(L"OK");
	about_win_exit_btn->setPosition(20, 30);
	about_win_exit_btn->connect("pressed", [=]() { about_win->setVisible(false); });
	about_win->add(about_win_exit_btn);

	auto about_btn = tgui::Button::create(L"О программе");
	about_btn->setPosition(bar_height * 4 + 80, 0);
	about_btn->setSize(100, 30);
	about_btn->connect("pressed", [=]() { about_win->setVisible(true); });
	gui.add(about_btn);
}

int main()
{
	//Шаги муравья
	steps.Add(sf::Color::Black, "right"); 
	steps.Add(sf::Color::White, "left");
	steps.LoopList();

	// Создание окна
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Langton's Ant");

	tgui::Gui gui(window);
	loadWidgets(gui);		

	//Главный цикл
	while (window.isOpen())
	{
		//Обработка событий
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Закрытие
			if (event.type == sf::Event::Closed)
				window.close();				
			
			gui.handleEvent(event);
		}
		//Отрисовка
		window.clear();
		window.draw(map);
		window.draw(ant);
		gui.draw();
		window.display();

		//Алгоритм ходьбы
		if (walking > 0) {
			//получить цвет плитки под муравьем
			sf::Color underfoot_color = map.get_color(ant.x, ant.y);
			//узнать следующий шаг по цвету плитки
			step* next_step = steps.NextStep(underfoot_color);
			//заменить цвет плитки
			map.set_color(ant.x, ant.y, next_step->color);
			//сказать муравью повернуть
			ant.turn(next_step->turn);
			//Sleep(100);
			if (walking == 1)walking = 0;
		}
	}

	return 0;
}