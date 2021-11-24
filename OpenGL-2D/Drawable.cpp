#include "Drawable.h"
#include "Projectile.h"

string Drawable::GetName()
{
	//TODO
	//return nullptr;
	return m_imageFilename;
}

void Drawable::SetName(string pName)
{
	m_imageFilename = pName;
}
