#include <SFML/Graphics.hpp>

class TileAnt : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u textureSize, sf::Vector2u tileSize, sf::Vector2u location = sf::Vector2u(0, 0), std::string direction = "up")
	{
		// загрузка файла текстур
		if (!a_tileset.loadFromFile(tileset))
			return false;

		a_vertices.setPrimitiveType(sf::Quads);
		a_vertices.resize(4);
		//
		a_location = location;
		a_tile_size = tileSize;
		a_texture_size = textureSize;
		//назначение первоначальной позиции
		update_location();
		//назначение первоначальной текстуры
		update_texture(direction);

		return true;
	}

	void go_up() {
		a_location -= sf::Vector2u(0, 1);
		update_location();
		update_texture("up");
	}

	void go_down() {
		a_location += sf::Vector2u(0, 1);
		update_location();
		update_texture("down");
	}

	void go_left() {
		a_location -= sf::Vector2u(1, 0);
		update_location();
		update_texture("left");
	}

	void go_right() {
		a_location += sf::Vector2u(1, 0);
		update_location();
		update_texture("right");
	}

private:

	void update_location() {
		a_vertices[0].position = sf::Vector2f(a_location.x * a_tile_size.x, a_location.y * a_tile_size.y);
		a_vertices[1].position = sf::Vector2f((a_location.x + 1) * a_tile_size.x, a_location.y * a_tile_size.y);
		a_vertices[2].position = sf::Vector2f((a_location.x + 1) * a_tile_size.x, (a_location.y + 1) * a_tile_size.y);
		a_vertices[3].position = sf::Vector2f(a_location.x * a_tile_size.x, (a_location.y + 1) * a_tile_size.y);
	}

	void update_texture(std::string direction) {

		if (direction == "right") {
			a_vertices[0].texCoords = sf::Vector2f(0, a_texture_size.y);
			a_vertices[1].texCoords = sf::Vector2f(0, 0);
			a_vertices[2].texCoords = sf::Vector2f(a_texture_size.x, 0);
			a_vertices[3].texCoords = sf::Vector2f(a_texture_size.x, a_texture_size.y);			
		}
		else if (direction == "left") {			
			a_vertices[0].texCoords = sf::Vector2f(a_texture_size.x, 0);
			a_vertices[1].texCoords = sf::Vector2f(a_texture_size.x, a_texture_size.y);
			a_vertices[2].texCoords = sf::Vector2f(0, a_texture_size.y);
			a_vertices[3].texCoords = sf::Vector2f(0, 0);
		}
		else if (direction == "down") {			
			a_vertices[0].texCoords = sf::Vector2f(a_texture_size.x, a_texture_size.y);
			a_vertices[1].texCoords = sf::Vector2f(0, a_texture_size.y);
			a_vertices[2].texCoords = sf::Vector2f(0, 0);
			a_vertices[3].texCoords = sf::Vector2f(a_texture_size.x, 0);
		}
		else { // по умолчанию up
			a_vertices[0].texCoords = sf::Vector2f(0, 0);
			a_vertices[1].texCoords = sf::Vector2f(a_texture_size.x, 0);
			a_vertices[2].texCoords = sf::Vector2f(a_texture_size.x, a_texture_size.y);
			a_vertices[3].texCoords = sf::Vector2f(0, a_texture_size.y);
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &a_tileset;

		// draw the vertex array
		target.draw(a_vertices, states);
	}

	sf::VertexArray a_vertices;
	sf::Texture a_tileset;
	sf::Vector2u a_location;
	sf::Vector2u a_texture_size;
	sf::Vector2u a_tile_size;

};