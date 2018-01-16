#include <SFML\Graphics.hpp>

#include <iostream>
#include "../include/Game_State_Menu.h"
#include "../include/Game_State_Gameplay.h"
#include "../include/Game_State_Game_Over.h"
#include "../include/Game_State.h"

void Game_State_Gameplay::show_debug(const float dt)
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Begin("Debug window");
	ImGui::Text("FPS: %lf", 1.f / dt);
	ImGui::Text("Window position: X : %d", this->game->window.getPosition().x); ImGui::SameLine(200); ImGui::Text("Y: %d", this->game->window.getPosition().y);
	ImGui::Text("Player position: X : %lf", entmgr->getByName("Knighto")->getPosition().x/8); ImGui::SameLine(220); ImGui::Text("Y: %lf", entmgr->getByName("Knighto")->getPosition().y/8);
	ImGui::Text("Player velocity: X : %lf",entmgr->getByName("Knighto")->getSpeed().x); ImGui::SameLine(220); ImGui::Text("Y: %lf", entmgr->getByName("Knighto")->getSpeed().y);
	ImGui::Text("Player size: X : %lf", entmgr->getByName("Knighto")->getSize().x); ImGui::SameLine(220); ImGui::Text("Y: %lf", entmgr->getByName("Knighto")->getSize().y);
	ImGui::Text("Player collision on X: %d", entmgr->getByName("Knighto")->getCollision().x); ImGui::SameLine(220); ImGui::Text("Y: %d", entmgr->getByName("Knighto")->getCollision().y);
	ImGui::Text("Player state: %d", entmgr->getByName("Knighto")->getState());
	ImGui::Text("Level width: %d", level->m_width); ImGui::SameLine(220); ImGui::Text(" height: %d", level->m_height);
	ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x/8, io.MousePos.y/8);
	ImGui::End();
}

void Game_State_Gameplay::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);
	this->game->window.setView(this->guiView);
	this->game->window.draw(this->game->background);

	this->game->window.setView(this->gameView);
	level->draw(this->game->window, dt);
	entmgr->draw(this->game->window, dt);
}

void Game_State_Gameplay::update(const float dt)
{
	ImGui::SFML::Update(this->game->window, sf::seconds(dt));				//ImGui update - needed for drawing gui
	this->gameView.setCenter(player->getPosition());	//set camera on player (scrolling view)
	//this->player->update(dt);
	//this->level->update(dt);			//update level(animations)
	entmgr->update(dt);	//update all entities 
	show_debug(dt); //show debug window
	return;
}

void Game_State_Gameplay::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		bool noKeyWasPressed = true;

		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			this->game->window.close();
			break;
		}
			/* Resize the window */
		case sf::Event::Resized:
		{
			gameView.setSize(event.size.width, event.size.height);
			guiView.setSize(event.size.width, event.size.height);
			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
			break;
		}
			/* if Key was pressed */
		case sf::Event::KeyPressed:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				player->handleInput("MoveLeft");											// move player to the left
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				player->handleInput("MoveRight");											// move player to the right
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				player->handleInput("Jump");					
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				player->handleInput("Attack");
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				player->setState(EntityState::Dying);
				this->game->pushState(new Game_State_Game_Over(this->game));
			}
			break;
		}
		default: break;
		}
	}

	return;
}

Game_State_Gameplay::Game_State_Gameplay(Game* game, std::string selectedLevel)
{
	this->game = game;
	this->entmgr = &game->entmgr;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);

	level = new Level(selectedLevel,this->game->tileAtlas);
	entmgr->setLevel(level);
	player = new Player(entmgr,this->game->texmgr.getRef("knightSS"));

	entmgr->add(player);
	//entmgr->add();
	//entmgr->add(new Enemy(entmgr,EnemyType::Skeleton, this->game->texmgr.getRef("orcSS"), { 125.f,100.f }));
	//entmgr->add(new Enemy(entmgr, EnemyType::Orc_Shaman, this->game->texmgr.getRef("shamanSS")));
	//entmgr->add(new Weapon(entmgr,WeaponType::SWORD));
	entmgr->getByName("Knighto")->setPosition({(float) level->m_startPos.x,(float) level->m_startPos.y });
	for (int i =0; i < level->monsterSpawns.size() ; i++)
	{
		entmgr->add(new Enemy(entmgr, EnemyType::Orc, this->game->texmgr.getRef("orcSS")));
		entmgr->getById(i + 1)->setPosition((float)level->monsterSpawns[i].x, (float)level->monsterSpawns[i].y);
	}
	for (int i = 0; i < entmgr->enCount(); i++)
	{
		std::cout << "Monster: " << entmgr->getById(i)->getName() << std::endl;
		std::cout << "ID:" << entmgr->getById(i)->getId() << std::endl;
		std::cout << "Position x: " << entmgr->getById(i)->getPosition().x << " y:" << entmgr->getById(i)->getPosition().y << std::endl;
	}
	std::cout << "Player starting position x:" << level->m_startPos.x << "y: " << level->m_startPos.y << std::endl;
	//sf::Vector2f center(player->getPlayerPos().x*0.5, player->getPlayerPos().y*0.5);
	//gameView.setCenter(center);

	sf::Vector2f centre(this->level->m_width / 2, this->level->m_height / 2);
	centre *= float(this->level->m_TileSize);
	gameView.setCenter(centre);
	gameView.zoom(0.25f);
	//player->setPosition(centre);

	this->actionState = ActionState::NONE;
}