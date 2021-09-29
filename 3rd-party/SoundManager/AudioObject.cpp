#include "AudioObject.h"
#include "../OpenALSoft/include/AL/al.h"
#include "SoundManager.h"

AudioObject::AudioObject(string filename)
{
	if (SoundManager::getInstance()->getVerbose())
		cout << "Loading audio file: " << filename << "\n";

	AudioFile<float> audioFile;
	m_bLoaded= audioFile.load(filename);
	m_sourceFilename = filename;

	if (m_bLoaded)
	{
		//format
		unsigned int format;
		double minSample,sampleWidth;
		if (audioFile.getBitDepth() == 8)
		{
			minSample = 0;
			sampleWidth = 255;
		}
		else
		{
			minSample = -32768;
			sampleWidth = 65536;
		}
		if (audioFile.isStereo())
		{
			if (audioFile.getBitDepth() == 8)
				format = AL_FORMAT_STEREO8;
			else format = AL_FORMAT_STEREO16;
		}
		else
		{
			if (audioFile.getBitDepth() == 8)
				format = AL_FORMAT_MONO8;
			else format = AL_FORMAT_MONO16;
		}

		//set the audio data: rearrange and send to openAL
		//assuming 16 pcm files for now
		int audioDataSize= audioFile.getNumChannels()*audioFile.getNumSamplesPerChannel();
		short* pData = new short[audioDataSize];
		int i = 0;
		double normSample;
		for (int sample = 0; sample < audioFile.getNumSamplesPerChannel(); sample++)
		{
			for (int channel = 0; channel < audioFile.getNumChannels(); channel++)
			{
				normSample = (1.0 + audioFile.samples[channel][sample]) * .5;
				pData[i] = (short) (minSample + normSample*sampleWidth);
				i++;
			}
		}
		//allocate the buffer object
		alGenBuffers((ALuint)1, &m_buffer);
		alBufferData(m_buffer, format, pData, audioDataSize, audioFile.getSampleRate());
		
		delete [] pData;
	}
}


AudioObject::~AudioObject()
{
	alDeleteBuffers(1, &m_buffer);
}

string AudioObject::getSourceFilename()
{
	return m_sourceFilename;
}


void AudioObject::play(float gain, float x, float y, float z, float dirX, float dirY, float dirZ)
{
	if (SoundManager::getInstance()->getVerbose())
		cout << "Playing audio: " << m_sourceFilename << "\n";

	unsigned int soundSource = SoundManager::getInstance()->getSoundSource();

	//create audio object and set basic properties
	alSourcef(soundSource, AL_PITCH, 1);
	alSourcef(soundSource, AL_GAIN, gain);
	alSource3f(soundSource, AL_POSITION, x, y, z);
	alSource3f(soundSource, AL_VELOCITY, dirX, dirY, dirZ);
	alSourcei(soundSource, AL_LOOPING, AL_FALSE);

	//bind source and buffer
	alSourcei(soundSource, AL_BUFFER, m_buffer);

	alSourcePlay(soundSource);
}