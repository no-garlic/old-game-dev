// ----------------------------------------------------------------------------
// File: VertexType.h
// Desc: Defines the built-in vertex types that we support in the application
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef _VERTEX_TYPE_H
#define _VERTEX_TYPE_H


// ----------------------------------------------------------------------------
// Standard includes
// ----------------------------------------------------------------------------
#include "Kernel/KernelInc.h"
#include "Engine/EngineInc.h"
#include "Maths/MathInc.h"


// ----------------------------------------------------------------------------
// Forward declarations
// ----------------------------------------------------------------------------
class VertexType;


// ----------------------------------------------------------------------------
// Name: VertexItem (enum)
// Desc: The available vertex attribute types
// ----------------------------------------------------------------------------
enum VertexItem
{
  VI_Position = 0,
  VI_Position2,
  VI_Normal,
  VI_Normal2,
  VI_Color,
  VI_Color2,
  VI_Texture,
  VI_Texture2,
  VI_BoneWeights,
  VI_BoneIndices
}; // enum VertexItem


// ----------------------------------------------------------------------------
// Name: VertexItemSize (array)
// Desc: An array of the size of each vertex item type
// ----------------------------------------------------------------------------
static ubyte VertexItemSize[] =
{
  sizeof(Vec3),   // VI_Position
  sizeof(Vec3),   // VI_Position2
  sizeof(Vec3),   // VI_Normal
  sizeof(Vec3),   // VI_Normal2
  sizeof(ulong),  // VI_Color
  sizeof(ulong),  // VI_Color2
  sizeof(Vec2),   // VI_Texture
  sizeof(Vec2),   // VI_Texture2
  sizeof(Vec4),   // VI_BoneWeights
  sizeof(Vec4)    // VI_BoneIndices
}; // VertexItemSize


// ----------------------------------------------------------------------------
// Defines for building vertex type structures
// ----------------------------------------------------------------------------
#define VERTEX_TYPE_START(x)  struct x {
#define VERTEX_TYPE_END                                         \
                static const ulong FVF;                         \
                static const uint SIZE;                         \
                static const ubyte NUM_ITEMS;                   \
                static const VertexItem ITEMS[];                \
                static const VertexType TYPE;                   \
                static const char *NAME;                        \
                static const D3DVERTEXELEMENT9 DECL[]; };


// ----------------------------------------------------------------------------
// Defines for pecifying vertex item data types
// ----------------------------------------------------------------------------
#define VT_FLOAT3     Vec3
#define VT_FLOAT4     Vec4
#define VT_FLOAT2     Vec2
#define VT_ULONG      ulong


// ----------------------------------------------------------------------------
// Name: GeomPtr (class)
// Desc: A smart pointer class that reads values that are segmented by a stride
//       through a block of data.
// ----------------------------------------------------------------------------
template <class T>
class GeomPtr
{
public:
  // ------------------------------------------------------------------------
  // Constructors
  // ------------------------------------------------------------------------
  GeomPtr() : m_pdata(0), m_stride(0) {}
  GeomPtr(ubyte stride, ubyte offset, void *pdata) : m_pdata((ubyte *)pdata + offset), m_stride(stride) {}

  // ------------------------------------------------------------------------
  // Pointer operators to manipulate and read the m_pdata pointer using the
  // stride of the data.
  // ------------------------------------------------------------------------
     operator T ()          { return *((T*)(m_pdata)); }
  T &operator * ()          { return *((T*)(m_pdata)); }
  T *operator ->()          { return  ((T*)(m_pdata)); }
  T &operator [](uint idx)  { return *((T*)(m_pdata + (idx * m_stride)));   }
  const T &operator [](uint idx) const { return *((T*)(m_pdata + (idx * m_stride)));   }
  T &operator ++()          { m_pdata += m_stride; return *((T*)(m_pdata)); }
  T &operator --()          { m_pdata -= m_stride; return *((T*)(m_pdata)); }
     operator bool()        { return (m_pdata != 0); }

private:
  // ------------------------------------------------------------------------
  // Private members
  // ------------------------------------------------------------------------
  uchar   *m_pdata;
  ubyte    m_stride;
}; // class GeomPtr


// ----------------------------------------------------------------------------
// Common pointer types for our geom data
// ----------------------------------------------------------------------------
typedef GeomPtr<VT_FLOAT4>  Vec4GeomPtr;
typedef GeomPtr<VT_FLOAT3>  Vec3GeomPtr;
typedef GeomPtr<VT_FLOAT2>  Vec2GeomPtr;
typedef GeomPtr<VT_ULONG>   ULongGeomPtr;


// ----------------------------------------------------------------------------
// Defines for specifying vertex type attributes
// ----------------------------------------------------------------------------
#ifdef VT_COLOR
# undef VT_COLOR
#endif

