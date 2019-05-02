#include "Polygon.hpp"

Polygon::Polygon(){
  vPosition = 0;
  vColor = 1;
  vTexture = 2;
  texture = nullptr;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &dataPtr);
  glGenBuffers(1, &indicePtr);
  glGenTextures(1, &TEX);
  shader.loadFromFile("shaders/2DBasic");
  setUseTexture(false);
  update = true;
  modelMatrix = glm::mat4(1.0f);
  shader.bind();
  uModel = shader.getUniformLocation("model");
}

Polygon::~Polygon(){
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &dataPtr);
  glDeleteBuffers(1, &indicePtr);
}

GLuint const Polygon::getVAO(){
  return VAO;
}

unsigned int Polygon::getVertexCount(){
  return vertices.size();
}
void Polygon::setTexture(Texture *tex){
  texture = tex;
  shader.bind();
  shader.setInt("texture1", 0);

  //Now we need to spread our texture
  for(unsigned int i=0; i<vertices.size(); i+=4){
    float v1 = vertices[i];
    float v2 = vertices[i+1];

    //Let's use these values, and assume our polygons are genrated at size 1, from 0.5 to -0.5 and scaled up using matrices later.
    //This way we can directly translate our textures early.
    texture_coords.push_back(v1 + 0.5);
    texture_coords.push_back(v2 + 0.5);
  }

  setUseTexture(true);
  update = true;
}
//Loads the data to our vertice & indice vectors and then to the graphics card.
void Polygon::loadVertices(vector<float> _vertices, vector<unsigned int> _indices){
  vertices.clear();
  indices.clear();
  vertices = _vertices;
  indices = _indices;
  update = true;
}
void Polygon::setColor(float r, float g, float b){
  colors.clear();
  for(unsigned int i=0; i<vertices.size()/4; i++){
    colors.push_back(r);
    colors.push_back(g);
    colors.push_back(b);
  }
  setUseTexture(false);
  update = true;
}
void Polygon::setColor(std::vector<float> c){
  colors.clear();
  if(c.size() < 3)
    return;
  if(c.size() == vertices.size())
    colors = c;
  else {
    //Here we have more vertices than colors or more colors, let's treat it as one color.
    for(unsigned int i=0; i<vertices.size()/4; i++){
      colors.push_back(c[0]);
      colors.push_back(c[1]);
      colors.push_back(c[2]);
    }
  }
  setUseTexture(false);
  update = true;
}

//Update's the vertex data on the graphics card.
void Polygon::updateGraphicsCard(){

  //Some pre-calc to make this cleaner.
  unsigned int vertice_size = vertices.size() * sizeof(float);
  unsigned int color_size = colors.size() * sizeof(float);
  unsigned int text_size = texture_coords.size() * sizeof(float);
  unsigned int indice_size = indices.size() * sizeof(unsigned int);
  unsigned int data_size = text_size + color_size + vertice_size;

  glBindVertexArray(VAO);
  //Load indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_size, &indices[0], GL_DYNAMIC_DRAW);

  //Allocate space for data
  glBindBuffer(GL_ARRAY_BUFFER, dataPtr);
  glBufferData(GL_ARRAY_BUFFER, data_size, NULL, GL_DYNAMIC_DRAW);

  //Load data as parts of sub partitions of the buffer
  //vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertice_size, &vertices[0]);
  //Color
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size, color_size, &colors[0]);
  //Texture
  glBufferSubData(GL_ARRAY_BUFFER, vertice_size + color_size, text_size, &texture_coords[0]);

  //Tell the shader how to find its data
  glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertice_size + color_size));
  glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(vertice_size));
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);
  glEnableVertexAttribArray(vTexture);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  update = false;
}
void Polygon::setUseTexture(bool use){
  shader.bind();
  shader.setBool("useTexture", use);
  useTexture = use;
}
void Polygon::draw(){
  //Every model has its own model matrix. So we should upload before every draw.
  glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  if(update){
    updateGraphicsCard();
  }
  shader.bind();
  if(useTexture){
    glActiveTexture(GL_TEXTURE0); //Activate texture unit
    glBindTexture(GL_TEXTURE_2D, texture->getID());
  }
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
