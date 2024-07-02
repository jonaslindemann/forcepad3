#pragma once

#include <memory>

namespace graphics {

class Brush {
private:
    float m_radius{20};
    unsigned char m_hardness{255};

public:
    Brush(float radius = 20, float hardness = 255);
    ~Brush();

    static std::shared_ptr<Brush> create(float radius = 20, float hardness = 255);

    void apply(float x, float y);

    void setRadius(float radius);
    void setHardness(unsigned char hardness);

    float radius() const;
    unsigned char hardness() const;
};

typedef std::shared_ptr<Brush> BrushPtr;

} // namespace graphics
