//
// Created by s0243673@ad.ua.ac.be on 11/6/25.
//

#ifndef FRUIT_H
#define FRUIT_H
#include "EntityModel.h"

class FruitModel : public EntityModel {
public:
    FruitModel(const Vector2f& position, const Vector2f& size,const std::string& textureId = "") ;

    // overwritten functiosn from entityModel
    void update(float deltaTime) override ;
    [[nodiscard]]  Vector2f getPosition() const override {return m_position;}
    void setPosition(const Vector2f& position) override;
    [[nodiscard]]  Vector2f getSize() const override{return m_size;}
    [[nodiscard]] bool getScoreAwarded() const {return m_scoreAwarded; }
    void setScoreAwarded(bool scoreAwarded) {m_scoreAwarded = scoreAwarded; }

    // FruitModel specific funcitons
    void collect();  // This will notify observers!

    [[nodiscard]] bool isCollected() const { return m_collected; }


private:
    //default privates
    Vector2f m_position;
    Vector2f m_size;

    //FruitModel specific privates
    bool m_collected = false;
    bool m_scoreAwarded = false;

};
#endif //FRUIT_H
