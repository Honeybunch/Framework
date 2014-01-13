#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"

class Player :
	public Paddle
{
public:
	Player();
	virtual ~Player();
};

#endif
