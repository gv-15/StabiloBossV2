#include "stdafx.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "../3rd-party/SOIL/src/SOIL.h"


Sprite::Sprite(string img, double x, double y, double x1, double y2)
{
	m_imageFilename = img;
	m_x = x;
	m_y = y;
	x_scale = x1;
	y_scale = y2;
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
	m_x = x;
	m_y = y;

}

double Sprite::GetX()
{
	//TODO
	return m_x;
	//return 0.0;
}

double Sprite::GetY()
{
	//TODO
	return m_y;
	//return 0.0;
}

void Sprite::SetDepth(double depth)
{
	m_depth = depth;
}

void Sprite::SetRotation(double angle)
{
	m_angle = angle;
}

void Sprite::SetSize(double size)
{
	//This method only updates internally the object's size. It still needs to be passed to OpenGL before drawing it
		//TODO
	m_size = size;
}

double Sprite::GetSize()
{
	//TODO
	//return 0.0;
	return m_size;
}

double Sprite::GetXScale()
{

	return x_scale;
}

double Sprite::GetYScale()
{

	return y_scale;
}

double Sprite::GetRotation()
{

	return m_angle;
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
	glRotatef(m_angle, 0, 0, 1);
	glScaled(x_scale, y_scale, 1);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	//------------------------------------------------------------------
	//Split "/img/PLAYER1 ROSA SMALL" into "img/PLAYER1 ROSA SMALL"
	std::string str = m_imageFilename;
	std::size_t pos = str.find("img");      // position of "img" in str
	std::string str3 = str.substr(pos);     // get from "img" to the end
	//------------------------------------------------------------------

	//-----------------------------------------------------
	//Add .png 
	string filename = str3 + ".png";
	//-----------------------------------------------------

	t.Create2DTexture(filename);
	t.UseTexture(filename);
	glBindTexture(GL_TEXTURE_2D, t.Create2DTexture(filename));
	

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
