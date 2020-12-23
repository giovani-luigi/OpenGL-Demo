# OpenGL-Demo
A simple C++ OpenGL 3D demo of a First Person camera, moving in a scene, using a skybox with night texture, and some objects.


## Scene
A dark night, surrounded by mountains in the far plane, using the moon as main light source.
The camera is controlled in first person, and a flashlight can be toggled on/off so you can inspect the objects in the scene.

## Implemented features
- First person camera, clamped to the ground (no movement on Y)
- Camera controlled by keyboard (position) and mouse (YAW, Pitch), so it moves towards where you look at
- Loading Wavefront OBJ files with textures 
  - Thanks to Syoyo Fujita for his amazing "tiny_obj_loader.h" single-file OBJ parser
- Loading texture files from 2D images
  - Thanks to Sean Barrett (and collaborators) for his amazing "stb_image.h" single-file image decoder.
- "Infinite" floor Quad, so you can walk forever
- Skybox with night sky and with the moon 
- Main light (point light) to mimic the moon's light (no decay over distance)
- A flashlight held in first person, with ON/OFF switch (mouse click to toggle a spot light)

## TODO
- Shadows support
- Simple collision detection
- Add texture to the floor

This is a work in progress... as of Dec. 2020
