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
 92;
-47.672997;42.262802;3.587110;,
-54.700909;42.262802;-3.587110;,
-47.672997;42.262802;-3.587110;,
-54.700909;42.262802;3.587110;,
-46.116791;27.340200;3.587110;,
-47.672997;42.262802;-3.587110;,
-46.116791;27.340200;-3.587110;,
-47.672997;42.262802;3.587110;,
-47.672997;0.000000;-3.587110;,
-47.672997;0.000000;3.587110;,
-53.144699;27.340200;3.587110;,
-54.700909;0.000000;-3.587110;,
-53.144699;27.340200;-3.587110;,
-54.700909;0.000000;3.587110;,
-54.700909;42.262802;-3.587110;,
-54.700909;42.262802;3.587110;,
-46.116791;27.340200;-3.587110;,
-54.700909;0.000000;-3.587110;,
-47.672997;0.000000;-3.587110;,
-53.144699;27.340200;-3.587110;,
-47.672997;42.262802;-3.587110;,
-54.700909;42.262802;-3.587110;,
-53.144699;27.340200;3.587110;,
-47.672997;0.000000;3.587110;,
-54.700909;0.000000;3.587110;,
-46.116791;27.340200;3.587110;,
-54.700909;42.262802;3.587110;,
-47.672997;42.262802;3.587110;,
47.716213;11.104650;2.861410;,
47.893215;15.414491;0.272560;,
47.795216;11.102861;0.272560;,
47.814114;15.416290;2.861410;,
-12.548187;8.397241;2.861410;,
47.795216;11.102861;0.272560;,
-12.469090;8.395441;0.272560;,
47.716213;11.104650;2.861410;,
-47.750263;12.062540;0.272560;,
-47.829311;12.064331;2.861410;,
-12.450188;12.708881;2.861410;,
-47.652332;16.374201;0.272560;,
-12.371189;12.707081;0.272560;,
-47.731380;16.375999;2.861410;,
47.893215;15.414491;0.272560;,
47.814114;15.416290;2.861410;,
-12.469090;8.395441;0.272560;,
-47.652332;16.374201;0.272560;,
-47.750263;12.062540;0.272560;,
-12.371189;12.707081;0.272560;,
47.795216;11.102861;0.272560;,
47.893215;15.414491;0.272560;,
-12.450188;12.708881;2.861410;,
-47.829311;12.064331;2.861410;,
-47.731380;16.375999;2.861410;,
-12.548187;8.397241;2.861410;,
47.814114;15.416290;2.861410;,
47.716213;11.104650;2.861410;,
52.800510;42.262802;3.587110;,
45.772610;42.262802;-3.587110;,
52.800510;42.262802;-3.587110;,
45.772610;42.262802;3.587110;,
54.700909;33.351101;3.587110;,
52.800510;42.262802;-3.587110;,
54.700909;33.351101;-3.587110;,
52.800510;42.262802;3.587110;,
45.772610;42.262802;-3.587110;,
47.672512;33.351101;3.587110;,
47.672512;33.351101;-3.587110;,
45.772610;42.262802;3.587110;,
52.800510;42.262802;-3.587110;,
47.672512;33.351101;-3.587110;,
54.700909;33.351101;-3.587110;,
45.772610;42.262802;-3.587110;,
45.772610;42.262802;3.587110;,
54.700909;33.351101;3.587110;,
47.672512;33.351101;3.587110;,
52.800510;42.262802;3.587110;,
54.700909;16.451302;-3.587110;,
54.700909;16.451302;3.587110;,
53.151409;0.000000;-3.587110;,
53.151409;0.000000;3.587110;,
47.672512;16.451302;3.587110;,
47.672512;0.000000;-3.587110;,
47.672512;16.451302;-3.587110;,
46.123508;0.000000;3.587110;,
54.700909;16.451302;-3.587110;,
47.672512;0.000000;-3.587110;,
53.151409;0.000000;-3.587110;,
47.672512;16.451302;-3.587110;,
47.672512;16.451302;3.587110;,
53.151409;0.000000;3.587110;,
46.123508;0.000000;3.587110;,
54.700909;16.451302;3.587110;;

 62;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;6,4,8;,
