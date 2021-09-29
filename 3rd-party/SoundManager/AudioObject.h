#pragma once

#include "AudioFile.h"

#include <string>
using namespace std;

class AudioObject
{
	unsigned int m_buffer;

	bool m_bLoaded = false;
	string m_sourceFilename;

public:
	AudioObject(string filename);
	virtual ~AudioObject();

	string getSourceFilename();

	void play(float gain, float x, float y, float z, float dirX, float dirY, float dirZ);
};

