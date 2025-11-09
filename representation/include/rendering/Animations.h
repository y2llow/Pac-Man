#ifndef ANIMATION_H
#define ANIMATION_H
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

class Animations {
public:
    void registerAnimation(const std::string& id,
                          const std::vector<sf::IntRect>& frames,
                          float frameDuration,
                          bool looping = true);

    sf::IntRect getCurrentFrame(const std::string& animationId,
                               float elapsedTime) const;

    bool isAnimationFinished(const std::string& animationId,
                            float elapsedTime) const;
private:
    struct Animation {
        std::vector<sf::IntRect> frames;
        float frameDuration;
        bool looping;
    };

    std::unordered_map<std::string, Animations> m_animations;
};


#endif //ANIMATION_H
