#include "Level.h"

#include <KlaoudeEngine/RessourceManager.h>

Level::Level()
{
	m_textureID = KlaoudeEngine::RessourceManager::getTexture("Sprites/map.png").id;
}

Level::~Level()
{

}

void Level::draw(KlaoudeEngine::SpriteBatch& spritebatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect(-300, -400, 600, 800);

	spritebatch.draw(destRect, uvRect, m_textureID, 0.0f, KlaoudeEngine::ColorRGBA8(255, 255, 255, 255), glm::vec2(0, 0));

}
