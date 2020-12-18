#pragma once
#include <iomanip>
#include <iostream>
#include "glm/glm.hpp"

class Camera;

class Debug {

public:

	void static print_debug(const Camera& camera, const glm::mat4& projection);

private:

	void static printMat4(const glm::mat4& m) {
        using namespace std;
        std::cout
            << std::fixed << std::setprecision(6) << std::setfill(' ')
            << "[" << setw(6) << m[0][0] << "][" << setw(6) << m[1][0] << "][" << setw(6) << m[2][2] << "][" << setw(6) << m[3][0] << "]" << std::endl
            << "[" << setw(6) << m[0][1] << "][" << setw(6) << m[1][1] << "][" << setw(6) << m[2][2] << "][" << setw(6) << m[3][1] << "]" << std::endl
            << "[" << setw(6) << m[0][2] << "][" << setw(6) << m[1][2] << "][" << setw(6) << m[2][2] << "][" << setw(6) << m[3][2] << "]" << std::endl
            << "[" << setw(6) << m[0][3] << "][" << setw(6) << m[1][3] << "][" << setw(6) << m[2][2] << "][" << setw(6) << m[3][3] << "]" << std::endl
            << std::endl;
    }
	
};

