
#include "Render/VertexType.h"


// ----------------------------------------------------------------------------
// Vertex Type: P
// ----------------------------------------------------------------------------
const ubyte               VT_P::NUM_ITEMS   = 1;
const VertexItem          VT_P::ITEMS[]     = { VI_Position };
const char               *VT_P::NAME        = "VertexType_P";
const uint                VT_P::SIZE        = sizeof(VT_P);
const D3DVERTEXELEMENT9   VT_P::DECL[]      = 
{
  { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  D3DDECL_END()
};
const VertexType          VT_P::TYPE        = VertexType_P();


// ----------------------------------------------------------------------------
// Vertex Type: PC
// ----------------------------------------------------------------------------
const ubyte               VT_PC::NUM_ITEMS  = 2;
const VertexItem          VT_PC::ITEMS[]    = { VI_Position, VI_Color };
const char               *VT_PC::NAME       = "VertexType_PC";
const uint                VT_PC::SIZE       = sizeof(VT_PC);
const D3DVERTEXELEMENT9   VT_PC::DECL[]     = 
{
  { 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
  D3DDECL_END()
};
const VertexType          VT_PC::TYPE       = VertexType_PC();


// ----------------------------------------------------------------------------
// Vertex Type: PT
// ----------------------------------------------------------------------------
const ubyte               VT_PT::NUM_ITEMS  = 2;
const VertexItem          VT_PT::ITEMS[]    = { VI_Position, VI_Texture };
const char               *VT_PT::NAME       = "VertexType_PT";
const uint                VT_PT::SIZE       = sizeof(VT_PT);
const D3DVERTEXELEMENT9   VT_PT::DECL[]     = 
{
  { 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
  D3DDECL_END()
};
const VertexType          VT_PT::TYPE       = VertexType_PT();


// ----------------------------------------------------------------------------
// Vertex Type: PCT
// ----------------------------------------------------------------------------
const ubyte               VT_PCT::NUM_ITEMS = 3;
const VertexItem          VT_PCT::ITEMS[]   = { VI_Position, VI_Color, VI_Texture };
const char               *VT_PCT::NAME      = "VertexType_PCT";
const uint                VT_PCT::SIZE      = sizeof(VT_PCT);
const D3DVERTEXELEMENT9   VT_PCT::DECL[]    = 
{
  { 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
  { 0, 16, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
  D3DDECL_END()
};
const VertexType          VT_PCT::TYPE      = VertexType_PCT();


// ----------------------------------------------------------------------------
// Vertex Type: PN
// ----------------------------------------------------------------------------
const ubyte               VT_PN::NUM_ITEMS  = 2;
const VertexItem          VT_PN::ITEMS[]    = { VI_Position, VI_Normal };
const char               *VT_PN::NAME       = "VertexType_PN";
const uint                VT_PN::SIZE       = sizeof(VT_PN);
const D3DVERTEXELEMENT9   VT_PN::DECL[]     = 
{
  { 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
  D3DDECL_END()
};
const VertexType          VT_PN::TYPE       = VertexType_PN();


// ----------------------------------------------------------------------------
// Vertex Type: PNC
// ----------------------------------------------------------------------------
const ubyte               VT_PNC::NUM_ITEMS = 3;
const VertexItem          VT_PNC::ITEMS[]   = { VI_Position, VI_Normal, VI_Color };
const char               *VT_PNC::NAME      = "VertexType_PNC";
const uint                VT_PNC::SIZE      = sizeof(VT_PNC);
const D3DVERTEXELEMENT9   VT_PNC::DECL[]    = 
{
  { 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
  { 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
  D3DDECL_END()
};
const VertexType          VT_PNC::TYPE      = VertexType_PNC();


// ----------------------------------------------------------------------------
// Vertex Type: PNCT
// ----------------------------------------------------------------------------
const ubyte               VT_PNCT::NUM_ITEMS  = 4;
const VertexItem          VT_PNCT::ITEMS[]    = { VI_Position, VI_Normal, VI_Color, VI_Texture };
const char               *VT_PNCT::NAME       = "VertexType_PNCT";
const uint                VT_PNCT::SIZE       = sizeof(VT_PNCT);
const D3DVERTEXELEMENT9   VT_PNCT::DECL[]     = 
{
  { 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
  { 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
  { 0, 28, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
  D3DDECL_END()
};
const VertexType          VT_PNCT::TYPE       = VertexType_PNCT();


// ----------------------------------------------------------------------------
// Vertex Type: PNT
// ----------------------------------------------------------------------------
const ubyte               VT_PNT::NUM_ITEMS = 3;
const VertexItem          VT_PNT::ITEMS[]   = { VI_Position, VI_Normal, VI_Texture };
const char               *VT_PNT::NAME      = "VertexType_PNT";
const uint                VT_PNT::SIZE      = sizeof(VT_PNT);
const D3DVERTEXELEMENT9   VT_PNT::DECL[]    = 
{
  { 0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
  { 0, 24, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
  D3DDECL_END()
};
const VertexType          VT_PNT::TYPE      = VertexType_PNT();


// ----------------------------------------------------------------------------
// Vertex Type: P_ANIM
// ----------------------------------------------------------------------------
const ubyte               VT_P_ANIM::NUM_ITEMS = 3;
const VertexItem          VT_P_ANIM::ITEMS[]   = { VI_Position, VI_BoneWeights, VI_BoneIndices };
const char               *VT_P_ANIM::NAME      = "VertexType_P_ANIM";
const uint                VT_P_ANIM::SIZE      = sizeof(VT_P_ANIM);
const D3DVERTEXELEMENT9   VT_P_ANIM::DECL[]    = 
{
  { 0, 0 ,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
  { 0, 28,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
  D3DDECL_END()
};
const VertexType          VT_P_ANIM::TYPE      = VertexType_P_ANIM();


// ----------------------------------------------------------------------------
// Vertex Type: PN_ANIM
// ----------------------------------------------------------------------------
const ubyte               VT_PN_ANIM::NUM_ITEMS = 4;
const VertexItem          VT_PN_ANIM::ITEMS[]   = { VI_Position, VI_BoneWeights, VI_BoneIndices, VI_Normal };
const char               *VT_PN_ANIM::NAME      = "VertexType_PN_ANIM";
const uint                VT_PN_ANIM::SIZE      = sizeof(VT_PN_ANIM);
const D3DVERTEXELEMENT9   VT_PN_ANIM::DECL[]    = 
{
  { 0, 0 ,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
  { 0, 28,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
  { 0, 44,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
  D3DDECL_END()
};
const VertexType          VT_PN_ANIM::TYPE      = VertexType_PN_ANIM();


// ----------------------------------------------------------------------------
// Vertex Type: PT_ANIM
// ----------------------------------------------------------------------------
const ubyte               VT_PT_ANIM::NUM_ITEMS = 4;
const VertexItem          VT_PT_ANIM::ITEMS[]   = { VI_Position, VI_BoneWeights, VI_BoneIndices, VI_Texture };
const char               *VT_PT_ANIM::NAME      = "VertexType_PT_ANIM";
const uint                VT_PT_ANIM::SIZE      = sizeof(VT_PT_ANIM);
const D3DVERTEXELEMENT9   VT_PT_ANIM::DECL[]    = 
{
  { 0, 0 ,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
  { 0, 28,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
  { 0, 44,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
  D3DDECL_END()
};
const VertexType          VT_PT_ANIM::TYPE      = VertexType_PT_ANIM();


// ----------------------------------------------------------------------------
// Vertex Type: PNT_ANIM
// ----------------------------------------------------------------------------
const ubyte               VT_PNT_ANIM::NUM_ITEMS = 5;
const VertexItem          VT_PNT_ANIM::ITEMS[]   = { VI_Position, VI_BoneWeights, VI_BoneIndices, VI_Normal, VI_Texture };
const char               *VT_PNT_ANIM::NAME      = "VertexType_PNT_ANIM";
const uint                VT_PNT_ANIM::SIZE      = sizeof(VT_PNT_ANIM);
const D3DVERTEXELEMENT9   VT_PNT_ANIM::DECL[]    = 
{
  { 0, 0 ,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
  { 0, 12,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
  { 0, 28,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
  { 0, 44,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
  { 0, 56,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
  D3DDECL_END()
};
const VertexType          VT_PNT_ANIM::TYPE      = VertexType_PNT_ANIM();


// -- EOF
