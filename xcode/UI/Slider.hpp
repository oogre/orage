//
//  slider.hpp
//  Orage
//
//  Created by Vincent Evrard on 9/06/18.
//

#pragma once

#include "Tools.hpp"
#include "MouseEvent.hpp"
#include "InteractionManager.hpp"


class Slider : public InteractionManager{
    typedef Slider * SliderRef;
    
    static cinder::ColorA BG_FILL;
    static cinder::ColorA FG_FILL;
    static cinder::ColorA TXT_FILL;
    static cinder::ColorA BG_STROKE;
    static cinder::Rectf MARGINS;
    cinder::Rectf wrapper;
    cinder::vec2 range = cinder::vec2(-1, 1);
    cinder::Rectf core;
    std::string name;
    
    float value = 0.5f;
    const static int precision = 3;
    public :
        Slider(std::string name, cinder::ivec2 position = cinder::ivec2(0, 100), cinder::ivec2 size = cinder::ivec2(200, 20));
        virtual ~Slider(){}
        void setValue(float v);
        float getValue(bool based = false);
        float getRangedValue();
        void update();
        void draw();
};
typedef Slider * SliderRef;

