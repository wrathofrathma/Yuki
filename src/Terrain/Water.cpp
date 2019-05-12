#include "Water.hpp"
#include "../Yuki.hpp"
Water::Water(){
  rotate(glm::vec3(0,PI/2,0));

}
Water::Water(AssetManager *am) : Quad(am){
  rotate(glm::vec3(0,PI/2,0));
  setShader(am->getShader("Water"));
  textures.push_back(am->getTexture("dudv"));
  textures.push_back(am->getTexture("water1"));

}

void Water::draw(){
  shader->bind();
  generateModelMatrix();
  shader->setMat4(uModel, model_matrix);
  shader->setBool("lighting_on", lighting_on);
  setUseTexture(useTexture);
  loadMaterial(); //Let's change this later when when we start loading proper meshes. Maybe then we can move texturing to material class.
  if(update){
    updateGraphicsCard();
    shader->bind();
    std::string s_loc = "texture1";
    gl_textures[0] = shader->getUniformLocation(s_loc);
    shader->setInt(gl_textures[0], (0));
    s_loc = "texture2";
    gl_textures[1] = shader->getUniformLocation(s_loc);
    shader->setInt(gl_textures[1], (1));
    shader->setInt(shader->getUniformLocation("texture3"),2);

  }
  //Also let's send a normal matrix.
  glm::mat3 normal_matrix = glm::mat3(glm::transpose(glm::inverse(model_matrix)));
  shader->setMat3("normal_matrix", normal_matrix);

  if(useTexture){


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, textures[0]->getID());
    glActiveTexture(GL_TEXTURE0+2);
    glBindTexture(GL_TEXTURE_2D, textures[1]->getID());
  }
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
