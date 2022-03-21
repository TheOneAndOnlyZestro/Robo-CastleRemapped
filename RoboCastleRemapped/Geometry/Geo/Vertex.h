#pragma once
#include <glm/glm.hpp>
namespace Geometry {
	struct Vertex {
	public:
		union {
			glm::vec3 pos;
			struct {
				float x, y, z;
			};
		};

	public:
		Vertex() {}
		Vertex(const glm::vec3& Pos) :pos(Pos) {}
		Vertex(float x, float y, float z) :pos(glm::vec3(x, y, z)) {}

		static unsigned int GetSize() { return (sizeof(float) * 3); }
		const float* GetRef() { return &x; }
	};
}
