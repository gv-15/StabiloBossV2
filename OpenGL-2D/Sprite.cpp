#include "stdafx.h"
#include "Sprite.h"
#include "TextureManager.h"


Sprite::Sprite(string img)
{
	//TODO
}


Sprite::~Sprite()
{
}

void Sprite::SetColor(float r, float g, float b)
{
	//When this method is called, we only store internally what this object's color will be
	//but, we need to pass the color to OpenGL every time the object is drawn
	//TODO
}

void Sprite::SetPosition(double x, double y)
{
	//This method only updates internally the object's position. It still needs to be passed to OpenGL before drawing it
	//TODO
}

double Sprite::GetX()
{
	//TODO
	return 0.0;
}

double Sprite::GetY()
{
	//TODO
	return 0.0;
}

void Sprite::SetDepth(double depth)
{
	//This method only updates internally the object's depth. It still needs to be passed to OpenGL before drawing it
		//TODO
}

void Sprite::SetRotation(double angle)
{
	//This method only updates internally the object's rotation. It still needs to be passed to OpenGL before drawing it
		//TODO
}

void Sprite::SetSize(double size)
{
	//This method only updates internally the object's size. It still needs to be passed to OpenGL before drawing it
		//TODO
}

double Sprite::GetSize()
{
	//TODO
	return 0.0;
}

void Sprite::Draw(double dt)
{
	//TODO:

	//1. Pass the object's color to OpenGL


	//2. Save the current transformation matrix

	glPushMatrix();

	//3. Set the transformation matrix of the quad using position, size and angle

	//TODO

	//4. Draw the quad centered in [0,0] with coordinates: [-1,-1], [1,-1], [1,1] and [-1,1]

	//TODO

	//5. Restore the transformation matrix

	glPopMatrix();
}