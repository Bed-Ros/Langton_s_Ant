#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(sf::Vector2u tileSize, const sf::Color* tiles_color, unsigned int width, unsigned int height)
	{
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
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[3].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[1].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				//присвоить цвет плитке
				for (int c = 0; c < 4; ++c) {
					quad[c].color = tiles_color[i + j * width];
				}
			}

		return true;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
};