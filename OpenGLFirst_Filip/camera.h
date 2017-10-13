#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum Camera_Movements {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera();

	glm::mat4 getLookAtMatrix();
	void move(Camera_Movements, float deltaTime);
	void setFront(glm::vec3 front);

	virtual ~Camera();
private:
	glm::vec3 m_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	float m_speed = 2.0f;
};

