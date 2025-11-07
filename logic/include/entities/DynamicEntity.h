//
// Created by s0243673@ad.ua.ac.be on 11/6/25.
//

#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H
#include "EntityModel.h"

class DynamicEntity : public EntityModel {
    enum class Direction{ None, Up, Down, Left, Right };
};

#endif //DYNAMICENTITY_H
