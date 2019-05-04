#include "Polygon.hpp"

Polygon::Polygon(AssetManager *am) : Drawable(am){

  shader = am->getShader("2DBasic");
  orientation = glm::vec3(0,0,0);
  setUseTexture(false);
  update = true;

  shader->bind();
  uModel = shader->getUniformLocation("model");
}

Polygon::~Polygon(){

}

GLuint const Polygon::getVAO(){
  return VAO;
}
void Polygon::setTexture(std::string tex){
  setTexture(asset_manager->getTexture(tex));
}

unsigned int Polygon::getVertexCount(){
  return vertices.size();
}
void Polygon::setTexture(Texture *tex){
  textures.push_back(tex);
  shader->bind();
  shader->setInt("texture1", 0);

  //Now we need to spread our texture
  for(unsigned int i=0; i<vertices.size(); i+=4){
    float v1 = vertices[i];
    float v2 = vertices[i+1];

    //Let's use these values, and assume our polygons are genrated at size 1, from 0.5 to -0.5 and scaled up using matrices later.
    //This way we can directly translate our textures early.
    texture_uvs.push_back(v1 + 0.5);
    texture_uvs.push_back(v2 + 0.5);
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

void Polygon::draw(){
  //Every model has its own model matrix. So we should upload before every draw.
  glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(generateModelMatrix()));
  setUseTexture(useTexture);
  if(update){
    updateGraphicsCard();
  }
  shader->bind();
  if(useTexture){
    if(textures.size()>0){
      glActiveTexture(GL_TEXTURE0); //Activate texture unit
      glBindTexture(GL_TEXTURE_2D, textures[0]->getID());
    }
  }
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