3;4,9,8;,
3;12,11,10;,
3;11,13,10;,
3;12,10,14;,
3;10,15,14;,
3;18,17,16;,
3;17,19,16;,
3;16,19,20;,
3;19,21,20;,
3;24,23,22;,
3;23,25,22;,
3;22,25,26;,
3;25,27,26;,
3;30,29,28;,
3;29,31,28;,
3;34,33,32;,
3;33,35,32;,
3;34,32,36;,
3;32,37,36;,
3;40,39,38;,
3;39,41,38;,
3;40,38,42;,
3;38,43,42;,
3;46,45,44;,
3;45,47,44;,
3;44,47,48;,
3;47,49,48;,
3;52,51,50;,
3;51,53,50;,
3;50,53,54;,
3;53,55,54;,
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
3;62,60,76;,
3;60,77,76;,
3;76,77,78;,
3;77,79,78;,
3;82,81,80;,
3;81,83,80;,
3;82,80,66;,
3;80,65,66;,
3;86,85,84;,
3;85,87,84;,
3;84,87,70;,
3;87,69,70;,
3;90,89,88;,
3;89,91,88;,
3;88,91,74;,
3;91,73,74;;
MeshMaterialList {
 1;
 62;
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
 92;
0.555356;0.616283;0.558368;,
-0.595183;0.536342;-0.598410;,
0.555356;0.616283;-0.558368;,
-0.595183;0.536342;0.598410;,
0.705767;0.016607;0.708249;,
0.555356;0.616283;-0.558368;,
0.705767;0.016607;-0.708249;,
0.555356;0.616283;0.558368;,
0.705964;-0.040184;-0.707107;,
0.705964;-0.040184;0.707107;,
-0.705767;-0.016607;0.708249;,
-0.705964;0.040184;-0.707107;,
-0.705767;-0.016607;-0.708249;,
-0.705964;0.040184;0.707107;,
-0.595183;0.536342;-0.598410;,
-0.595183;0.536342;0.598410;,
0.705767;0.016607;-0.708249;,
-0.705964;0.040184;-0.707107;,
0.705964;-0.040184;-0.707107;,
-0.705767;-0.016607;-0.708249;,
0.555356;0.616283;-0.558368;,
-0.595183;0.536342;-0.598410;,
-0.705767;-0.016607;0.708249;,
0.705964;-0.040184;0.707107;,
-0.705964;0.040184;0.707107;,
0.705767;0.016607;0.708249;,
-0.595183;0.536342;0.598410;,
0.555356;0.616283;0.558368;,
0.583663;-0.571112;0.577208;,
0.569564;0.582623;-0.579782;,
0.595933;-0.583118;-0.552121;,
0.558349;0.571150;0.601693;,
-0.020714;-0.705898;0.708010;,
0.595933;-0.583118;-0.552121;,
-0.020710;-0.705754;-0.708154;,
0.583663;-0.571112;0.577208;,
-0.073012;-0.702450;-0.707979;,
-0.073192;-0.704185;0.706234;,
0.020710;0.705755;0.708153;,
0.073193;0.704184;-0.706234;,
0.020714;0.705897;-0.708011;,
0.073013;0.702450;0.707978;,
0.569564;0.582623;-0.579782;,
0.558349;0.571150;0.601693;,
-0.020710;-0.705754;-0.708154;,
0.073193;0.704184;-0.706234;,
-0.073012;-0.702450;-0.707979;,
0.020714;0.705897;-0.708011;,
0.595933;-0.583118;-0.552121;,
0.569564;0.582623;-0.579782;,
0.020710;0.705755;0.708153;,
-0.073192;-0.704185;0.706234;,
0.073013;0.702450;0.707978;,
-0.020714;-0.705898;0.708010;,
0.558349;0.571150;0.601693;,
0.583663;-0.571112;0.577208;,
0.529070;0.653789;0.540966;,
-0.608537;0.492477;-0.622213;,
0.529070;0.653789;-0.540966;,
-0.608537;0.492477;0.622213;,
0.701262;0.073940;0.709059;,
0.529070;0.653789;-0.540966;,
0.701262;0.073940;-0.709059;,
0.529070;0.653789;0.540966;,
-0.608537;0.492477;-0.622213;,
-0.701265;-0.073921;0.709058;,
-0.701265;-0.073921;-0.709058;,
-0.608537;0.492477;0.622213;,
0.529070;0.653789;-0.540966;,
-0.701265;-0.073921;-0.709058;,
0.701262;0.073940;-0.709059;,
-0.608537;0.492477;-0.622213;,
-0.608537;0.492477;0.622213;,
0.701262;0.073940;0.709059;,
-0.701265;-0.073921;0.709058;,
0.529070;0.653789;0.540966;,
0.705938;-0.033172;-0.707497;,
0.705938;-0.033172;0.707497;,
0.703991;-0.066307;-0.707107;,
0.703991;-0.066307;0.707107;,
-0.741572;0.000000;0.670873;,
-0.628073;0.000000;-0.778155;,
-0.666639;0.000000;-0.745381;,
-0.778155;0.000000;0.628073;,
0.705938;-0.033172;-0.707497;,
-0.628073;0.000000;-0.778155;,
0.703991;-0.066307;-0.707107;,
-0.666639;0.000000;-0.745381;,
-0.741572;0.000000;0.670873;,
0.703991;-0.066307;0.707107;,
-0.778155;0.000000;0.628073;,
0.705938;-0.033172;0.707497;;

 62;
3;2,1,0;,
3;1,3,0;,
3;6,5,4;,
3;5,7,4;,
3;6,4,8;,
3;4,9,8;,
3;12,11,10;,
3;11,13,10;,
3;12,10,14;,
3;10,15,14;,
3;18,17,16;,
3;17,19,16;,
3;16,19,20;,
3;19,21,20;,
3;24,23,22;,
3;23,25,22;,
3;22,25,26;,
3;25,27,26;,
3;30,29,28;,
3;29,31,28;,
3;34,33,32;,
3;33,35,32;,
3;34,32,36;,
3;32,37,36;,
3;40,39,38;,
3;39,41,38;,
3;40,38,42;,
3;38,43,42;,
3;46,45,44;,
3;45,47,44;,
3;44,47,48;,
3;47,49,48;,
3;52,51,50;,
3;51,53,50;,
3;50,53,54;,
3;53,55,54;,
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
3;62,60,76;,
3;60,77,76;,
3;76,77,78;,
3;77,79,78;,
3;82,81,80;,
3;81,83,80;,
3;82,80,66;,
3;80,65,66;,
3;86,85,84;,
3;85,87,84;,
3;84,87,70;,
3;87,69,70;,
3;90,89,88;,
3;89,91,88;,
3;88,91,74;,
3;91,73,74;;
 }
