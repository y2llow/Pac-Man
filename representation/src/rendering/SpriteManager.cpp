#include "rendering/SpriteManager.h"
#include <iostream>

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

bool TextureManager::loadTexture(const std::string& id, const std::string& filename) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << " with ID: " << id << std::endl;
        return false;
    }
    
    m_textures[id] = std::move(texture);
    std::cout << "Loaded texture: " << id << " from " << filename << std::endl;
    return true;
}

const sf::Texture* TextureManager::getTexture(const std::string& id) const {
    auto it = m_textures.find(id);
    if (it != m_textures.end()) {
        return it->second.get();
    }
    std::cerr << "Texture not found: " << id << std::endl;
    return nullptr;
}

void TextureManager::setRepeated(const std::string& id, bool repeated) {
    auto it = m_textures.find(id);
    if (it != m_textures.end()) {
        it->second->setRepeated(repeated);
    }
}