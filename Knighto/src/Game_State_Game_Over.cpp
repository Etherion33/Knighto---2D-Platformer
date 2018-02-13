#include "../include/Game_State.h"
#include "../include/Game_State_Menu.h"
#include "../include/Game_State_Gameplay.h"
#include "../include/Game_State_Game_Over.h"

void Game_State_Game_Over::show_debug(const float dt)
{

}

void Game_State_Game_Over::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);

	this->game->window.setView(this->view);

	sf::Text game_over,command;
	game_over.setString("Game over");
	game_over.setCharacterSize(72);
	game_over.setFont(this->game->fntmgr.getRef("runescape"));
	game_over.setPosition({ this->game->window.getSize().x*0.1f,this->game->window.getSize().y*0.3f});
	command.setString("Press Escape to exit or \n press Space to go back to main menu");
	command.setFont(this->game->fntmgr.getRef("runescape"));
	command.setCharacterSize(48);
	command.setPosition({ this->game->window.getSize().x*0.1f,this->game->window.getSize().y*0.6f });

	this->game->window.draw(game_over);

	this->game->window.draw(command);

}

void Game_State_Game_Over::update(const float dt)
{
	ImGui::SFML::Update(this->game->window, sf::seconds(dt));				//ImGui update - needed for drawing gui
	return;
}

void Game_State_Game_Over::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
		/* Resize the window */
		case sf::Event::Resized:
		{
			this->view.setSize(event.size.width, event.size.height);
			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();


			if (event.key.code == sf::Keyboard::Space) {
				this->game->popState();
			}
			break;
		}
		default: break;
		}
	}

	return;
}

Game_State_Game_Over::Game_State_Game_Over(Game * game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	//pos *= 0.5f;
	//this->view.setCenter(pos);
}