#ifndef YUKI_GRAPHICS_HPP
#define YUKI_GRAPHICS_HPP

// Catchall include file for when I use this as a game engine for the projects.

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // value ptr
#include <vector>
#include <iostream>

#include "graphics/GraphicsDefinitions.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Shader.hpp"

#include "graphics/QuaternionObject.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Material.hpp"
#include "graphics/Light.hpp"
#include "graphics/drawables/LightCube.hpp"
//Drawables
#include "graphics/drawables/Polygon.hpp"
#include "graphics/drawables/Quad.hpp"
#include "graphics/drawables/Cube.hpp"
#include "graphics/drawables/Model.hpp"



#include "graphics/GraphicsEngine.hpp"


#endif
