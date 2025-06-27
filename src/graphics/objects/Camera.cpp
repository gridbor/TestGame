#include "Camera.h"

#include "Transform.h"
#include "helpers/Coord.h"


namespace graphics {

	Camera::Camera():
		BaseObject{ EMeshType::CAMERA },
		m_pitchLimits{ glm::radians<float>(-89.f), glm::radians<float>(89)},
		m_isMovable{ true },
		m_isRenderDisabled{ false }
	{
		LOG("Camera::constructor");

		m_worldForward = { 0.f, 0.f, -1.f };
		m_forward = { 0.f, 0.f, -1.f };

		SetRotation(glm::identity<glm::quat>());

		CalculateVectors();
	}

	Camera::~Camera()
	{
		LOG("Camera::~destructor");
	}

	void Camera::Initialize()
	{
		m_vertices = {
			 0.00f,  0.00f,  0.25f,  1.f, 0.f, 0.f, 0.2f,
			-0.25f, -0.25f, -0.25f,  0.f, 1.f, 0.f, 0.2f,
			-0.25f,  0.25f, -0.25f,  0.f, 1.f, 0.f, 0.2f,
			 0.25f,  0.25f, -0.25f,  0.f, 0.f, 1.f, 0.2f,
			 0.25f, -0.25f, -0.25f,  0.f, 0.f, 1.f, 0.2f
		};
		m_indices = { 1, 2, 4, 2, 3, 4, 0, 2, 1, 0, 3, 2, 0, 4, 3, 0, 1, 4 };
		m_stride = 7;

		m_useTexture = false;

		m_shader = Globals::GetShader("default");

		BaseObject::Initialize();

		CalculateVectors();
	}

	void Camera::Update(float deltaTime)
	{
		BaseObject::Update(deltaTime);
	}

	void Camera::Render()
	{
		if (m_isRenderDisabled) return;
		BaseObject::Render();

		if (!m_inited) return;
	}

	void Camera::SetPosition(const glm::vec3& vec)
	{
		BaseObject::SetPosition(vec);
		CalculateVectors();
	}

	void Camera::SetRotation(const glm::quat& rot)
	{
		BaseObject::SetRotation(rot);
		CalculateVectors();
	}

	void Camera::UpdateViewMatrix()
	{
		auto shaders = Globals::GetAllShaders();
		for (auto& shader : shaders) {
			if (shader) {
				shader->SetUniformMatrix("u_view", m_viewMatrix);
			}
		}
	}

	bool Camera::MousePitchYawUpdate(float pitch, float yaw)
	{
		SetYaw(GetYaw() + yaw);
		if (GetPitch() + pitch < m_pitchLimits.first) {
			SetPitch(m_pitchLimits.first);
		}
		else if (GetPitch() + pitch > m_pitchLimits.second) {
			SetPitch(m_pitchLimits.second);
		}
		else {
			SetPitch(GetPitch() + pitch);
		}
		RefreshRotationFromEuler();
		return true;
	}

	void Camera::SetRenderDisabled(bool isDisable)
	{
		if (m_isRenderDisabled == isDisable) return;
		m_isRenderDisabled = isDisable;
	}

	void Camera::CalculateVectors()
	{
		BaseObject::CalculateVectors();
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
	}

}
