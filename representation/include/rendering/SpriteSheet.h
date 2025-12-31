#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

namespace pacman::representation::rendering {

class SpriteSheet {
public:
    static SpriteSheet& getInstance();

    bool loadSpriteSheet(const std::string& filename);
    sf::IntRect getSpriteRect(const std::string& spriteId) const;
    const sf::Texture& getTexture() const { return m_texture; }

private:
    SpriteSheet() = default;
    void defineAllSprites();
    void defineSpriteRect(const std::string& name, const sf::IntRect& rect);

    sf::Texture m_texture;
    std::unordered_map<std::string, sf::IntRect> spriteRects;
};

} // namespace pacman::representation::rendering

#endif
