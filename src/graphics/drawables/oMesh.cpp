// #include "../Texture.hpp"
// #include "../Material.hpp"
// #include "../Shader.hpp"
// #include "Mesh.hpp"
//
// /**
// \file Mesh.cpp
// \brief Implementation of the Mesh class.
//
// \author Christopher Arausa
// \version 0.1
// \date 5/10/2019
//
// */
//
// Mesh::Mesh(){
//   vPosition = 0;
//   vNormal = 1;
//   vColor = 2;
//   vTexture = 3;
//   shader = nullptr;
//   lighting_on = true;
//   useTexture = false;
//
// }
//
// Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures){
//   this->vertices = vertices;
//   this->indices = indices;
//   this->textures = textures;
//   vPosition = 0;
//   vNormal = 1;
//   vColor = 2;
//   vTexture = 3;
//   update = true;
//   shader = nullptr;
//   lighting_on = true;
//   useTexture = false;
//
// }
//
// Mesh::~Mesh(){
//
// }
// /**
// \brief Loads the material data to the shader.
// */
// void Mesh::loadMaterial(){
//   shader->bind();
//   glm::vec4 amb = material.getAmbient();
//   glm::vec4 diff = material.getDiffuse();
//   glm::vec4 spec = material.getSpecular();
//   glm::vec4 emis = material.getEmission();
//   shader->setVec4("material.ambient",amb);
//   shader->setVec4("material.diffuse", diff);
//   shader->setVec4("material.specular",spec);
//   shader->setFloat("material.shininess",material.getShininess());
//   shader->setVec4("material.emission",emis);
//
// }
// /**
// \brief Calculates model matrix, sets shader uniforms and then draws the mesh.
// */
// void Mesh::draw(){
//
//   //If we didn't set the shader then we don't need to really do anything.
//   if(shader==nullptr)
//     return;
//   shader->bind();
//   //If our mesh has changed we need to upload it again.
//   if(update){
//     updateMesh();
//     loadTextures();
//   }
//   //Generating model matrix.
//   generateModelMatrix();
//   //Updating uniforms.
//   shader->setMat4(uModel, model_matrix);
//   shader->setBool("lighting_on", lighting_on);
//   shader->setBool("useTexture", useTexture);
//
//   loadMaterial();
//
//   glm::mat3 normal_matrix = glm::mat3(glm::transpose(glm::inverse(model_matrix)));
//   shader->setMat3("normal_matrix", normal_matrix);
//   //Now we actually draw whatever.
//
//   for(unsigned int i=0; i<textures.size(); i++){
//     glActiveTexture(GL_TEXTURE0+i);
//     std::string s_loc = "textures[" + std::to_string(i) + "]";
//     glBindTexture(GL_TEXTURE_2D,textures[i]->getID());
//   }
//
//   glActiveTexture(GL_TEXTURE0);
//   glBindVertexArray(VAO);
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);
//   glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//   glBindVertexArray(0);
// }
// /**
// \brief Loads all vertice, color, texture, indice, and normal data to the graphics card.
// */
// void Mesh::updateMesh(){
//   //This function should only get called if the update flag is set and the shader has been set.
//   //Which means we'll have VAO/VBO/EBO space already.
//   glBindVertexArray(VAO);
//   //Load in data.
//   glBindBuffer(GL_ARRAY_BUFFER, dataPtr);
//   glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
//   //Load indices
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicePtr);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);
//
//   std::cout << sizeof(Vertex) << std::endl;
//   std::cout << sizeof(glm::vec4) << std::endl;
//   std::cout << sizeof(offsetof(Vertex,normal)) << std::endl;
//
//   //Tell the shader how to find the data.
//   //index - size - type - normalized - stride - pointer to the data.
//   glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
//   glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)16);
//   glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
//   glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texture));
//
//   glEnableVertexAttribArray(vPosition);
//   glEnableVertexAttribArray(vColor);
//   glEnableVertexAttribArray(vNormal);
//   glEnableVertexAttribArray(vTexture);
//   update = false;
// }
//
// void Mesh::loadTextures(){
//   shader->bind();
//   for(int i=0; i<=textures.size() &&  i<10; i++){
//     std::string s_loc = "textures[" + std::to_string(i) + "]";
//     gl_textures[i] = shader->getUniformLocation(s_loc);
//     shader->setInt(gl_textures[i], (i));
//   }
// }
//
// /**
// \brief Tells the class to bind a texture on the draw loop and sets the uniform on our shader for if we're using a texture.
// \param use --- The boolean value to set for if we're using a texture.
// */
// void Mesh::setUseTexture(bool use){
//   useTexture = use;
// }
// /**
// \brief Releases VAO/VBO/EBO data on the graphics card.
// */
// void Mesh::cleanup(){
//   glDeleteVertexArrays(1, &VAO);
//   glDeleteBuffers(1, &dataPtr);
//   glDeleteBuffers(1, &indicePtr);
// }
//
// void Mesh::setVertices(std::vector<Vertex> vertices){
//   this->vertices = vertices;
//   update = true;
// }
// void Mesh::setIndices(std::vector<unsigned int> indices){
//   this->indices = indices;
// }
// void Mesh::setTexture(std::vector<Texture*> textures){
//   this->textures = textures;
//   update=true;
//   useTexture = true;
// }
// /**
// \brief Sets the shader to use directly by setting the shader.
// \param shader --- Pointer to the shader to use.
// */
// void Mesh::setShader(Shader* shader){
//   this->shader = shader;
//   if(shader!=nullptr){
//     cleanup();
//     update = true;
//     shader->bind();
//     uModel = shader->getUniformLocation("model");
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &dataPtr);
//     glGenBuffers(1, &indicePtr);
//   }
//   update = true;
// }
//
// unsigned int Mesh::getVertexCount(){
//   return vertices.size();
// }
//
// /**
// \brief Sets whether to apply lighting to this object.
// \param onoff --- Boolean value to use.
// */
// void Mesh::setLightingOn(bool onoff){
//   lighting_on = onoff;
// }
// /**
// \brief Returns whether to apply lighting to this object.
// */
// bool Mesh::getLightingOn(){
//   return lighting_on;
// }
//
// void Mesh::setMaterial(Material mat){
//   material = mat;
// }
