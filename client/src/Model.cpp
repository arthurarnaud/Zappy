#include "zappy_ai_stdafx.hpp"

namespace zappy
{
  Model::Model(std::vector<glm::vec3> const &vertices,
               std::vector<GLuint> const &   indices)
      : m_vertices(vertices), m_normals(), m_indices(indices), m_vao(),
        m_vbos()
  {
    this->calcNormals();
    this->init();
  }

  Model::Model(std::vector<glm::vec3> &&vertices,
               std::vector<GLuint> &&   indices)
      : m_vertices(std::move(vertices)), m_normals(),
        m_indices(std::move(indices)), m_vao(), m_vbos()
  {
    this->calcNormals();
    this->init();
  }

  Model::Model(Model const &that)
      : m_vertices(that.m_vertices), m_normals(that.m_normals),
        m_indices(that.m_indices), m_vao(), m_vbos()
  {
    this->init();
  }

  Model::Model(Model &&that)
      : m_vertices(std::move(that.m_vertices)),
        m_normals(std::move(that.m_normals)),
        m_indices(std::move(that.m_indices)), m_vao(std::move(that.m_vao)),
        m_vbos(std::move(that.m_vbos))
  {
    that.m_vao = 0;
    for (std::size_t i = 0; i < NB_BUFFER_TYPES; ++i)
      {
	that.m_vbos[i] = 0;
      }
  }

  Model::~Model()
  {
  }

  Model &Model::operator=(Model const &that)
  {
    if (this == &that)
      return (*this);
    m_vertices = that.m_vertices;
    m_normals = that.m_normals;
    m_indices = that.m_indices;
    this->init();
    return (*this);
  }

  Model &Model::operator=(Model &&that)
  {
    if (this == &that)
      return (*this);
    m_vertices = std::move(that.m_vertices);
    m_normals = std::move(that.m_normals);
    m_indices = std::move(that.m_indices);
    m_vao = std::move(that.m_vao);
    m_vbos = std::move(that.m_vbos);

    that.m_vao = 0;
    for (std::size_t i = 0; i < NB_BUFFER_TYPES; ++i)
      {
	that.m_vbos[i] = 0;
      }
    return (*this);
  }

  Model Model::fromObj(std::string const &path)
  {
    std::vector<glm::vec3> vertices;
    std::vector<GLuint>    indices;

    std::size_t   lineCount = 1;
    std::string   line;
    std::ifstream fs(path.c_str());

    if (fs.is_open() == false)
      {
	throw std::system_error();
	// throw std::system_error((std::string("Failed to open obj file: ") +
	//                         path).c_str());
      }

    while (std::getline(fs, line))
      {
	line = line.substr(0, line.find_last_of("\n"));

	std::istringstream is(line);
	std::string        firstWord;

	is >> firstWord;

	while (is.peek() == ' ')
	  {
	    is.get();
	  }

	// It's a vertex
	if (firstWord == "v")
	  {
	    glm::vec3 vertex;

	    int res = std::sscanf(is.str().c_str(), "v %f %f %f", &vertex.x,
	                          &vertex.y, &vertex.z);

	    if (res == 3)
	      {
		vertices.push_back(vertex);
	      }
	    else
	      {
		nope::log::Log(Error)
		    << "Invalid vertex in " << path << ':' << lineCount;
	      }
	  }
	// It's a uv
	else if (firstWord == "vt")
	  {
	    // Well we don't care, don't do anything
	  }
	// It's a normal
	else if (firstWord == "vn")
	  {
	    // Well we don't care, don't do anything
	  }
	// It's a face
	else if (firstWord == "f")
	  {
	    std::uint32_t vertex[3];
	    std::uint32_t uv[3];
	    std::uint32_t normal[3];

	    int res =
	        sscanf(is.str().c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u",
	               &vertex[0], &uv[0], &normal[0], &vertex[1], &uv[1],
	               &normal[1], &vertex[2], &uv[2], &normal[2]);

	    if (res == 9)
	      {
		indices.push_back(vertex[0] - 1);
		indices.push_back(vertex[1] - 1);
		indices.push_back(vertex[2] - 1);
	      }
	    else
	      {
		nope::log::Log(Error)
		    << "Invalid face in " << path << ':' << lineCount;
	      }
	  }
	else if (std::all_of(firstWord.begin(), firstWord.end(), isspace) ==
	         false)
	  {
	    nope::log::Log(Warning)
	        << "Unknown line in " << path << ':' << lineCount;
	  }
	++lineCount;
      }

    return (Model(std::move(vertices), std::move(indices)));
  }

