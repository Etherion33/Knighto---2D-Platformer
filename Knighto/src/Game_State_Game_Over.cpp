#include "..\include\Game_State_Game_Over.h"

void Game_State_Game_Over::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);

	this->game->window.setView(this->view);
}

void Game_State_Game_Over::update(const float dt)
{

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
}
