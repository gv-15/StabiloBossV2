#pragma once
#include "Sprite.h"
class AnimatedSprite :
	public Sprite
{
	double animationPoint = 0.0;

public:
	AnimatedSprite(const char* textureFilename, int numImagesX, int numImagesY, bool loop);
	virtual ~AnimatedSprite();

	virtual void Draw(double dt);
};

