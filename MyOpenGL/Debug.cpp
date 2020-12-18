#include "Debug.h"
#include "Camera.h"

void Debug::print_debug(const Camera& camera, const glm::mat4& projection) {
	std::cout << "Camera matrix:" << std::endl;
	printMat4(camera.get_matrix());
	std::cout << std::endl;
	std::cout << "Projection matrix:" << std::endl;
	printMat4(projection);
	std::cout << std::endl;

	std::cout << "YAW: " << camera.get_yaw_deg() << std::endl;
	std::cout << "Roll: " << camera.get_roll_deg() << std::endl;
	std::cout << "Pitch: " << camera.get_pitch_deg() << std::endl;

	std::cout << "Cam X: " << camera.get_position().x << std::endl;
	std::cout << "Cam Y: " << camera.get_position().y << std::endl;
	std::cout << "Cam Z: " << camera.get_position().z << std::endl;

	std::cout << "Zoom: " << camera.get_zoom() << std::endl;
}
