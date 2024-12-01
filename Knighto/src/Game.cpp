#include <stack>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "../include/Game.h"
#include "../include/Game_State.h"

void Game::loadTextures()
{
	texmgr.load("grass", "Res/Textures/grass.png");
	texmgr.load("wood", "Res/Textures/wood.png");
	texmgr.load("knight", "Res/Textures/wood.png");
	texmgr.load("orc", "Res/Textures/orc.png");
	texmgr.load("knightSS", "Res/Textures/knight_outline.png");
	texmgr.load("orcSS", "Res/Textures/orc_middle_outline.png");
	texmgr.load("shaman", "Res/Textures/Shaman/shaman.png");
	texmgr.load("shamanSS", "Res/Textures/Shaman/shaman_outline.png");
	texmgr.load("tileset", "Res/Textures/tileset.png");
	texmgr.load("background", "Res/Textures/bg.png");
	texmgr.load("heart", "Res/Textures/heart.png");
	texmgr.load("coin", "Res/Textures/coin.png");
	texmgr.load("keyboard", "Res/Textures/keyboard.png");

}

void Game::loadTiles()
{
	std::map<std::string, Animation> staticAnim;
	staticAnim["air"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["air"].addFrame(sf::IntRect(56, 0, 8, 8));
	staticAnim["grass"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["grass"].addFrame(sf::IntRect(0, 0, 8, 8));
	staticAnim["grass"].addFrame(sf::IntRect(8, 0, 8, 8));
	staticAnim["grass"].addFrame(sf::IntRect(16, 0, 8, 8));
	staticAnim["grass"].addFrame(sf::IntRect(24, 0, 8, 8));
	staticAnim["dirt"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["dirt"].addFrame(sf::IntRect(0, 24, 8, 8));
	staticAnim["dirt"].addFrame(sf::IntRect(8, 24, 8, 8));
	staticAnim["dirt"].addFrame(sf::IntRect(16, 24, 8, 8));
	staticAnim["dirt"].addFrame(sf::IntRect(24, 24, 8, 8));
	staticAnim["forest"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["forest"].addFrame(sf::IntRect(112, 0, 8, 8));
	staticAnim["water"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["water"].addFrame(sf::IntRect(0, 104, 8, 8));
	staticAnim["water"].addFrame(sf::IntRect(8, 104, 8, 8));
	staticAnim["water"].addFrame(sf::IntRect(16, 104, 8, 8));
	staticAnim["water"].addFrame(sf::IntRect(24, 104, 8, 8));

	staticAnim["brick"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["brick"].addFrame(sf::IntRect(8, 168, 8, 8));

	staticAnim["chest"].setSpriteSheet(texmgr.getRef("tileset"));
	staticAnim["chest"].addFrame(sf::IntRect(24, 224, 8, 8));

	this->tileAtlas["air"] = Tile(staticAnim["air"], TileType::AIR, { 0.f,0.f }, { 0.0f,0.0f });
	this->tileAtlas["grass"] = Tile(staticAnim["grass"], TileType::GRASS, { 0.f,0.f }, { 0.8f,0.0f });
	this->tileAtlas["dirt"] = Tile(staticAnim["dirt"], TileType::DIRT, { 0.f,0.f }, { 0.8f,0.0f });
	this->tileAtlas["forest"] = Tile(staticAnim["forest"], TileType::FOREST, { 0.f,0.f }, { 0.8f,0.0f });
	this->tileAtlas["water"] = Tile(staticAnim["water"], TileType::WATER, { 0.f,0.f }, { 0.8f,0.8f });
	this->tileAtlas["brick"] = Tile(staticAnim["brick"], TileType::BRICK, { 0.f,0.f }, { 0.5f,0.0f });

	this->tileAtlas["playerSpawn"] = Tile(staticAnim["air"], TileType::PLAYER_SPAWN, { 0.f,0.f }, { 0.0f,0.0f });
	this->tileAtlas["monsterSpawn"] = Tile(staticAnim["air"], TileType::MONSTER_SPAWN, { 0.f,0.f }, { 0.0f,0.0f });
	this->tileAtlas["chest"] = Tile(staticAnim["chest"], TileType::CHEST, { 0.f,0.f }, { 0.0f,0.0f });
	this->tileAtlas["itemSpawn"] = Tile(staticAnim["air"], TileType::ITEM, { 0.f,0.f }, { 0.0f,0.0f });

}

void Game::loadFonts()
{
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromFileTTF("Res/Fonts/rs.ttf", 24.f);
	io.Fonts->AddFontFromFileTTF("Res/Fonts/mario_font.ttf", 12.f);
	io.Fonts->AddFontFromFileTTF("Res/Fonts/comic.ttf", 12.f);
	ImGui::SFML::UpdateFontTexture();

	fntmgr.load("comic", "Res/Fonts/comic.ttf");
	fntmgr.load("mario", "Res/Fonts/mario_font.ttf");
	fntmgr.load("runescape", "Res/Fonts/rs.ttf");
}

void Game::loadSounds()
{

}

void Game::pushState(Game_State* state)
{
	this->states.push(state);
	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();
}

void Game::changeState(Game_State* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);
}

Game_State* Game::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time mTimePerFrame = sf::seconds(1.f / 60.f);


	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		if (timeSinceLastUpdate > mTimePerFrame) {
			do {
				timeSinceLastUpdate -= mTimePerFrame;
				if (peekState() == nullptr) continue;
				peekState()->handleInput();
				peekState()->update(mTimePerFrame.asSeconds());
				this->window.clear(sf::Color::Black);
				peekState()->draw(mTimePerFrame.asSeconds());
			} while (timeSinceLastUpdate > mTimePerFrame);
			ImGui::SFML::Render(this->window);
			this->window.display();
		}
		else {
			sf::sleep(mTimePerFrame - timeSinceLastUpdate);
		}
	}
}

Game::Game()
{
	this->window.create(sf::VideoMode(1024, 768), "Knighto - 2D Platformer");
	//this->window.setFramerateLimit(60);
	ImGui::SFML::Init(this->window);

	this->loadTextures();
	this->loadTiles();
	this->loadFonts();	
	this->loadSounds();

	this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
	while (!this->states.empty()) popState();
	ImGui::SFML::Shutdown();
}