#define VT_POSITION(x)    VT_FLOAT3 x;
#define VT_NORMAL(x)      VT_FLOAT3 x;
#define VT_TEXTURE(x)     VT_FLOAT2 x;
#define VT_COLOR(x)       VT_ULONG  x;
#define VT_BONE_WEIGHT(x) VT_FLOAT4 x;
#define VT_BONE_INDEX(x)  VT_FLOAT4 x;


// ----------------------------------------------------------------------------
// Name: VT_P
// Desc: Vertex type for position only
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_P)

  VT_POSITION (pos)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PC
// Desc: Vertex type for position and color
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PC)

  VT_POSITION (pos)
  VT_COLOR    (col)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PT
// Desc: Vertex type for position and texture
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PT)

  VT_POSITION (pos)
  VT_TEXTURE  (tex)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PCT
// Desc: Vertex type for position, color, and texture
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PCT)

  VT_POSITION (pos)
  VT_COLOR    (col)
  VT_TEXTURE  (tex)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PN
// Desc: Vertex type for position and normal
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PN)

  VT_POSITION (pos)
  VT_NORMAL   (norm)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PNC
// Desc: Vertex type for position, normal, and color
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PNC)

  VT_POSITION (pos)
  VT_NORMAL   (norm)
  VT_COLOR    (col)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PNT
// Desc: Vertex type for position, normal, and a single texture
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PNT)

  VT_POSITION (pos)
  VT_NORMAL   (norm)
  VT_TEXTURE  (tex)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PNCT
// Desc: Vertex type for position, normal, color, and a single texture
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PNCT)

  VT_POSITION (pos)
  VT_NORMAL   (norm)
  VT_COLOR    (col)
  VT_TEXTURE  (tex)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_P_ANIM
// Desc: Animation vertex type for position
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_P_ANIM)

  VT_POSITION     (pos)
  VT_BONE_WEIGHT  (weight)
  VT_BONE_INDEX   (index)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PN_ANIM
// Desc: Animation vertex type for position and normal
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PN_ANIM)

  VT_POSITION     (pos)
  VT_BONE_WEIGHT  (weight)
  VT_BONE_INDEX   (index)
  VT_NORMAL       (norm)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PT_ANIM
// Desc: Animation vertex type for position and a single texture
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PT_ANIM)

  VT_POSITION     (pos)
  VT_BONE_WEIGHT  (weight)
  VT_BONE_INDEX   (index)
  VT_TEXTURE      (tex)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VT_PNT_ANIM
// Desc: Animation vertex type for position, normal, and a single texture
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PNT_ANIM)

  VT_POSITION     (pos)
  VT_BONE_WEIGHT  (weight)
  VT_BONE_INDEX   (index)
  VT_NORMAL       (norm)
  VT_TEXTURE      (tex)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VertexType  (class)
// Desc: Provides the information required to render with an array of vertex 
//     data in a particular format.
// ----------------------------------------------------------------------------
class VertexType : public RefCounted, private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor and destructor
  // --------------------------------------------------------------------------
  VertexType(const char *name) : m_name(name), m_pdecl(0), m_size(0), m_num_decl(0), m_vertex_decl(0)
  {
    REF_COUNT_CTOR(VertexType);
  }


  virtual ~VertexType()
  {
    REF_COUNT_DTOR(VertexType);
    SafeRelease(m_vertex_decl);
  }


  // ------------------------------------------------------------------------
  // Get the attributes of the vertex type
  // ------------------------------------------------------------------------
  const String             &GetName()       const { return m_name;   }
  ubyte                     GetSize()       const { return m_size;   }
  const D3DVERTEXELEMENT9  *GetDECL()       const { return m_pdecl;  }  


  LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration() const
  {
    if (!m_vertex_decl)
      if (m_pdecl)
        D3DCheck(ApplicationCentral.GetDevice()->CreateVertexDeclaration(m_pdecl, &m_vertex_decl));

    return m_vertex_decl;
  } // GetVertexDeclaration


  VertexType(const VertexType &other)
  {
    REF_COUNT_CTOR(VertexType);

    m_items = other.m_items;
    m_name = other.m_name;
    m_size = other.m_size;
    m_num_decl = other.m_num_decl;
    m_vertex_decl = NULL;

    m_pdecl = new D3DVERTEXELEMENT9[m_num_decl + 1];
    memcpy(m_pdecl, other.m_pdecl, ( m_num_decl + 1) * sizeof(D3DVERTEXELEMENT9));
  } // VertexType


  VertexType &operator=(const VertexType &other)
  {
    m_items = other.m_items;
    m_name = other.m_name;
    m_size = other.m_size;
    m_num_decl = other.m_num_decl;
    m_vertex_decl = NULL;

    if (m_pdecl)
      delete[] m_pdecl;

    m_pdecl = new D3DVERTEXELEMENT9[m_num_decl + 1];
    memcpy(m_pdecl, other.m_pdecl, ( m_num_decl + 1) * sizeof(D3DVERTEXELEMENT9));

    return *this;
  } // operator=

  
  // ------------------------------------------------------------------------
  // Get the offset (stride) of the item
  // ------------------------------------------------------------------------
  int GetItemOffset(VertexItem vertex_item) const
  {
    Map<VertexItem, ubyte>::const_iterator iter = m_items.find(vertex_item);
    if (iter != m_items.end())
    return iter->second;

    return -1;
  } // GetItemOffset