  std::vector<glm::vec3> const &Model::vertices() const
  {
    return (m_vertices);
  }

  std::vector<glm::vec3> const &Model::normals() const
  {
    return (m_normals);
  }

  void Model::render() const
  {
    glBindVertexArray(m_vao);

    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

    // glBindVertexArray(0);
  }

  void Model::init()
  {
    //     std::vector<glm::vec3> vert = {
    //         {-0.5, -1.0, -0.5}, {0.0, -1.0, 0.5}, {0.5, -1.0, -0.5}};

    //     vert.reserve(m_vertices.indices.size());
    //     for (GLuint id : m_vertices.indices)
    //       {
    // 	vert.push_back(m_vertices.elements[id]);
    //       }
    // Generate and bind the vao

    // Create Vertex Array
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    //
    // Vertex
    //
    glGenBuffers(NB_BUFFER_TYPES, m_vbos.data());
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VERTEX_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]),
                 &m_vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //
    // Normals
    //
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(m_normals[0]),
                 &m_normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //
    // Indices
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[INDICES_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_indices.size() * sizeof(m_indices[0]), &m_indices[0],
                 GL_STATIC_DRAW);

    // Unbind Vertex Array
    glBindVertexArray(0);

    //     // Vertex indices
    //     glBindBuffer(GL_ARRAY_BUFFER, m_buffersId[VERTEX_IDX]);
    //     glBufferData(GL_ARRAY_BUFFER,
    //                  m_vertices.indices.size() *
    //                  sizeof(m_vertices.indices[0]),
    //                  &m_vertices.indices[0], GL_STATIC_DRAW);

    //     glEnableVertexAttribArray(1);
    //     glVertexAttribPointer(1, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

    //     //
    //     // UV
    //     //
    //     glBindBuffer(GL_ARRAY_BUFFER, m_buffersId[UV]);
    //     glBufferData(GL_ARRAY_BUFFER,
    //                  m_uv.elements.size() * sizeof(m_uv.elements[0]),
    //                  &m_uv.elements[0], GL_STATIC_DRAW);
    // Normals

    //     glEnableVertexAttribArray(2);
    //     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //     // UV indices
    //     glBindBuffer(GL_ARRAY_BUFFER, m_buffersId[UV_IDX]);
    //     glBufferData(GL_ARRAY_BUFFER,
    //                  m_uv.indices.size() * sizeof(m_uv.indices[0]),
    //                  &m_uv.indices[0], GL_STATIC_DRAW);

    //     glEnableVertexAttribArray(3);
    //     glVertexAttribPointer(3, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

    //     //
    //     // Normals
    //     //
    //     glBindBuffer(GL_ARRAY_BUFFER, m_buffersId[NORMAL]);
    //     glBufferData(GL_ARRAY_BUFFER,
    //                  m_normals.elements.size() *
    //                  sizeof(m_normals.elements[0]),
    //                  &m_normals.elements[0], GL_STATIC_DRAW);

    //     glEnableVertexAttribArray(4);
    //     glVertexAttribPointer(4, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

    //     // Normals indices
    //     glBindBuffer(GL_ARRAY_BUFFER, m_buffersId[NORMAL_IDX]);
    //     glBufferData(GL_ARRAY_BUFFER,
    //                  m_normals.indices.size() *
    //                  sizeof(m_normals.indices[0]),
    //                  &m_normals.indices[0], GL_STATIC_DRAW);

    //     glEnableVertexAttribArray(5);
    //     glVertexAttribPointer(5, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

    // Unbind the vao
    // glBindVertexArray(0);
    // Normals
  }

  void Model::calcNormals()
  {
    m_normals.clear();
    m_normals.resize(m_vertices.size());

    for (std::size_t i = 0; i < m_indices.size(); i += 3)
      {
	GLuint i0 = m_indices[i];
	GLuint i1 = m_indices[i + 1];
	GLuint i2 = m_indices[i + 2];

	glm::vec3 v1 = m_vertices[i1] - m_vertices[i0];
	glm::vec3 v2 = m_vertices[i2] - m_vertices[i0];

	glm::vec3 normale = glm::normalize(glm::cross(v1, v2));

	m_normals[i0] += normale;
	m_normals[i1] += normale;
	m_normals[i2] += normale;
      }

    for (GLuint i = 0; i < m_vertices.size(); i++)
      {
	m_normals[i] = glm::normalize(m_normals[i]);
      }
  }
}
