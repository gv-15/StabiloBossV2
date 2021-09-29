#pragma once
#include <string>
using namespace std;

class Drawable
{
public:
	virtual void draw(double dt) = 0;

	string GetName();
	void SetName(string name);
};