#pragma once
#include <iostream>
#include "MathUtils.h"
#include "Transform3D.h"

class Scene; // forward declaration

class Camera
{
public:

    enum CameraMovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    explicit Camera(Scene& scene, glm::vec3 position = glm::vec3());

    const glm::mat4 get_matrix() const
    {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void update_vectors();

    void set_pitch_deg(float degrees)
    {
        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (degrees > 89.0f) degrees = 89.0f;
        if (degrees < -89.0f) degrees = -89.0f;
        m_pitch = degrees;
        update_vectors();
    }

    float get_pitch_deg() const
    {
        return m_pitch;
    }

    void set_roll_deg(float degrees)
    {
        m_roll = degrees;
        update_vectors();
    }

    float get_roll_deg() const
    {
        return m_roll;
    }

    void set_yaw_deg(float degrees)
    {
        m_yaw = degrees;
        update_vectors();
    }

    float get_yaw_deg() const
    {
        return m_yaw;
    }

    void set_position(glm::vec3 position)
    {
        m_position = position;
        update_vectors();
    }

    glm::vec3 get_position() const
    {
        return m_position;
    }

    void set_zoom(float scale)
    {
        m_zoom = scale;
        update_vectors();
    }

    float get_zoom() const
    {
        return m_zoom;
    }

    void zoom(float value)
    {
        m_zoom *= 1.0f + value;
        update_vectors();
    }

    void move(CameraMovement direction, float units);

    void walk(CameraMovement direction, float units);

    void yaw(float degrees)
    {
        set_yaw_deg(get_yaw_deg() + degrees);
        update_vectors();
    }

    void pitch(float degrees)
    {
        set_pitch_deg(get_pitch_deg() + degrees);
        update_vectors();
    }

    void roll(float degrees)
    {
        set_roll_deg(get_roll_deg() + degrees);
        update_vectors();
    }

    glm::vec3 get_displacement_vector(CameraMovement direction, float units, bool clampToGround) const;

    glm::vec3 get_front_direction() const { return m_front; }


private:

    float m_zoom;

    float m_roll;
    float m_pitch;
    float m_yaw;

    glm::vec3 m_right;
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_world_up;

    Scene& m_scene;
};
