#pragma once

#include "Drawable.h"
#include "TextureManager.h"

class Sprite: public Drawable
{
protected:
	float m_r, m_g, m_b;
	
	double m_x= 0.0, m_y= 0.0; //position around which the quad is drawn

	double x_scale = 0.0, y_scale = 0.0;
	
	double m_depth = 1.0; // the renderer draws depths in range [1.0,20.0]

	double m_size= 1; //size of the quad

	double m_angle= 0.0; //rotation angle

	string m_imageFilename = ""; //Path to the file where the texture is
	
	TextureManager t;

	int textureId = 0;
	
	

public:
	Sprite(string img, double x, double y, double x1, double y2);
	~Sprite();
	virtual void Draw(double dt);
	void SetColor(float r, float g, float b);
	void SetPosition(double x, double y);
	void SetDepth(double depth);
	void SetRotation(double angle);
	void SetSize(double size);
	double GetSize();
	double GetX();
	double GetY();
};

