#include "Mesh.h"
class Geometry::Mesh::impl {
public:
	impl(){}
	impl(const std::string& Name): m_Name(Name) {}
	impl(const std::string& Name ,const std::initializer_list<Vertex>& _initlist):m_Name(Name), m_Vertices(_initlist) {}
	impl(const std::string& Name, const std::vector<Vertex>& _initlist):m_Name(Name), m_Vertices(_initlist) {}
public:
	void _UpdateVertices(const std::initializer_list<Vertex>& _initlist);
	void _UpdateVertices(const std::vector<Vertex>& _initlist);

	void _AddVertexMesh(const std::initializer_list<Vertex>& _intlist);
	void _AddVertexMesh(const std::vector<Vertex>& _intlist);
	void _AddVertexMesh(const Vertex& Vertex);
public:
	std::string m_Name;
	std::vector<Vertex> m_Vertices;
	std::function<std::vector<Vertex>(const std::string&)> m_ParseFunction;
};
Geometry::Mesh::Mesh(const std::string& Name)
{
	m_impl = new impl(Name);
}

Geometry::Mesh::Mesh(const std::string& Name, const std::string& FilePath,
const std::function<std::vector<Vertex>(const std::string&)> ParseFunction)
{
	m_impl = new impl(Name);
	m_impl->m_ParseFunction = ParseFunction;
	m_impl->m_Vertices =  m_impl->m_ParseFunction(FilePath);
}

Geometry::Mesh::Mesh(const std::string& Name, const std::initializer_list<Vertex>& initlist)
{
	m_impl = new impl(Name, initlist);
}

Geometry::Mesh::Mesh(const std::string& Name, const Vertex* Vertices, size_t sizeInBytes)
{
	m_impl = new impl(Name);
	if ((sizeInBytes % Vertex::GetSize()) == 0) {
		m_impl->m_Vertices.resize((sizeInBytes / Vertex::GetSize()));
		memcpy_s(&(m_impl->m_Vertices[0].x), sizeInBytes, &(Vertices->x), sizeInBytes);
	}
	else {
		__debugbreak();
	}
	
}

Geometry::Mesh::Mesh(const std::string& Name, const std::vector<Vertex>& Vertices)
{
	m_impl = new impl(Name, Vertices);
}

void Geometry::Mesh::UpdateMesh(const std::initializer_list<Vertex>& initlist)
{
	m_impl->_UpdateVertices(initlist);
}

void Geometry::Mesh::UpdateMesh(const std::vector<Vertex>& initlist)
{
	m_impl->_UpdateVertices(initlist);
}

void Geometry::Mesh::UpdateMesh(const std::string& NewFilePath)
{
	m_impl->m_Vertices = m_impl->m_ParseFunction(NewFilePath);
}

void Geometry::Mesh::UpdateMesh(const std::string& NewFilePath, const std::function<std::vector<Vertex>(const std::string&)> NewParseFunction)
{
	m_impl->m_ParseFunction = NewParseFunction;
	m_impl->m_Vertices = m_impl->m_ParseFunction(NewFilePath);
}

void Geometry::Mesh::AddVertexMesh(const std::initializer_list<Vertex>& initlist)
{
	m_impl->_AddVertexMesh(initlist);
}

void Geometry::Mesh::AddVertexMesh(const std::vector<Vertex>& initlist)
{
	m_impl->_AddVertexMesh(initlist);
}

void Geometry::Mesh::AddVertexMesh(const Vertex& Vertex)
{
	m_impl->_AddVertexMesh(Vertex);
}

Geometry::Mesh::~Mesh()
{
	delete m_impl;
}

Geometry::Mesh::Mesh(const Mesh& rtside)
{
	m_impl = new impl(*(rtside.m_impl));

}

Geometry::Mesh& Geometry::Mesh::operator=(const Mesh& rtside)
{
	m_impl = new impl(*(rtside.m_impl));
	return *this;
}

const Geometry::Vertex* Geometry::Mesh::GetVertices() const
{
	return &(m_impl->m_Vertices[0]);
}

size_t Geometry::Mesh::GetSizeInBytes() const
{
	return m_impl->m_Vertices.size() * Vertex::GetSize();
}

void Geometry::Mesh::impl::_UpdateVertices(const std::initializer_list<Vertex>& _initlist)
{
	m_Vertices = _initlist;
}

void Geometry::Mesh::impl::_UpdateVertices(const std::vector<Vertex>& _initlist)
{
	m_Vertices = _initlist;
}

void Geometry::Mesh::impl::_AddVertexMesh(const std::initializer_list<Vertex>& _initlist)
{
	m_Vertices.insert(m_Vertices.end(), _initlist);
}

void Geometry::Mesh::impl::_AddVertexMesh(const std::vector<Vertex>& _initlist)
{
	m_Vertices.insert(m_Vertices.end(), _initlist.begin(), _initlist.end());
}

void Geometry::Mesh::impl::_AddVertexMesh(const Vertex& Vertex)
{
	m_Vertices.push_back(Vertex);
}
