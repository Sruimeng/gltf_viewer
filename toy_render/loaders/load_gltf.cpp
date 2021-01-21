#include <iostream>
#include "../scene/scene.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#if defined( WIN32 )
#    pragma warning( push )
#    pragma warning( disable : 4267 )
#endif
#include "../supports/tinygltf/tiny_gltf.h"
#if defined( WIN32 )
#    pragma warning( pop )
#endif

#include "../math/vector.h"
namespace toy
{
    namespace
    {

        union Convert
        {
            uchar2 intTobyte;
            uchar4 byte;
            float outByte;
            int outInt;
        };

        float3 make_float3_from_double(double x, double y, double z)
        {
            return make_float3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
        }

        float makeRealFolat(unsigned char x, unsigned char y, unsigned char z, unsigned char w)
        {
            Convert convert;
            convert.byte.x = x;
            convert.byte.y = y;
            convert.byte.z = z;
            convert.byte.w = w;
            return convert.outByte;
        }

        uchar4 makeByteByFloat(float num)
        {
            Convert convert;
            convert.outByte = num;
            return convert.byte;
        }

        uchar2 makeByteInt(int num)
        {
            Convert convert;
            convert.outInt = num;
            return convert.intTobyte;
        }
    } // namespace

    void bufferViewFromGLTF(const tinygltf::Model &model, Scene *scene, const int32_t accessor_idx, const int32_t type, Mesh *mesh)
    {
        if (accessor_idx == -1)
            std::cerr << "glTF accessor_idx is -1;"
                      << "'\n";

        const auto &gltf_accessor = model.accessors[accessor_idx];
        const auto &gltf_buffer_view = model.bufferViews[gltf_accessor.bufferView];
        const int32_t elmt_byte_size =
            gltf_accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT ? 2 : gltf_accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT ? 4 : gltf_accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT ? 4 : 0;
        if (!elmt_byte_size)
            std::cerr << "gltf accessor component type not supported;"
                      << "'\n";
        std::vector<unsigned char>::const_iterator begin;
        std::vector<unsigned char>::const_iterator end;

        // if (gltf_buffer_view.byteOffset != 0)
        // {
        //     begin = scene->m_data.begin() + gltf_buffer_view.byteOffset;
        //     end = scene->m_data.begin() + gltf_buffer_view.byteOffset + gltf_buffer_view.byteLength;
        // }
        // else
        // {
        //     begin = scene->m_data.begin();
        //     end = scene->m_data.begin() + gltf_buffer_view.byteLength;
        // }
        std::vector<unsigned char> index(begin, end);
        int byte = elmt_byte_size * 3;
        auto length = index.size() / byte;
        switch (type)
        {
        case 0:

            for (size_t i = 0; i < length; i++)
            {
                int3 inde;
                inde.x = index[byte * i] + index[byte * i + 1] * 256;
                inde.y = index[byte * i + elmt_byte_size] + index[byte * i + elmt_byte_size + 1] * 256;
                inde.z = index[byte * i + elmt_byte_size * 2] + index[byte * i + elmt_byte_size * 2 + 1] * 256;
                mesh->indicesArray.push_back(inde);
            }
            break;
        case 1:

            for (size_t i = 0; i < length; i++)
            {
                float3 point;
                //point.x = index[byte * i];
                //point.y = index[byte * i + elmt_byte_size];
                //point.z = index[byte * i + elmt_byte_size * 2];
                point.x = makeRealFolat(index[byte * i], index[byte * i + 1], index[byte * i + 2], index[byte * i + 3]);

                point.y = makeRealFolat(index[byte * i + elmt_byte_size], index[byte * i + elmt_byte_size + 1], index[byte * i + elmt_byte_size + 2], index[byte * i + elmt_byte_size + 3]);

                point.z = makeRealFolat(index[byte * i + elmt_byte_size * 2], index[byte * i + 1 + elmt_byte_size * 2], index[byte * i + 2 + elmt_byte_size * 2], index[byte * i + 3 + elmt_byte_size * 2]);

                mesh->verticesArray.push_back(point);
            }
            break;
        case 2:
            for (size_t i = 0; i < length; i++)
            {
                float3 normal;
                normal.x = makeRealFolat(index[byte * i], index[byte * i + 1], index[byte * i + 2], index[byte * i + 3]);

                normal.y = makeRealFolat(index[byte * i + elmt_byte_size], index[byte * i + elmt_byte_size + 1], index[byte * i + elmt_byte_size + 2], index[byte * i + elmt_byte_size + 3]);

                normal.z = makeRealFolat(index[byte * i + elmt_byte_size * 2], index[byte * i + 1 + elmt_byte_size * 2], index[byte * i + 2 + elmt_byte_size * 2], index[byte * i + 3 + elmt_byte_size * 2]);

                mesh->normalsArray.push_back(normal);
            }
            break;
        }
    }

