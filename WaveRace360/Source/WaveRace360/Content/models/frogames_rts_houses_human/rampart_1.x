xof 0303txt 0032

// DirectX file
// Creator: Ultimate Unwrap3D v2.26
// Time: Mon Mar 27 02:34:57 2006

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
       0.932760, 0.000000, -0.360499, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.360499, 0.000000, 0.932760, 0.000000,
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
       21;
       -1.779633; -0.077464; -2.906969;,
       -1.645894; 6.654757; 1.333549;,
       -1.705770; 6.652939; -1.860994;,
       -1.662311; -0.072387; 1.331180;,
       0.142499; 8.220624; 0.038553;,
       -1.662311; -0.072387; 1.331180;,
       1.526893; 6.654757; 1.333861;,
       -1.645894; 6.654757; 1.333549;,
       1.562629; -0.072387; 1.335286;,
       0.142499; 8.220624; 0.038553;,
       -1.705770; 6.652939; -1.860994;,
       1.556375; 6.652939; -1.861382;,
       1.562629; -0.072387; 1.335286;,
       1.556375; 6.652939; -1.861382;,
       1.526893; 6.654757; 1.333861;,
       1.694918; -0.077464; -2.902543;,
       0.142499; 8.220624; 0.038553;,
       -1.705770; 6.652939; -1.860994;,
       1.694918; -0.077464; -2.902543;,
       -1.779633; -0.077464; -2.906969;,
       1.556375; 6.652939; -1.861382;;
       12;
       3;0, 1, 2;,
       3;0, 3, 1;,
       3;1, 4, 2;,
       3;5, 6, 7;,
       3;5, 8, 6;,
       3;6, 9, 7;,
       3;10, 9, 11;,
       3;12, 13, 14;,
       3;12, 15, 13;,
       3;13, 16, 14;,
       3;17, 18, 19;,
       3;17, 20, 18;;

      MeshNormals {
       21;
       -0.999717; 0.005245; 0.023202;,
       -0.960449; 0.277657; 0.021078;,
       -0.907543; 0.419625; 0.016771;,
       -0.999614; 0.002430; 0.027669;,
       -0.653842; 0.756539; 0.011825;,
       -0.000686; -0.000073; 1.000000;,
       -0.000509; 0.224141; 0.974557;,
       -0.000093; 0.338532; 0.940955;,
       -0.001273; 0.000205; 0.999999;,
       -0.000107; 0.995500; 0.094764;,
       -0.000076; 0.771298; -0.636474;,
       -0.000076; 0.771298; -0.636474;,
       0.999740; 0.010532; 0.020202;,
       0.970012; 0.242492; 0.016572;,
       0.933497; 0.358487; 0.008409;,
       0.999390; 0.015749; 0.031178;,
       0.746492; 0.665363; 0.006509;,
       0.000571; 0.153214; -0.988193;,
       0.000571; 0.153214; -0.988193;,
       0.001259; 0.153553; -0.988140;,
       -0.000118; 0.152874; -0.988246;;
       12;
       3;0, 1, 2;,
       3;0, 3, 1;,
       3;1, 4, 2;,
       3;5, 6, 7;,
       3;5, 8, 6;,
       3;6, 9, 7;,
       3;10, 9, 11;,
       3;12, 13, 14;,
       3;12, 15, 13;,
       3;13, 16, 14;,
       3;17, 18, 19;,
       3;17, 20, 18;;
      }

      MeshTextureCoords {
       21;
       0.624242; 0.968134;,
       0.127299; 0.649035;,
       0.125365; 0.886143;,
       0.626610; 0.653567;,
       0.010235; 0.744234;,
       0.013570; 0.625814;,
       0.515106; 0.383831;,
       0.513031; 0.621959;,
       0.015729; 0.378111;,
       0.691339; 0.513023;,
       0.512993; 0.622968;,
       0.515085; 0.383473;,
       0.626611; 0.653433;,
       0.125363; 0.886344;,
       0.127298; 0.649179;,
       0.624243; 0.967990;,
       0.010235; 0.744234;,
       0.512993; 0.622968;,
       0.015613; 0.378501;,
       0.013451; 0.625878;,
       0.515085; 0.383473;;
      }

      MeshVertexColors {
       21;
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
       19; 1.000000; 1.000000; 1.000000; 1.000000;,
       20; 1.000000; 1.000000; 1.000000; 1.000000;;
      }

      MeshMaterialList {
       1;
       12;
       0,
       0,
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
         "walls.jpg";
        }
       }

      }
     }
   }
}
