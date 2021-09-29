#include "stdafx.h"
#include "SoundManager.h"
#include "AudioObject.h"

#include "../OpenALSoft/include/AL/al.h"
#include "../OpenALSoft/include/AL/alc.h"

SoundManager* SoundManager::m_pInstance = nullptr;

SoundManager::SoundManager()
{
	m_pInstance = this;

	m_device = alcOpenDevice(NULL);
	if (!m_device)
		return;


	m_context = alcCreateContext((ALCdevice*)m_device, NULL);
	if (!alcMakeContextCurrent((ALCcontext*)m_context))
		return;

	//listener properties
	ALfloat listenerOri[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);

	//create source pool
	alGenSources(NUM_MAX_SOURCES, m_soundSources);
	for (size_t i = 0; i < NUM_MAX_SOURCES; i++)
		m_freeSoundSources.push_back(m_soundSources[i]);

	m_bInitialized = true;
}


SoundManager::~SoundManager()
{
	//make sure to stop all sources before freeing them
	int source_state;
	for (size_t i = 0; i < NUM_MAX_SOURCES; i++)
	{
		alGetSourcei(m_soundSources[i], AL_SOURCE_STATE, &source_state);

		if (source_state == AL_PLAYING)
			alSourceStop(m_soundSources[i]);

		alDeleteSources(1, &m_soundSources[i]);
	}

	for (size_t i = 0; i < m_audioObjects.size(); i++)
		delete m_audioObjects[i];

	m_device = alcGetContextsDevice((ALCcontext*)m_context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext((ALCcontext*)m_context);
	alcCloseDevice((ALCdevice*)m_device);
}

int SoundManager::createAudioObject(string filename)
{
	int audioId = getAudioObjectId(filename);

	if (audioId >= 0)
		return audioId;

	AudioObject* pNewAudioObject= new AudioObject(filename);

	m_audioObjects.push_back(pNewAudioObject);

	return (int) (m_audioObjects.size()-1);
}

int SoundManager::getAudioObjectId(string filename)
{
	for (size_t i = 0; i < m_audioObjects.size(); i++)
	{
		if (m_audioObjects[i]->getSourceFilename() == filename)
			return (int) i;
	}
	return -1;
}

void SoundManager::play(int audioObjectId, float gain, float x, float y, float z, float dirX, float dirY, float dirZ)
{
	if (audioObjectId<0 || (size_t)audioObjectId>m_audioObjects.size())
		return;

	m_audioObjects[audioObjectId]->play( gain, x, y, z, dirX, dirY, dirZ);

	int error= alGetError();
}

unsigned int SoundManager::getFirstFreeSoundSource()
{
	if (m_freeSoundSources.size() > 0)
	{
		//there are free sources
		unsigned int source = m_freeSoundSources.front();
		m_freeSoundSources.pop_front();
		m_busySoundSources.push_back(source);
		return source;
	}
	return 0;
}

unsigned int SoundManager::getSoundSource()
{
	if (getVerbose())
		cout << "Sound source requested: " << m_freeSoundSources.size() << " free and " << m_busySoundSources.size() << " busy\n";

	unsigned int firstFree = getFirstFreeSoundSource();
	if (firstFree > 0)
		return firstFree;

	//check the state of all the sources
	auto it = m_busySoundSources.begin();
	while (it!=m_busySoundSources.end())
	{
		int source_state;
		alGetSourcei((*it), AL_SOURCE_STATE, &source_state);
		if (source_state == AL_STOPPED)
		{
			//move from busy to free
			m_freeSoundSources.push_back(*it);
			it= m_busySoundSources.erase(it);
		}
		else it++;
	}
	firstFree = getFirstFreeSoundSource();
	if (firstFree > 0)
		return firstFree;

	//no free sources, need to free one
	//for now, the first
	unsigned int freedSource = m_busySoundSources.front();
	alSourceStop(freedSource);
	return freedSource;
}