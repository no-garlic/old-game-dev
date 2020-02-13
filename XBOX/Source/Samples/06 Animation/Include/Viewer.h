//----------------------------------------------------------------------------//
// viewer.cpp                                                                 //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//            Adapted by Laurent Desmecht for D3D version                     //
//----------------------------------------------------------------------------//
// This program is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU General Public License as published by the Free //
// Software Foundation; either version 2 of the License, or (at your option)  //
// any later version.                                                         //
//----------------------------------------------------------------------------//

#ifndef VIEWER_H
#define VIEWER_H

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//
#include "libEngine.h"


// 29 is the hardware maximum with vs1.1 but
// the program will subdivise the submesh
// if this contraint is not respected
// 80 is for vertex shader 2.0 but
// this don't change the performance

#define MAXBONESPERMESH 29
//#define MAXBONESPERMESH 80


//----------------------------------------------------------------------------//
// Class declaration                                                          //
//----------------------------------------------------------------------------//

class Viewer
{
// member variables
protected:
  unsigned int m_lastTick;
  CalCoreModel* m_calCoreModel;
  CalModel* m_calModel;
  CalHardwareModel* m_calHardwareModel; 
  float m_scale;
  int m_currentAnimationId;
  float m_leftAnimationTime;
  float m_blendTime;
  float m_lodLevel;

  struct VERTEX
  {
    D3DXVECTOR3    pos;
    float  Weight[4];
    float Indices[4];
    D3DXVECTOR3	normal;
    FLOAT tu,tv;
  };


// constructors/destructor
public:
	Viewer();
	virtual ~Viewer();
	
// member functions
public:
  bool onCreate(LPSTR lpCmdLine);
  void onIdle();
  bool onInit();
  void onRender();
  void onShutdown();

protected:
  bool parseModelConfiguration(const std::string& strFilename);
  void renderModel();
  bool loadVertexBuffer();
  bool loadVertexShader();
private:
	// D3D vertex & index buffer
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	int m_numVertices;
	LPDIRECT3DINDEXBUFFER9  m_pIB;
	int m_numFaces;
	LPDIRECT3DVERTEXSHADER9 m_pVS;

	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration;
};

extern Viewer theViewer;

#endif

//----------------------------------------------------------------------------//
