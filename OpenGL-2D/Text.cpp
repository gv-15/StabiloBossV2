#include "stdafx.h"
#include "text.h"
#include "renderer.h"
#include "../3rd-party/freeglut3/include/GL/freeglut.h"


Text2D::Text2D(string name, double x, double y, double depth)
{
	m_x = x;
	m_y = y;
	m_depth = depth;
	setColor(255,0,0);
	setText(name);
}


Text2D::~Text2D()
{
}

void Text2D::draw(double dt)
{
	return;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	//set color
	//glColor3f(m_r, m_g, m_b);

	//save the current transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	//set the matrix: only translation
	glTranslatef(m_x, m_y, -m_depth);
	
	//according to the OpenGL documentation, passed coordinates are transformed by the modelview matrix
	glRasterPos3d(0.0, 0.0, 0);

	void * font = GLUT_BITMAP_HELVETICA_18;

	glutBitmapString(font, (const unsigned char*)m_text.c_str());

	//restore the matrix
	glPopMatrix();
}

void Text2D::setColor(double r, double g, double b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}
void Text2D::updateScore(string pl, int score)
{
	setText(string("PLAYER ")+pl+string(": ")+to_string(score));
}
void Text2D::updateScore(int score)
{
	//string s = m_text.substr(0, m_text.size-2);
	string s = m_text.substr(0, 10);
	setText(s + to_string(score));

	if(score==8){
	
		setColor(150, 50, 0);
	}
	if (score == 6) {

		setColor(100, 150, 0);
	}
	if (score == 4 ){

setColor(0, 255, 0);
	}
	if (score == 2) {

setColor(0, 150, 100);
	}
	if (score == 1) {

		setColor(255, 255, 255);
	}


}


void Text2D::setText(string text)
{
	m_text = text;
}