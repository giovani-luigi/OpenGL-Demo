#include "FloorSceneObject.h"

constexpr auto GRID_TILE_SIZE = 10; // you want this to be greater or equal than zFar of the perspective projection;

std::vector<glm::vec3> FloorSceneObject::create_corners(float size)
{
    return std::vector<glm::vec3>{
        glm::vec3(-size/2.0f, 0, +size/2.0f),
        glm::vec3(+size/2.0f, 0, +size/2.0f),
        glm::vec3(+size/2.0f, 0, -size/2.0f),
        glm::vec3(-size/2.0f, 0, -size/2.0f),
    };
}

FloorSceneObject::FloorSceneObject(Shader shader) :
    SceneObject(
        QuadSurfaceSceneObject::generate_vertices(create_corners(GRID_TILE_SIZE)),
        QuadSurfaceSceneObject::generate_normals(create_corners(GRID_TILE_SIZE)),
        STATIC, 
        shader, 
        Material::create_night_floor()), m_row(0), m_col(0), m_camera(nullptr), m_projection(nullptr), m_lights(nullptr)
{
    
    m_material = Material::create_texture("Images\\Floor.jpg", Material::create_default());
    auto f_texts = std::vector<float>{
        QuadSurfaceSceneObject::generate_texture_coordinates()
    };
    set_texture_coordinates(f_texts);
}

void FloorSceneObject::draw() {

    if (m_camera == nullptr || m_lights == nullptr || m_projection == nullptr)
        return; // object not configured yet, so we cannot draw...

    // draw center tile

    //  [ ][ ][ ]
    //  [ ][+][ ]
    //  [ ][ ][ ]

    // translate to the tile in the given row and column
    // this is the center tile to bw drawn
    m_transformation = Transform3D()
        .translate(
            (m_col * GRID_TILE_SIZE),     // x
            0.0f,                       // y
            (m_row * GRID_TILE_SIZE));    // z

    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    // we also need to draw all other tiles around it, so the transitions are not visible
    // as long as the lenght of 1 tile, is at least the length of the Z depth of the frustrum (zFar-zNear)

    //  [1][2][3]
    //  [8][ ][4]
    //  [7][6][5]

    m_transformation = Transform3D().translate((m_col - 1) * GRID_TILE_SIZE, 0.0f, (m_row - 1) * GRID_TILE_SIZE); // tile 1
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    m_transformation = Transform3D().translate((m_col)*GRID_TILE_SIZE, 0.0f, (m_row - 1) * GRID_TILE_SIZE); // tile 2
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    m_transformation = Transform3D().translate((m_col + 1) * GRID_TILE_SIZE, 0.0f, (m_row - 1) * GRID_TILE_SIZE); // tile 3
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    m_transformation = Transform3D().translate((m_col + 1) * GRID_TILE_SIZE, 0.0f, (m_row)*GRID_TILE_SIZE); // tile 4
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    m_transformation = Transform3D().translate((m_col + 1) * GRID_TILE_SIZE, 0.0f, (m_row + 1) * GRID_TILE_SIZE); // tile 5
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    m_transformation = Transform3D().translate((m_col)*GRID_TILE_SIZE, 0.0f, (m_row + 1) * GRID_TILE_SIZE); // tile 6
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    m_transformation = Transform3D().translate((m_col - 1) * GRID_TILE_SIZE, 0.0f, (m_row + 1) * GRID_TILE_SIZE); // tile 7
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

    m_transformation = Transform3D().translate((m_col - 1) * GRID_TILE_SIZE, 0.0f, (m_row)*GRID_TILE_SIZE); // tile 8
    SceneObject::configure(*m_camera, *m_projection, *m_lights); // update shaders
    SceneObject::draw();

}

void FloorSceneObject::configure(const Camera& camera, const glm::mat4& projection, const SceneLights& lights)
{
    const auto cam_pos = camera.get_position();

    // calculate in which tile of an imaginary grid (XZ plane) we are
    m_row = glm::round(cam_pos.z / GRID_TILE_SIZE);
    m_col = glm::round(cam_pos.x / GRID_TILE_SIZE);

    SceneObject::configure(camera, projection, lights);

    // store parameters for usage in draw call
    m_camera = &camera;
    m_projection = &projection;
    m_lights = &lights;
}
