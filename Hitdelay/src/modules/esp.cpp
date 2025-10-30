#include <Windows.h>
#include <list>

#include <gl/GL.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "modules.hpp"
#include "../hook/hook.hpp"
#include <imgui.h>


void drawBox(glm::vec4 color, bool filled)
{
    if (filled)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(color.r, color.g, color.b, color.a * 0.3f); 

        glBegin(GL_QUADS);
        {
            // Front face
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);

            // Back face
            glVertex3f(1.0f, 1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);

            // Top face
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);

            // Bottom face
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);

            // Left face
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);

            // Right face
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);
        }
        glEnd();

        glDisable(GL_BLEND);
    }

    // Draw the wireframe
    glColor4f(color.r, color.g, color.b, color.a); // Solid color

    glBegin(GL_LINES);
    {
        // Front face
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);

        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        // Back face
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);

        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);

        // Left face
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);

        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        // Right face
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
    }
    glEnd();
}

vec2f world_to_screen(vec3f world_pos, vec3f cam_pos)
{
    GLdouble modelview[16];
    GLdouble projection[16];

     convert to double types 
    for (int i = 0; i < 16; i++)
    {
        modelview[i] = static_cast<GLdouble>(game->MODELVIEW[i]);
        projection[i] = static_cast<GLdouble>(game->PROJECTION[i]);
    }

    double screenX, screenY, screenZ;
    gluProject(world_pos.x, world_pos.y, world_pos.z,
        modelview, projection, game->VIEWPORT.data(),
        &screenX, &screenY, &screenZ);

    vec3f cam_forward = { game->MODELVIEW[2], game->MODELVIEW[6], game->MODELVIEW[10] };
    vec3f cam_pos_relative = world_pos - cam_pos;
    float dot = cam_pos_relative.dot(vec3f::normalize(cam_forward));

     check if worldPos is in front of the camera
    if (dot < 0) {
        return { static_cast<float>(screenX), static_cast<float>(game->VIEWPORT[3] - screenY) };
    }

     is behind the camera 
    return { -1.0f, -1.0f };

    return { static_cast<float>(screenX), static_cast<float>(viewport[3] - screenY) };
}

void modules::esp::run(::cache& cache) {

    vec3f m_pos = utils::get_cam_pos(game->MODELVIEW);
    render_pos = vec3d((double)m_pos.x, (double)m_pos.y, (double)m_pos.z);
    render_pos = {
        cache.theMinecraft->getRenderManager().renderPosX.get(),
        cache.theMinecraft->getRenderManager().renderPosY.get(),
        cache.theMinecraft->getRenderManager().renderPosZ.get()
    };
    player_pos = cache.thePlayer.get_position();
    player_prev_pos = cache.thePlayer.get_prev_position();

    boxes = get_boxes(manager);*/
}

void modules::esp::on_enable(::cache& cache) {
    static bool once = true;
    if (once) {
        once = false;
    }
}

void modules::esp::on_disable(::cache& cache) {
}

void modules::esp::render_options() {
    ImGui::Checkbox("Fill Box", &modules::fill_3d);
}