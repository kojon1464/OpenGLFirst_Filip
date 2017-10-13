#include "camera.h"

Camera::Camera()
{
}

glm::mat4 Camera::getLookAtMatrix() 
{
	return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

void Camera::move(Camera_Movements movement, float deltaTime)
{
	switch (movement)
	{
	case FORWARD: m_pos += m_front * deltaTime * m_speed;
		break;
	case BACKWARD: m_pos -= m_front * deltaTime * m_speed;
		break;
	case LEFT: m_pos -= glm::normalize(glm::cross(m_front, m_up)) * deltaTime * m_speed;
		break;
	case RIGHT: m_pos += glm::normalize(glm::cross(m_front, m_up)) * deltaTime * m_speed;
		break;
	default:
		break;
	}
}

void Camera::setFront(glm::vec3 front)
{
	m_front = front;
}

Camera::~Camera()
{
}
