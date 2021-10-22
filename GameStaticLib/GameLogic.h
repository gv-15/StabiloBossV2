#pragma once

class Player;
class World;

class GameLogic
{
	World* m_pWorld;

public:
	GameLogic(World* pWorld);
	~GameLogic();

	void ProcessInput();
	bool IsGameEnded();
	bool IsGameStarted();
	void restart();
};

