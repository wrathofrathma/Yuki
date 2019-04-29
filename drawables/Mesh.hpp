#ifndef MESH_HPP
#define MESH_HPP


/**
\file Mesh.hpp
\brief header file for Mesh.cpp

\author Christopher Arausa
\version 0.1
\date 4/20/2019

*/

/**
\class Mesh

\brief The Mesh class is the base object for any drawable. It contains all of the VAO, VBO, EBO, vertices, indices, textures/material data.

*/

class Mesh {
  private:
    GLint vPosition; ///< Shader position of vertex data.
    GLint vColor; ///< Shader position of vertex color.
    GLint vNormal; ///< Shader position of vertex normal.

    GLfloat* vertex_data;  ///< Pointer to the vertex data.
    
    unsigned int vertex_count; ///< Total number of vertices in the object.
    void bindVAO();
    void unbindVAO();

  public:
    Mesh();
    Mesh(float *vertices, unsigned int *indices);
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
    ~Mesh();
    void draw();

    void loadVertices(float *vertices, unsigned int *indices);
    void loadVertices(vector<Vertex> vertices, vector<unsigned int> indices);
    GLint const getVAO();
    unsigned int getVertexCount();


};

#endif
