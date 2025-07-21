#pragma once
#include "Framework/Game.h"

class SpaceGame : public viper::Game {
public:
	SpaceGame() = default;

	bool Initialize() override;
	void Shutdown() override;

	void Update() override;
	void Draw() override;

private:

};
