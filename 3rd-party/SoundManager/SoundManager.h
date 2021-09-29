#pragma once

#include <string>
#include <vector>
#include <list>
using namespace std;

class AudioObject;
#define NUM_MAX_SOURCES 32

class SoundManager
{
	static SoundManager* m_pInstance;

	bool m_bInitialized = false;
	vector<AudioObject*> m_audioObjects;

	unsigned int m_soundSources[NUM_MAX_SOURCES];
	list<unsigned int> m_freeSoundSources;
	list<unsigned int> m_busySoundSources;

	void *m_device;
	void *m_context;

	unsigned int getFirstFreeSoundSource();

	bool m_bVerbose = false;
public:
	SoundManager();
	virtual ~SoundManager();

	void setVerbose(bool verbose) { m_bVerbose = verbose; }
	bool getVerbose() { return m_bVerbose; }

	//Used from any client
	int getAudioObjectId(string filename);
	int createAudioObject(string filename);
	void play(int audioObjectId, float gain= 1.f, float x= 0.f, float y= 0.f, float z= 0.f
		, float dirX= 0.f, float dirY= 0.f, float dirZ= 0.f);

	//Used from AudioObject
	unsigned int getSoundSource();

	static SoundManager* getInstance() { return m_pInstance; }
};

