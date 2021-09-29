#include "stdafx.h"
#include "AnimatedSprite.h"
#include "TextureManager.h"
#include <string>

AnimatedSprite::AnimatedSprite(const char* textureFilename, int numSubImagesX, int numSubImagesY, bool loop)
:Sprite(string(""))
{
	m_imageFilename = textureFilename;
	TextureManager::GetInstance()->Create3DTexture(textureFilename, numSubImagesX, numSubImagesY,loop);
}


AnimatedSprite::~AnimatedSprite()
{
}



void AnimatedSprite::Draw(double dt)
{
	//0. Calculate what point of the animation [0,1] to show this frame
	animationPoint += 0.01*dt;

	//2. Save the current transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//3. Set the transformation matrix of the quad using position, size and angle
	glTranslated(m_x, m_y, 0.0);
	glRotated(m_angle, 0.0, 0.0, 1.0);
	glScaled(m_size, m_size, 1.0);

	//4. Draw the quad centered in [0,0] with coordinates: [-1,-1], [1,-1], [1,1] and [-1,1]

	TextureManager::GetInstance()->UseTexture(m_imageFilename);

	glBegin(GL_QUADS);
	glTexCoord3d(0.0, 1.0, animationPoint);
	glVertex3d(-1.0, -1.0, -m_depth);
	glTexCoord3d(1.0, 1.0, animationPoint);
	glVertex3d(1.0, -1.0, -m_depth);
	glTexCoord3d(1.0, 0.0, animationPoint);
	glVertex3d(1.0, 1.0, -m_depth);
	glTexCoord3d(0.0, 0.0, animationPoint);
	glVertex3d(-1.0, 1.0, -m_depth);
	glEnd();

	//5. Restore the transformation matrix
	glPopMatrix();
}