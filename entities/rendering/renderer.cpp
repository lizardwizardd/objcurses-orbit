/*
 * renderer.cpp (patched for MeshGit: camera view_transform + pan)
 */

#include "renderer.h"

#include <limits>
#include <vector>

char Renderer::luminance_char(const Vec3 &normal, const Vec3 &light, const std::string &scale)
{
    const float sim = (Vec3::cosine_similarity(normal, light) + 1.0f) * 0.5f;
    const int idx = std::clamp(static_cast<int>(std::round(sim * static_cast<float>(scale.size() - 1))), 0, static_cast<int>(scale.size() - 1));
    return scale[idx];
}

void Renderer::render(Buffer &buf, const Object &obj, const Camera &cam,
                      const Light &light, bool static_light, bool color_support,
                      bool highlight_moved)
{
    const float lx = buf.logical_x;
    const float ly = buf.logical_y;

    const size_t vcount = obj.vertices.size();

    std::vector<Vec3> rverts(vcount);   // rotated vertices
    std::vector<Vec3> sverts(vcount);   // screen coords (without offset)

    float min_x = std::numeric_limits<float>::max();
    float max_x = -std::numeric_limits<float>::max();
    float min_y = std::numeric_limits<float>::max();
    float max_y = -std::numeric_limits<float>::max();

    for (size_t i = 0; i < vcount; i++)
    {
        const Vec3 rv = cam.view_transform(obj.vertices[i]);
        rverts[i] = rv;

        const Vec3 sv = Vec3::to_screen(rv, cam.zoom, lx, ly);
        sverts[i] = sv;

        min_x = std::min(min_x, sv.x);
        max_x = std::max(max_x, sv.x);
        min_y = std::min(min_y, sv.y);
        max_y = std::max(max_y, sv.y);
    }

    // offset with camera pan added
    const float off_x = 0.0f + cam.pan_x;
    const float off_y = (ly - (max_y - min_y)) * 0.5f - min_y + cam.pan_y;
    const Vec3 offset(off_x, off_y, 0.0f);

    int moved_mat = -1;
    if (highlight_moved && color_support)
    {
        for (size_t i = 0; i < obj.materials.size(); ++i)
        {
            if (obj.materials[i].material_name == "moved")
            {
                moved_mat = static_cast<int>(i);
                break;
            }
        }
    }

    const bool use_moved = highlight_moved && moved_mat >= 0 &&
                           obj.moved_triangle.size() == obj.faces.size();

    size_t face_index = 0;
    for (const auto &face : obj.faces)
    {
        const size_t fi = face_index++;

        const Vec3 &rv1 = rverts[face.indices[0]];
        const Vec3 &rv2 = rverts[face.indices[1]];
        const Vec3 &rv3 = rverts[face.indices[2]];

        // back-face culling in camera space
        Vec3 normal_cam = Vec3::cross(rv2 - rv1, rv3 - rv1).normalize();

        if (normal_cam.z >= 0.0f)
        {
            continue;
        }

        const Vec3 normal_view = -normal_cam;

        // screen coordinates with centering offset
        const Vec3 s1 = sverts[face.indices[0]] + offset;
        const Vec3 s2 = sverts[face.indices[1]] + offset;
        const Vec3 s3 = sverts[face.indices[2]] + offset;

        const Vec3 n_light = static_light ? Vec3::cross(obj.vertices[face.indices[1]] - obj.vertices[face.indices[0]],
                                                        obj.vertices[face.indices[2]] - obj.vertices[face.indices[0]])
                                                .normalize()
                                          : normal_view;
        const char lum = luminance_char(n_light, light.direction, CHARS_LUM);

        int mat = (color_support && face.material) ? *face.material : -1;
        if (use_moved && obj.moved_triangle[fi]) mat = moved_mat;
        buf.draw_projection(Projection(s1, s2, s3, lum), lum, mat);
    }
}
