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
Frame Body {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh Body1 {
 120;
-47.672997;42.262802;3.587110;,
-54.700909;42.262802;-3.587110;,
-47.672997;42.262802;-3.587110;,
-54.700909;42.262802;3.587110;,
-47.672997;0.000000;3.587110;,
-47.672997;42.262802;-3.587110;,
-47.672997;0.000000;-3.587110;,
-47.672997;42.262802;3.587110;,
-54.700909;42.262802;3.587110;,
-54.700909;0.000000;-3.587110;,
-54.700909;42.262802;-3.587110;,
-54.700909;0.000000;3.587110;,
-47.672997;42.262802;-3.587110;,
-54.700909;0.000000;-3.587110;,
-47.672997;0.000000;-3.587110;,
-54.700909;42.262802;-3.587110;,
-54.700909;42.262802;3.587110;,
-47.672997;0.000000;3.587110;,
-54.700909;0.000000;3.587110;,
-47.672997;42.262802;3.587110;,
-15.922688;42.262802;0.457570;,
-20.235388;42.341896;-2.131279;,
-15.922688;42.341896;-2.131279;,
-20.235388;42.262802;0.457570;,
-15.922688;0.000000;0.457570;,
-15.922688;42.341896;-2.131279;,
-15.922688;0.079069;-2.131279;,
-15.922688;42.262802;0.457570;,
-20.235388;42.262802;0.457570;,
-20.235388;0.079069;-2.131279;,
-20.235388;42.341896;-2.131279;,
-20.235388;0.000000;0.457570;,
-15.922688;42.341896;-2.131279;,
-20.235388;0.079069;-2.131279;,
-15.922688;0.079069;-2.131279;,
-20.235388;42.341896;-2.131279;,
-20.235388;42.262802;0.457570;,
-15.922688;0.000000;0.457570;,
-20.235388;0.000000;0.457570;,
-15.922688;42.262802;0.457570;,
47.716213;32.222298;2.861410;,
47.893215;36.532097;0.272560;,
47.795216;32.220497;0.272560;,
47.814114;36.533897;2.861410;,
-47.829311;33.181900;2.861410;,
47.795216;32.220497;0.272560;,
-47.750263;33.180099;0.272560;,
47.716213;32.222298;2.861410;,
47.814114;36.533897;2.861410;,
-47.652332;37.491798;0.272560;,
47.893215;36.532097;0.272560;,
-47.731380;37.493599;2.861410;,
47.795216;32.220497;0.272560;,
-47.652332;37.491798;0.272560;,
-47.750263;33.180099;0.272560;,
47.893215;36.532097;0.272560;,
47.814114;36.533897;2.861410;,
-47.829311;33.181900;2.861410;,
-47.731380;37.493599;2.861410;,
47.716213;32.222298;2.861410;,
47.716213;11.104649;2.861410;,
47.893215;15.414489;0.272560;,
47.795216;11.102859;0.272560;,
47.814114;15.416288;2.861410;,
-47.829311;12.064329;2.861410;,
47.795216;11.102859;0.272560;,
-47.750263;12.062538;0.272560;,
47.716213;11.104649;2.861410;,
47.814114;15.416288;2.861410;,
-47.652332;16.374199;0.272560;,
47.893215;15.414489;0.272560;,
-47.731380;16.375999;2.861410;,
47.795216;11.102859;0.272560;,
-47.652332;16.374199;0.272560;,
-47.750263;12.062538;0.272560;,
47.893215;15.414489;0.272560;,
47.814114;15.416288;2.861410;,
-47.829311;12.064329;2.861410;,
-47.731380;16.375999;2.861410;,
47.716213;11.104649;2.861410;,
54.700909;42.262802;3.587110;,
47.672512;42.262802;-3.587110;,
54.700909;42.262802;-3.587110;,
47.672512;42.262802;3.587110;,
54.700909;0.000000;3.587110;,
54.700909;42.262802;-3.587110;,
54.700909;0.000000;-3.587110;,
54.700909;42.262802;3.587110;,
47.672512;42.262802;3.587110;,
47.672512;0.000000;-3.587110;,
47.672512;42.262802;-3.587110;,
47.672512;0.000000;3.587110;,
54.700909;42.262802;-3.587110;,
47.672512;0.000000;-3.587110;,
54.700909;0.000000;-3.587110;,
47.672512;42.262802;-3.587110;,
47.672512;42.262802;3.587110;,
54.700909;0.000000;3.587110;,
47.672512;0.000000;3.587110;,
54.700909;42.262802;3.587110;,
22.162014;42.262802;0.457570;,
17.849316;42.341896;-2.131279;,
22.162014;42.341896;-2.131279;,
17.849316;42.262802;0.457570;,
22.162014;0.000000;0.457570;,
22.162014;42.341896;-2.131279;,
22.162014;0.079069;-2.131279;,
22.162014;42.262802;0.457570;,
17.849316;42.262802;0.457570;,
17.849316;0.079069;-2.131279;,
17.849316;42.341896;-2.131279;,
17.849316;0.000000;0.457570;,
22.162014;42.341896;-2.131279;,
17.849316;0.079069;-2.131279;,
22.162014;0.079069;-2.131279;,
17.849316;42.341896;-2.131279;,
17.849316;42.262802;0.457570;,
22.162014;0.000000;0.457570;,
17.849316;0.000000;0.457570;,
22.162014;42.262802;0.457570;;

 60;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;30,29,28;,
3;29,31,28;,
3;34,33,32;,
3;33,35,32;,
3;38,37,36;,
3;37,39,36;,
3;42,41,40;,
3;41,43,40;,
3;46,45,44;,
3;45,47,44;,
3;50,49,48;,
3;49,51,48;,
3;54,53,52;,
3;53,55,52;,
3;58,57,56;,
3;57,59,56;,
3;62,61,60;,
3;61,63,60;,
3;66,65,64;,
3;65,67,64;,
3;70,69,68;,
3;69,71,68;,
3;74,73,72;,
3;73,75,72;,
3;78,77,76;,
3;77,79,76;,
3;82,81,80;,
3;81,83,80;,
3;86,85,84;,
3;85,87,84;,
3;90,89,88;,
3;89,91,88;,
3;94,93,92;,
3;93,95,92;,
3;98,97,96;,
3;97,99,96;,
3;102,101,100;,
3;101,103,100;,
3;106,105,104;,
3;105,107,104;,
3;110,109,108;,
3;109,111,108;,
3;114,113,112;,
3;113,115,112;,
3;118,117,116;,
3;117,119,116;;
MeshMaterialList {
 1;
 60;
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
  0,
  0,
  0,
  0,
  0;;
Material Material {
 1.000000;1.000000;1.000000;1.000000;;
128.000015;
 1.000000;1.000000;1.000000;;
 0.000000;0.000000;0.000000;;
TextureFilename {
"r_fen2.bmp";
}
 }
}

 MeshNormals {
 120;
0.577350;0.577350;0.577350;,
-0.577350;0.577350;-0.577350;,
0.577350;0.577350;-0.577350;,
-0.577350;0.577350;0.577350;,
0.707107;0.000000;0.707107;,
0.577350;0.577350;-0.577350;,
0.707107;0.000000;-0.707107;,
0.577350;0.577350;0.577350;,
-0.577350;0.577350;0.577350;,
-0.707107;0.000000;-0.707107;,
-0.577350;0.577350;-0.577350;,
-0.707107;0.000000;0.707107;,
0.577350;0.577350;-0.577350;,
-0.707107;0.000000;-0.707107;,
0.707107;0.000000;-0.707107;,
-0.577350;0.577350;-0.577350;,
-0.577350;0.577350;0.577350;,
0.707107;0.000000;0.707107;,
-0.707107;0.000000;0.707107;,
0.577350;0.577350;0.577350;,
0.571562;0.571295;0.589016;,
-0.583319;0.583046;-0.565505;,
0.583319;0.583046;-0.565505;,
-0.571562;0.571295;0.589016;,
0.707107;0.000000;0.707107;,
0.583319;0.583046;-0.565505;,
0.707107;0.000000;-0.707107;,
0.571562;0.571295;0.589016;,
-0.571562;0.571295;0.589016;,
-0.707107;0.000000;-0.707107;,
-0.583319;0.583046;-0.565505;,
-0.707107;0.000000;0.707107;,
0.583319;0.583046;-0.565505;,
-0.707107;0.000000;-0.707107;,
0.707107;0.000000;-0.707107;,
-0.583319;0.583046;-0.565505;,
-0.571562;0.571295;0.589016;,
0.707107;0.000000;0.707107;,
-0.707107;0.000000;0.707107;,
0.571562;0.571295;0.589016;,
0.563005;-0.582031;0.586741;,
0.591236;0.572443;-0.568110;,
0.574640;-0.594059;-0.562923;,
0.579366;0.560950;0.591329;,
-0.007100;-0.706934;0.707244;,
0.574640;-0.594059;-0.562923;,
-0.007103;-0.707209;-0.706969;,
0.563005;-0.582031;0.586741;,
0.579366;0.560950;0.591329;,
0.007101;0.706934;-0.707244;,
0.591236;0.572443;-0.568110;,
0.007104;0.707209;0.706969;,
0.574640;-0.594059;-0.562923;,
0.007101;0.706934;-0.707244;,
-0.007103;-0.707209;-0.706969;,
0.591236;0.572443;-0.568110;,
0.579366;0.560950;0.591329;,
-0.007100;-0.706934;0.707244;,
0.007104;0.707209;0.706969;,
0.563005;-0.582031;0.586741;,
0.563006;-0.582032;0.586739;,
0.591236;0.572443;-0.568110;,
0.574639;-0.594058;-0.562925;,
0.579366;0.560950;0.591329;,
-0.007101;-0.706935;0.707243;,
0.574639;-0.594058;-0.562925;,
-0.007103;-0.707207;-0.706971;,
0.563006;-0.582032;0.586739;,
0.579366;0.560950;0.591329;,
0.007101;0.706934;-0.707244;,
0.591236;0.572443;-0.568110;,
0.007104;0.707209;0.706969;,
0.574639;-0.594058;-0.562925;,
0.007101;0.706934;-0.707244;,
-0.007103;-0.707207;-0.706971;,
0.591236;0.572443;-0.568110;,
0.579366;0.560950;0.591329;,
-0.007101;-0.706935;0.707243;,
0.007104;0.707209;0.706969;,
0.563006;-0.582032;0.586739;,
0.577350;0.577350;0.577350;,
-0.577350;0.577350;-0.577350;,
0.577350;0.577350;-0.577350;,
-0.577350;0.577350;0.577350;,
0.707107;0.000000;0.707107;,
0.577350;0.577350;-0.577350;,
0.707107;0.000000;-0.707107;,
0.577350;0.577350;0.577350;,
-0.577350;0.577350;0.577350;,
-0.707107;0.000000;-0.707107;,
-0.577350;0.577350;-0.577350;,
-0.707107;0.000000;0.707107;,
0.577350;0.577350;-0.577350;,
-0.707107;0.000000;-0.707107;,
0.707107;0.000000;-0.707107;,
-0.577350;0.577350;-0.577350;,
-0.577350;0.577350;0.577350;,
0.707107;0.000000;0.707107;,
-0.707107;0.000000;0.707107;,
0.577350;0.577350;0.577350;,
0.571562;0.571295;0.589016;,
-0.583319;0.583046;-0.565505;,
0.583319;0.583046;-0.565505;,
-0.571562;0.571295;0.589016;,
0.707107;0.000000;0.707107;,
0.583319;0.583046;-0.565505;,
0.707107;0.000000;-0.707107;,
0.571562;0.571295;0.589016;,
-0.571562;0.571295;0.589016;,
-0.707107;0.000000;-0.707107;,
-0.583319;0.583046;-0.565505;,
-0.707107;0.000000;0.707107;,
0.583319;0.583046;-0.565505;,
-0.707107;0.000000;-0.707107;,
0.707107;0.000000;-0.707107;,
-0.583319;0.583046;-0.565505;,
-0.571562;0.571295;0.589016;,
0.707107;0.000000;0.707107;,
-0.707107;0.000000;0.707107;,
0.571562;0.571295;0.589016;;

 60;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;10,9,8;,
3;9,11,8;,
3;14,13,12;,
3;13,15,12;,
3;18,17,16;,
3;17,19,16;,
3;22,21,20;,
3;21,23,20;,
3;26,25,24;,
3;25,27,24;,
3;30,29,28;,
3;29,31,28;,
3;34,33,32;,
3;33,35,32;,
3;38,37,36;,
3;37,39,36;,
3;42,41,40;,
3;41,43,40;,
3;46,45,44;,
3;45,47,44;,
3;50,49,48;,
3;49,51,48;,
3;54,53,52;,
3;53,55,52;,
3;58,57,56;,
3;57,59,56;,
3;62,61,60;,
3;61,63,60;,
3;66,65,64;,
3;65,67,64;,
3;70,69,68;,
3;69,71,68;,
3;74,73,72;,
3;73,75,72;,
3;78,77,76;,
3;77,79,76;,
3;82,81,80;,
3;81,83,80;,
3;86,85,84;,
3;85,87,84;,
3;90,89,88;,
3;89,91,88;,
3;94,93,92;,
3;93,95,92;,
3;98,97,96;,
3;97,99,96;,
3;102,101,100;,
3;101,103,100;,
3;106,105,104;,
3;105,107,104;,
3;110,109,108;,
3;109,111,108;,
3;114,113,112;,
3;113,115,112;,
3;118,117,116;,
3;117,119,116;;
 }
MeshTextureCoords {
 120;
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
1.128100;1.006162;,
-0.126895;0.014807;,
1.128100;0.014807;,
-0.126895;1.006162;,
-0.131798;0.001650;,
1.123200;0.993006;,
-0.131798;0.993006;,
1.123200;0.001650;,
-0.131798;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
-0.131798;0.008711;,
-0.121993;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
-0.121993;0.005152;,
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
1.128100;1.006162;,
-0.126895;0.014807;,
1.128100;0.014807;,
-0.126895;1.006162;,
-0.131798;0.001650;,
1.123200;0.993006;,
-0.131798;0.993006;,
1.123200;0.001650;,
-0.131798;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
-0.131798;0.008711;,
-0.121993;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
-0.121993;0.005152;,
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
1.128100;1.006162;,
-0.126895;0.014807;,
1.128100;0.014807;,
-0.126895;1.006162;,
-0.131798;0.001650;,
1.123200;0.993006;,
-0.131798;0.993006;,
1.123200;0.001650;,
-0.131798;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
-0.131798;0.008711;,
-0.121993;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
-0.121993;0.005152;,
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
1.128100;1.006162;,
-0.126895;0.014807;,
1.128100;0.014807;,
-0.126895;1.006162;,
-0.131798;0.001650;,
1.123200;0.993006;,
-0.131798;0.993006;,
1.123200;0.001650;,
-0.131798;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
-0.131798;0.008711;,
-0.121993;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
-0.121993;0.005152;,
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
1.128100;1.006162;,
-0.126895;0.014807;,
1.128100;0.014807;,
-0.126895;1.006162;,
-0.131798;0.001650;,
1.123200;0.993006;,
-0.131798;0.993006;,
1.123200;0.001650;,
-0.131798;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
-0.131798;0.008711;,
-0.121993;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
-0.121993;0.005152;,
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
1.128100;1.006162;,
-0.126895;0.014807;,
1.128100;0.014807;,
-0.126895;1.006162;,
-0.131798;0.001650;,
1.123200;0.993006;,
-0.131798;0.993006;,
1.123200;0.001650;,
-0.131798;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
-0.131798;0.008711;,
-0.121993;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
-0.121993;0.005152;;
}
}
 }
