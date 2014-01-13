#include <Framework\Game.h>
#include <Framework\Sprite.h>
#include <Framework\Text.h>
#include <Framework\Quad.h>
#include <Framework\Ellip.h>
#include <Framework\Color.h>

#include "AIPaddle.h"
#include "Ball.h"
#include "Player.h"

class Pong : public Game
{
private:
	Ball* ball;
	Sprite* kanoonoo;
	Text* fps;

	int startTime;
	int elapsedTime;
	int frames;
	float framesPerSecond;

public:
	Pong(int screenWidth, int screenHeight);

	virtual void poll() override;
	virtual void update() override;
	virtual void render(float interpolation) override;

private:
	virtual bool loadMedia() override;

	virtual ~Pong(void);
};

