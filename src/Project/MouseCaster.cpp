#include "MouseCaster.hpp"
#include "../graphics/cameras/Camera.hpp"
/**
\file MouseCaster.cpp
\brief Implementation file for the MouseCaster class

\author Christopher Arausa
\date 05/15/2019
\version Final
*/

/**
\brief Constructor
*/
MouseCaster::MouseCaster(){

}

/**
\brief This function returns the current mouse location in the world by unrolling all of the projection, view, clipspace, and screenspace factors.
\param proj --- mat4 projection matrix
\param view --- mat4 view matrix
*/
glm::vec3 MouseCaster::calculateMouseRay(glm::vec2 mouse_pos, glm::mat4 proj, glm::mat4 view){
  //Convert to clip space
  glm::vec4 clipped_direction = glm::vec4(mouse_pos.x, mouse_pos.y,-1, 1);

  //Converting to eyespace
  glm::mat4 invert_projection = glm::inverse(proj);
  glm::vec4 eye_trans = invert_projection * clipped_direction;
  glm::vec4 eye_coords = glm::vec4(eye_trans.x, eye_trans.y, -1, 0);

  //Convert to world space with the inverse view and transforming by our eye coordinates.
  glm::mat4 inverse_view = glm::inverse(view);
  glm::vec4 ray_direction= inverse_view *  eye_coords;

  //Normalize the ray so we have a unit vector
  ray_direction = glm::normalize(ray_direction);
  glm::vec3 final_direction = glm::vec3(ray_direction.x, ray_direction.y, ray_direction.z);
  return final_direction;
}


/**
\brief Returns the current location of the mouse.
*/
glm::vec3 MouseCaster::getRay(){
  return current_ray;
}

/**
\brief Updates the current ray location
\param mouse_pos --- Mouse position in normalized device coordinates.
\param camera --- Camera to grab the projection and view matrix from
*/
void MouseCaster::update(glm::vec2 mouse_pos, Camera* camera){
  if(camera!=nullptr){
    // glm::mat4 proj = camera->getProjection();
    // glm::mat4 view = camera->getView();
    // current_ray = calculateMouseRay(proj,view);
    current_ray = calculateMouseRay(mouse_pos, camera->getProjection(), camera->getView());
  }
}