protected:
  // ------------------------------------------------------------------------
  // Private members
  // ------------------------------------------------------------------------
  Map<VertexItem, ubyte>                m_items;
  uint                                  m_num_decl;
  D3DVERTEXELEMENT9                    *m_pdecl;
  mutable LPDIRECT3DVERTEXDECLARATION9  m_vertex_decl;
  String                                m_name;
  ubyte                                 m_size;

}; // class VertexType


template <typename T>
class VertexTypeTemplate : public VertexType
{
public:
  VertexTypeTemplate() : VertexType(T::NAME)
  {
    REF_COUNT_CTOR(VertexTypeTemplate);

    // Set the vertex info
    m_size      = sizeof(T);
    m_num_decl  = T::NUM_ITEMS;
    m_pdecl     = new D3DVERTEXELEMENT9[T::NUM_ITEMS + 1];

    for (uint i = 0; i < T::NUM_ITEMS; i++)
      m_pdecl[i] = T::DECL[i];

    D3DVERTEXELEMENT9 decl_end = D3DDECL_END();
    m_pdecl[T::NUM_ITEMS] = decl_end;

    // Create the items
    ubyte offset = 0;
    for (ubyte i = 0; i < T::NUM_ITEMS; i++)
    {
      m_items.insert(MakePair(T::ITEMS[i], offset));
      offset += VertexItemSize[T::ITEMS[i]];
    } // for

    // Make sure that built in vertex types dont get ref counted
    SetRefCount(0xffff);
  } // VertexTypeTemplate

  virtual ~VertexTypeTemplate()
  {
    REF_COUNT_DTOR(VertexTypeTemplate);

    if (m_pdecl) 
      delete[] m_pdecl;

    m_pdecl = 0;
  } // ~VertexTypeTemplate

}; // class VertexTypeTemplate


typedef VertexTypeTemplate<VT_P>        VertexType_P;
typedef VertexTypeTemplate<VT_PC>       VertexType_PC;
typedef VertexTypeTemplate<VT_PT>       VertexType_PT;
typedef VertexTypeTemplate<VT_PCT>      VertexType_PCT;
typedef VertexTypeTemplate<VT_PN>       VertexType_PN;
typedef VertexTypeTemplate<VT_PNC>      VertexType_PNC;
typedef VertexTypeTemplate<VT_PNCT>     VertexType_PNCT;
typedef VertexTypeTemplate<VT_PNT>      VertexType_PNT;
typedef VertexTypeTemplate<VT_P_ANIM>   VertexType_P_ANIM;  
typedef VertexTypeTemplate<VT_PN_ANIM>  VertexType_PN_ANIM;  
typedef VertexTypeTemplate<VT_PT_ANIM>  VertexType_PT_ANIM;  
typedef VertexTypeTemplate<VT_PNT_ANIM> VertexType_PNT_ANIM;  


class CustomVertexType : public VertexType
{
public:
  CustomVertexType(const char *name) : VertexType(name) { REF_COUNT_CTOR(CustomVertexType); }
  virtual ~CustomVertexType() { REF_COUNT_DTOR(CustomVertexType); if (m_pdecl) delete[] m_pdecl; }

  void AddItem(VertexItem vertex_item, D3DVERTEXELEMENT9 decl)
  {
    m_items.insert(MakePair(vertex_item, m_size));
    m_size += VertexItemSize[vertex_item]; 

    D3DVERTEXELEMENT9 decl_end = D3DDECL_END();

    if (m_num_decl > 0)
    {
      m_num_decl++;
      D3DVERTEXELEMENT9 *pold_decl = m_pdecl;
      m_pdecl = new D3DVERTEXELEMENT9[m_num_decl + 1];

      for (uint i = 0; i < m_num_decl - 1; i++)
        m_pdecl[i] = pold_decl[i];

      m_pdecl[m_num_decl - 1] = decl;
      m_pdecl[m_num_decl]     = decl_end;

      delete[] pold_decl;
    } // if
    else
    {
      m_num_decl = 1;
      m_pdecl = new D3DVERTEXELEMENT9[2];
      m_pdecl[0] = decl;
      m_pdecl[1] = decl_end;
    } // else
  } // AddItem

}; // class CustomVertexType


#endif // _VERTEX_TYPE_H

// -- EOF

