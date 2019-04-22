#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	TileMap(sf::Vector2u tile_size, std::vector<std::vector<sf::Color>> tiles_color) 
	{
		m_colors = tiles_color;

		int width = m_colors.size();
		int	height = m_colors[0].size();

		// изменение размера массива вершин в соответствии с размером уровня
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// заполнение массива вершин одним квадратом на плитку
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// получить указатель на квадрат текущей плитки
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// определить его 4 угла
				quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
				quad[3].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
				quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
				quad[1].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

				//присвоить цвет плитке
				set_color(i, j, m_colors[i][j]);
			}
	}

	void set_color(int x, int y, sf::Color color) {
		int width = m_colors.size();
		sf::Vertex* quad = &m_vertices[(x + y * width) * 4];
		for (int c = 0; c < 4; ++c) {
			quad[c].color = color;
		}
		m_colors[x][y] = color;
	}

	sf::Color get_color(int x, int y) {
		return m_colors[x][y];
	}

private:
	sf::VertexArray m_vertices;
	std::vector<std::vector<sf::Color>> m_colors;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// draw the vertex array
		target.draw(m_vertices, states);
	}
};