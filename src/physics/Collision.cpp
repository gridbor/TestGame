#include "Collision.h"


namespace physics {

	Collision::Collision():
		m_boundingBox{ }
	{
	}

	Collision::~Collision()
	{
	}

	void Collision::RefreshAABB(const std::vector<glm::vec3>& vertices, const glm::mat4& modelMatrix)
	{
		if (vertices.empty()) return;
		bool isFirst = true;
		for (const auto& vertex : vertices) {
			glm::vec4 transformed = modelMatrix * glm::vec4(vertex, 1.f);
			glm::vec3 divided = transformed / transformed.w;
			if (isFirst) {
				m_boundingBox.SetMin(divided);
				m_boundingBox.SetMax(divided);
				isFirst = false;
			}
			else {
				m_boundingBox.SetMin(glm::min(m_boundingBox.GetMin(), divided));
				m_boundingBox.SetMax(glm::max(m_boundingBox.GetMax(), divided));
			}
		}
	}

}
