#pragma once

#include "Drawable.h"

#include <string>
using namespace std;

class Text2D: public Drawable
{
	double m_x, m_y, m_depth;
	double m_r, m_g, m_b;
	string m_text;
public:

	Text2D(string name,double x, double y, double depth);
	virtual ~Text2D();

	void setText(string text);
	void updateScore(string pl, int score);
	void updateScore(int score);

	void setColor(double r, double g, double b);
	void draw(double dt);
};

