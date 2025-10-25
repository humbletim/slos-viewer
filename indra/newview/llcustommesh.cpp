#include "llcustommesh.h"

#include "llmodel.h"
#include "llmodelpreview.h"
#include "llvolume.h"
#include "llsd.h"
#include "llmath.h"

namespace LLCustomMesh
{

void createCubeMesh(LLModelPreview* modelPreview, S32 lod)
{
    // 1. Define Cube Geometry
    const LLVector3 positions[] = {
        // Front face
        LLVector3(-0.5f, -0.5f,  0.5f), LLVector3( 0.5f, -0.5f,  0.5f), LLVector3( 0.5f,  0.5f,  0.5f), LLVector3(-0.5f,  0.5f,  0.5f),
        // Back face
        LLVector3(-0.5f, -0.5f, -0.5f), LLVector3(-0.5f,  0.5f, -0.5f), LLVector3( 0.5f,  0.5f, -0.5f), LLVector3( 0.5f, -0.5f, -0.5f),
        // Top face
        LLVector3(-0.5f,  0.5f,  0.5f), LLVector3( 0.5f,  0.5f,  0.5f), LLVector3( 0.5f,  0.5f, -0.5f), LLVector3(-0.5f,  0.5f, -0.5f),
        // Bottom face
        LLVector3(-0.5f, -0.5f, -0.5f), LLVector3( 0.5f, -0.5f, -0.5f), LLVector3( 0.5f, -0.5f,  0.5f), LLVector3(-0.5f, -0.5f,  0.5f),
        // Right face
        LLVector3( 0.5f, -0.5f,  0.5f), LLVector3( 0.5f, -0.5f, -0.5f), LLVector3( 0.5f,  0.5f, -0.5f), LLVector3( 0.5f,  0.5f,  0.5f),
        // Left face
        LLVector3(-0.5f, -0.5f, -0.5f), LLVector3(-0.5f, -0.5f,  0.5f), LLVector3(-0.5f,  0.5f,  0.5f), LLVector3(-0.5f,  0.5f, -0.5f)
    };

    const LLVector3 normals[] = {
        // Front face
        LLVector3( 0.0f,  0.0f,  1.0f), LLVector3( 0.0f,  0.0f,  1.0f), LLVector3( 0.0f,  0.0f,  1.0f), LLVector3( 0.0f,  0.0f,  1.0f),
        // Back face
        LLVector3( 0.0f,  0.0f, -1.0f), LLVector3( 0.0f,  0.0f, -1.0f), LLVector3( 0.0f,  0.0f, -1.0f), LLVector3( 0.0f,  0.0f, -1.0f),
        // Top face
        LLVector3( 0.0f,  1.0f,  0.0f), LLVector3( 0.0f,  1.0f,  0.0f), LLVector3( 0.0f,  1.0f,  0.0f), LLVector3( 0.0f,  1.0f,  0.0f),
        // Bottom face
        LLVector3( 0.0f, -1.0f,  0.0f), LLVector3( 0.0f, -1.0f,  0.0f), LLVector3( 0.0f, -1.0f,  0.0f), LLVector3( 0.0f, -1.0f,  0.0f),
        // Right face
        LLVector3( 1.0f,  0.0f,  0.0f), LLVector3( 1.0f,  0.0f,  0.0f), LLVector3( 1.0f,  0.0f,  0.0f), LLVector3( 1.0f,  0.0f,  0.0f),
        // Left face
        LLVector3(-1.0f,  0.0f,  0.0f), LLVector3(-1.0f,  0.0f,  0.0f), LLVector3(-1.0f,  0.0f,  0.0f), LLVector3(-1.0f,  0.0f,  0.0f)
    };

    const LLVector2 tex_coords[] = {
        // Front face
        LLVector2(0.0f, 0.0f), LLVector2(1.0f, 0.0f), LLVector2(1.0f, 1.0f), LLVector2(0.0f, 1.0f),
        // Back face
        LLVector2(1.0f, 0.0f), LLVector2(1.0f, 1.0f), LLVector2(0.0f, 1.0f), LLVector2(0.0f, 0.0f),
        // Top face
        LLVector2(0.0f, 1.0f), LLVector2(1.0f, 1.0f), LLVector2(1.0f, 0.0f), LLVector2(0.0f, 0.0f),
        // Bottom face
        LLVector2(1.0f, 1.0f), LLVector2(0.0f, 1.0f), LLVector2(0.0f, 0.0f), LLVector2(1.0f, 0.0f),
        // Right face
        LLVector2(1.0f, 0.0f), LLVector2(1.0f, 1.0f), LLVector2(0.0f, 1.0f), LLVector2(0.0f, 0.0f),
        // Left face
        LLVector2(0.0f, 0.0f), LLVector2(1.0f, 0.0f), LLVector2(1.0f, 1.0f), LLVector2(0.0f, 1.0f),
    };

    const U16 indices[] = {
         0,  1,  2,  0,  2,  3, // Front
         4,  5,  6,  4,  6,  7, // Back
         8,  9, 10,  8, 10, 11, // Top
        12, 13, 14, 12, 14, 15, // Bottom
        16, 17, 18, 16, 18, 19, // Right
        20, 21, 22, 20, 22, 23  // Left
    };

    // 2. Create LLModel
    LLVolumeParams params;
    LLPointer<LLModel> model = new LLModel(params, 0.f);
    model->setNumVolumeFaces(1);

    // 3. Populate LLVolumeFace
    LLStrider<LLVector3> pos_strider((void*)positions, sizeof(LLVector3));
    LLStrider<LLVector3> norm_strider((void*)normals, sizeof(LLVector3));
    LLStrider<LLVector2> tc_strider((void*)tex_coords, sizeof(LLVector2));
    LLStrider<U16> ind_strider((void*)indices, sizeof(U16));

    model->setVolumeFaceData(0, pos_strider, norm_strider, tc_strider, ind_strider, 24, 36);

    // 4. Populate mBaseModel and mBaseScene
    modelPreview->mModel[lod].clear();
    modelPreview->mModel[lod].push_back(model);

    modelPreview->mScene[lod].clear();
    LLModelInstance instance(model, "", LLMatrix4::gIdentity, LLModelInstance::material_map());
    modelPreview->mScene[lod][LLMatrix4::gIdentity].push_back(instance);

    modelPreview->mBaseModel = modelPreview->mModel[lod];
    modelPreview->mBaseScene = modelPreview->mScene[lod];

    // 5. Trigger UI update
    modelPreview->mDirty = true;
    modelPreview->resetPreviewTarget();
    modelPreview->loadModelCallback(lod);
}

} // namespace LLCustomMesh
