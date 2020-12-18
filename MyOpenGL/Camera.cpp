#include "Camera.h"

#include "Scene.h" // leave include in CPP 

Camera::Camera(Scene& scene, glm::vec3 position) :
	m_zoom(1.0f), m_roll(0), m_pitch(0), m_yaw(-90), // Notice that 0 degrees in math. is to the "right" (protractor)
	m_right(1.0f, 0.0f, 0.0f), m_position(position), m_front(0.0f, 0.0f, -1.0f),
	m_up(0.0f, 1.0f, 0.0f), m_world_up(0.0f, 1.0f, 0.0f), m_scene(scene)
{
	update_vectors();
}

void Camera::update_vectors()
{
	// update the front vector so we can derive all others
	m_front = glm::vec3();
	m_front.x = cos(MathUtils::deg_to_rad(m_yaw)) * cos(MathUtils::deg_to_rad(m_pitch));
	m_front.y = sin(MathUtils::deg_to_rad(m_pitch));
	m_front.z = sin(MathUtils::deg_to_rad(m_yaw)) * cos(MathUtils::deg_to_rad(m_pitch));
	glm::normalize(m_front);

	// derive all other camera vectors from Front and World Up vectors
	// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_right = glm::normalize(glm::cross(m_front, m_world_up));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::move(CameraMovement direction, float units)
{
	// translate the camera's position using the front/right/up vector (scaled by the amount of units)
	set_position(m_position + get_displacement_vector(direction, units, false));
}

void Camera::walk(CameraMovement direction, float units)
{
	// translate the camera's position using the front/right/up vector (scaled by the amount of units)
	set_position(m_position + get_displacement_vector(direction, units, true));
}

glm::vec3 Camera::get_displacement_vector(CameraMovement direction, float units, bool clampToGround) const
{
	if (clampToGround) {
		// move clamping to the ground, by removing Y component from the vector vector used in the modulation
		if (direction == FORWARD)
			return glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z)) * units;
		if (direction == BACKWARD)
			return -glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z)) * units;
		if (direction == LEFT)
			return -glm::normalize(glm::vec3(m_right.x, 0.0f, m_right.z)) * units;
		if (direction == RIGHT)
			return glm::normalize(glm::vec3(m_right.x, 0.0f, m_right.z)) * units;
	}
	else {
		if (direction == FORWARD)
			return m_front * units;
		if (direction == BACKWARD)
			return -m_front * units;
		if (direction == LEFT)
			return -m_right * units;
		if (direction == RIGHT)
			return m_right * units;
		if (direction == UP)
			return m_up * units;
		if (direction == DOWN)
			return -m_up * units;
	}

	return glm::vec3(0);
}
