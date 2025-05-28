#include "Camera.h"

#include "Transform.h"
#include "helpers/Coord.h"


namespace graphics {

	Camera::Camera():
		m_pitchLimits{ glm::radians<float>(-89.f), glm::radians<float>(89)},
		m_isMovable{ true },
		m_isRenderDisabled{ false }
	{
		LOG("Camera::constructor");
		m_coordOrigin = std::make_unique<Coord>();

		m_worldForward = { 0.f, 0.f, -1.f };
		m_forward = { 0.f, 0.f, -1.f };

		SetRotation(glm::identity<glm::quat>());
		m_coordOrigin->SetRotation(m_rotation);

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

		m_coordOrigin->Initialize();

		CalculateVectors();
	}

	void Camera::Update(float deltaTime)
	{

	}

	void Camera::Render()
	{
		if (m_isRenderDisabled) return;
		BaseObject::Render();

		if (!m_inited) return;
		m_coordOrigin->Render();
	}

	void Camera::SetPosition(const glm::vec3& vec)
	{
		m_coordOrigin->SetPosition(vec);
		BaseObject::SetPosition(vec);
		CalculateVectors();
	}

	void Camera::SetRotation(const glm::quat& rot)
	{
		m_coordOrigin->SetRotation(rot);
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
		SetPitch(GetPitch() + pitch);
		if (GetPitch() < m_pitchLimits.first) {
			SetPitch(m_pitchLimits.first);
		}
		if (GetPitch() > m_pitchLimits.second) {
			SetPitch(m_pitchLimits.second);
		}
		glm::quat quatPitch = glm::angleAxis(GetPitch(), glm::vec3(1.f, 0.f, 0.f));
		glm::quat quatYaw = glm::angleAxis(GetYaw(), glm::vec3(0.f, 1.f, 0.f));
		SetRotation(glm::normalize(quatYaw * quatPitch));
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
