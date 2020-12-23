#include "FloorSceneObject.h"

constexpr auto GRID_TILE_SIZE = 10; // you want this to be greater or equal than zFar of the perspective projection;

std::vector<glm::vec3> FloorSceneObject::create_corners(float size)
{
    return vector<glm::vec3>{
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
        Material::create_night_floor())
{
    
    m_material = Material::create_texture("Models\\Floor.jpg", Material::create_default());
    auto f_texts = std::vector<float>{
        QuadSurfaceSceneObject::generate_texture_coordinates()
    };
    set_texture_coordinates(f_texts);

}

void FloorSceneObject::draw(const Camera& camera, const glm::mat4& projection, const SceneLights& lights)
{
    const auto cam_pos = camera.get_position();

    // calculate in which tile of an imaginary grid (XZ plane) we are
    float row = glm::round(cam_pos.z / GRID_TILE_SIZE);
    float col = glm::round(cam_pos.x / GRID_TILE_SIZE);

    // translate to the tile in the given row and column
    // this is the center tile to bw drawn
    m_transformation = Transform3D()
        .translate(
            (col * GRID_TILE_SIZE),     // x
            0.0f,                       // y
            (row * GRID_TILE_SIZE));    // z


    // draw center tile

    //  [ ][ ][ ]
    //  [ ][+][ ]
    //  [ ][ ][ ]

    SceneObject::draw(camera, projection, lights);

    // we also need to draw all other tiles around it, so the transitions are not visible
    // as long as the lenght of 1 tile, is at least the length of the Z depth of the frustrum (zFar-zNear)

    //  [1][2][3]
    //  [8][ ][4]
    //  [7][6][5]

    m_transformation = Transform3D().translate((col - 1) * GRID_TILE_SIZE, 0.0f, (row - 1) * GRID_TILE_SIZE); // tile 1
    SceneObject::draw(camera, projection, lights);
    m_transformation = Transform3D().translate((col    ) * GRID_TILE_SIZE, 0.0f, (row - 1) * GRID_TILE_SIZE); // tile 2
    SceneObject::draw(camera, projection, lights);
    m_transformation = Transform3D().translate((col + 1) * GRID_TILE_SIZE, 0.0f, (row - 1) * GRID_TILE_SIZE); // tile 3
    SceneObject::draw(camera, projection, lights);
    m_transformation = Transform3D().translate((col + 1) * GRID_TILE_SIZE, 0.0f, (row    ) * GRID_TILE_SIZE); // tile 4
    SceneObject::draw(camera, projection, lights);
    m_transformation = Transform3D().translate((col + 1) * GRID_TILE_SIZE, 0.0f, (row + 1) * GRID_TILE_SIZE); // tile 5
    SceneObject::draw(camera, projection, lights);
    m_transformation = Transform3D().translate((col    ) * GRID_TILE_SIZE, 0.0f, (row + 1) * GRID_TILE_SIZE); // tile 6
    SceneObject::draw(camera, projection, lights);
    m_transformation = Transform3D().translate((col - 1) * GRID_TILE_SIZE, 0.0f, (row + 1) * GRID_TILE_SIZE); // tile 7
    SceneObject::draw(camera, projection, lights);
    m_transformation = Transform3D().translate((col - 1) * GRID_TILE_SIZE, 0.0f, (row    ) * GRID_TILE_SIZE); // tile 8
    SceneObject::draw(camera, projection, lights);
}
