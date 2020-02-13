xof 0303txt 0032
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename;
 [...]
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName;
 DWORD nFloats;
 array FLOAT Floats[nFloats];
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName;
 STRING Value;
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName;
 DWORD Value;
}


Frame tree-foliage {
 

 FrameTransformMatrix {
  10.000000,0.000000,0.000000,0.000000,0.000000,10.000000,-0.000000,0.000000,0.000000,0.000000,10.000000,0.000000,0.051281,-0.001729,5.185308,1.000000;;
 }

 Frame {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,2.835009,0.000000,-0.000050,1.000000;;
  }

  Mesh  {
   12;
   -5.000000;-5.000000;0.000000;,
   -5.000000;5.000000;0.000000;,
   -0.670017;5.000000;0.000000;,
   -0.670017;5.000000;0.000000;,
   -0.670017;-5.000000;0.000000;,
   -5.000000;-5.000000;0.000000;,
   -5.000000;5.000000;0.000000;,
   -5.000000;-5.000000;0.000000;,
   -0.670017;5.000000;0.000000;,
   -0.670017;-5.000000;0.000000;,
   -0.670017;5.000000;0.000000;,
   -5.000000;-5.000000;0.000000;;
   4;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;;

   MeshNormals  {
    12;
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;-0.000000;1.000000;,
    0.000000;-0.000000;1.000000;,
    0.000000;-0.000000;1.000000;,
    0.000000;-0.000000;1.000000;,
    0.000000;-0.000000;1.000000;,
    0.000000;-0.000000;1.000000;;
    4;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;;
   }

   MeshMaterialList  {
    1;
    4;
    0,
    0,
    0,
    0;

    Material PDX01_-_Par_d_faut {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "tree_foliage.png";
     }
    }
   }

   MeshTextureCoords  {
    12;
    0.038402;0.918075;,
    0.038402;0.046083;,
    0.421403;0.046083;,
    0.421403;0.046083;,
    0.421403;0.918075;,
    0.038402;0.918075;,
    0.038402;0.046083;,
    0.038402;0.918075;,
    0.421403;0.046083;,
    0.421403;0.918075;,
    0.421403;0.046083;,
    0.038402;0.918075;;
   }
  }
 }
}