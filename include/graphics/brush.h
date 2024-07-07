#pragma once

#include <memory>
#include <raylib.h>

namespace graphics {

class Brush {
private:
    float m_radius{20};
    unsigned char m_hardness{255};
    Color m_color{0, 0, 0, 255};
    BlendMode m_blendMode{BLEND_ADDITIVE};
    bool m_blending{true};

public:
    Brush(float radius = 20, float hardness = 255);
    ~Brush();

    static std::shared_ptr<Brush> create(float radius = 20, float hardness = 255);

    void apply(float x, float y);

    void setRadius(float radius);
    void setHardness(unsigned char hardness);
    void setColor(Color color);
    void setBlendMode(BlendMode blendMode);
    void setBlending(bool blending);

    float radius() const;
    unsigned char hardness() const;
    Color color() const;
    BlendMode blendMode() const;
    bool blending() const;
};

typedef std::shared_ptr<Brush> BrushPtr;

} // namespace graphics
