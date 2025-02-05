xof 0303txt 0032

// DirectX file
// Creator: Ultimate Unwrap3D v2.26
// Time: Mon Mar 27 02:35:08 2006

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
       0.999946, 0.000000, 0.010437, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       -0.010437, 0.000000, 0.999946, 0.000000,
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
       -6.054562; 1.262486; -0.355986;,
       6.094215; 4.391952; 1.345861;,
       6.088199; 4.391952; -0.374896;,
       -6.048553; 1.262486; 1.364761;,
       6.088199; 4.391952; -0.374896;,
       6.094215; -0.144599; 1.345861;,
       6.102282; -0.140537; -1.364200;,
       6.094215; 4.391952; 1.345861;,
       -6.054562; 1.262486; -0.355986;,
       6.102282; -0.140537; -1.364200;,
       -6.094280; -3.270004; -1.339586;,
       6.088199; 4.391952; -0.374896;,
       -6.048553; 1.262486; 1.364761;,
       -6.094280; -3.270004; -1.339586;,
       -6.048553; -3.274065; 1.364761;,
       -6.054562; 1.262486; -0.355986;,
       6.094215; 4.391952; 1.345861;,
       -6.048553; -3.274065; 1.364761;,
       6.094215; -0.144599; 1.345861;,
       -6.048553; 1.262486; 1.364761;;
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
       -0.249566; 0.968357; 0.000872;,
       -0.249566; 0.968357; 0.000872;,
       -0.249566; 0.968357; 0.000872;,
       -0.249566; 0.968357; 0.000872;,
       0.999999; 0.001228; -0.000258;,
       0.999999; 0.001228; -0.000258;,
       0.999993; 0.002456; 0.002980;,
       0.999994; 0.000000; -0.003496;,
       -0.056383; 0.212476; -0.975538;,
       -0.056383; 0.212476; -0.975538;,
       -0.056419; 0.212209; -0.975594;,
       -0.056348; 0.212743; -0.975482;,
       -0.999940; 0.004003; 0.010200;,
       -0.999940; 0.004003; 0.010200;,
       -0.999857; 0.000000; 0.016907;,
       -0.999962; 0.008005; 0.003492;,
       0.001556; 0.000000; 0.999999;,
       0.001556; 0.000000; 0.999999;,
       0.001556; 0.000000; 0.999999;,
       0.001556; 0.000000; 0.999999;;
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
       0.960622; 0.022686;,
       0.838565; 0.824759;,
       0.966288; 0.823856;,
       0.832899; 0.023589;,
       0.773379; 0.630095;,
       0.645335; 0.966827;,
       0.846275; 0.966526;,
       0.645660; 0.630095;,
       0.814650; 0.023765;,
       0.012698; 0.360196;,
       0.815974; 0.360334;,
       0.013481; 0.023765;,
       0.644679; 0.630095;,
       0.845943; 0.966526;,
       0.645004; 0.966827;,
       0.772405; 0.630095;,
       0.012577; 0.023766;,
       0.815633; 0.360359;,
       0.012577; 0.360497;,
       0.813747; 0.023765;;
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
         "walls.jpg";
        }
       }

      }
     }
   }
}
