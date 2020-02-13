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

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include "Viewer.h"


//----------------------------------------------------------------------------//
// The one and only Viewer instance                                           //
//----------------------------------------------------------------------------//




Viewer theViewer;

//----------------------------------------------------------------------------//
// The Direct3D Vertex                                                        //
//----------------------------------------------------------------------------//



//#define D3DFVF_VERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

/*
The vertex shader has been generated by this hlsl code, and small
optimisation gave been done manually:
you can compile with the command :

fxc /Tvs_1_1 VertexShader.fx /Fc dx9_vs1_1.vsa /Zpr


#define MAXBONES 29

struct appdata  {
  float3 Position: POSITION;
  float4 Weight:BLENDWEIGHT;
  float4 Indices:BLENDINDICES;
  float3 Normal: NORMAL;
    float2 TexCoord:TEXCOORD0;    
};

struct vpconn  {
  float4 HPosition: POSITION;
  float2 TexCoord: TEXCOORD0;
  float4 Color: COLOR0;
};


vpconn main(appdata IN,
      uniform float4x4 WorldViewProj: register (c0),
      uniform float3 LightVec: register (c4),
      uniform float4 Diffuse: register (c5),
      uniform float4 Ambient: register (c6),
      uniform float3x4 Bones[MAXBONES]: register (c7)
      )
{
  vpconn OUT;
  
  float4 tempPos;
  tempPos.xyz = IN.Position.xyz;
  tempPos.w = 1.0;
  
  float3 pos= 0;
  float3 normal= 0;
  
  float4 i;
  
  i = IN.Indices;
  
  pos  = mul(Bones[i.x], tempPos) * IN.Weight.x;
  pos += mul(Bones[i.y], tempPos) * IN.Weight.y;
  pos += mul(Bones[i.z], tempPos) * IN.Weight.z;
  pos += mul(Bones[i.w], tempPos) * IN.Weight.w;
  
  float3x3 m;
  
  m[0].xyz = Bones[i.x][0].xyz;
  m[1].xyz = Bones[i.x][1].xyz;
  m[2].xyz = Bones[i.x][2].xyz;
     
  normal += mul(m, IN.Normal)* IN.Weight.x;
  
  
  m[0].xyz = Bones[i.y][0].xyz;
  m[1].xyz = Bones[i.y][1].xyz;
  m[2].xyz = Bones[i.y][2].xyz;
     
  normal += normalize(mul(m, IN.Normal)* IN.Weight.y);    
  
  normal = normalize(normal);
  
  OUT.Color.xyzw = (max(dot(normal, LightVec),0).xxxx+Ambient)*Diffuse;
  
  OUT.TexCoord.xy = IN.TexCoord.xy;
  
  float4 tempPos2;
  
  tempPos2.xyz = pos.xyz;
  tempPos2.w = 1.0;
  
  OUT.HPosition = mul(WorldViewProj, tempPos2);
  
  return OUT;
}
*/


