#include "SceneShadows.h"
#include "glm/ext/matrix_clip_space.hpp"

constexpr unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

SceneShadows::SceneShadows(const SceneLights& lights): m_lights(lights), m_fbo(0), m_depthMap(0)
{

    // create a frame buffer, so we can use to render the depth map
    // scene viewed from the light's source point of view
	glGenFramebuffers(1, &m_fbo);

	// Next we create a 2D texture that we'll use as the framebuffer's depth buffer:
	glGenTextures(1, &m_depthMap);
	glBindTexture(GL_TEXTURE_2D, m_depthMap);
	// Because we only care about depth values we specify the texture's formats as GL_DEPTH_COMPONENT
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	m_shader = Shader("shadow.vertex.shader", "shadow.fragment.shader");
}

void SceneShadows::compute(std::vector<SceneObject*>& objects)
{
	glBindTexture(GL_TEXTURE_2D, m_depthMap);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// attach the texture buffer as the buffer of the framebuffer, so all rendering commands will write to the texture 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);

	// A framebuffer object however is not complete without a color buffer so we need to explicitly tell OpenGL
    // we're not going to render any color data. We do this by setting both the read and draw buffer to GL_NONE
    glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// set the current frame buffer (from now on, we will be rendering to the texture)

	// With a properly configured framebuffer that renders depth values to a texture we can generate the depth map
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClear(GL_DEPTH_BUFFER_BIT);

    configure_shader();
	render_scene(objects);

	// restore the default normal framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // restore the original viewport size
	//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void SceneShadows::configure_shader()
{
	// set the projection to be used by the shader. We can use perspective since its a point light.
	// if we were using directional light (no position) all rays would be parallel, hence an orthogonal projection is prefered
	auto proj = glm::perspective(MathUtils::deg_to_rad(67.0f), (float)SHADOW_WIDTH / SHADOW_HEIGHT, 0.1f, 10.0f);

	// create a transformation matrix to transform each object to the light's point of view
	// for this, we generate a look at matrix from the light position, looking to the center of the scene
	auto light_matrix = glm::lookAt(m_lights.position, glm::vec3(0, 0, 0), glm::vec3(0., 1., 0.));

	auto lightSpaceMatrix = proj * light_matrix;

	m_shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
}

void SceneShadows::render_scene(std::vector<SceneObject*>& objects)
{
	for (auto obj : objects)
	{
		obj->draw();
	}
}
