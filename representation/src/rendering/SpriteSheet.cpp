#include "rendering/SpriteSheet.h"
#include <iostream>

SpriteSheet& SpriteSheet::getInstance() {
    static SpriteSheet instance;
    return instance;
}

bool SpriteSheet::loadSpriteSheet(const std::string& filename) {
    if (!m_texture.loadFromFile(filename)) {
        std::cerr << "Failed to load sprite sheet: " << filename << std::endl;
        return false;
    }
    
    defineAllSprites();
    std::cout << "Sprite sheet loaded successfully: " << filename << std::endl;
    return true;
}

void SpriteSheet::defineSpriteRect(const std::string& name, const sf::IntRect& rect) {
    if (spriteRects.count(name) > 0) {
        std::cout << "Warning: Sprite '" << name << "' already defined, overwriting" << std::endl;
    }
    spriteRects[name] = rect;
}

void SpriteSheet::defineAllSprites() {
    // ===== PACMAN SPRITES =====
    // Closed mouth (circle - used for all directions when closed)
    defineSpriteRect("pacman_closed", sf::IntRect(853, 5, 33, 33));

    // RIGHT direction
    defineSpriteRect("pacman_right_closed", sf::IntRect(853, 5, 33, 33));
    defineSpriteRect("pacman_right_half", sf::IntRect(853, 55, 33, 33));
    defineSpriteRect("pacman_right_open", sf::IntRect(853, 105, 33, 33));

    // DOWN direction
    defineSpriteRect("pacman_down_closed", sf::IntRect(852, 155, 33, 33));
    defineSpriteRect("pacman_down_half", sf::IntRect(852, 205, 33, 33));
    defineSpriteRect("pacman_down_open", sf::IntRect(852, 255, 33, 33));

    // LEFT direction
    defineSpriteRect("pacman_left_closed", sf::IntRect(853, 5, 33, 33));
    defineSpriteRect("pacman_left_half", sf::IntRect(853, 355, 33, 33));
    defineSpriteRect("pacman_left_open", sf::IntRect(853, 405, 33, 33));

    // UP direction
    defineSpriteRect("pacman_up_closed", sf::IntRect(853, 454, 33, 33));
    defineSpriteRect("pacman_up_half", sf::IntRect(853, 504, 33, 33));
    defineSpriteRect("pacman_up_open", sf::IntRect(853, 554, 33, 33));

    // ===== PACMAN DEATH ANIMATION =====
    defineSpriteRect("pacman_death_0", sf::IntRect(353, 9, 33, 23));
    defineSpriteRect("pacman_death_1", sf::IntRect(351, 62, 37, 20));
    defineSpriteRect("pacman_death_2", sf::IntRect(351, 117, 37, 15));
    defineSpriteRect("pacman_death_3", sf::IntRect(351, 170, 37, 12));
    defineSpriteRect("pacman_death_4", sf::IntRect(351, 222, 37, 13));
    defineSpriteRect("pacman_death_5", sf::IntRect(351, 272, 37, 15));
    defineSpriteRect("pacman_death_6", sf::IntRect(353, 322, 33, 18));
    defineSpriteRect("pacman_death_7", sf::IntRect(358, 372, 23, 18));
    defineSpriteRect("pacman_death_8", sf::IntRect(363, 422, 13, 18));
    defineSpriteRect("pacman_death_9", sf::IntRect(368, 472, 3, 15));
    defineSpriteRect("pacman_death_10", sf::IntRect(356, 517, 27, 25));

    // ===== GHOST RED =====
    defineSpriteRect("ghost_red_right_1", sf::IntRect(1, 4, 35, 35));
    defineSpriteRect("ghost_red_right_2", sf::IntRect(1, 4, 35, 35));
    defineSpriteRect("ghost_red_down_1", sf::IntRect(1, 104, 35, 35));
    defineSpriteRect("ghost_red_down_2", sf::IntRect(1, 104, 35, 35));
    defineSpriteRect("ghost_red_left_1", sf::IntRect(1, 204, 35, 35));
    defineSpriteRect("ghost_red_left_2", sf::IntRect(1, 204, 35, 35));
    defineSpriteRect("ghost_red_up_1", sf::IntRect(1, 304, 35, 35));
    defineSpriteRect("ghost_red_up_2", sf::IntRect(1, 304, 35, 35));

    // ===== GHOST PINK =====
    defineSpriteRect("ghost_pink_right_1", sf::IntRect(51, 4, 35, 35));
    defineSpriteRect("ghost_pink_right_2", sf::IntRect(51, 4, 35, 35));
    defineSpriteRect("ghost_pink_down_1", sf::IntRect(51, 104, 35, 35));
    defineSpriteRect("ghost_pink_down_2", sf::IntRect(51, 104, 35, 35));
    defineSpriteRect("ghost_pink_left_1", sf::IntRect(51, 204, 35, 35));
    defineSpriteRect("ghost_pink_left_2", sf::IntRect(51, 204, 35, 35));
    defineSpriteRect("ghost_pink_up_1", sf::IntRect(51, 304, 35, 35));
    defineSpriteRect("ghost_pink_up_2", sf::IntRect(51, 304, 35, 35));

    // ===== GHOST CYAN (BLUE) =====
    defineSpriteRect("ghost_blue_right_1", sf::IntRect(101, 4, 35, 35));
    defineSpriteRect("ghost_blue_right_2", sf::IntRect(101, 4, 35, 35));
    defineSpriteRect("ghost_blue_down_1", sf::IntRect(101, 104, 35, 35));
    defineSpriteRect("ghost_blue_down_2", sf::IntRect(101, 104, 35, 35));
    defineSpriteRect("ghost_blue_left_1", sf::IntRect(101, 204, 35, 35));
    defineSpriteRect("ghost_blue_left_2", sf::IntRect(101, 204, 35, 35));
    defineSpriteRect("ghost_blue_up_1", sf::IntRect(101, 304, 35, 35));
    defineSpriteRect("ghost_blue_up_2", sf::IntRect(101, 304, 35, 35));

    // ===== GHOST ORANGE =====
    defineSpriteRect("ghost_orange_right_1", sf::IntRect(151, 4, 35, 35));
    defineSpriteRect("ghost_orange_right_2", sf::IntRect(151, 4, 35, 35));
    defineSpriteRect("ghost_orange_down_1", sf::IntRect(151, 104, 35, 35));
    defineSpriteRect("ghost_orange_down_2", sf::IntRect(151, 104, 35, 35));
    defineSpriteRect("ghost_orange_left_1", sf::IntRect(151, 204, 35, 35));
    defineSpriteRect("ghost_orange_left_2", sf::IntRect(151, 204, 35, 35));
    defineSpriteRect("ghost_orange_up_1", sf::IntRect(151, 304, 35, 35));
    defineSpriteRect("ghost_orange_up_2", sf::IntRect(151, 304, 35, 35));

    // ===== GHOST GREEN =====
    defineSpriteRect("ghost_green_right_1", sf::IntRect(201, 4, 35, 35));
    defineSpriteRect("ghost_green_right_2", sf::IntRect(201, 4, 35, 35));
    defineSpriteRect("ghost_green_down_1", sf::IntRect(201, 104, 35, 35));
    defineSpriteRect("ghost_green_down_2", sf::IntRect(201, 104, 35, 35));
    defineSpriteRect("ghost_green_left_1", sf::IntRect(201, 204, 35, 35));
    defineSpriteRect("ghost_green_left_2", sf::IntRect(201, 204, 35, 35));
    defineSpriteRect("ghost_green_up_1", sf::IntRect(201, 304, 35, 35));
    defineSpriteRect("ghost_green_up_2", sf::IntRect(201, 304, 35, 35));

    // ===== GHOST PURPLE =====
    defineSpriteRect("ghost_purple_right_1", sf::IntRect(251, 4, 35, 35));
    defineSpriteRect("ghost_purple_right_2", sf::IntRect(251, 4, 35, 35));
    defineSpriteRect("ghost_purple_down_1", sf::IntRect(251, 104, 35, 35));
    defineSpriteRect("ghost_purple_down_2", sf::IntRect(251, 104, 35, 35));
    defineSpriteRect("ghost_purple_left_1", sf::IntRect(251, 204, 35, 35));
    defineSpriteRect("ghost_purple_left_2", sf::IntRect(251, 204, 35, 35));
    defineSpriteRect("ghost_purple_up_1", sf::IntRect(251, 304, 35, 35));
    defineSpriteRect("ghost_purple_up_2", sf::IntRect(251, 304, 35, 35));

    // ===== GHOST SCARED (fear mode) =====
    defineSpriteRect("ghost_scared_1", sf::IntRect(1, 554, 35, 35));
    defineSpriteRect("ghost_scared_2", sf::IntRect(51, 554, 35, 35));

    // ===== COLLECTIBLES =====
    defineSpriteRect("coin", sf::IntRect(411, 313, 16, 16));

    // ===== FRUITS =====
    defineSpriteRect("fruit", sf::IntRect(601, 200, 33, 42));
    defineSpriteRect("bomb", sf::IntRect(455, 250, 33, 43));
    defineSpriteRect("burger", sf::IntRect(548, 103, 42, 36));
    defineSpriteRect("exclamation_point", sf::IntRect(500, 445, 18, 42));
    defineSpriteRect("star", sf::IntRect(561, 599, 30, 30));
    defineSpriteRect("big_coin", sf::IntRect(411, 463, 16, 16));
}

sf::IntRect SpriteSheet::getSpriteRect(const std::string& spriteId) const {
    auto it = spriteRects.find(spriteId);
    if (it != spriteRects.end()) {
        return it->second;
    }
    std::cerr << "Sprite not found: " << spriteId << std::endl;
    return sf::IntRect(853, 5, 33, 33); // Default: closed pacman
}