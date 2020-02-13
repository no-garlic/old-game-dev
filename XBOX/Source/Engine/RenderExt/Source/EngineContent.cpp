
#include "EngineContent.h"
#include "libRenderCore.h"
#include "Material.h"
#include "VertexType.h"
#include "FixedFunctionMaterial.h"
#include "Material_PNT_ANIM.h"
#include "DebugMaterial.h"


bool RegisterEngineContent()
{
  // Fixed function materials
  REGISTER_DEFAULT_MATERIAL(FixedFunctionMaterial_P);
  REGISTER_MATERIAL(FixedFunctionMaterial_PC);
  REGISTER_MATERIAL(FixedFunctionMaterial_PT);
  REGISTER_MATERIAL(FixedFunctionMaterial_PCT);
  REGISTER_MATERIAL(FixedFunctionMaterial_PN);
  REGISTER_MATERIAL(FixedFunctionMaterial_PNC);
  REGISTER_MATERIAL(FixedFunctionMaterial_PNCT);
  REGISTER_MATERIAL(FixedFunctionMaterial_PNT);

  // Shader materials
  REGISTER_MATERIAL(Material_PNT_ANIM);
  REGISTER_MATERIAL(DebugMaterial);

  // Vertex types
  REGISTER_VERTEXTYPE(VertexType_P);
  REGISTER_VERTEXTYPE(VertexType_PC);
  REGISTER_VERTEXTYPE(VertexType_PT);
  REGISTER_VERTEXTYPE(VertexType_PCT);
  REGISTER_VERTEXTYPE(VertexType_PN);
  REGISTER_VERTEXTYPE(VertexType_PNC);
  REGISTER_VERTEXTYPE(VertexType_PNCT);
  REGISTER_VERTEXTYPE(VertexType_PNT);
  REGISTER_VERTEXTYPE(VertexType_PNT_ANIM);

  return true;
}


// -- EOF

