#pragma once

#include <ostream>

class Vector3 {

public:

	// static
	const static Vector3& empty();
	const static Vector3& identity();

	// instance

	// constructors
	Vector3();
	Vector3(const Vector3& from); // copy constructor
	Vector3(float x, float y, float z);
	explicit Vector3(float v[]); // non converting constructor

	// getters
	float x() const { return m_Array[0]; }
	float y() const { return m_Array[1]; }
	float z() const { return m_Array[2]; }
	float get(const int i) const { return m_Array[i]; }
	float get_length() const;
	Vector3 get_normalize() const;

	// methods
	float dot(const Vector3& other) const;
	Vector3& normalize();
	Vector3& move(float dx, float dy, float dz);
	
	// operators
	friend std::ostream& operator<<(std::ostream& out, const Vector3& v);
	float& operator[](const int i) { return m_Array[i]; }
	const float& operator[](const int i) const { return m_Array[i]; }

private:

	float m_Array[3];
	
};

