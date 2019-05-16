#ifndef TGEN_SCENE
#define TGEN_SCENE
#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <chrono>
#include "../graphics/Scene.hpp"
#include "../graphics/drawables/Mesh.hpp"
#include "MouseCaster.hpp"
#include <deque>
using namespace std;
class Light;
class Yuki;
class Mesh;
class Quad;
class TerrainChunk;
class Light;

/**
\mainpage 3D Project

\tableofcontents

\section intro Introduction

This project was an exploration and learning process of randomly generated terrains in 3D worlds, and shader exploration.
Fully loaded, this project includes a skybox, a heightmap terrain generated mesh, instanced grass drawing, and some REALLY bad water. I was playing with framebuffers and didn't get too far. I really wanted to finish the water in time but didn't.

I spent a fair amount of time working with the water and kind of fell on my face. I tried using a 3D mesh for the water, then use sin/cos functions to oscilate the Y values of the water to simulate waves. But I just got a sort of diseased twitching effect.
So I started looking into uvmapping and refaction techniques.
Which lead me to attmept to draw the scene to a separate framebuffer, extract the texture, then draw the scene again with my water texture. Then I was going to try to flip it and do the refraction and mix them. But I ran out of time.
(Update) with your extra day I mostly finished! Thank you. I also got a chance to do raycasting in 3d.
The water is created by using a flat quad, and creating textures of the planes below and above the water by creating new framebuffers and clipping the planes. Then combining them in the fragment shader and applying distortion using a dudv map.

The grass I initially had a LOT of problems with and spent a lot of time fighting with ideas on how to do it. What I ended up with was an idea of seeding a grass patch in every chunk where grass exists, using only the vertices on the mesh as point data.
Then I pass the data to the graphics card and use the geoemtry shader to multiply the seeds and turn each into a quad, and use some trig on the top vertices of the grass to simulate a smooth sway of wind. Playing with the wave variables drastically alters the product so I left it VERY low. You can see it if you get up close.
The grass was a serious win in my opinion. It could be better, but this one is mine. I want to apply billboarding to it and see what I can accomplish with more time.(Most of the 3D stuff I only learned recently).
I also didn't have time to figure out normals for my grass.

The terrain is generated by using noise to generate a heightmap. Then using that heightmap I map them to vertices in a mesh and load them in and scale them. This took a lot of tweaking.
I multi-threaded the terrain generation using c++ threading so there won't be lag when the user flies around(another big win).

There is very basic raycasting in the scene where if the user right clicks, a light cube is placed units away from the user in teh direction they clicked.
I didn't have time to code the intersection stuff.

The relevant shaders to this project are the Default, CubeMap, Water, and Grass shaders.

Unseen in the folder are mesh loading classes, asset managing classes, various camera types.

When the user first spawns in, there is only a skybox around the camera with nothing else.
Terrain spawning options are in the key control section, but you have to enable the Terrain generator with the T key. (old relic from before multithreading was in the project.)

\subsection options User Options
- Escape: Exits the program
- F10: Takes a screenshot

Movement
- W: Moves the camera forward relative ot the camera face
- A: Moves the camera left relative to the camera face
- D: Moves the camera right relative to the camera face
- S: Moves the camera backwards relative to the camera face.
- Shift: Moves the camera down relative to the camera face.
- Space: Moves the camera up relative to the camera face.
- Up: Rotates the camera up
- Down: Rotates the camera down
- Left: Rotates the camera left
- Right: Rotates the camera right.

Toggle Options
- M: Toggles between fill and line modes to draw triangles.
- G: Toggles grass on and off.
- Y: Toggles the skybox
- U: Toggles the sun
- F: Toggles the framerate calc in the title.
- T: Toggles the terrain generator on and off.
- Q: Toggles the water distortion.
- C: Toggles clipping of the water plane
- V: Toggles which plane to clip, higher or lower. 
Left clicking and dragging the mouse will rotate the camera in place and look around.

Right clicking in the scene places a light cube 30 units in the direction of the ray vector.
*/

/**
\file TerrainGenScene.hpp
\brief Primary header file for the project.

\author Christopher Arausa
\version Final
\date 05/14/2019
*/

/**
\class TGenScene
\brief The scene class contains all of the logic for our simulation.
*/
class TGenScene : public Scene {
  private:
    Cube* skybox; ///< Skybox cube
    std::map<std::pair<int,int>, TerrainChunk*> chunks; ///< A map of the terrain chunks with the world coordinates as a key.
    std::deque<Light*> lights; ///< A vector containing all of the lights in our scene.
    bool draw_mesh; ///< Boolean toggle for whether to draw the mesh.
    bool draw_skybox; ///< Boolean toggle for whether to draw the skybox.
    Light *Sun; ///< The primary light in the scene is the sun.
    std::vector<Quad> grass; ///< I don't think I use this anymore. But it was early grass.
    int chunk_view_distance; ///< The view distance of the camera chunk-wise.
    bool framerate; ///< Boolean toggle for whether to show the framerate.
    bool draw_grass; ///< Boolean value for whether we draw our grass.
    glm::vec4 upper_plane; ///< Plane equations for clipspace math
    glm::vec4 lower_plane; ///< Plane equation for clipspace math
    bool apply_distortion; ///< Boolean for whether to apply distortion to our water.
    MouseCaster mouse_caster; ///< MouseCaster class for using raycasting to location our mouse in the scene.
    std::deque<LightCube*> cubes; ///< Light cubes to draw.
    bool clip_plane; ///< Boolean value for whether to clip the planes
    bool clip_low; ///< Boolean value for whether to clip high or low.
  public:
    TGenScene(Yuki *yuki);
    ~TGenScene();
    unsigned int seed; ///< The seed for this iteration
    unsigned int chunk_size; ///< The chunk size for the terrain.
    void draw();
    void update(float delta);
    void updateShaders();
    void keyPressedEventHandler(sf::Event::KeyEvent event);
    void keyStateEventHandler();
    void mouseButtonEventHandler(sf::Event::MouseButtonEvent event);
    void mouseMoveEventHandler(sf::Event::MouseMoveEvent event);

    static void tChunkGen(TGenScene* tgs, int x, int z, int seed);
};

#endif