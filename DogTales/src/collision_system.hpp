// Created by ian on 1/29/24.
#include <bave/graphics/rect.hpp>
#include <bave/graphics/drawable.hpp>
#include <bave/graphics/shape.hpp>


#pragma once

class Collider : public bave::Rect<float>, public bave::Drawable
{
public:
    Collider(bave::Rect<float> const& rect);

};