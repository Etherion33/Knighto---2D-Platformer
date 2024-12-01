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
	ImGui::Text("Player position: X : %lf", entmgr->getByName("Knighto")->getPosition().x); ImGui::SameLine(300); ImGui::Text("Y: %lf", entmgr->getByName("Knighto")->getPosition().y);
	ImGui::Text("Player position / tileSize (8): X : %lf", entmgr->getByName("Knighto")->getPosition().x/8); ImGui::SameLine(300); ImGui::Text(" Y: %lf", entmgr->getByName("Knighto")->getPosition().y/8);
	ImGui::Text("Player velocity: X : %lf",entmgr->getByName("Knighto")->getSpeed().x); ImGui::SameLine(220); ImGui::Text("Y: %lf", entmgr->getByName("Knighto")->getSpeed().y);
	ImGui::Text("Player size: X : %lf", entmgr->getByName("Knighto")->getSize().x); ImGui::SameLine(220); ImGui::Text("Y: %lf", entmgr->getByName("Knighto")->getSize().y);
	ImGui::Text("Player collision on X: %d", entmgr->getByName("Knighto")->getCollision().x); ImGui::SameLine(220); ImGui::Text("Y: %d", entmgr->getByName("Knighto")->getCollision().y);
	ImGui::Text("Player state: %d", entmgr->getByName("Knighto")->getState());
	ImGui::Text("Player health: %d", entmgr->getByName("Knighto")->getHealth());
	ImGui::Text("Level width: %d", level->m_width); ImGui::SameLine(220); ImGui::Text(" height: %d", level->m_height);
	ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x/8, io.MousePos.y/8);
	ImGui::End();
}

void Game_State_Gameplay::show_gui(const float dt)
{
	ImGuiStyle& style = ImGui::GetStyle();

	if (ImGui::Begin("Player status", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings)) {
		//style.Alpha = 0;
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		unsigned int playerHealth = entmgr->getByName("Knighto")->getHealth();
		unsigned int playerScore = entmgr->getByName("Knighto")->getScore();
		ImGui::SetWindowFontScale(2.f);
		//ImGui::Text("HP:"); ImGui::SameLine(100.f); ImGui::Text("%d", playerHealth);
		if (playerHealth >= 90)
		{
			ImGui::Image(this->game->texmgr.getRef("heart"), { 64.f,64.f }); ImGui::SameLine(64.f);
			ImGui::Image(this->game->texmgr.getRef("heart"), { 64.f,64.f }); ImGui::SameLine(128.f);
			ImGui::Image(this->game->texmgr.getRef("heart"), { 64.f,64.f });  ImGui::SameLine(196.f);
		}
		else if (playerHealth < 90 && playerHealth >= 50)
		{
			ImGui::Image(this->game->texmgr.getRef("heart"), { 64.f,64.f });  ImGui::SameLine(64.f);
			ImGui::Image(this->game->texmgr.getRef("heart"), { 64.f,64.f });  ImGui::SameLine(128.f);
		}
		else if (playerHealth < 50)
		{
			ImGui::Image(this->game->texmgr.getRef("heart"), { 64.f,64.f });  ImGui::SameLine(64.f);
		}
		else {

		}
		ImGui::SameLine(200.f);
		ImGui::Text("Points: %d", playerScore); ImGui::SameLine(400.f); ImGui::Text("Level: %s", level->m_levelName.c_str());
		
	}
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
	this->gameView.setCenter(entmgr->getByName("Knighto")->getPosition());	//set camera on player (scrolling view)
	//this->player->update(dt);
	//this->level->update(dt);			//update level(animations)
	level->update(dt);
	entmgr->update(dt);	//update all entities 
	show_gui(dt);
	show_debug(dt); //show debug window
	//ImGui::ShowTestWindow();
	ImGui::EndFrame();
	return;
}

void Game_State_Gameplay::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(this->game->window, event);
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				player->handleInput("MoveLeft");											// move player to the left
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				player->handleInput("MoveRight");											// move player to the right
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				player->handleInput("Jump");					
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				player->handleInput("Attack");
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				this->game->pushState(new Game_State_Game_Over(this->game));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				entmgr->getByName("Knighto")->setPosition({(float)this->level->m_startPos.x,(float) this->level->m_startPos.y});
				entmgr->getByName("Knighto")->setState(EntityState::Idle);
				entmgr->getByName("Knighto")->resetHP();
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
	
	if (loadEntities(entmgr, level)) { std::cout << "\nEntities loaded !" << std::endl; }
	else { std::cerr << "Error occured while loading entities!" << std::endl; }

	for (int i = 0; i < entmgr->enCount(); i++)
	{
		std::cout << "Monster: " << entmgr->getById(i)->getName() << std::endl;
		std::cout << "ID:" << entmgr->getById(i)->getId() << std::endl;
		std::cout << "Position x: " << entmgr->getById(i)->getPosition().x << " y:" << entmgr->getById(i)->getPosition().y << std::endl;
	}
	//sf::Vector2f center(player->getPlayerPos().x*0.5, player->getPlayerPos().y*0.5);
	//gameView.setCenter(center);

	sf::Vector2f centre(this->level->m_width / 2, this->level->m_height / 2);
	centre *= float(this->level->m_TileSize);
	gameView.setCenter(centre);
	gameView.zoom(0.25f);
	//player->setPosition(centre);

	this->actionState = ActionState::NONE;
}

Game_State_Gameplay::~Game_State_Gameplay()
{
	level = nullptr;
	player = nullptr;
	entmgr = nullptr;
	delete level;
	delete player;
	delete entmgr;
}

bool Game_State_Gameplay::loadEntities(Entity_Manager * entmgr, Level * level)
{
	if (entmgr != nullptr && level != nullptr)
	{
		player = new Player(entmgr, this->game->texmgr.getRef("knightSS"));
		std::cout << "Player starting position x:" << level->m_startPos.x << "y: " << level->m_startPos.y << std::endl;
		player->setPosition({ (float)level->m_startPos.x,(float)level->m_startPos.y });
		entmgr->add(player);
		if (level->monsterSpawns.size() > 0 || level->itemSpawns.size() > 0)
		{
			int monsterSpawns = level->monsterSpawns.size() - 1;
			do
			{
				Enemy* enemy = new Enemy(entmgr, EnemyType::Orc_Shaman, this->game->texmgr.getRef("shamanSS"));
				enemy->setPosition((float)level->monsterSpawns[monsterSpawns].x, (float)level->monsterSpawns[monsterSpawns].y);
				entmgr->add(enemy);
				monsterSpawns--;
			} while (monsterSpawns >= 0);

			int itemSpawns = level->itemSpawns.size() - 1;
			do
			{
				Item * item = new Item(entmgr, ItemType::WEAPON, this->game->texmgr.getRef("coin"));
				item->setPosition((float)level->itemSpawns[itemSpawns].x, (float)level->itemSpawns[itemSpawns].y);
				entmgr->add(item);
				itemSpawns--;
			} while (itemSpawns >= 0);
			return true;
		}
		else {
			std::cout << "No entities found!";
			return true;
		}
	}
	return false;
}
