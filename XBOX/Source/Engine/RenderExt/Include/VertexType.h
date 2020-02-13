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
#include "libStandard.h"
#include "libRenderCore.h"
#include "libMaths.h"


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
  VI_BoneWeight,
  VI_BoneIndex
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
  sizeof(Vec4),   // VI_BoneWeight
  sizeof(Vec4)    // VI_BoneIndex
}; // VertexItemSize


// ----------------------------------------------------------------------------
// Defines for building vertex type structures
// ----------------------------------------------------------------------------
#define VERTEX_TYPE_START(x)  struct x {
#define VERTEX_TYPE_END                                         \
                static const uint SIZE;                         \
                static const ubyte NUM_ITEMS;                   \
                static const VertexItem ITEMS[];                \
                static const char *NAME; };


// ----------------------------------------------------------------------------
// Defines for specifying vertex item data types
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
  T &operator +=(int num)   { m_pdata += (m_stride * num); return *((T*)(m_pdata)); }
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
#define VT_BONEWEIGHT(x)  VT_FLOAT4 x;
#define VT_BONEINDEX(x)   VT_FLOAT4 x;


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
// Name: VT_PNCT
// Desc: Vertex type for position, normal, color, and a single texture
// ----------------------------------------------------------------------------
VERTEX_TYPE_START(VT_PNT_ANIM)

  VT_POSITION   (pos)
  VT_BONEWEIGHT (weight)
  VT_BONEINDEX  (index)
  VT_NORMAL     (norm)
  VT_TEXTURE    (tex)

VERTEX_TYPE_END


// ----------------------------------------------------------------------------
// Name: VertexType  (class)
// Desc: Provides the information required to render with an array of vertex 
//     data in a particular format.
// ----------------------------------------------------------------------------
class VertexType : private Unique
{
public:
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  VertexType(const char *name) : m_name(name), m_size(0)
  {
    REF_COUNT_CTOR(VertexType);
  }

  // --------------------------------------------------------------------------
  // Destructor
  // --------------------------------------------------------------------------
  virtual ~VertexType()
  {
    REF_COUNT_DTOR(VertexType);
  }

  // ------------------------------------------------------------------------
  // Get the attributes of the vertex type
  // ------------------------------------------------------------------------
  const String             &GetName()       const { return m_name;   }
  ubyte                     GetSize()       const { return m_size;   }

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
  String                                m_name;
  ubyte                                 m_size;

}; // class VertexType


// ----------------------------------------------------------------------------
// Templated vertex type class
// ----------------------------------------------------------------------------
template <typename T>
class VertexTypeTemplate : public VertexType
{
public:
  // ------------------------------------------------------------------------
  // Constructor
  // ------------------------------------------------------------------------
  VertexTypeTemplate() : VertexType(T::NAME)
  {
    // Set the vertex info
    m_size      = sizeof(T);

    // Create the items
    ubyte offset = 0;
    for (ubyte i = 0; i < T::NUM_ITEMS; i++)
    {
      m_items.insert(MakePair(T::ITEMS[i], offset));
      offset += VertexItemSize[T::ITEMS[i]];
    } // for
  } // VertexTypeTemplate


  // ------------------------------------------------------------------------
  // Destructor
  // ------------------------------------------------------------------------
  virtual ~VertexTypeTemplate()
  {
  } // ~VertexTypeTemplate

}; // class VertexTypeTemplate


// ----------------------------------------------------------------------------
// Common vertex type templates
// ----------------------------------------------------------------------------
typedef VertexTypeTemplate<VT_P>        VertexType_P;
typedef VertexTypeTemplate<VT_PC>       VertexType_PC;
typedef VertexTypeTemplate<VT_PT>       VertexType_PT;
typedef VertexTypeTemplate<VT_PCT>      VertexType_PCT;
typedef VertexTypeTemplate<VT_PN>       VertexType_PN;
typedef VertexTypeTemplate<VT_PNC>      VertexType_PNC;
typedef VertexTypeTemplate<VT_PNCT>     VertexType_PNCT;
typedef VertexTypeTemplate<VT_PNT>      VertexType_PNT;
typedef VertexTypeTemplate<VT_PNT_ANIM> VertexType_PNT_ANIM;


// ----------------------------------------------------------------------------
// Custom vertex type
// ----------------------------------------------------------------------------
class CustomVertexType : public VertexType
{
public:
  // ------------------------------------------------------------------------
  // ------------------------------------------------------------------------
  CustomVertexType(const char *name) 
    : VertexType(name)
  {
    REF_COUNT_CTOR(CustomVertexType);
  }


  // ------------------------------------------------------------------------
  // Destructor
  // ------------------------------------------------------------------------
  virtual ~CustomVertexType()
  {
    REF_COUNT_DTOR(CustomVertexType);
  }


  // ------------------------------------------------------------------------
  // Add an item to the vertex type
  // ------------------------------------------------------------------------
  void AddItem(VertexItem vertex_item)
  {
    m_items.insert(MakePair(vertex_item, m_size));
    m_size += VertexItemSize[vertex_item]; 
  } // AddItem

}; // class CustomVertexType


// ----------------------------------------------------------------------------
// Name: VertexTypeCache (class)
// Desc: Class to cache vertex types
// ----------------------------------------------------------------------------
class VertexTypeCache
{
public:
  // --------------------------------------------------------------------------
  // Get a vertex type from the cache
  // --------------------------------------------------------------------------
  static const VertexType *GetVertexType(const String &name);

  // --------------------------------------------------------------------------
  // Register a vertex type in the cache
  // --------------------------------------------------------------------------
  static void RegisterVertexType(const String &name, VertexType *pVertexType);
  static void UnRegisterVertexType(const String &name);
  
private:
  // --------------------------------------------------------------------------
  // Private static members
  // --------------------------------------------------------------------------
  static Map<String, VertexType *>  s_VertexTypeMap;

}; // class VertexTypeCache


template <class T>
struct VertexTypeCreationFunctor : public ApplicationCentral::CreationFunctor
{
  VertexTypeCreationFunctor(const String &name) 
    : ApplicationCentral::CreationFunctor(name) { pItem = NULL; }

  virtual bool Create()
  {
    pItem = new T;
    VertexTypeCache::RegisterVertexType(Name, pItem);
    return true;
  }

  virtual bool Destroy()
  {
    if (pItem)
    {
      VertexTypeCache::UnRegisterVertexType(Name);
          delete pItem;
      pItem = NULL;
    }
    return true;
  }

  T *pItem;
};


#define REGISTER_VERTEXTYPE(x) ApplicationCentral::AddCreationFunctor(new VertexTypeCreationFunctor<x>(#x));


#endif // _VERTEX_TYPE_H

// -- EOF

