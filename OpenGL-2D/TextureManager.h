#pragma once
#include <unordered_map>
using namespace std;

class TextureObject
{
	unsigned int m_type, m_textureId;

public:
	TextureObject();
	TextureObject(int type, unsigned int textureId);
	~TextureObject();

	void set();
	unsigned int GetTextureId() { return m_textureId; }
	void SetTextureId(unsigned int id) { m_textureId = id; }
	void SetType(unsigned int type) { m_type = type; }
};

class TextureManager
{
	static TextureManager* m_pInstance;

	unordered_map<string, TextureObject> m_textureObjects;

	bool m_bVerbose = false;
public:
	TextureManager();
	virtual ~TextureManager();

	void SetVerbose(bool verbose) { m_bVerbose = verbose; }
	bool IsVerbose() { return m_bVerbose; }

	//Used from any client
	void UseTexture(string filename);
	unsigned int Create2DTexture(string filename);
	unsigned int Create3DTexture(string filename, int numSubImagesX, int numSubImagesY, bool loop);

	static TextureManager* GetInstance() { return m_pInstance; }
};