MeshTextureCoords {
 92;
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
0.316235;1.006162;,
-0.126895;0.014807;,
0.316235;0.014807;,
-0.126895;1.006162;,
1.128100;0.014807;,
1.128100;1.006162;,
0.311332;0.001650;,
1.123200;0.993006;,
0.311332;0.993006;,
1.123200;0.001650;,
-0.131798;0.993006;,
-0.131798;0.001650;,
0.311332;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
0.311332;0.008711;,
-0.131798;0.979849;,
-0.131798;0.008711;,
0.321137;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
0.321137;0.005152;,
-0.121993;0.976289;,
-0.121993;0.005152;,
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
0.664683;1.006162;,
-0.126895;0.014807;,
0.664683;0.014807;,
-0.126895;1.006162;,
1.128100;0.014807;,
1.128100;1.006162;,
0.659781;0.001650;,
1.123200;0.993006;,
0.659781;0.993006;,
1.123200;0.001650;,
-0.131798;0.993006;,
-0.131798;0.001650;,
0.659781;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
0.659781;0.008711;,
-0.131798;0.979849;,
-0.131798;0.008711;,
0.669586;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
0.669586;0.005151;,
-0.121993;0.976289;,
-0.121993;0.005152;,
0.086144;0.015771;,
-0.126895;0.986909;,
-0.126895;0.015771;,
0.086144;0.986909;,
0.137740;1.006162;,
-0.126895;0.014807;,
0.137740;0.014807;,
-0.126895;1.006162;,
-0.131798;0.993006;,
0.132837;0.001650;,
0.132837;0.993006;,
-0.131798;0.001650;,
-0.131798;0.979849;,
0.132837;0.008711;,
0.132837;0.979849;,
-0.131798;0.008711;,
-0.121993;0.976289;,
0.142642;0.005152;,
0.142642;0.976289;,
-0.121993;0.005152;,
0.639582;0.014807;,
0.639582;1.006162;,
1.128100;0.014807;,
1.128100;1.006162;,
0.634680;0.001650;,
1.123200;0.993006;,
0.634680;0.993006;,
1.123200;0.001650;,
0.634680;0.979849;,
1.123200;0.008711;,
1.123200;0.979849;,
0.634680;0.008711;,
0.644485;0.976289;,
1.133010;0.005151;,
1.133010;0.976289;,
0.644485;0.005151;;
}
}
 }
