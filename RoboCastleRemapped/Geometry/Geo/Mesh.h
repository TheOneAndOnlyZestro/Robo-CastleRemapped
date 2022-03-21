#pragma once
#include "Vertex.h"
#include <initializer_list>
#include <string>
#include <functional>
#include <vector>
namespace Geometry {
	class Mesh
	{
	public:
		Mesh(const std::string& Name);
		Mesh(const std::string& Name, const std::string& FilePath,
			const std::function<std::vector<Vertex>(const std::string&)> ParseFunction);
		Mesh(const std::string& Name, const std::initializer_list<Vertex>& initlist);
		Mesh(const std::string& Name, const Vertex* Vertices, size_t sizeInBytes);
		Mesh(const std::string& Name, const std::vector<Vertex>& Vertices);

		//Update Function
		void UpdateMesh(const std::initializer_list<Vertex>& initlist);
		void UpdateMesh(const std::vector<Vertex>& initlist);
		void UpdateMesh(const std::string& NewFilePath);
		void UpdateMesh(const std::string& NewFilePath, 
		const std::function<std::vector<Vertex>(const std::string&)> NewParseFunction);

		void AddVertexMesh(const std::initializer_list<Vertex>& initlist);
		void AddVertexMesh(const std::vector<Vertex>& initlist);
		void AddVertexMesh(const Vertex& Vertex);


		//Rule Of Three
		~Mesh();
		Mesh(const Mesh& rtside);
		Mesh& operator=(const Mesh& rtside);
	
		//Query Functions
		const Vertex* GetVertices() const;
		size_t GetSizeInBytes() const;
	private:
		class impl;
		impl* m_impl;
	};
}


