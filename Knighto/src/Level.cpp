#include "../include/Level.h"
#include <fstream>
#include <string>
//void Level::load(const std::string & filename, unsigned int width, unsigned int height, std::map<std::string, Tile>& tileAtlas)

void Level::loadByText(const std::string & filename, std::map<std::string, Tile>& tileAtlas)
{
	std::ifstream inputFile;
	inputFile.open(filename, std::ios::in);
	if (inputFile.is_open()) {
		this->m_levelName = filename;
		inputFile >> this->m_width;
		inputFile >> this->m_height;

		for (unsigned int y = 0; y <= this->m_height; ++y)
		{
			for (unsigned int x = 0; x <= this->m_width; ++x)
			{
				char type;
				inputFile >> type;
				switch (type)
				{
				default:
				case '.':
					this->tiles.push_back(tileAtlas.at("air"));
					break;
				case 'G':
					this->tiles.push_back(tileAtlas.at("grass"));
					break;
				case 'F':
					this->tiles.push_back(tileAtlas.at("forest"));
					break;
				case 'W':
					this->tiles.push_back(tileAtlas.at("water"));
					break;
				case 'D':
					this->tiles.push_back(tileAtlas.at("dirt"));
					break;
				case 'B':
					this->tiles.push_back(tileAtlas.at("brick"));
					break;
				case 'P':
					this->tiles.push_back(tileAtlas.at("playerSpawn"));
					this->m_startPos = { (int)x * (int)m_TileSize, (int)y * (int)m_TileSize };
					break;
				case 'M':
					this->tiles.push_back(tileAtlas.at("monsterSpawn"));
					this->monsterSpawns.push_back({ (int)x * (int)m_TileSize,(int)y * (int) m_TileSize });
					break;
				case 'C':
					this->tiles.push_back(tileAtlas.at("chest"));
					this->chestSpawns.push_back({ (int)x * (int)m_TileSize,(int)y * (int)m_TileSize });
					break;
				case 'I':
					this->tiles.push_back(tileAtlas.at("itemSpawn"));
					this->itemSpawns.push_back({ (int)x * (int)m_TileSize,(int)y * (int)m_TileSize });
					break;
				}
				Tile& tile = this->tiles.back();
				tile.m_TileId = { x* y* m_TileSize };
				tile.m_TilePos = { (float)x*m_TileSize,(float)y * m_TileSize };
			}
		}
	}
	inputFile.close();
}

void Level::create(const std::string& filename, unsigned int width, unsigned int height, std::map<std::string, Tile>& tileAtlas)

{
	std::ofstream outputFileText;

	this->m_width = width;
	this->m_height = height;

	for (unsigned int y = 0; y < this->m_height; ++y)
	{
		for (unsigned int x = 0; x < this->m_width; ++x)
		{
			sf::Vector2f pos;
			pos.x = x * this->m_TileSize;
			pos.y = y * this->m_TileSize;
			if (y == 0) {
				this->tiles.push_back(tileAtlas.at("brick"));
				this->tiles[y*this->m_width + x].m_TileType = TileType::BRICK;
			}
			else if (y == (this->m_height - 1)) {
				this->tiles.push_back(tileAtlas.at("brick"));
				this->tiles[y*this->m_width + x].m_TileType = TileType::BRICK;
				this->tiles[y*this->m_width + x].isSolid = true;
			}
			else if (x == 0 || x == (this->m_width - 1)) {
				this->tiles.push_back(tileAtlas.at("brick"));
				this->tiles[y*this->m_width + x].m_TileType = TileType::BRICK;
				this->tiles[y*this->m_width + x].isSolid = true;
			}
			else {
				this->tiles.push_back(tileAtlas.at("air"));
				this->tiles[y*this->m_width + x].m_TileType = TileType::AIR;
				this->tiles[y*this->m_width + x].isSolid = false;
			}
		}
	}

	outputFileText.open(filename, std::ios::out);
	outputFileText << width << std::endl;
	outputFileText << height << std::endl;

	for (unsigned int y = 0; y < this->m_height; ++y)
	{
		for (unsigned int x = 0; x < this->m_width; ++x)
		{
			sf::Vector2f pos;
			pos.x = x * this->m_TileSize;
			pos.y = y * this->m_TileSize;
			switch (tiles[y*this->m_width + x].m_TileType)
			{
			case TileType::AIR: 
				outputFileText << '.';
				break;
			case TileType::GRASS:
				outputFileText << 'G';
				break;
			case TileType::FOREST:
				outputFileText << 'F';
				break;
			case TileType::WATER:
				outputFileText << 'W';
				break;
			case TileType::DIRT:
				outputFileText << 'D';
				break;
			case TileType::BRICK:
				outputFileText << 'B';
				break;
			case TileType::PLAYER_SPAWN:
				outputFileText << 'P';
				break;
			case TileType::MONSTER_SPAWN:
				outputFileText << 'M';
				break;
			case TileType::CHEST:
				outputFileText << 'C';
				break;
			case TileType::ITEM:
				outputFileText << 'I';
				break;
			default:
				break;
			}
		}
		outputFileText << std::endl;
	}
	outputFileText.close();
}

void Level::save(const std::string & filename)
{
	std::ofstream outputFile;
	outputFile.open(filename, std::ios::out | std::ios::binary);
	outputFile.write((char*)&m_width, sizeof(int));
	outputFile.write((char*)&m_height, sizeof(int));
	for (auto tile : this->tiles)
	{
		outputFile.write((char*)&tile.m_TileType, sizeof(int));
	}
	outputFile.close();
}

void Level::update(float dt)
{
	
}

void Level::draw(sf::RenderWindow& window, float dt)
{
	for (int y = 0; y < this->m_height; ++y)
	{
		for (int x = 0; x < this->m_width; ++x)
		{
			if (x < 0 || y < 0) { continue; }
			sf::Vector2f pos;
			pos.x = x * this->m_TileSize;
			pos.y = y * this->m_TileSize;
			//this->tiles[y*this->width + x].m_TileSprite.setPosition(pos);
			this->tiles[y*this->m_width + x].m_TileAnimatedSprite.setPosition(pos);
			this->tiles[y*this->m_width + x].m_TilePos = pos;
			if (this->tiles[y*this->m_width + x].m_TileType == TileType::BRICK || 
				this->tiles[y*this->m_width + x].m_TileType == TileType::GRASS ||
				this->tiles[y*this->m_width + x].m_TileType == TileType::DIRT  ||
				this->tiles[y*this->m_width + x].m_TileType == TileType::FOREST) this->tiles[y*this->m_width + x].isSolid = true;
			else {
				this->tiles[y*this->m_width + x].isSolid = false;
			}
			/* Draw the tile */
			if (this->tiles[y*this->m_width + x].m_isVisible) {
				this->tiles[y*this->m_width + x].draw(window, dt);
			}
		}
	}
}


unsigned int Level::ConvertCoords(unsigned int l_x, unsigned int l_y)
{
	return (l_y* this->m_width) + l_x;
}

Tile* Level::GetTile(unsigned int l_x, unsigned int l_y)
{
	if (l_x < this->m_width && l_y < this->m_height) {
		return &tiles[(l_y* this->m_width) + l_x];
	}
	else
	{
		return nullptr;
	}
}

Tile* Level::GetDefaultTile()
{
	Tile* tile = new Tile();
	return tile;
}
