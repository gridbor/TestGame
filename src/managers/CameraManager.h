#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>


namespace graphics {
	class Camera;
}


class CameraManager {
public:
	CameraManager();
	~CameraManager();

	void Initialize();
	void Update(float deltaTime);
	void Render();

	graphics::Camera* GetCurrentCamera() const {
		return m_currentCamera != nullptr ? m_currentCamera : m_cameras.at("main_camera").get();
	};

private:
	std::pair<bool, glm::vec3> PositionChange();
	bool LookDirectionChange();

	void SetCurrentCamera(graphics::Camera* camera);

private:
	graphics::Camera* m_currentCamera;
	std::unordered_map<std::string, std::unique_ptr<graphics::Camera>> m_cameras;
	float m_moveSpeed;
	float m_sensitivity;
	bool m_cameraChanged;

};
