# Yuki
---
This is a game engine that I'm going to be programming over the course of a few weeks for my COSC482 Graphics class at Salisbury University.
My goal is to make something that I can use for the remaining labs & project and help solidify my understanding of the work I've done this semester.

## Information
#### Why Yuki?
I like snow and my only other real hobby is studying japanese, so I'm trying to mask my inability to think of creative names. It's also conveniently 4 letters, so namespaces don't need to be trimmed much at all.

#### Current Features
Mediocre Shader class. It functions.
Basic polygon drawing, texturing, & coloring.
Asset Manager to hold and distribute shared resources.
Quaternion based camera.

#### TODO List
Spherical Camera
Model & loading
Quaternion based model rotations
Transformations
Basic Shapes(Circle, rec, triangle) generation
Model generation(Cube, spheres, and planes)
Materials
Lighting
Cubemaps
Model Loading
Terrain objects
Terrain Generation & Perlin noise
Collision
Finding Objects at a given location
Finding object under mouse
Ray Casting
Particle Systems(fire)
Grass, Water, leaf shaders.
Beam/Rays

#### Technologies used
SFML - Input & Window handling. Maybe down the line I'll use their sound class, but I haven't looked into it too much yet.
Bullet physics engine(TM) - We haven't started this yet in class, but I'm assuming I might want this.
OpenGL - Pretty much the bulk of the class.
