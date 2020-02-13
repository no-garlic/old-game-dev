
#include "VertexType.h"


// --------------------------------------------------------------------------
// Initialise the static members
// --------------------------------------------------------------------------
Map<String, VertexType *>  VertexTypeCache::s_VertexTypeMap;


// ----------------------------------------------------------------------------
// Vertex Type: P
// ----------------------------------------------------------------------------
const ubyte               VT_P::NUM_ITEMS   = 1;
const VertexItem          VT_P::ITEMS[]     = { VI_Position };
const char               *VT_P::NAME        = "VertexType_P";
const uint                VT_P::SIZE        = sizeof(VT_P);


// ----------------------------------------------------------------------------
// Vertex Type: PC
// ----------------------------------------------------------------------------
const ubyte               VT_PC::NUM_ITEMS  = 2;
const VertexItem          VT_PC::ITEMS[]    = { VI_Position, VI_Color };
const char               *VT_PC::NAME       = "VertexType_PC";
const uint                VT_PC::SIZE       = sizeof(VT_PC);


// ----------------------------------------------------------------------------
// Vertex Type: PT
// ----------------------------------------------------------------------------
const ubyte               VT_PT::NUM_ITEMS  = 2;
const VertexItem          VT_PT::ITEMS[]    = { VI_Position, VI_Texture };
const char               *VT_PT::NAME       = "VertexType_PT";
const uint                VT_PT::SIZE       = sizeof(VT_PT);


// ----------------------------------------------------------------------------
// Vertex Type: PCT
// ----------------------------------------------------------------------------
const ubyte               VT_PCT::NUM_ITEMS = 3;
const VertexItem          VT_PCT::ITEMS[]   = { VI_Position, VI_Color, VI_Texture };
const char               *VT_PCT::NAME      = "VertexType_PCT";
const uint                VT_PCT::SIZE      = sizeof(VT_PCT);


// ----------------------------------------------------------------------------
// Vertex Type: PN
// ----------------------------------------------------------------------------
const ubyte               VT_PN::NUM_ITEMS  = 2;
const VertexItem          VT_PN::ITEMS[]    = { VI_Position, VI_Normal };
const char               *VT_PN::NAME       = "VertexType_PN";
const uint                VT_PN::SIZE       = sizeof(VT_PN);


// ----------------------------------------------------------------------------
// Vertex Type: PNC
// ----------------------------------------------------------------------------
const ubyte               VT_PNC::NUM_ITEMS = 3;
const VertexItem          VT_PNC::ITEMS[]   = { VI_Position, VI_Normal, VI_Color };
const char               *VT_PNC::NAME      = "VertexType_PNC";
const uint                VT_PNC::SIZE      = sizeof(VT_PNC);


// ----------------------------------------------------------------------------
// Vertex Type: PNCT
// ----------------------------------------------------------------------------
const ubyte               VT_PNCT::NUM_ITEMS  = 4;
const VertexItem          VT_PNCT::ITEMS[]    = { VI_Position, VI_Normal, VI_Color, VI_Texture };
const char               *VT_PNCT::NAME       = "VertexType_PNCT";
const uint                VT_PNCT::SIZE       = sizeof(VT_PNCT);


// ----------------------------------------------------------------------------
// Vertex Type: PNT
// ----------------------------------------------------------------------------
const ubyte               VT_PNT::NUM_ITEMS = 3;
const VertexItem          VT_PNT::ITEMS[]   = { VI_Position, VI_Normal, VI_Texture };
const char               *VT_PNT::NAME      = "VertexType_PNT";
const uint                VT_PNT::SIZE      = sizeof(VT_PNT);


// ----------------------------------------------------------------------------
// Vertex Type: PNT ANIM
// ----------------------------------------------------------------------------
const ubyte               VT_PNT_ANIM::NUM_ITEMS = 5;
const VertexItem          VT_PNT_ANIM::ITEMS[]   = { VI_Position, VI_BoneWeight, VI_BoneIndex, VI_Normal, VI_Texture };
const char               *VT_PNT_ANIM::NAME      = "VertexType_PNT_ANIM";
const uint                VT_PNT_ANIM::SIZE      = sizeof(VT_PNT_ANIM);


// --------------------------------------------------------------------------
// Get a vertex type from the cache
// --------------------------------------------------------------------------
const VertexType *VertexTypeCache::GetVertexType(const String &name)
{
  Map<String, VertexType *>::iterator iter = s_VertexTypeMap.find(name);
  if (iter != s_VertexTypeMap.end())
    return iter->second;

  return NULL;
}


// --------------------------------------------------------------------------
// Register a vertex type in the cache
// --------------------------------------------------------------------------
void VertexTypeCache::RegisterVertexType(const String &name, VertexType *pVertexType)
{
  ASSERT(GetVertexType(name) == NULL, "Cannot register two vertex types with the same name");
  s_VertexTypeMap.insert(MakePair(name, pVertexType));
}


// --------------------------------------------------------------------------
// UnRegister a vertex type in the cache
// --------------------------------------------------------------------------
void VertexTypeCache::UnRegisterVertexType(const String &name)
{
  s_VertexTypeMap.erase(name);
}


// -- EOF
