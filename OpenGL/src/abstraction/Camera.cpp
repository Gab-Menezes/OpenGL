#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(bool fpsStyle, const glm::vec3 & pos, const glm::vec3 & front, const glm::vec3 & up,  float yaw, float pitch, float sens, float speed) :
	m_CamPos(pos), m_CamFront(front), m_CamUp(up), m_FpsStyle(fpsStyle),
	m_Yaw(yaw), m_Pitch(pitch), m_Sensitivity(sens),
	m_MoveSpeed(speed), m_InitYPos(m_CamPos.y),
	m_Window(glfwGetCurrentContext())
{
	//Get the pmouse
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);
	m_PMousePos = { (float)xpos, (float)ypos };
}

Camera::~Camera()
{
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

//VIEW MATRIX (glm::lookAt)
glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_CamPos, m_CamPos + m_CamFront, m_CamUp);
}

//SETTERS
void Camera::SetCamPos(const glm::vec3 & pos)
{
	m_CamPos = pos;
}

void Camera::SetCamFront(const glm::vec3 & front)
{
	m_CamFront = front;
}

void Camera::SetCamUp(const glm::vec3 & up)
{
	m_CamUp = up;
}

void Camera::SetMoveSpeed(float speed)
{
	m_MoveSpeed = speed;
}

void Camera::SetSensitivity(float sens)
{
	m_Sensitivity = sens;
}

void Camera::SetFpsStyle(bool style)
{
	m_FpsStyle = style;
}

//GETTERS
glm::vec3 Camera::GetCamPos() const
{
	return m_CamPos;
}

glm::vec3 Camera::GetCamFront() const
{
	return m_CamFront;
}

std::pair<float, float> Camera::GetCamAngles() const
{
	return std::make_pair(m_Yaw, m_Pitch);
}

//UPDATE
void Camera::MouseMove()
{
	//Get current mouse pos
	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);

	//Offset the mouse pos with the pmouse pos
	float xOff = ((float)xpos - m_PMousePos.first) * m_Sensitivity;
	float yOff = (m_PMousePos.second - (float)ypos) * m_Sensitivity;
	m_PMousePos = { xpos, ypos };//pmouse pos = current mouse pos

	//Yaw and Pitch update
	m_Yaw += xOff;
	m_Pitch += yOff;
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	else if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	//Camera Front vector update
	m_CamFront.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CamFront.y = sin(glm::radians(m_Pitch));
	m_CamFront.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
	m_CamFront = glm::normalize(m_CamFront);
}

void Camera::KeyboardMove(float deltaTime)
{
	float camSpeed = m_MoveSpeed * deltaTime;
	//Update the position based on the key pressed
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		m_CamPos += camSpeed * m_CamFront;
	else if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		m_CamPos -= camSpeed * m_CamFront;
	else if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		m_CamPos -= glm::normalize(glm::cross(m_CamFront, m_CamUp)) * camSpeed;
	else if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		m_CamPos += glm::normalize(glm::cross(m_CamFront, m_CamUp)) * camSpeed;

	if (m_FpsStyle)
		m_CamPos.y = m_InitYPos;
}
