#include "TextureManager.h"
#include "../3rd-party/glew-2.0.0/src/glew.h"
#include "../3rd-party/SOIL/src/SOIL.h"
#include <iostream>

TextureObject::TextureObject()
{
	m_type = GL_TEXTURE_2D;
	m_textureId = 0;
}
TextureObject::TextureObject(int type, unsigned int textureId)
{
	m_type = type;
	m_textureId = textureId;
}
TextureObject::~TextureObject()
{
}

void TextureObject::set()
{
	if (m_type == GL_TEXTURE_2D)
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_3D);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}
	else
	{
		glEnable(GL_TEXTURE_3D);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_3D, m_textureId);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


TextureManager* TextureManager::m_pInstance = nullptr;

TextureManager::TextureManager()
{
	m_pInstance = this;
}


TextureManager::~TextureManager()
{
}

void TextureManager::UseTexture(string filename)
{
	auto textureObject = m_textureObjects.find(filename);
	if (textureObject != m_textureObjects.end())
		textureObject->second.set();
}

unsigned int TextureManager::Create2DTexture(string filename)
{
	if (filename.empty()) return 0;

	//does it already exist??
	auto textureObject = m_textureObjects.find(filename);
	if (textureObject != m_textureObjects.end())
		return textureObject->second.GetTextureId();

	//not? load it
	if (m_bVerbose)
		cout << "Loading texture " << filename.c_str();
	unsigned int id = SOIL_load_OGL_texture(filename.c_str(), 0, 0, 0);
	

	if (m_bVerbose)
	{
		if (id > 0)
			cout << "... Succesful\n";
		else
			cout << "... ERROR\n";
	}

	m_textureObjects[filename] = TextureObject(GL_TEXTURE_2D, id);

	return id;
}

unsigned int TextureManager::Create3DTexture(string filename, int numSubImagesX, int numSubImagesY, bool loop)
{
	return 0;
	if (filename.empty()) return 0;

	//does it already exist??
	auto textureObject = m_textureObjects.find(filename);
	if (textureObject != m_textureObjects.end())
		return textureObject->second.GetTextureId();

	if (m_bVerbose)
		cout << "Loading texture " << filename.c_str();

	//not? load it
	unsigned int textureId= 0;
	int width, height, nChannels;
	unsigned char* pImage = SOIL_load_image(filename.c_str(), &width, &height, &nChannels, 0);
	if (pImage)
	{
		int numImageBytes = width * height*nChannels;
		char* pDstBuffer = new char[numImageBytes];

		int subImageSizeX = width / numSubImagesX;
		int subImageSizeY = height / numSubImagesY;

		int numSubImages = numSubImagesX * numSubImagesY;
		int numSubImageRows = numSubImages * subImageSizeY;
		int subImageX, subImageY;
		int srcOffsetInBytes = 0, dstOffsetInBytes;
		int dstSubImageIndex;
		int numBytesPerSubImage = nChannels * subImageSizeX * subImageSizeY;
		int numBytesPerSubImageRow = nChannels * subImageSizeX;
		int numSubImageRowsPerImageRow = subImageSizeY * numSubImagesX;

		for (int subImageRow = 0; subImageRow < numSubImageRows; subImageRow++)
		{

			subImageY = subImageRow / numSubImageRowsPerImageRow;
			subImageX = (subImageRow % numSubImageRowsPerImageRow) % numSubImagesX;

			//dstSubImageIndex = subImageY * numSubImagesX + subImageX;
			dstOffsetInBytes = (subImageY*numSubImagesX + subImageX) * numBytesPerSubImage
				+ ((subImageRow%numSubImageRowsPerImageRow) / numSubImagesX)* numBytesPerSubImageRow;

			memcpy_s(&pDstBuffer[dstOffsetInBytes], numImageBytes - dstOffsetInBytes, &pImage[srcOffsetInBytes]
				, numBytesPerSubImageRow);

			srcOffsetInBytes += numBytesPerSubImageRow;
		}

		glEnable(GL_TEXTURE_3D);
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_3D, textureId);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, subImageSizeX, subImageSizeY, numSubImages, 0
			, GL_RGBA, GL_UNSIGNED_BYTE, pDstBuffer);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		if (!loop)
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		else
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_3D, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_TEXTURE_3D);
		glEnable(GL_TEXTURE_2D);

		delete[] pDstBuffer;
		delete[] pImage;
	}

	if (m_bVerbose)
	{
		if (textureId > 0)
			cout << "... Succesful\n";
		else
			cout << "... ERROR\n";
	}

	m_textureObjects[filename] = TextureObject(GL_TEXTURE_3D, textureId);
	return textureId;
}

