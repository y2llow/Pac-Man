#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class TextureManager {
public:
    static TextureManager& getInstance();
    
    bool loadTexture(const std::string& id, const std::string& filename);
    const sf::Texture& getTexture(const std::string& id) const;
    bool hasTexture(const std::string& id) const;
    void setRepeated(const std::string& id, bool repeated);
    
private:
    TextureManager() = default;
    ~TextureManager() = default;
    
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};

#endif