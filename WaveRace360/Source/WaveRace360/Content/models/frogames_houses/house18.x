xof 0302txt 0032
Header {
 1;
 0;
 1;
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

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
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
Frame napr {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh napr1 {
 6;
18.000000;94.500000;8.500000;,
18.000000;0.000000;8.500000;,
-16.000000;0.000000;37.500000;,
-16.000000;94.500000;37.500000;,
-50.500000;0.000000;8.500000;,
-50.500000;94.500000;8.500000;;

 4;
3;2,1,0;,
3;3,2,0;,
3;4,2,3;,
3;5,4,3;;
MeshMaterialList {
 1;
 4;
  0,
  0,
  0,
  0;;
Material {
 0.800000;0.800000;0.800000;1.000000;;
2.000000;
 0.000000;0.000000;0.000000;;
 0.059608;0.059608;0.059608;;
TextureFilename {
"house18.bmp";
}
 }
}

 MeshNormals {
 6;
0.648947;0.000000;0.760834;,
0.648947;0.000000;0.760834;,
0.275097;0.000000;0.961416;,
-0.268169;0.000000;0.963372;,
-0.643452;0.000000;0.765486;,
-0.643452;0.000000;0.765486;;

 4;
3;2,1,0;,
3;3,2,0;,
3;4,2,3;,
3;5,4,3;;
 }
MeshTextureCoords {
 6;
0.992754;0.376623;,
0.992754;0.376623;,
0.500000;0.000000;,
0.500000;0.000000;,
0.000000;0.376623;,
0.000000;0.376623;;
}
}
 }
Frame nazad {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh nazad1 {
 14;
18.500000;94.500000;-39.500000;,
-50.500000;94.500000;8.500000;,
-50.000000;94.500000;-39.500000;,
18.000000;94.500000;8.500000;,
-16.000000;94.500000;37.500000;,
-16.021776;98.082794;37.746052;,
-16.000000;94.500000;37.500000;,
18.000000;94.500000;8.500000;,
20.535017;98.082794;4.210309;,
-53.346565;98.082794;4.210309;,
-50.500000;94.500000;8.500000;,
-16.021776;98.577919;43.246014;,
20.535017;98.577919;9.710328;,
-53.346565;98.577919;9.710328;;

 11;
3;2,1,0;,
3;1,3,0;,
3;1,4,3;,
3;7,6,5;,
3;8,7,5;,
3;6,10,9;,
3;5,6,9;,
3;8,5,11;,
3;12,8,11;,
3;5,9,13;,
3;11,5,13;;
MeshMaterialList {
 1;
 11;
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
  0;;
Material {
 0.800000;0.800000;0.800000;1.000000;;
2.000000;
 0.000000;0.000000;0.000000;;
 0.059608;0.059608;0.059608;;
TextureFilename {
"house18.bmp";
}
 }
}

 MeshNormals {
 14;
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
-0.143299;0.733215;-0.664726;,
0.266182;-0.117765;-0.956702;,
-0.652773;-0.167073;-0.738900;,
-0.397234;0.809135;-0.433019;,
0.624295;0.312252;-0.716069;,
0.596336;-0.375613;-0.709435;,
-0.027965;0.995583;-0.089625;,
-0.081973;0.992621;-0.089358;,
0.080298;0.992756;-0.089371;;

 11;
3;2,1,0;,
3;1,3,0;,
3;1,4,3;,
3;7,6,5;,
3;8,7,5;,
3;6,10,9;,
3;5,6,9;,
3;8,5,11;,
3;12,8,11;,
3;5,9,13;,
3;11,5,13;;
 }
MeshTextureCoords {
 14;
0.658250;0.805172;,
0.099472;0.436127;,
0.120391;0.799313;,
0.621705;0.418549;,
0.331986;0.211942;,
0.331840;0.210471;,
0.331986;0.211942;,
0.621705;0.418549;,
0.638647;0.444199;,
0.080448;0.461777;,
0.099472;0.436127;,
0.331840;0.177584;,
0.638647;0.411312;,
0.080448;0.428890;;
}
}
 }
Frame levo {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh levo1 {
 14;
18.500000;94.500000;-39.500000;,
18.500000;0.000000;-39.500000;,
18.000000;0.000000;8.500000;,
18.000000;94.500000;8.500000;,
20.535017;98.577919;9.710328;,
20.535017;-3.082840;9.710328;,
-16.021776;-3.082840;43.246014;,
-16.021776;98.577919;43.246014;,
20.535017;98.082794;4.210309;,
18.000000;94.500000;8.500000;,
18.000000;0.000000;8.500000;,
20.535017;-3.577961;4.210309;,
20.535017;98.577919;9.710328;,
20.535017;-3.082840;9.710328;;

 8;
3;2,1,0;,
3;3,2,0;,
3;6,5,4;,
3;7,6,4;,
3;10,9,8;,
3;11,10,8;,
3;11,8,12;,
3;13,11,12;;
MeshMaterialList {
 1;
 8;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
Material {
 0.800000;0.800000;0.800000;1.000000;;
2.000000;
 0.000000;0.000000;0.000000;;
 0.059608;0.059608;0.059608;;
TextureFilename {
"house18.bmp";
}
 }
}

 MeshNormals {
 14;
0.999946;0.000000;0.010416;,
0.999946;0.000000;0.010416;,
0.999946;0.000000;0.010416;,
0.999946;0.000000;0.010416;,
0.676002;0.000000;0.736900;,
0.676002;0.000000;0.736900;,
0.676002;0.000000;0.736900;,
0.676002;0.000000;0.736900;,
-0.578592;0.000000;-0.815617;,
-0.860909;0.000000;-0.508759;,
-0.860909;0.000000;-0.508759;,
0.913067;0.000000;-0.407809;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;;

 8;
3;2,1,0;,
3;3,2,0;,
3;6,5,4;,
3;7,6,4;,
3;10,9,8;,
3;11,10,8;,
3;11,8,12;,
3;13,11,12;;
 }
MeshTextureCoords {
 14;
0.899888;0.778994;,
0.650888;0.788759;,
0.635263;0.405756;,
0.895982;0.501459;,
0.947346;0.488486;,
0.621534;0.396689;,
0.342237;0.180631;,
0.689534;0.301724;,
0.945141;0.508202;,
0.895982;0.501459;,
0.635263;0.405756;,
0.619328;0.437890;,
0.947346;0.488486;,
0.621534;0.396689;;
}
}
 }
Frame desno {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh desno1 {
 14;
-50.500000;94.500000;8.500000;,
-50.500000;0.000000;8.500000;,
-50.000000;0.000000;-39.500000;,
-50.000000;94.500000;-39.500000;,
-16.021776;98.577919;43.246014;,
-16.021776;-3.082840;43.246014;,
-53.346565;-3.082840;9.710328;,
-53.346565;98.577919;9.710328;,
-53.346565;-3.577961;4.210309;,
-50.500000;0.000000;8.500000;,
-50.500000;94.500000;8.500000;,
-53.346565;98.082794;4.210309;,
-53.346565;-3.082840;9.710328;,
-53.346565;98.577919;9.710328;;

 8;
3;2,1,0;,
3;3,2,0;,
3;6,5,4;,
3;7,6,4;,
3;10,9,8;,
3;11,10,8;,
3;11,8,12;,
3;13,11,12;;
MeshMaterialList {
 1;
 8;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
Material {
 0.800000;0.800000;0.800000;1.000000;;
2.000000;
 0.000000;0.000000;0.000000;;
 0.059608;0.059608;0.059608;;
TextureFilename {
"house18.bmp";
}
 }
}

 MeshNormals {
 14;
-0.999946;0.000000;-0.010416;,
-0.999946;0.000000;-0.010416;,
-0.999946;0.000000;-0.010416;,
-0.999946;0.000000;-0.010416;,
-0.668341;0.000000;0.743855;,
-0.668341;0.000000;0.743855;,
-0.668341;0.000000;0.743855;,
-0.668341;0.000000;0.743855;,
0.516183;0.000000;-0.856478;,
0.833234;0.000000;-0.552920;,
0.833234;0.000000;-0.552920;,
-0.903665;0.000000;-0.428239;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;;

 8;
3;2,1,0;,
3;3,2,0;,
3;6,5,4;,
3;7,6,4;,
3;10,9,8;,
3;11,10,8;,
3;11,8,12;,
3;13,11,12;;
 }
MeshTextureCoords {
 14;
0.900417;0.502812;,
0.642083;0.434452;,
0.655755;0.791454;,
0.896511;0.775829;,
0.688399;0.303097;,
0.341978;0.178097;,
0.625181;0.399880;,
0.950118;0.495583;,
0.647858;0.421011;,
0.642083;0.434452;,
0.900417;0.502812;,
0.949356;0.504995;,
0.625181;0.399880;,
0.950118;0.495583;;
}
}
 }
Frame napred {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh napred1 {
 14;
-50.000000;0.000000;-39.500000;,
-50.500000;0.000000;8.500000;,
18.500000;0.000000;-39.500000;,
18.000000;0.000000;8.500000;,
-16.000000;0.000000;37.500000;,
20.535017;-3.577961;4.210309;,
18.000000;0.000000;8.500000;,
-16.000000;0.000000;37.500000;,
-16.021776;-3.577961;37.746052;,
-50.500000;0.000000;8.500000;,
-53.346565;-3.577961;4.210309;,
20.535017;-3.082840;9.710328;,
-16.021776;-3.082840;43.246014;,
-53.346565;-3.082840;9.710328;;

 11;
3;2,1,0;,
3;2,3,1;,
3;3,4,1;,
3;7,6,5;,
3;8,7,5;,
3;9,7,8;,
3;10,9,8;,
3;8,5,11;,
3;12,8,11;,
3;10,8,12;,
3;13,10,12;;
MeshMaterialList {
 1;
 11;
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
  0;;
Material {
 0.800000;0.800000;0.800000;1.000000;;
2.000000;
 0.000000;0.000000;0.000000;;
 0.059608;0.059608;0.059608;;
TextureFilename {
"house18.bmp";
}
 }
}

 MeshNormals {
 14;
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
-0.625037;-0.330815;-0.707029;,
-0.591257;0.412179;-0.693198;,
-0.271174;0.134348;-0.953108;,
0.198564;-0.801183;-0.564516;,
0.648775;0.144090;-0.747214;,
0.261642;-0.920187;-0.291204;,
0.081973;-0.992621;0.089358;,
-0.026284;-0.995628;0.089629;,
-0.080297;-0.992756;0.089370;;

 11;
3;2,1,0;,
3;2,3,1;,
3;3,4,1;,
3;7,6,5;,
3;8,7,5;,
3;9,7,8;,
3;10,9,8;,
3;8,5,11;,
3;12,8,11;,
3;10,8,12;,
3;13,10,12;;
 }
MeshTextureCoords {
 14;
0.114278;0.798286;,
0.102636;0.438492;,
0.652586;0.798286;,
0.625319;0.407242;,
0.335619;0.213466;,
0.617391;0.414421;,
0.625319;0.407242;,
0.335619;0.213466;,
0.335452;0.211822;,
0.102636;0.438492;,
0.078881;0.461296;,
0.617391;0.387436;,
0.335452;0.175071;,
0.073022;0.436264;;
}
}
 }