char vertexShaderStr[] =
"    vs_1_1\n"\
"    def c94, 3, 1, 0, 0\n"\
"    dcl_position v0\n"\
"    dcl_blendweight v1\n"\
"    dcl_blendindices v2\n"\
"    dcl_normal v3\n"\
"    dcl_texcoord v4\n"\
"    mul r5, v2, c94.x\n"\
"    mov a0.x, r5.y\n"\
"    dp3 r1.x, c7[a0.x], v3\n"\
"    dp3 r1.y, c8[a0.x], v3\n"\
"    dp3 r1.z, c9[a0.x], v3\n"\
"    mul r1.xyz, r1, v1.y\n"\
"    dp3 r2.x, r1, r1\n"\
"    rsq r1.w, r2.x\n"\
"    mul r2.xyz, r1, r1.w\n"\
"    mov a0.x, r5.x\n"\
"    dp3 r1.x, c7[a0.x], v3\n"\
"    dp3 r1.y, c8[a0.x], v3\n"\
"    dp3 r1.z, c9[a0.x], v3\n"\
"    mad r1.xyz, r1, v1.x, r2\n"\
"    dp3 r2.x, r1, r1\n"\
"    rsq r1.w, r2.x\n"\
"    mul r1.xyz, r1, r1.w\n"\
"    dp3 r1.x, r1, c4\n"\
"    max r1.w, r1.x, c94.z\n"\
"    mov r2.xyz, v0\n"\
"    mov r2.w, c94.y\n"\
"    add r1, r1.w, c6\n"\
"    mov a0.x, r5.y\n"\
"    dp4 r3.x, c7[a0.x], r2\n"\
"    dp4 r3.y, c8[a0.x], r2\n"\
"    dp4 r3.z, c9[a0.x], r2\n"\
"    mul r4.xyz, r3, v1.y\n"\
"    mov a0.x, r5.x\n"\
"    dp4 r3.x, c7[a0.x], r2\n"\
"    dp4 r3.y, c8[a0.x], r2\n"\
"    dp4 r3.z, c9[a0.x], r2\n"\
"    mad r3.xyz, r3, v1.x, r4\n"\
"    mov a0.x, r5.z\n"\
"    dp4 r0.x, c7[a0.x], r2\n"\
"    dp4 r0.y, c8[a0.x], r2\n"\
"    dp4 r0.z, c9[a0.x], r2\n"\
"    mad r3.xyz, r0, v1.z, r3\n"\
"    mov a0.x, r5.w\n"\
"    dp4 r0.x, c7[a0.x], r2\n"\
"    dp4 r0.y, c8[a0.x], r2\n"\
"    dp4 r0.z, c9[a0.x], r2\n"\
"    mad r0.xyz, r0, v1.w, r3\n"\
"    mov r0.w, c94.y\n"\
"    mul oD0, r1, c5\n"\
"    dp4 oPos.x, c0, r0\n"\
"    dp4 oPos.y, c1, r0\n"\
"    dp4 oPos.z, c2, r0\n"\
"    dp4 oPos.w, c3, r0\n"\
"    mov oT0.xy, v4\n";



struct VERTEX2 //Use for the cursor
{
    D3DXVECTOR3    pos;
  DWORD     d;
};

#define D3DFVF_VERTEX2 (D3DFVF_XYZ|D3DFVF_DIFFUSE)


//----------------------------------------------------------------------------//
// Constructors                                                               //
//----------------------------------------------------------------------------//
Viewer::Viewer()
{
  m_calCoreModel = new CalCoreModel("dummy");
  m_lastTick = 0;
  m_scale = 1.0f;
  m_blendTime = 0.3f;
  m_lodLevel = 1.0f;
  m_pVB=NULL;
  m_pIB=NULL;
}


//----------------------------------------------------------------------------//
// Destructor                                                                 //
//----------------------------------------------------------------------------//
Viewer::~Viewer()
{
}

