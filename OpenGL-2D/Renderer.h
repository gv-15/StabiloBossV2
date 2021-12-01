#pragma once

class Drawable;
#include <vector>
#include <string>
using namespace std;
#include "Timer.h"

class Renderer
{
	static Renderer* m_pRenderer;
	int m_windowWidth = 0, m_windowHeight = 0;
	double m_frameDuration = 0.0;
	Timer m_frameTimer;
	vector <Drawable*> m_objects2D;

	void set2DMatrix();
public:
	Renderer();
	~Renderer();

	void Initialize(int argc, char** argv);

	void SetFrameRate(int framesPerSecond);
	double getFrameDuration() { return m_frameDuration; }
	Timer GetFrameTimer() { return m_frameTimer; }

	static Renderer* Get(); //this method returns the only instance to the renderer. Needs to be called after creating an instance

	void DrawScene();
	void AddObject(Drawable* pObj);
	void RemoveObject(Drawable * pObj);
	void ReshapeWindow(int x, int y);
	
	static void __drawScene();
	static void __reshapeWindow(int x, int y);
	Drawable* ObjectByName(string name);
};

