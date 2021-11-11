#include "stdafx.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "../3rd-party/SOIL/src/SOIL.h"


Sprite::Sprite(string img, double x, double y)
{
	m_imageFilename = img;
	m_x = x;
	m_y = y;
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

	//1. Pass the object's color to OpenGL
	//2. Save the current transformation matrix
	//3. Set the transformation matrix of the quad using position, size and angle
	//4. Draw the quad centered in [0,0] with coordinates: [-1,-1], [1,-1], [1,1] and [-1,1]
	//5. Restore the transformation matrix
	//gl.scale
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(m_x, m_y, -1.0);
	//glRotatef(45, 0, 0, 1);
	glScaled(m_x, m_y, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_QUADS);
	
	//glColor3f(1, 0, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(0.5, 0.5);
	//glColor3f(0, 1, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(0.5, -0.5);
	//glColor3f(1, 0, 1);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(-0.5, -0.5);
	//glColor3f(1, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-0.5, 0.5);
	glEnd();
	glPopMatrix();
}

void Sprite::initializeImage()
{
	 textureId = SOIL_load_OGL_texture("img/alien-01.png", 0, 0, 0);
}