#include "Polygon.hpp"

Polygon::Polygon(){
  vPosition = 0;
  vColor = 1;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenTextures(1, &TEX);
  shader.loadFromFile("shaders/2DPoly");
}

Polygon::~Polygon(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

GLuint const Polygon::getVAO(){
  return VAO;
}

unsigned int Polygon::getVertexCount(){
  return vertices.size();
}

//Loads the data to our vertice & indice vectors and then to the graphics card.
void Polygon::loadVertices(vector<float> _vertices, vector<unsigned int> _indices){
  vertices.clear();
  indices.clear();
  vertices = _vertices;
  indices = _indices;
  updateGraphicsCard();
}
void Polygon::setColor(float r, float g, float b){
  colors.clear();
  for(unsigned int i=0; i<vertices.size()/3; i++){
    colors.push_back(r);
    colors.push_back(g);
    colors.push_back(b);
  }
  updateGraphicsCard();
}
void Polygon::setColor(std::vector<float> c){
  colors.clear();
  if(c.size() < 3)
    return;
  if(c.size() == vertices.size())
    colors = c;
  else {
    //Here we have more vertices than colors or more colors, let's treat it as one color.
    for(unsigned int i=0; i<vertices.size()/3; i++){
      colors.push_back(c[0]);
      colors.push_back(c[1]);
      colors.push_back(c[2]);
    }
  }
  updateGraphicsCard();
}
//Update's the vertex data on the graphics card.
void Polygon::updateGraphicsCard(){
  glBindVertexArray(VAO);
  //Loading our vertices & color info(maybe texture later)
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //Allocate space
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) + colors.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

  //Load data as parts of sub partitions of the buffer
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices[0]);
  glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), colors.size() * sizeof(float), &colors[0]);

  //Tell the shader how to find its data
  glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(float)));

  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);

  glBindBuffer(GL_ARRAY_BUFFER,0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);

  glBindVertexArray(0);
}

void Polygon::draw(){
  shader.bind();

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
