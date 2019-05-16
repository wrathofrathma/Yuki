#ifndef MOUSE_CASTER
#define MOUSE_CASTER
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

class Camera;
/**
\file MouseCaster.hpp
\brief Header file for MouseCaster.cpp

\author Christopher Arausa
\version Final
\date 05/15/2019
*/

/**
\class MouseCaster
\brief The mouse caster class utilizes raycasting to select objects in a 3D world
*/
class MouseCaster {
  private:
   glm::vec3 current_ray; ///< vec3 containing the current direction of the mouse. 
 public:
   MouseCaster();
   void update(glm::vec2 mouse_pos, Camera* camera);
   glm::vec3 calculateMouseRay(glm::vec2 mouse_pos, glm::mat4 proj, glm::mat4 view);
   glm::vec3 getRay();
};
#endif
