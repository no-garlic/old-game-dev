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
Frame SceneRoot {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Frame Bone {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,-13.471828,-0.602991,1.000000;;
 }
 }
Mesh Body {
 124;
38.985401;104.755997;-11.919000;,
0.711479;104.755997;-40.760502;,
0.000000;79.237602;0.000000;,
23.382799;104.755997;33.394100;,
-24.534000;104.755997;32.557800;,
-38.545700;104.755997;-13.272300;,
38.985401;104.755997;-11.919000;,
0.000000;79.237602;0.000000;,
0.711479;104.755997;-40.760502;,
23.382799;104.755997;33.394100;,
-24.534000;104.755997;32.557800;,
-38.545700;104.755997;-13.272300;,
38.335098;89.186996;-11.718100;,
-38.337799;9.010720;11.723100;,
-38.337799;89.186996;11.723100;,
38.335098;9.010720;-11.718100;,
-38.337799;89.186996;11.723100;,
38.335098;9.010720;-11.718100;,
38.335098;89.186996;-11.718100;,
-38.337799;9.010720;11.723100;,
-11.722000;89.186996;-38.334000;,
11.719300;9.010720;38.339001;,
11.719300;89.186996;38.339001;,
-11.722000;9.010720;-38.334000;,
11.719300;89.186996;38.339001;,
-11.722000;9.010720;-38.334000;,
-11.722000;89.186996;-38.334000;,
11.719300;9.010720;38.339001;,
73.866096;51.446899;-35.489601;,
-19.859600;56.367100;-45.329300;,
31.940901;54.122200;-87.334503;,
22.065599;53.691799;6.515570;,
31.940901;54.122200;-87.334503;,
22.065599;53.691799;6.515570;,
73.866096;51.446999;-35.489601;,
-19.859600;56.367100;-45.329300;,
51.189400;19.465799;-61.745201;,
2.817080;88.348297;-19.073700;,
54.617599;86.103401;-61.078899;,
-0.611092;21.710600;-19.740101;,
54.617599;86.103401;-61.078899;,
-0.611092;21.710600;-19.740101;,
51.189499;19.465799;-61.745201;,
2.817080;88.348297;-19.073700;,
-72.047699;40.885300;46.900902;,
18.046600;53.124001;21.627100;,
-13.785900;42.877102;79.371902;,
-40.215199;51.132198;-10.843900;,
-13.785900;42.877102;79.371902;,
-40.215199;51.132198;-10.843900;,
-72.047699;40.885300;46.901001;,
18.046600;53.124001;21.627100;,
-39.561798;8.927400;59.138199;,
-14.439200;85.081902;9.389900;,
-46.271702;74.834900;67.134697;,
-7.729310;19.174400;1.393370;,
-46.271702;74.834900;67.134697;,
-7.729310;19.174400;1.393370;,
-39.561798;8.927400;59.138199;,
-14.439200;85.081902;9.389900;,
61.671001;41.998299;69.330704;,
-20.866100;41.998299;23.579599;,
-2.473100;41.998299;87.723701;,
43.278000;41.998299;5.186560;,
-2.473100;41.998299;87.723701;,
43.278000;41.998299;5.186560;,
61.671001;41.998299;69.330704;,
-20.866100;41.998299;23.579599;,
29.599001;75.362900;78.527199;,
11.205900;8.633790;14.383100;,
29.599001;8.633790;78.527199;,
11.205900;75.362900;14.383100;,
29.599001;8.633790;78.527199;,
11.205900;75.362900;14.383100;,
29.599001;75.362900;78.527199;,
11.205900;8.633790;14.383100;,
-50.168800;88.487701;38.218700;,
16.941299;27.837601;11.323600;,
-45.154999;22.022600;35.051399;,
11.927500;94.302597;14.490900;,
-45.154999;22.022600;35.051399;,
11.927500;94.302597;14.490900;,
-50.168800;88.487701;38.218700;,
16.941299;27.837601;11.323600;,
-59.616901;55.837399;5.491280;,
26.389299;60.487801;44.050900;,
-35.706902;54.672901;67.778702;,
2.479410;61.652401;-18.236500;,
-35.706902;54.672901;67.778801;,
2.479410;61.652401;-18.236500;,
-59.616901;55.837399;5.491290;,
26.389299;60.487801;44.050900;,
28.342699;-20.113300;-31.620001;,
-14.425400;51.716702;12.162200;,
-2.583170;-12.258200;26.986000;,
16.500401;43.861599;-46.443699;,
-2.583180;-12.258200;26.986000;,
16.500401;43.861599;-46.443699;,
28.342699;-20.113300;-31.620001;,
-14.425400;51.716702;12.162200;,
41.845798;-7.550370;11.810700;,
-27.928499;39.153801;-31.268400;,
-16.086300;-24.821100;-16.444700;,
30.003599;56.424500;-3.013060;,
-16.086300;-24.821100;-16.444700;,
30.003599;56.424500;-3.013060;,
41.845798;-7.550380;11.810700;,
-27.928499;39.153801;-31.268400;,
-52.622700;103.946999;-0.000995;,
52.624699;-1.300260;-0.001005;,
52.624699;103.946999;-0.001005;,
-52.622700;-1.300250;-0.000995;,
52.624699;103.946999;-0.001014;,
-52.622700;-1.300250;-0.000995;,
-52.622700;103.946999;-0.001004;,
52.624699;-1.300260;-0.001004;,
0.001005;103.946999;52.622700;,
0.000995;-1.300260;-52.624699;,
0.000995;103.946999;-52.624699;,
0.001005;-1.300250;52.622700;,
0.000986;103.946999;-52.624699;,
0.001005;-1.300250;52.622700;,
0.000996;103.946999;52.622700;,
0.000996;-1.300260;-52.624699;;

 66;
3;2,1,0;,
3;2,0,3;,
3;2,3,4;,
3;2,4,5;,
3;2,5,1;,
3;8,7,6;,
3;6,7,9;,
3;9,7,10;,
3;10,7,11;,
3;11,7,8;,
3;14,13,12;,
3;15,12,13;,
3;18,17,16;,
3;19,16,17;,
3;22,21,20;,
3;23,20,21;,
3;26,25,24;,
3;27,24,25;,
3;30,29,28;,
3;31,28,29;,
3;34,33,32;,
3;35,32,33;,
3;38,37,36;,
3;39,36,37;,
3;42,41,40;,
3;43,40,41;,
3;46,45,44;,
3;47,44,45;,
3;50,49,48;,
3;51,48,49;,
3;54,53,52;,
3;55,52,53;,
3;58,57,56;,
3;59,56,57;,
3;62,61,60;,
3;63,60,61;,
3;66,65,64;,
3;67,64,65;,
3;70,69,68;,
3;71,68,69;,
3;74,73,72;,
3;75,72,73;,
3;78,77,76;,
3;79,76,77;,
3;82,81,80;,
3;83,80,81;,
3;86,85,84;,
3;87,84,85;,
3;90,89,88;,
3;91,88,89;,
3;94,93,92;,
3;95,92,93;,
3;98,97,96;,
3;99,96,97;,
3;102,101,100;,
3;103,100,101;,
3;106,105,104;,
3;107,104,105;,
3;110,109,108;,
3;111,108,109;,
3;114,113,112;,
3;115,112,113;,
3;118,117,116;,
3;119,116,117;,
3;122,121,120;,
3;123,120,121;;
MeshMaterialList {
 1;
 66;
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
  0,
  0,
  0,
  0,
  0;;
Material Material {
 1.000000;1.000000;1.000000;1.000000;;
116.686287;
 1.000000;1.000000;1.000000;;
 0.000000;0.000000;0.000000;;
TextureFilename {
"bushflower13.bmp";
}
 }
}
XSkinMeshHeader {
 1;
 3;
 1;
}

  SkinWeights {
   "Bone";
   124;
   0,
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   11,
   12,
   13,
   14,
   15,
   16,
   17,
   18,
   19,
   20,
   21,
   22,
   23,
   24,
   25,
   26,
   27,
   28,
   29,
   30,
   31,
   32,
   33,
   34,
   35,
   36,
   37,
   38,
   39,
   40,
   41,
   42,
   43,
   44,
   45,
   46,
   47,
   48,
   49,
   50,
   51,
   52,
   53,
   54,
   55,
   56,
   57,
   58,
   59,
   60,
   61,
   62,
   63,
   64,
   65,
   66,
   67,
   68,
   69,
   70,
   71,
   72,
   73,
   74,
   75,
   76,
   77,
   78,
   79,
   80,
   81,
   82,
   83,
   84,
   85,
   86,
   87,
   88,
   89,
   90,
   91,
   92,
   93,
   94,
   95,
   96,
   97,
   98,
   99,
   100,
   101,
   102,
   103,
   104,
   105,
   106,
   107,
   108,
   109,
   110,
   111,
   112,
   113,
   114,
   115,
   116,
   117,
   118,
   119,
   120,
   121,
   122,
   123;
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000;
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,13.471828,0.602991,1.000000;;
  }

 MeshNormals {
 124;
0.507401;-0.847632;-0.155128;,
0.009260;-0.847632;-0.530504;,
0.000000;-1.000000;0.000000;,
0.304332;-0.847632;0.434630;,
-0.319313;-0.847632;0.423744;,
-0.501678;-0.847632;-0.172741;,
-0.507401;0.847632;0.155128;,
0.000000;1.000000;0.000000;,
-0.009260;0.847632;0.530504;,
-0.304331;0.847632;-0.434630;,
0.319313;0.847632;-0.423744;,
0.501678;0.847632;0.172741;,
0.292371;0.000000;0.956305;,
0.292371;0.000000;0.956305;,
0.292371;0.000000;0.956305;,
0.292371;0.000000;0.956305;,
-0.292371;0.000000;-0.956305;,
-0.292371;0.000000;-0.956305;,
-0.292371;0.000000;-0.956305;,
-0.292371;0.000000;-0.956305;,
0.956305;0.000000;-0.292372;,
0.956305;0.000000;-0.292372;,
0.956305;0.000000;-0.292372;,
0.956305;0.000000;-0.292372;,
-0.956305;0.000000;0.292372;,
-0.956305;0.000000;0.292372;,
-0.956305;0.000000;0.292372;,
-0.956305;0.000000;0.292372;,
0.051375;0.998630;0.009986;,
0.051375;0.998630;0.009986;,
0.051375;0.998630;0.009986;,
0.051375;0.998630;0.009986;,
-0.051374;-0.998630;-0.009986;,
-0.051374;-0.998630;-0.009986;,
-0.051373;-0.998630;-0.009985;,
-0.051375;-0.998630;-0.009986;,
0.628290;-0.040092;0.776946;,
0.628290;-0.040092;0.776946;,
0.628290;-0.040091;0.776946;,
0.628289;-0.040092;0.776946;,
-0.628289;0.040091;-0.776946;,
-0.628289;0.040091;-0.776946;,
-0.628289;0.040090;-0.776947;,
-0.628290;0.040092;-0.776945;,
-0.100554;0.987688;0.119835;,
-0.100554;0.987688;0.119835;,
-0.100554;0.987688;0.119835;,
-0.100554;0.987688;0.119835;,
0.100554;-0.987689;-0.119835;,
0.100554;-0.987689;-0.119835;,
0.100554;-0.987689;-0.119835;,
0.100554;-0.987688;-0.119835;,
-0.873110;-0.029849;-0.486609;,
-0.873110;-0.029849;-0.486609;,
-0.873110;-0.029850;-0.486609;,
-0.873110;-0.029849;-0.486609;,
0.873110;0.029849;0.486609;,
0.873110;0.029849;0.486609;,
0.873110;0.029850;0.486609;,
0.873110;0.029849;0.486609;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.961262;0.000000;-0.275638;,
0.961262;0.000000;-0.275638;,
0.961262;0.000000;-0.275638;,
0.961262;0.000000;-0.275638;,
-0.961262;0.000000;0.275638;,
-0.961262;0.000000;0.275638;,
-0.961262;0.000000;0.275638;,
-0.961262;0.000000;0.275638;,
0.358313;-0.017452;0.933438;,
0.358313;-0.017452;0.933438;,
0.358313;-0.017452;0.933438;,
0.358313;-0.017452;0.933438;,
-0.358313;0.017452;-0.933438;,
-0.358313;0.017452;-0.933438;,
-0.358313;0.017452;-0.933438;,
-0.358313;0.017452;-0.933438;,
-0.075137;0.996043;0.047465;,
-0.075137;0.996043;0.047465;,
-0.075136;0.996043;0.047464;,
-0.075137;0.996043;0.047466;,
0.075137;-0.996043;-0.047465;,
0.075137;-0.996043;-0.047465;,
0.075138;-0.996043;-0.047464;,
0.075136;-0.996043;-0.047465;,
-0.868168;-0.258820;-0.423434;,
-0.868168;-0.258820;-0.423434;,
-0.868168;-0.258820;-0.423434;,
-0.868168;-0.258820;-0.423434;,
0.868168;0.258820;0.423434;,
0.868168;0.258820;0.423434;,
0.868168;0.258820;0.423434;,
0.868168;0.258819;0.423434;,
0.463453;-0.117716;-0.878268;,
0.463453;-0.117716;-0.878268;,
0.463454;-0.117716;-0.878267;,
0.463453;-0.117717;-0.878268;,
-0.463453;0.117716;0.878268;,
-0.463453;0.117716;0.878268;,
-0.463454;0.117717;0.878267;,
-0.463453;0.117716;0.878268;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;;

 66;
3;2,1,0;,
3;2,0,3;,
3;2,3,4;,
3;2,4,5;,
3;2,5,1;,
3;8,7,6;,
3;6,7,9;,
3;9,7,10;,
3;10,7,11;,
3;11,7,8;,
3;14,13,12;,
3;15,12,13;,
3;18,17,16;,
3;19,16,17;,
3;22,21,20;,
3;23,20,21;,
3;26,25,24;,
3;27,24,25;,
3;30,29,28;,
3;31,28,29;,
3;34,33,32;,
3;35,32,33;,
3;38,37,36;,
3;39,36,37;,
3;42,41,40;,
3;43,40,41;,
3;46,45,44;,
3;47,44,45;,
3;50,49,48;,
3;51,48,49;,
3;54,53,52;,
3;55,52,53;,
3;58,57,56;,
3;59,56,57;,
3;62,61,60;,
3;63,60,61;,
3;66,65,64;,
3;67,64,65;,
3;70,69,68;,
3;71,68,69;,
3;74,73,72;,
3;75,72,73;,
3;78,77,76;,
3;79,76,77;,
3;82,81,80;,
3;83,80,81;,
3;86,85,84;,
3;87,84,85;,
3;90,89,88;,
3;91,88,89;,
3;94,93,92;,
3;95,92,93;,
3;98,97,96;,
3;99,96,97;,
3;102,101,100;,
3;103,100,101;,
3;106,105,104;,
3;107,104,105;,
3;110,109,108;,
3;111,108,109;,
3;114,113,112;,
3;115,112,113;,
3;118,117,116;,
3;119,116,117;,
3;122,121,120;,
3;123,120,121;;
 }
MeshTextureCoords {
 124;
1.000410;1.000140;,
1.000430;0.500155;,
0.758746;0.743208;,
0.500443;1.000100;,
0.500444;0.765669;,
0.500400;0.500161;,
1.000410;1.000140;,
0.758746;0.743208;,
1.000430;0.500155;,
0.500443;1.000100;,
0.500444;0.765669;,
0.500400;0.500161;,
1.000020;0.501310;,
0.499999;1.001310;,
0.499997;0.501329;,
1.000010;1.001310;,
0.499995;0.501324;,
1.000010;1.001300;,
1.000020;0.501320;,
0.499998;1.001310;,
1.000020;0.501310;,
0.499999;1.001310;,
0.499997;0.501329;,
1.000010;1.001310;,
0.499995;0.501324;,
1.000010;1.001300;,
1.000020;0.501320;,
0.499998;1.001310;,
1.000020;0.501310;,
0.499999;1.001310;,
0.499997;0.501329;,
1.000010;1.001310;,
0.499995;0.501324;,
1.000010;1.001300;,
1.000020;0.501320;,
0.499998;1.001310;,
1.000020;0.501310;,
0.499999;1.001310;,
0.499997;0.501329;,
1.000010;1.001310;,
0.499995;0.501324;,
1.000010;1.001300;,
1.000020;0.501320;,
0.499998;1.001310;,
1.000020;0.501310;,
0.499999;1.001310;,
0.499997;0.501329;,
1.000010;1.001310;,
0.499995;0.501324;,
1.000010;1.001300;,
1.000020;0.501320;,
0.499998;1.001310;,
1.000020;0.501310;,
0.499999;1.001310;,
0.499997;0.501329;,
1.000010;1.001310;,
0.499995;0.501324;,
1.000010;1.001300;,
1.000020;0.501320;,
0.499998;1.001310;,
1.000020;0.000000;,
0.499999;0.500001;,
0.499997;0.000020;,
1.000010;0.499996;,
0.499995;0.000014;,
1.000010;0.499991;,
1.000020;0.000010;,
0.499998;0.499999;,
1.000020;0.000000;,
0.499999;0.500001;,
0.499997;0.000020;,
1.000010;0.499996;,
0.499995;0.000014;,
1.000010;0.499991;,
1.000020;0.000010;,
0.499998;0.499999;,
1.000020;0.000000;,
0.499999;0.500001;,
0.499997;0.000020;,
1.000010;0.499996;,
0.499995;0.000014;,
1.000010;0.499991;,
1.000020;0.000010;,
0.499998;0.499999;,
1.000020;0.000000;,
0.499999;0.500001;,
0.499997;0.000020;,
1.000010;0.499996;,
0.499995;0.000014;,
1.000010;0.499991;,
1.000020;0.000010;,
0.499998;0.499999;,
1.000020;0.000000;,
0.499999;0.500001;,
0.499997;0.000020;,
1.000010;0.499996;,
0.499995;0.000014;,
1.000010;0.499991;,
1.000020;0.000010;,
0.499998;0.499999;,
1.000020;0.000000;,
0.499999;0.500001;,
0.499997;0.000020;,
1.000010;0.499996;,
0.499995;0.000014;,
1.000010;0.499991;,
1.000020;0.000010;,
0.499998;0.499999;,
0.500102;0.000213;,
-0.000083;0.499949;,
0.000192;0.000000;,
0.500040;0.499934;,
0.000028;0.000206;,
0.500205;0.499949;,
0.499937;0.000000;,
0.000082;0.499927;,
0.500102;0.000213;,
-0.000083;0.499949;,
0.000192;0.000000;,
0.500040;0.499934;,
0.000028;0.000206;,
0.500205;0.499949;,
0.499937;0.000000;,
0.000082;0.499927;;
}
}
 }
AnimationSet {
 Animation {
  {Bone}
  AnimationKey {
  0;
  4;
  0; 4; 1.000000, 0.000000, 0.000000, 0.000000;;,
  1; 4; 1.000000, 0.000000, 0.000000, 0.000000;;,
  45; 4; 0.999848, 0.000000, 0.000000, 0.017452;;,
  90; 4; 1.000000, 0.000000, 0.000000, 0.000000;;;
   }
  AnimationKey {
  1;
  4;
  0; 3; 1.000000, 1.000000, 1.000000;;,
  1; 3; 1.000000, 1.000000, 1.000000;;,
  45; 3; 1.000000, 1.000000, 1.000000;;,
  90; 3; 1.000000, 1.000000, 1.000000;;;
   }
  AnimationKey {
  2;
  4;
  0; 3; 0.000000, -13.471828, -0.602991;;,
  1; 3; 0.000000, -13.471828, -0.602991;;,
  45; 3; 0.000000, -13.471828, -0.602991;;,
  90; 3; 0.000000, -13.471828, -0.602991;;;
   }
      AnimationOptions {
            0; 0;
      }
  }
 }
