#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <utility>

class Camera
{
public:
	Camera(bool fpsStyle, const glm::vec3& pos, const glm::vec3& front, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 0.0f, float pitch = 0.0f, float sens = 0.05f, float speed = 3.0f);
	~Camera();
	
	//Setters
	void SetCamPos(const glm::vec3& pos);
	void SetCamFront(const glm::vec3& front);
	void SetCamUp(const glm::vec3& up);
	void SetMoveSpeed(float speed);
	void SetSensitivity(float sens);
	void SetFpsStyle(bool style);

	//Getters
	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetCamPos() const;
	glm::vec3 GetCamFront() const;
	std::pair<float, float> GetCamAngles() const;

	void MouseMove();
	void KeyboardMove(float deltaTime);

private:
	GLFWwindow* m_Window;

	glm::vec3 m_CamPos;
	glm::vec3 m_CamFront;
	glm::vec3 m_CamUp;
	bool m_FpsStyle;

	//Keyboard Event
	float m_MoveSpeed;
	float m_InitYPos;

	//Mouse Event
	std::pair<float, float> m_PMousePos;
	float m_Sensitivity;
	float m_Yaw, m_Pitch;
};

