#include "CameraManager.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "graphics/objects/Camera.h"
#include "events/Events.h"
#include "InputManager.h"
#include "Globals.h"


CameraManager::CameraManager():
	m_currentCamera{ nullptr },
	m_moveSpeed{ 3.f },
	m_sensitivity{ 0.05f },
	m_cameraChanged{ false }
{
}

CameraManager::~CameraManager()
{
	m_currentCamera = nullptr;
	for (auto& c : m_cameras) {
		c.second.reset();
	}
	m_cameras.clear();
}

void CameraManager::Initialize()
{
	m_cameras["main_camera"] = std::make_unique<graphics::Camera>();
	m_cameras["main_camera"]->Initialize();
	m_cameras["main_camera"]->SetPosition(glm::vec3(0.f, 0.f, 3.f));

	m_cameras["from_side"] = std::make_unique<graphics::Camera>();
	m_cameras["from_side"]->SetPosition(glm::vec3(10.f, 0.f, 10.f));
	m_cameras["from_side"]->SetRotation(glm::quat(glm::vec3(0.f, glm::pi<float>() * 0.25f, 0.f)));

	SetCurrentCamera(m_cameras["main_camera"].get()); // m_cameras["from_side"].get());
}

void CameraManager::Update(float deltaTime)
{
	graphics::Camera* camera = GetCurrentCamera();
	if (camera == nullptr) return;

	bool f1Pressed = Globals::KeyIsPressed(GLFW_KEY_F1, EInputButtonType::KEYBOARD);
	if (f1Pressed && !m_cameraChanged) {
		m_cameraChanged = true;
		SetCurrentCamera(camera == m_cameras["main_camera"].get() ? m_cameras["from_side"].get() : m_cameras["main_camera"].get());
		camera = GetCurrentCamera();
	}
	else if (!f1Pressed && m_cameraChanged) {
		m_cameraChanged = false;
	}

	if (graphics::Camera* mCamera = m_cameras["main_camera"].get(); mCamera != nullptr) {
		bool lookChange = LookDirectionChange();
		std::pair<bool, glm::vec3> positionUpdate = PositionChange();

		if (positionUpdate.first || lookChange) {
			if (mCamera == camera) {
				mCamera->UpdateViewMatrix();
			}
			if (positionUpdate.first) {
				mCamera->SetPosition(positionUpdate.second);
			}
		}
	}

	camera->Update(deltaTime);
}

void CameraManager::Render()
{
	graphics::Camera* camera = GetCurrentCamera();
	if (camera == nullptr) return;

	std::vector<graphics::Camera*> cs;
	for (const auto& c : m_cameras) {
		if (c.second.get() != camera) cs.push_back(c.second.get());
	}

	camera->Render();

	for (const auto& c : cs) {
		c->Render();
	}
}

std::pair<bool, glm::vec3> CameraManager::PositionChange()
{
	bool result = false;

	graphics::Camera* camera = m_cameras["main_camera"].get();
	if (camera == nullptr) return std::make_pair(result, glm::vec3());

	glm::vec3 deltaPos = camera->GetPosition();
	if (!camera->IsMovable()) return std::make_pair(result, deltaPos);

	glm::vec3 fwd = camera->GetForward();
	glm::vec3 side = camera->GetRight();
	glm::vec3 up = camera->GetUp();

	float moveVelocity = (float)Globals::GetDeltaTime() * m_moveSpeed;
	if (Globals::KeyIsPressed(GLFW_KEY_W, EInputButtonType::KEYBOARD)) {
		deltaPos += fwd * moveVelocity;
		if (!result) result = true;
	}
	if (Globals::KeyIsPressed(GLFW_KEY_S, EInputButtonType::KEYBOARD)) {
		deltaPos -= fwd * moveVelocity;
		if (!result) result = true;
	}
	if (Globals::KeyIsPressed(GLFW_KEY_A, EInputButtonType::KEYBOARD)) {
		deltaPos -= side * moveVelocity;
		if (!result) result = true;
	}
	if (Globals::KeyIsPressed(GLFW_KEY_D, EInputButtonType::KEYBOARD)) {
		deltaPos += side * moveVelocity;
		if (!result) result = true;
	}
	if (Globals::KeyIsPressed(GLFW_KEY_Q, EInputButtonType::KEYBOARD)) {
		deltaPos += up * moveVelocity;
		if (!result) result = true;
	}
	if (Globals::KeyIsPressed(GLFW_KEY_E, EInputButtonType::KEYBOARD)) {
		deltaPos -= up * moveVelocity;
		if (!result) result = true;
	}
	return std::make_pair(result, deltaPos);
}

bool CameraManager::LookDirectionChange()
{
	bool result = false;

	graphics::Camera* camera = m_cameras["main_camera"].get();
	if (camera == nullptr) return result;

	MouseMove mouseMove = Globals::MouseMoveDelta();
	if (glm::abs(mouseMove.x) < glm::epsilon<double>() && glm::abs(mouseMove.y) < glm::epsilon<double>()) {
		return result;
	}
	result = camera->MousePitchYawUpdate(glm::radians(-mouseMove.y * m_sensitivity), glm::radians(-mouseMove.x * m_sensitivity));
	return result;
}

void CameraManager::SetCurrentCamera(graphics::Camera* camera)
{
	if (camera == nullptr || m_currentCamera == camera) return;

	m_currentCamera = camera;
	m_currentCamera->UpdateViewMatrix();
}