//----------------------------------------------------------------------------//
// Create the viewer                                                          //
//----------------------------------------------------------------------------//
bool Viewer::onCreate(LPSTR lpCmdLine)
{
  // parse the model configuration file
  if (!parseModelConfiguration(lpCmdLine))
  {
    LOG_ERROR << "No model configuration file given." << ENDLOG;
    return false;
  }

  for (int materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
  {
    // create the a material thread
    m_calCoreModel->createCoreMaterialThread(materialId);

    // initialize the material thread
    m_calCoreModel->setCoreMaterialId(materialId, 0, materialId);
  }

  m_calModel = new CalModel(m_calCoreModel);
  return true;
}


//----------------------------------------------------------------------------//
// Init the viewer                                                            //
//----------------------------------------------------------------------------//
bool Viewer::onInit()
{
  // load all textures and store the D3D texture object id in the corresponding map in the material
  for (int materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
  {
    // get the core material
    CalCoreMaterial *pCoreMaterial;
    pCoreMaterial = m_calCoreModel->getCoreMaterial(materialId);

    // loop through all maps of the core material
    for (int mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
    {
      // get the filename of the texture
      std::string strFilename;
      strFilename = pCoreMaterial->getMapFilename(mapId);

      // load the texture from the file
      FileHandle handle = Application.GetTextureDatabase()->FindFileHandle(strFilename);
      Texture *pTexture = TextureLoader::LoadTexture(handle);
      if (!pTexture)
      {
        LOG_ERROR << "Failed to load the texture: " << strFilename << ENDLOG;
        return false;
      }
      SafeRef(pTexture);

      // store the d3d texture id in the user data of the map
      pCoreMaterial->setMapUserData(mapId, (Cal::UserData)pTexture);
    }
  }

  // attach all meshes to the model
  for (int meshId = 0; meshId < m_calCoreModel->getCoreMeshCount(); meshId++)
  {
    m_calModel->attachMesh(meshId);
  }

  // set the material set of the whole model
  m_calModel->setMaterialSet(0);

  // set initial animation state
  m_currentAnimationId = 0;
  m_leftAnimationTime = m_calCoreModel->getCoreAnimation(m_currentAnimationId)->getDuration() - m_blendTime;
  if (m_calCoreModel->getCoreAnimationCount() > 1)
  {
    m_calModel->getMixer()->executeAction(m_currentAnimationId, 0.0f, m_blendTime);
  }
  else
  {
    m_calModel->getMixer()->blendCycle(m_currentAnimationId, 1.0f, 0.0f);
  }

  m_calModel->disableInternalData();

  // we're done
  LOG_INFO << "Initialization done." << ENDLOG;
  LOG_INFO << "Quit the viewer by pressing 'q' or ESC" << ENDLOG;

  m_lastTick = GetTickCount();

  if(!loadVertexBuffer())
    return false;

  if(!loadVertexShader())
    return false;

  return true;
}



//----------------------------------------------------------------------------//
// Handle an idle event                                                       //
//----------------------------------------------------------------------------//

void Viewer::onIdle()
{
  // get the current tick value
  unsigned int tick;
  tick = GetTickCount();

  // calculate the amount of elapsed seconds
  float elapsedSeconds;
  elapsedSeconds = (float)(tick - m_lastTick) / 1000.0f;

  // check if the time has come to blend to the next animation
  if(m_calCoreModel->getCoreAnimationCount() > 1)
  {
    m_leftAnimationTime -= elapsedSeconds;
    if(m_leftAnimationTime <= m_blendTime)
    {
      // get the next animation
      m_currentAnimationId = (m_currentAnimationId + 1) % m_calCoreModel->getCoreAnimationCount();

      // fade in the new animation
      m_calModel->getMixer()->executeAction(m_currentAnimationId, m_leftAnimationTime, m_blendTime);

      // adjust the animation time left until next animation flip
      m_leftAnimationTime = m_calCoreModel->getCoreAnimation(m_currentAnimationId)->getDuration() - m_blendTime;
    }
  }

  m_calModel->update(elapsedSeconds);

  // current tick will be last tick next round
  m_lastTick = tick;
}


bool Viewer::loadVertexBuffer()
{
  // Create vertex buffer
  Device->CreateVertexBuffer(30000*sizeof(VERTEX),
    D3DUSAGE_WRITEONLY, 0, 
    D3DPOOL_DEFAULT , &m_pVB, NULL
    );  

  // Create index buffer
  if(sizeof(CalIndex)==2)
  {
    Device->CreateIndexBuffer(50000*3*sizeof(CalIndex),
      D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,
      D3DPOOL_DEFAULT ,&m_pIB, NULL);
  }
  else
  {
    Device->CreateIndexBuffer(50000*3*sizeof(CalIndex),
      D3DUSAGE_WRITEONLY,D3DFMT_INDEX32,
      D3DPOOL_DEFAULT ,&m_pIB, NULL);
  }

  VERTEX* pVertex;
  CalIndex *pFace;

  m_calHardwareModel = new CalHardwareModel(m_calCoreModel);
  m_pVB->Lock(0, 0, (void**)&pVertex, D3DLOCK_DISCARD);
  m_pIB->Lock(0, 0, (void**)&pFace, D3DLOCK_DISCARD);

  m_calHardwareModel->setVertexBuffer((char*)pVertex,sizeof(VERTEX));
  m_calHardwareModel->setWeightBuffer(((char*)pVertex) + 12 ,sizeof(VERTEX));
  m_calHardwareModel->setMatrixIndexBuffer(((char*)pVertex) + 28 ,sizeof(VERTEX));  
  m_calHardwareModel->setNormalBuffer(((char*)pVertex)+44,sizeof(VERTEX));
  m_calHardwareModel->setTextureCoordNum(1);
  m_calHardwareModel->setTextureCoordBuffer(0,((char*)pVertex)+56,sizeof(VERTEX));
  m_calHardwareModel->setIndexBuffer(pFace);

  m_calHardwareModel->load( 0, 0, MAXBONESPERMESH);  

  m_pVB->Unlock();
  m_pIB->Unlock();
  return true;
}

bool Viewer::loadVertexShader()
{
  LPD3DXBUFFER pCode;
  LPD3DXBUFFER pError;

  D3DVERTEXELEMENT9 decl[] = 
  {
    { 0, 0 ,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
    { 0, 12,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
    { 0, 28,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
    { 0, 44,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
    { 0, 56,  D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
    D3DDECL_END()
  };


  Device->CreateVertexDeclaration( decl, &m_pVertexDeclaration );

  if(FAILED(D3DXAssembleShader(vertexShaderStr,sizeof(vertexShaderStr),NULL, NULL, 0,  
    &pCode, &pError)))
  {
    LOG_INFO << "Error while assembling default vertex shader:\n " << (char *)pError->GetBufferPointer();
    pError->Release();
    return false;    
  }   


  if(FAILED(Device->CreateVertexShader((DWORD*)pCode->GetBufferPointer(),
    &m_pVS)))
  {
    pCode->Release();
    return false;
  }
  pCode->Release();  
  return true;
}


//----------------------------------------------------------------------------//
// Render the current scene                                                   //
//----------------------------------------------------------------------------//

void Viewer::onRender()
{
  D3DXMATRIX matProj;
  D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, Application.CalculateAspectRatio(), m_scale * 50.0f, m_scale * 1000.0f );
  Device->SetTransform( D3DTS_PROJECTION, &matProj );

  // setup the light attributes
  D3DLIGHT9 light;
  ZeroMemory( &light, sizeof(D3DLIGHT9) );
  light.Type       = D3DLIGHT_DIRECTIONAL;
  light.Ambient.r=0.3f;light.Ambient.g=0.3f;light.Ambient.b=0.3f;light.Ambient.a=1.0f;
  light.Diffuse.r=0.9f;light.Diffuse.g=0.9f;light.Diffuse.b=0.9f;light.Diffuse.a=1.0f;
  light.Specular.r=0.1f;light.Specular.g=0.1f;light.Specular.b=0.1f;light.Specular.a=1.0f;
  light.Direction= D3DXVECTOR3(0.0f,0.70f,0.70f);

  Device->SetLight( 0, &light );
  Device->LightEnable( 0, TRUE );  
  Device->SetRenderState( D3DRS_LIGHTING, TRUE );

  D3DXMATRIX Mat1, Mat2, MatView;
  D3DXMatrixIdentity(&Mat1);
  D3DXMatrixTranslation(&Mat2,0.0f,0.0f,270.0f * m_scale);
  D3DXMatrixMultiply(&Mat1,&Mat2,&Mat1);
  D3DXMatrixRotationX(&Mat2, -110.0f/180.0f*3.14159f);
  D3DXMatrixMultiply(&Mat1,&Mat2,&Mat1);
  D3DXMatrixRotationZ(&Mat2, 135.0f/180.0f*3.14159f);
  D3DXMatrixMultiply(&Mat1,&Mat2,&Mat1);
  D3DXMatrixTranslation(&Mat2,0.0f,0.0f,-90.0f * m_scale);
  D3DXMatrixMultiply(&MatView,&Mat2,&Mat1);
  Device->SetTransform( D3DTS_VIEW, &MatView );

  D3DXMATRIX MatWorld;
  D3DXMatrixIdentity( &MatWorld );
  Device->SetTransform( D3DTS_WORLD, &MatWorld );

  D3DXMATRIX WorldViewProj;
  D3DXMatrixMultiply(&WorldViewProj,&MatView,&matProj);
  D3DXMatrixMultiply(&WorldViewProj,&MatWorld,&WorldViewProj);
  D3DXMatrixTranspose(&WorldViewProj, &WorldViewProj);  

  light.Direction=-((D3DXVECTOR3)light.Direction);
  Device->SetVertexShaderConstantF(  0,(float *)&WorldViewProj, 4 );
  Device->SetVertexShaderConstantF(  4,(float *)&light.Direction, 1 );  
  Device->SetVertexShaderConstantF(  6,(float *)&light.Ambient, 1 );

  // render the model
  renderModel();

}


//----------------------------------------------------------------------------//
// Shut the viewer down                                                       //
//----------------------------------------------------------------------------//

void Viewer::onShutdown()
{
  int materialId;
  for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
  {
    // get the core material
    CalCoreMaterial *pCoreMaterial;
    pCoreMaterial = m_calCoreModel->getCoreMaterial(materialId);

    // loop through all maps of the core material
    int mapId;
    for(mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
    {
      // get the d3d texture id in the user data of the map
      Texture *pTexture = (Texture *) pCoreMaterial->getMapUserData(mapId);
      SafeUnRef(pTexture);
    }
  }

  // destroy
  delete m_calHardwareModel;
  delete m_calModel;
  delete m_calCoreModel;

  if(m_pVB!=NULL)
    m_pVB->Release();  

  if(m_pIB!=NULL)
    m_pIB->Release();
}


//----------------------------------------------------------------------------//
// Parse the configuration file and load the whole model                      //
//----------------------------------------------------------------------------//

bool Viewer::parseModelConfiguration(const std::string& strFilename)
{
  // open the model configuration file
  std::ifstream file;
  file.open(strFilename.c_str(), std::ios::in | std::ios::binary);
  if(!file)
  {
    LOG_INFO << "Failed to open model configuration file '" << strFilename << "'." << ENDLOG;
    return false;
  }

  // parse all lines from the model configuration file
  int line;
  for(line = 1; ; line++)
  {
    // read the next model configuration line
    std::string strBuffer;
    std::getline(file, strBuffer);

    // stop if we reached the end of file
    if(file.eof()) break;

    // check if an error happend while reading from the file
    if(!file)
    {
      LOG_INFO << "Error while reading from the model configuration file '" << strFilename << "'." << ENDLOG;
      return false;
    }

    // find the first non-whitespace character
    std::string::size_type pos;
    pos = strBuffer.find_first_not_of(" \t");

    // check for empty lines
    if((pos == std::string::npos) || (strBuffer[pos] == '\n') || (strBuffer[pos] == '\r') || (strBuffer[pos] == 0)) continue;

    // check for comment lines
    if(strBuffer[pos] == '#') continue;

    // get the key
    std::string strKey;
    strKey = strBuffer.substr(pos, strBuffer.find_first_of(" =\t\n\r", pos) - pos);
    pos += strKey.size();

    // get the '=' character
    pos = strBuffer.find_first_not_of(" \t", pos);
    if((pos == std::string::npos) || (strBuffer[pos] != '='))
    {
      LOG_INFO << strFilename << "(" << line << "): Invalid syntax." << ENDLOG;
      return false;
    }

    // find the first non-whitespace character after the '=' character
    pos = strBuffer.find_first_not_of(" \t", pos + 1);

    // get the data
    std::string strData;
    strData = strBuffer.substr(pos, strBuffer.find_first_of("\n\r", pos) - pos);

    // handle the model creation
    if(strKey == "scale")
    {
      // set rendering scale factor
      m_scale = (float) atof(strData.c_str());
    }
    else if(strKey == "skeleton")
    {
      // load core skeleton
      LOG_INFO << "Loading skeleton '" << strData << "'..." << ENDLOG;
      if(!m_calCoreModel->loadCoreSkeleton(strData))
      {
        CalError::printLastError();
        return false;
      }
    }
    else if(strKey == "animation")
    {
      // load core animation
      LOG_INFO << "Loading animation '" << strData << "'..." << ENDLOG;
      if(m_calCoreModel->loadCoreAnimation(strData) == -1)
      {
        CalError::printLastError();
        return false;
      }
    }
    else if(strKey == "mesh")
    {
      // load core mesh
      LOG_INFO << "Loading mesh '" << strData << "'..." << ENDLOG;
      if(m_calCoreModel->loadCoreMesh(strData) == -1)
      {
        CalError::printLastError();
        return false;
      }
    }
    else if(strKey == "material")
    {
      // load core material
      LOG_INFO << "Loading material '" << strData << "'..." << ENDLOG;
      if(m_calCoreModel->loadCoreMaterial(strData) == -1)
      {
        CalError::printLastError();
        return false;
      }
    }
    else
    {
      // everything else triggers an error message, but is ignored
      LOG_INFO << strFilename << "(" << line << "): Invalid syntax." << ENDLOG;
    }
  }

  // explicitely close the file
  file.close();

  return true;
}

//----------------------------------------------------------------------------//
// Render the model                                                           //
//----------------------------------------------------------------------------//


void Viewer::renderModel()
{
  // get the number of meshes  

  Device->SetVertexShader(m_pVS);
  Device->SetVertexDeclaration( m_pVertexDeclaration );
  Device->SetStreamSource( 0, m_pVB,0, sizeof(VERTEX) );
  Device->SetIndices( m_pIB);

  for (int hardwareMeshId=0;hardwareMeshId<m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
  {
    m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

    D3DMATERIAL9 mat;
    unsigned char meshColor[4];
    m_calHardwareModel->getAmbientColor(&meshColor[0]);
    mat.Ambient.r=meshColor[0]/255.0f;mat.Ambient.g=meshColor[1]/255.0f;
    mat.Ambient.b=meshColor[2]/255.0f;mat.Ambient.a=meshColor[3]/255.0f;

    m_calHardwareModel->getDiffuseColor(&meshColor[0]);
    mat.Diffuse.r=meshColor[0]/255.0f;mat.Diffuse.g=meshColor[1]/255.0f;
    mat.Diffuse.b=meshColor[2]/255.0f;mat.Diffuse.a=meshColor[3]/255.0f;

    m_calHardwareModel->getSpecularColor(&meshColor[0]);
    mat.Specular.r=meshColor[0]/255.0f;mat.Specular.g=meshColor[1]/255.0f;
    mat.Specular.b=meshColor[2]/255.0f;mat.Specular.a=meshColor[3]/255.0f;

    mat.Power=0.0f;
    mat.Emissive.r=0.0f;mat.Emissive.g=0.0f;mat.Emissive.b=0.0f;mat.Emissive.a=0.0f;

    Device->SetVertexShaderConstantF(  5,(float*)&mat.Diffuse , 1 );
    //Device->SetVertexShaderConstantF(  6,(float*)&mat.Ambient , 1 );

    for (int boneId = 0; boneId < m_calHardwareModel->getBoneCount(); boneId++)
    {

      D3DXMATRIX transformation;
      D3DXMatrixRotationQuaternion(&transformation,(CONST D3DXQUATERNION*)&m_calHardwareModel->getRotationBoneSpace(boneId, m_calModel->getSkeleton()));

      CalVector translationBoneSpace = m_calHardwareModel->getTranslationBoneSpace(boneId, m_calModel->getSkeleton());

      transformation._14=translationBoneSpace.x;
      transformation._24=translationBoneSpace.y;
      transformation._34=translationBoneSpace.z;

      Device->SetVertexShaderConstantF(7+boneId*3, (float*)&transformation, 3 );
    }

    Device->SetMaterial(&mat);    
    Device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

    Texture *pTexture = (Texture *) m_calHardwareModel->getMapUserData(0);

    if (pTexture)
      Device->SetTexture(0, pTexture->GetPtr());

    Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
      m_calHardwareModel->getBaseVertexIndex(),0,m_calHardwareModel->getVertexCount(),
      m_calHardwareModel->getStartIndex(),m_calHardwareModel->getFaceCount());

  }

  Device->SetVertexShader(NULL);
  Device->SetVertexDeclaration(NULL);
}







