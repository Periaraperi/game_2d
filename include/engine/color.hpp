# pragma once

struct Color {
    Color()
        :r(0.0f), g(0.0f), b(0.0f), a(1.0f)
    {}
    Color(float rr, float gg, float  bb, float aa) 
        :r(rr), g(gg), b(bb), a(aa)
    {}
    float r,g,b,a;
};
