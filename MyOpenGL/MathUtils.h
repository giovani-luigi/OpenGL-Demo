#pragma once

class MathUtils
{
public:

    static constexpr double pi = 3.14159265359;

    static constexpr double deg_to_rad(double degrees)
    {
        return degrees * pi / 180;
    }

    static constexpr double rad_to_deg(double radians)
    {
        return radians * 180 / pi;
    }

    static constexpr float deg_to_rad(float degrees)
    {
        return degrees * static_cast<float>(pi) / 180.0f;
    }

    static constexpr float rad_to_deg(float radians)
    {
        return radians * 180.0f / static_cast<float>(pi);
    }
};
