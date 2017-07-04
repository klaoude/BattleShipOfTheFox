#pragma once

#include <KlaoudeEngine/SpriteBatch.h>

class Level
{
public:
	Level();
	~Level();

	void draw(KlaoudeEngine::SpriteBatch& spritebatch);

private:
	GLuint m_textureID;
};