    void processGLTFNode(
        Scene *scene,
        const tinygltf::Model &model,
        const tinygltf::Node &gltf_node,
        const Matrix4x4 &parent_matrix)
    {
        // const Matrix4x4 translation = gltf_node.translation.empty() ? Matrix4x4::identity() : Matrix4x4::translate(make_float3_from_double(gltf_node.translation[0], gltf_node.translation[1], gltf_node.translation[2]));
        // const Matrix4x4 rotation = gltf_node.rotation.empty() ? Matrix4x4::identity() : Quaternion(static_cast<float>(gltf_node.rotation[3]), static_cast<float>(gltf_node.rotation[0]), static_cast<float>(gltf_node.rotation[1]), static_cast<float>(gltf_node.rotation[2])).rotationMatrix();
        // const Matrix4x4 scale = gltf_node.scale.empty() ? Matrix4x4::identity() : Matrix4x4::scale(make_float3_from_double(gltf_node.scale[0], gltf_node.scale[1], gltf_node.scale[2]));
        // std::vector<float> gltf_matrix;
        // for (double x : gltf_node.matrix)
        //     gltf_matrix.push_back(static_cast<float>(x));
        // const Matrix4x4 matrix = gltf_node.matrix.empty() ? Matrix4x4::identity() : Matrix4x4(reinterpret_cast<float *>(gltf_matrix.data())).transpose();

       // Matrix4x4 node_xform = parent_matrix * matrix * translation * rotation * scale;

        // if (gltf_node.mesh != -1)
        // {
        //     const auto &gltf_mesh = model.meshes[gltf_node.mesh];
        //     std::cerr << "Processing glTF mesh: '" << gltf_mesh.name << "'\n";
        //     std::cerr << "\tNum mesh primitive groups: " << gltf_mesh.primitives.size() << std::endl;
        //     for (auto &gltf_primitive : gltf_mesh.primitives)
        //     {
        //         if (gltf_primitive.mode != TINYGLTF_MODE_TRIANGLES) // Ignore non-triangle meshes
        //         {
        //             std::cerr << "\tNon-triangle primitive: skipping\n";
        //             continue;
        //         }

        //         Mesh mesh;

        //         mesh.name = gltf_mesh.name;

        //         bufferViewFromGLTF(model, scene, gltf_primitive.indices, 0, &mesh);
        //         mesh.material_idx.push_back(gltf_primitive.material);
        //         mesh.transform = node_xform;
        //         mesh.num_triangles = mesh.indicesArray.size();
        //         std::cerr << "\t\tNum triangles: " << mesh.num_triangles << std::endl;

        //         assert(gltf_primitive.attributes.find("POSITION") != gltf_primitive.attributes.end());
        //         const int32_t pos_accessor_idx = gltf_primitive.attributes.at("POSITION");
        //         bufferViewFromGLTF(model, scene, pos_accessor_idx, 1, &mesh);
        //         mesh.num_vertices = mesh.verticesArray.size();
        //         std::cerr << "\t\tNum vertices: " << mesh.num_vertices << std::endl;
        //         const auto &pos_gltf_accessor = model.accessors[pos_accessor_idx];
        //         mesh.object_aabb = Aabb(
        //             make_float3_from_double(
        //                 pos_gltf_accessor.minValues[0],
        //                 pos_gltf_accessor.minValues[1],
        //                 pos_gltf_accessor.minValues[2]),
        //             make_float3_from_double(
        //                 pos_gltf_accessor.maxValues[0],
        //                 pos_gltf_accessor.maxValues[1],
        //                 pos_gltf_accessor.maxValues[2]));
        //         mesh.world_aabb = mesh.object_aabb;
        //         //mesh.world_aabb.transform(node_xform);

        //         auto normal_accessor_iter = gltf_primitive.attributes.find("NORMAL");
        //         if (normal_accessor_iter != gltf_primitive.attributes.end())
        //         {
        //             std::cerr << "\t\tHas vertex normals: true\n";
        //             bufferViewFromGLTF(model, scene, normal_accessor_iter->second, 2, &mesh);
        //         }
        //         else
        //         {
        //             std::cerr << "\t\tHas vertex normals: false\n";
        //             bufferViewFromGLTF(model, scene, -1, 2, &mesh);
        //         }

        //         /*auto texcoord_accessor_iter = gltf_primitive.attributes.find("TEXCOORD_0");
		// 		if (texcoord_accessor_iter != gltf_primitive.attributes.end())
		// 		{
		// 			std::cerr << "\t\tHas texcoords: true\n";
		// 			bufferViewFromGLTF(model, scene, texcoord_accessor_iter->second, 3, &mesh);
		// 		}
		// 		else
		// 		{
		// 			std::cerr << "\t\tHas texcoords: false\n";
		// 			bufferViewFromGLTF(model, scene, -1, 3, &mesh);
		// 		}*/

        //         //scene->m_meshes.push_back(mesh);
        //     }
        // }
        // else if (!gltf_node.children.empty())
        // {
        //     for (int32_t child : gltf_node.children)
        //     {
        //         processGLTFNode(scene, model, model.nodes[child], node_xform);
        //     }
        // }
    }

