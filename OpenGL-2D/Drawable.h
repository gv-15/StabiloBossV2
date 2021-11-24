#pragma once
#include <string>
using namespace std;

class Drawable
{
protected:
	string m_imageFilename = "";
public:
	virtual void Draw(double dt) = 0;
	string GetName();
	void SetName(string name);
};