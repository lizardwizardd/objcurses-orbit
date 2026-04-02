/*
 * light.h
 */

#pragma once

#include "utils/mathematics.h"

class Light {
public:
    Vec3 direction;

    // constructors
    Light() : direction(Vec3(0.75F, -1.0F, -0.5F).normalize()) { }
    explicit Light(const Vec3 &dir) : direction(dir.normalize()) {}

};
