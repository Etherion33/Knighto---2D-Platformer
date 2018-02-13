#ifndef GAME_STATE_GAMEPLAY_H
#define GAME_STATE_GAMEPLAY_H

#include <SFML\Graphics.hpp>

#include "Game_State.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"

enum class ActionState { NONE, PANNING };

class Game_State_Gameplay : public Game_State
{
private:

	ActionState actionState;

	sf::View gameView;
	sf::View guiView;

public:
	Level* level;
	Player* player;
	Entity_Manager* entmgr;
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();
	virtual void show_debug(const float dt);
	virtual void show_gui(const float dt);

	Player * getPlayer() { return player; }
	Level * getLevel() { return level; }
	Game_State_Gameplay(Game* game, std::string level);
	~Game_State_Gameplay();

	bool loadEntities(Entity_Manager * entmgr,Level * level);
};
#endif // !GAME_STATE_GAMEPLAY_H