    void loadGLTF(const std::string& filename, Scene* scene, const std::string& model_type)
    {

        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;
        tinygltf::Model model;
        bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
        if (!warn.empty())
            std::cerr << "glTF WARNING: " << warn << std::endl;
        if (!ret)
        {
            std::cerr << "Failed to load GLTF scene '" << filename << "': " << err << std::endl;
        }

        //
        // Process buffer data first -- buffer views will reference this list
        //
        for (const auto &gltf_buffer : model.buffers)
        {
            const uint64_t buf_size = gltf_buffer.data.size();
            /*std::cerr << "Processing glTF buffer '" << gltf_buffer.name << "'\n"
				<< "\tbyte size: " << buf_size << "\n"
				<< "\turi      : " << gltf_buffer.uri << std::endl;*/
            auto data = gltf_buffer.data;
            //scene->m_data = gltf_buffer.data;
        }

        //
        // Process nodes
        //
        std::vector<int32_t> root_nodes(model.nodes.size(), 1);
        for (auto &gltf_node : model.nodes)
            for (int32_t child : gltf_node.children)
                root_nodes[child] = 0;

        for (size_t i = 0; i < root_nodes.size(); ++i)
        {
            if (!root_nodes[i])
                continue;
            auto &gltf_node = model.nodes[i];
            processGLTFNode(scene, model, gltf_node, Matrix4x4::identity());
        }
        // scene->m_num_meshes = scene->m_meshes.size();
        // scene->m_scene_aabb.invalidate();
        // for (const auto mesh : scene->m_meshes)
        //     scene->m_scene_aabb.include(mesh.world_aabb);
        //return model;
    }

} // namespace uality
