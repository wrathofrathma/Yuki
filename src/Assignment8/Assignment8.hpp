#include "../Yuki.hpp"
#include "../graphics/Scene.hpp"
#include "../Graphics.hpp"
#include "../UserInput.hpp"
#include <random>

/**
\mainpage Assignment8

\tableofcontents

\section intro Introduction

There is a large flat plane with a stone texture and green material.
There are 50 randomly placed cubes above y=0 with unique textures on each face.
Each texture on the cube is able to rotate in place, as well as the cubes themselves over a random axis.
There is a cubemap as a background.

You can find most of the relevant code in Assignment8.hpp, Assignment8.cpp, and the RotatingTexture.vs shader.

\subsection options User Options
- Escape: Ends the program
- M: Toggles between fill and line mode to draw the triangles.
- F1: Turns off lighting for the ground plane.
- F2: Turns off lighting on the ground plane.
- F3: Turns on the ground texture.
- F4: Turns off the ground texture.
- F5: Turns on lighting for the cubes.
- F6: Turns off lighting for the cubes.
- F7: Turns on the cube textures
- F8: Turns off cube textures.
- F10: Saves a screenshot of the current screen.
- F11: Turns on the Quaternion camera.
- F12: Turns on the Spherical camera.

If the spherical camera is currently selected,

If no modifier keys are pressed:

- Up: Increases the Psi of the camera.
- Down: Decreases the Psi of the camera.
- Left: Increases the Theta of the camera.
- Right: Decreases the Theta of the camera.

If the control key is down:

- Up: Decreases the radius of the camera to the origin.
- Down: Inreases the radius of the camera to the origin.

Clicking and dragging will alter the Psi and Theta values to give the impression of grabbing and moving the coordinate system.

If the Quaternion camera is currently selected.

If no modifier keys are pressed:

- W: Moves the camera forward relative to itself.
- S: Moves the camera backwards relative to itself.
- A: Moves the camera left relative to itself.
- D: Moves the camera right relative to itself.
- Shift: Moves the camera down relative to itself.
- Space: Moves the camera up relative to itself.
- Up: Rotates the camera up.
- Down: Rotates the camera down.
- Left: Rotates the camera left.
- Right: Rotates the camera right.

Clicking and dragging will alter the orientation of the camera giving the impression of looking around.

*/


/**
\file Assignment8.hpp
\brief Header file for Assignment8.cpp

\author Christopher Arausa
\version Final
\date 5/9/2019

*/

/**
\class SchoolScene
\brief This class contains the scene described in the Assignment 8 PDF.
*/
class SchoolScene : public Scene {
	private:
		std::vector<TestCube*> cubes; ///< A vector containing all of our cube objects in the scene.
    bool text_rotate; ///< Boolean deciding if the texture will rotate.
    bool cube_rotate; ///< Boolean deciding if our cubes will rotate in place.
    float rot_speed = 0.05; ///< Rotation multiplier so our cubes don't go crazy fast.
		Cube* skybox; ///< Skybox for the scene. 
  public:
		SchoolScene(Yuki *yuki);
		~SchoolScene();

    void update(float delta);
    void draw();
    void keyPressedEventHandler(sf::Event::KeyEvent event);
    void keyStateEventHandler();
    void mouseButtonEventHandler(sf::Event::MouseButtonEvent event);
    void mouseMoveEventHandler(sf::Event::MouseMoveEvent event);
};
