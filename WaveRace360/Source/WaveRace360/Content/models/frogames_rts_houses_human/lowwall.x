xof 0303txt 0032

// DirectX file
// Creator: Ultimate Unwrap3D v2.26
// Time: Mon Mar 27 02:34:50 2006

// Start of Templates

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}

template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}

// Start of Frames

Frame SceneRoot {
  FrameTransformMatrix {
   1.000000, 0.000000, 0.000000, 0.000000,
   0.000000, 1.000000, 0.000000, 0.000000,
   0.000000, 0.000000, 1.000000, 0.000000,
   0.000000, 0.000000, 0.000000, 1.000000;;
  }

   Frame building2 {
      FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 0.002806, -0.999996, 0.000000,
       0.000000, 0.999996, 0.002806, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
      }

   }

   Frame Body {
      FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
      }

      Mesh staticMesh {
       20;
       -2.860978; -0.065373; -0.436035;,
       2.873761; 0.832408; -0.232810;,
       2.875548; -0.065375; -0.325994;,
       -2.862765; 0.832411; -0.342851;,
       -2.873761; 0.832399; 0.230348;,
       2.873761; 0.832408; -0.232810;,
       -2.862765; 0.832411; -0.342851;,
       2.862765; 0.832397; 0.340390;,
       2.862765; 0.832397; 0.340390;,
       -2.875548; -0.065388; 0.323491;,
       2.860978; -0.065391; 0.433531;,
       -2.873761; 0.832399; 0.230348;,
       -2.875548; -0.065388; 0.323491;,
       -2.862765; 0.832411; -0.342851;,
       -2.860978; -0.065373; -0.436035;,
       -2.873761; 0.832399; 0.230348;,
       2.873761; 0.832408; -0.232810;,
       2.860978; -0.065391; 0.433531;,
       2.875548; -0.065375; -0.325994;,
       2.862765; 0.832397; 0.340390;;
       10;
       3;0, 1, 2;,
       3;0, 3, 1;,
       3;4, 5, 6;,
       3;4, 7, 5;,
       3;8, 9, 10;,
       3;8, 11, 9;,
       3;12, 13, 14;,
       3;12, 15, 13;,
       3;16, 17, 18;,
       3;16, 19, 17;;

      MeshNormals {
       20;
       0.019077; 0.103257; -0.994472;,
       0.019077; 0.103257; -0.994472;,
       0.019077; 0.103257; -0.994472;,
       0.019077; 0.103257; -0.994472;,
       -0.000000; 1.000000; 0.000020;,
       -0.000000; 1.000000; 0.000020;,
       -0.000000; 1.000000; 0.000020;,
       0.000000; 1.000000; 0.000020;,
       -0.019077; 0.103211; 0.994477;,
       -0.019077; 0.103211; 0.994477;,
       -0.019076; 0.103211; 0.994477;,
       -0.019077; 0.103211; 0.994476;,
       -0.999816; 0.000000; -0.019179;,
       -0.999816; 0.000000; -0.019179;,
       -0.999816; 0.000000; -0.019179;,
       -0.999816; 0.000001; -0.019179;,
       0.999816; -0.000000; 0.019179;,
       0.999816; -0.000000; 0.019179;,
       0.999816; -0.000000; 0.019179;,
       0.999816; -0.000001; 0.019179;;
       10;
       3;0, 1, 2;,
       3;0, 3, 1;,
       3;4, 5, 6;,
       3;4, 7, 5;,
       3;8, 9, 10;,
       3;8, 11, 9;,
       3;12, 13, 14;,
       3;12, 15, 13;,
       3;16, 17, 18;,
       3;16, 19, 17;;
      }

      MeshTextureCoords {
       20;
       0.686031; 0.160165;,
       0.104467; 0.069165;,
       0.104467; 0.160165;,
       0.686031; 0.069165;,
       0.686031; 0.068898;,
       0.104467; 0.010788;,
       0.686031; 0.010788;,
       0.104467; 0.068898;,
       0.104467; 0.069165;,
       0.686031; 0.160165;,
       0.104467; 0.160165;,
       0.686031; 0.069165;,
       0.014437; 0.160165;,
       0.081992; 0.069165;,
       0.091437; 0.160165;,
       0.023881; 0.069165;,
       0.081992; 0.069165;,
       0.014437; 0.160165;,
       0.091437; 0.160165;,
       0.023881; 0.069165;;
      }

      MeshVertexColors {
       20;
       0; 1.000000; 1.000000; 1.000000; 1.000000;,
       1; 1.000000; 1.000000; 1.000000; 1.000000;,
       2; 1.000000; 1.000000; 1.000000; 1.000000;,
       3; 1.000000; 1.000000; 1.000000; 1.000000;,
       4; 1.000000; 1.000000; 1.000000; 1.000000;,
       5; 1.000000; 1.000000; 1.000000; 1.000000;,
       6; 1.000000; 1.000000; 1.000000; 1.000000;,
       7; 1.000000; 1.000000; 1.000000; 1.000000;,
       8; 1.000000; 1.000000; 1.000000; 1.000000;,
       9; 1.000000; 1.000000; 1.000000; 1.000000;,
       10; 1.000000; 1.000000; 1.000000; 1.000000;,
       11; 1.000000; 1.000000; 1.000000; 1.000000;,
       12; 1.000000; 1.000000; 1.000000; 1.000000;,
       13; 1.000000; 1.000000; 1.000000; 1.000000;,
       14; 1.000000; 1.000000; 1.000000; 1.000000;,
       15; 1.000000; 1.000000; 1.000000; 1.000000;,
       16; 1.000000; 1.000000; 1.000000; 1.000000;,
       17; 1.000000; 1.000000; 1.000000; 1.000000;,
       18; 1.000000; 1.000000; 1.000000; 1.000000;,
       19; 1.000000; 1.000000; 1.000000; 1.000000;;
      }

      MeshMaterialList {
       1;
       10;
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0;

       Material {
        1.000000; 1.000000; 1.000000; 1.000000;;
        128.000000;
        0.000000; 0.000000; 0.000000;;
        0.000000; 0.000000; 0.000000;;

        TextureFilename {
         "humans1.jpg";
        }
       }

      }
     }
   }
}
