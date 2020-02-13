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
0.000000,0.044885,0.332833,1.000000;;
 }
 }
Mesh Body {
 236;
-15.208500;45.319199;5.535370;,
6.717240;38.011002;4.586060;,
-1.991720;47.195702;14.965000;,
-6.499490;36.134499;-4.843570;,
-1.991720;47.195702;14.965000;,
-6.499490;36.134499;-4.843570;,
-15.208500;45.319199;5.535370;,
6.717240;38.011002;4.586060;,
14.454700;46.503201;-5.678880;,
-6.322680;36.357800;-5.115460;,
2.018140;45.061699;-16.184099;,
6.113910;37.799400;5.389760;,
2.018130;45.061699;-16.184099;,
6.113910;37.799400;5.389760;,
14.454700;46.503201;-5.678880;,
-6.322680;36.357800;-5.115460;,
-5.254170;18.411900;22.557501;,
1.968940;25.039600;-3.915170;,
-1.401860;34.554901;15.201600;,
-1.883370;8.896600;3.440690;,
-1.401860;34.554901;15.201600;,
-1.883370;8.896600;3.440690;,
-5.254170;18.411900;22.557501;,
1.968940;25.039600;-3.915170;,
-11.508300;26.078800;13.707600;,
8.758260;15.861900;1.899370;,
5.936240;23.827999;17.903900;,
-8.686260;18.112600;-2.296890;,
5.936240;23.827999;17.903900;,
-8.686260;18.112600;-2.296890;,
-11.508300;26.078800;13.707600;,
8.758260;15.861900;1.899370;,
5.004110;23.570299;-21.723000;,
-0.769503;23.923201;5.913320;,
3.574620;37.583302;-10.299200;,
0.659992;9.910280;-5.510470;,
3.574620;37.583302;-10.299200;,
0.659992;9.910280;-5.510470;,
5.004120;23.570400;-21.723000;,
-0.769503;23.923201;5.913320;,
12.419000;27.771099;-11.552100;,
-8.874140;17.553600;-1.683310;,
-5.237260;28.989700;-15.256300;,
8.782120;16.334900;2.020900;,
-5.237260;28.989700;-15.256300;,
8.782120;16.334900;2.020900;,
12.419000;27.771099;-11.552100;,
-8.874140;17.553600;-1.683310;,
4.472490;53.616402;10.748500;,
2.011510;29.150000;3.811250;,
8.659430;39.817600;18.742701;,
-2.175430;42.948700;-4.183000;,
8.659430;39.817600;18.742701;,
-2.175430;42.948700;-4.183000;,
4.472490;53.616402;10.748500;,
2.011510;29.150000;3.811250;,
-1.901200;44.824001;15.912800;,
7.367550;36.309299;-3.638820;,
12.972000;45.302502;8.949000;,
-7.505660;35.830799;3.325020;,
12.972000;45.302502;8.948990;,
-7.505660;35.830799;3.325020;,
-1.901200;44.824001;15.912800;,
7.367550;36.309299;-3.638820;,
-12.308600;38.448601;-16.966600;,
2.947930;43.239700;3.091350;,
-6.650110;52.801701;-11.138300;,
-2.710550;28.886600;-2.736950;,
-6.650100;52.801701;-11.138300;,
-2.710550;28.886600;-2.736950;,
-12.308600;38.448601;-16.966600;,
2.947930;43.239700;3.091350;,
-1.345300;43.464600;-16.628700;,
-6.491400;36.705502;5.012800;,
-14.526800;44.710800;-6.900230;,
6.690140;35.459301;-4.715690;,
-14.526800;44.710800;-6.900230;,
6.690140;35.459301;-4.715690;,
-1.345300;43.464600;-16.628700;,
-6.491400;36.705502;5.012800;,
-11.936900;52.065102;4.038730;,
-3.610110;27.889099;1.621460;,
-19.553801;37.734200;7.424490;,
4.006840;42.220001;-1.764300;,
-19.553801;37.734200;7.424490;,
4.006840;42.220001;-1.764300;,
-11.936900;52.065102;4.038730;,
-3.610110;27.889099;1.621460;,
-16.232000;43.125099;-2.874290;,
3.125650;35.321999;7.646160;,
-10.315500;43.621799;12.538300;,
-2.790800;34.825298;-7.766470;,
-10.315500;43.621799;12.538300;,
-2.790800;34.825298;-7.766470;,
-16.232000;43.125099;-2.874290;,
3.125650;35.321999;7.646160;,
9.421700;49.660198;6.140560;,
-1.609170;34.711300;-8.090110;,
6.403820;49.087002;-10.088000;,
1.408710;35.284500;8.138420;,
6.403820;49.087002;-10.088000;,
1.408710;35.284500;8.138420;,
9.421700;49.660198;6.140560;,
-1.609170;34.711300;-8.090110;,
5.169650;40.598499;-12.523300;,
-8.192100;26.967100;2.642740;,
-11.290300;40.598499;-7.491010;,
8.267850;26.967100;-2.389570;,
-11.290300;40.598499;-7.491010;,
8.267850;26.967100;-2.389570;,
5.169650;40.598499;-12.523300;,
-8.192100;26.967100;2.642740;,
-6.046490;39.833599;12.917400;,
8.337220;27.170300;-2.147770;,
10.685000;40.225700;8.897580;,
-8.394260;26.778200;1.872100;,
10.685000;40.225700;8.897580;,
-8.394260;26.778200;1.872100;,
-6.046490;39.833599;12.917400;,
8.337220;27.170300;-2.147770;,
1.025080;19.574499;17.417299;,
7.258460;8.391200;-6.018740;,
15.752200;20.577499;5.671900;,
-7.468670;7.388200;5.726670;,
15.752200;20.577499;5.671890;,
-7.468670;7.388200;5.726670;,
1.025080;19.574499;17.417299;,
7.258460;8.391200;-6.018740;,
-16.585400;25.063400;-18.913401;,
5.575440;13.522800;5.319700;,
-5.714090;36.599400;-8.621690;,
-5.295850;1.986800;-4.971990;,
-5.714080;36.599400;-8.621690;,
-5.295850;1.986800;-4.971990;,
-16.585400;25.063400;-18.913401;,
5.575440;13.522800;5.319700;,
-0.417003;22.191000;-15.419600;,
-6.710550;8.459380;6.620250;,
-14.019300;23.398899;-2.405250;,
6.891700;7.251450;-6.394090;,
-14.019300;23.398899;-2.405250;,
6.891700;7.251450;-6.394090;,
-0.417005;22.191000;-15.419600;,
-6.710550;8.459380;6.620250;,
-0.843708;43.952599;-12.763800;,
-5.350390;30.439100;6.571640;,
-11.702200;44.886902;0.219844;,
5.508090;29.504801;-6.411970;,
-11.702200;44.886902;0.219848;,
5.508090;29.504801;-6.411970;,
-0.843709;43.952599;-12.763800;,
-5.350390;30.439100;6.571640;,
3.131430;51.183201;4.100830;,
4.295380;24.858200;5.068080;,
11.910700;40.997299;14.472200;,
-4.483890;35.044102;-5.303310;,
11.910700;40.997299;14.472200;,
-4.483890;35.044102;-5.303310;,
3.131440;51.183201;4.100830;,
4.295380;24.858200;5.068080;,
-0.170907;43.499802;13.253600;,
6.431980;30.070999;-5.524250;,
12.852000;43.676998;2.403820;,
-6.590930;29.893900;5.325520;,
12.852000;43.676998;2.403810;,
-6.590930;29.893900;5.325520;,
-0.170906;43.499802;13.253600;,
6.431980;30.070999;-5.524250;,
24.225201;27.333300;4.495970;,
-7.491290;15.366000;-1.847440;,
9.668960;38.538200;0.870477;,
7.064960;4.161110;1.778050;,
9.668960;38.538200;0.870479;,
7.064960;4.161110;1.778050;,
24.225201;27.333300;4.495970;,
-7.491290;15.366000;-1.847440;,
8.998450;25.256300;10.862800;,
1.834180;9.474240;-9.148940;,
12.943500;24.475700;-7.389400;,
-2.110890;10.254900;9.103260;,
12.943500;24.475700;-7.389400;,
-2.110890;10.254900;9.103260;,
8.998460;25.256399;10.862800;,
1.834180;9.474240;-9.148940;,
-10.830500;22.463800;-12.575700;,
-2.251810;9.894940;9.072090;,
-15.667800;22.463800;5.477290;,
2.585470;9.894940;-8.980900;,
-15.667800;22.463800;5.477290;,
2.585470;9.894940;-8.980900;,
-10.830500;22.463800;-12.575700;,
-2.251810;9.894940;9.072090;,
4.538280;49.211700;-5.886510;,
-4.747440;41.352699;-0.075897;,
-4.960980;48.681099;-6.190720;,
4.751810;41.883301;0.228310;,
-4.960980;48.681099;-6.190720;,
4.751810;41.883301;0.228310;,
4.538280;49.211700;-5.886510;,
-4.747440;41.352699;-0.075897;,
-5.822150;46.439602;7.416650;,
4.739530;42.059601;0.292152;,
3.628500;47.269901;8.197580;,
-4.711110;41.229198;-0.488775;,
3.628500;47.269901;8.197580;,
-4.711110;41.229198;-0.488775;,
-5.822150;46.439602;7.416650;,
4.739530;42.059601;0.292152;,
7.397290;46.214600;5.403430;,
0.492970;41.443199;-4.575020;,
8.584340;45.790901;-3.724590;,
-0.694079;41.866901;4.552990;,
8.584340;45.790901;-3.724590;,
-0.694079;41.866901;4.552990;,
7.397290;46.214600;5.403430;,
0.492970;41.443199;-4.575020;,
-3.670050;49.966801;-4.799180;,
-0.403170;41.497501;4.586600;,
-4.580740;49.749001;4.367670;,
0.507524;41.715401;-4.580240;,
-4.580740;49.749001;4.367670;,
0.507524;41.715401;-4.580240;,
-3.670050;49.966801;-4.799180;,
-0.403170;41.497501;4.586600;,
0.247281;41.620399;-0.001000;,
1.000360;0.001005;-0.001000;,
-0.188199;0.001005;0.585159;,
0.061709;41.620399;0.090518;,
0.061709;41.620399;0.090518;,
-0.188199;0.001005;0.585159;,
-0.188199;0.001005;-0.587159;,
0.061709;41.620399;-0.092518;,
0.061709;41.620399;-0.092518;,
-0.188199;0.001005;-0.587159;,
1.000360;0.001005;-0.001000;,
0.247281;41.620399;-0.001000;;

 118;
3;2,1,0;,
3;3,0,1;,
3;6,5,4;,
3;7,4,5;,
3;10,9,8;,
3;11,8,9;,
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
3;123,120,121;,
3;126,125,124;,
3;127,124,125;,
3;130,129,128;,
3;131,128,129;,
3;134,133,132;,
3;135,132,133;,
3;138,137,136;,
3;139,136,137;,
3;142,141,140;,
3;143,140,141;,
3;146,145,144;,
3;147,144,145;,
3;150,149,148;,
3;151,148,149;,
3;154,153,152;,
3;155,152,153;,
3;158,157,156;,
3;159,156,157;,
3;162,161,160;,
3;163,160,161;,
3;166,165,164;,
3;167,164,165;,
3;170,169,168;,
3;171,168,169;,
3;174,173,172;,
3;175,172,173;,
3;178,177,176;,
3;179,176,177;,
3;182,181,180;,
3;183,180,181;,
3;186,185,184;,
3;187,184,185;,
3;190,189,188;,
3;191,188,189;,
3;194,193,192;,
3;195,192,193;,
3;198,197,196;,
3;199,196,197;,
3;202,201,200;,
3;203,200,201;,
3;206,205,204;,
3;207,204,205;,
3;210,209,208;,
3;211,208,209;,
3;214,213,212;,
3;215,212,213;,
3;218,217,216;,
3;219,216,217;,
3;222,221,220;,
3;223,220,221;,
3;226,225,224;,
3;226,224,227;,
3;230,229,228;,
3;230,228,231;,
3;234,233,232;,
3;234,232,235;;
MeshMaterialList {
 1;
 118;
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
"small plant4.bmp";
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
   236;
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
   123,
   124,
   125,
   126,
   127,
   128,
   129,
   130,
   131,
   132,
   133,
   134,
   135,
   136,
   137,
   138,
   139,
   140,
   141,
   142,
   143,
   144,
   145,
   146,
   147,
   148,
   149,
   150,
   151,
   152,
   153,
   154,
   155,
   156,
   157,
   158,
   159,
   160,
   161,
   162,
   163,
   164,
   165,
   166,
   167,
   168,
   169,
   170,
   171,
   172,
   173,
   174,
   175,
   176,
   177,
   178,
   179,
   180,
   181,
   182,
   183,
   184,
   185,
   186,
   187,
   188,
   189,
   190,
   191,
   192,
   193,
   194,
   195,
   196,
   197,
   198,
   199,
   200,
   201,
   202,
   203,
   204,
   205,
   206,
   207,
   208,
   209,
   210,
   211,
   212,
   213,
   214,
   215,
   216,
   217,
   218,
   219,
   220,
   221,
   222,
   223,
   224,
   225,
   226,
   227,
   228,
   229,
   230,
   231,
   232,
   233,
   234,
   235;
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
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.044885,-0.332833,1.000000;;
  }

 MeshNormals {
 236;
0.250939;0.819733;-0.514848;,
0.250939;0.819733;-0.514848;,
0.250939;0.819732;-0.514848;,
0.250939;0.819733;-0.514848;,
-0.250939;-0.819733;0.514848;,
-0.250939;-0.819733;0.514848;,
-0.250938;-0.819733;0.514848;,
-0.250939;-0.819732;0.514848;,
-0.401505;0.842245;0.359746;,
-0.401505;0.842245;0.359746;,
-0.401505;0.842244;0.359749;,
-0.401506;0.842246;0.359743;,
0.401505;-0.842245;-0.359746;,
0.401505;-0.842245;-0.359746;,
0.401502;-0.842246;-0.359746;,
0.401508;-0.842244;-0.359746;,
-0.964705;0.124472;-0.232059;,
-0.964705;0.124472;-0.232059;,
-0.964705;0.124471;-0.232059;,
-0.964705;0.124472;-0.232058;,
0.964705;-0.124472;0.232058;,
0.964705;-0.124472;0.232058;,
0.964705;-0.124472;0.232058;,
0.964705;-0.124472;0.232059;,
0.212207;0.889257;-0.405205;,
0.212207;0.889257;-0.405205;,
0.212209;0.889258;-0.405201;,
0.212204;0.889256;-0.405208;,
-0.212207;-0.889257;0.405205;,
-0.212207;-0.889257;0.405205;,
-0.212210;-0.889255;0.405206;,
-0.212204;-0.889258;0.405203;,
0.976469;-0.067395;0.204859;,
0.976469;-0.067395;0.204859;,
0.976469;-0.067395;0.204859;,
0.976469;-0.067395;0.204859;,
-0.976469;0.067395;-0.204859;,
-0.976469;0.067395;-0.204859;,
-0.976469;0.067395;-0.204859;,
-0.976469;0.067395;-0.204859;,
-0.078821;0.772665;0.629902;,
-0.078821;0.772665;0.629902;,
-0.078822;0.772666;0.629900;,
-0.078819;0.772664;0.629904;,
0.078821;-0.772665;-0.629902;,
0.078821;-0.772665;-0.629902;,
0.078823;-0.772664;-0.629903;,
0.078818;-0.772666;-0.629901;,
0.905261;0.029124;-0.423856;,
0.905261;0.029124;-0.423856;,
0.905261;0.029124;-0.423856;,
0.905262;0.029124;-0.423855;,
-0.905261;-0.029124;0.423856;,
-0.905261;-0.029124;0.423856;,
-0.905261;-0.029125;0.423856;,
-0.905261;-0.029123;0.423856;,
-0.253943;0.836913;-0.484860;,
-0.253943;0.836913;-0.484860;,
-0.253942;0.836914;-0.484860;,
-0.253943;0.836913;-0.484860;,
0.253943;-0.836913;0.484860;,
0.253943;-0.836913;0.484860;,
0.253943;-0.836913;0.484860;,
0.253943;-0.836914;0.484860;,
0.802278;-0.075849;-0.592113;,
0.802278;-0.075849;-0.592113;,
0.802278;-0.075849;-0.592113;,
0.802278;-0.075848;-0.592113;,
-0.802278;0.075849;0.592113;,
-0.802278;0.075849;0.592113;,
-0.802277;0.075849;0.592113;,
-0.802278;0.075849;0.592112;,
0.343096;0.870286;0.353393;,
0.343096;0.870286;0.353393;,
0.343096;0.870286;0.353393;,
0.343096;0.870287;0.353393;,
-0.343096;-0.870286;-0.353393;,
-0.343096;-0.870286;-0.353393;,
-0.343096;-0.870286;-0.353393;,
-0.343096;-0.870286;-0.353393;,
0.358211;0.030073;0.933156;,
0.358211;0.030073;0.933156;,
0.358211;0.030074;0.933156;,
0.358210;0.030073;0.933157;,
-0.358211;-0.030073;-0.933156;,
-0.358211;-0.030073;-0.933156;,
-0.358211;-0.030074;-0.933156;,
-0.358211;-0.030073;-0.933156;,
0.459437;0.864414;-0.204223;,
0.459437;0.864414;-0.204223;,
0.459437;0.864413;-0.204224;,
0.459437;0.864414;-0.204221;,
-0.459437;-0.864414;0.204223;,
-0.459437;-0.864414;0.204223;,
-0.459436;-0.864414;0.204223;,
-0.459438;-0.864413;0.204222;,
-0.856161;0.496910;0.141662;,
-0.856161;0.496910;0.141662;,
-0.856161;0.496910;0.141662;,
-0.856161;0.496910;0.141662;,
0.856161;-0.496910;-0.141662;,
0.856161;-0.496910;-0.141662;,
0.856161;-0.496910;-0.141662;,
0.856161;-0.496910;-0.141662;,
0.230828;0.613745;0.755007;,
0.230828;0.613745;0.755007;,
0.230828;0.613745;0.755007;,
0.230829;0.613744;0.755007;,
-0.230828;-0.613745;-0.755007;,
-0.230828;-0.613745;-0.755007;,
-0.230828;-0.613744;-0.755008;,
-0.230829;-0.613745;-0.755007;,
-0.191218;0.653786;-0.732120;,
-0.191218;0.653786;-0.732120;,
-0.191217;0.653787;-0.732119;,
-0.191219;0.653785;-0.732120;,
0.191218;-0.653786;0.732120;,
0.191218;-0.653786;0.732120;,
0.191217;-0.653785;0.732121;,
0.191219;-0.653787;0.732119;,
-0.434284;0.762603;-0.479410;,
-0.434284;0.762603;-0.479410;,
-0.434284;0.762603;-0.479410;,
-0.434284;0.762603;-0.479410;,
0.434284;-0.762603;0.479410;,
0.434284;-0.762603;0.479410;,
0.434284;-0.762603;0.479410;,
0.434284;-0.762603;0.479410;,
0.721067;-0.064033;-0.689900;,
0.721067;-0.064033;-0.689900;,
0.721067;-0.064033;-0.689900;,
0.721067;-0.064033;-0.689900;,
-0.721067;0.064033;0.689900;,
-0.721067;0.064033;0.689900;,
-0.721067;0.064033;0.689901;,
-0.721067;0.064033;0.689900;,
0.575221;0.610394;0.544554;,
0.575221;0.610394;0.544554;,
0.575220;0.610395;0.544554;,
0.575223;0.610394;0.544554;,
-0.575221;-0.610395;-0.544554;,
-0.575221;-0.610395;-0.544554;,
-0.575221;-0.610394;-0.544555;,
-0.575222;-0.610395;-0.544553;,
0.671033;0.525124;0.523412;,
0.671033;0.525124;0.523412;,
0.671034;0.525123;0.523411;,
0.671033;0.525124;0.523412;,
-0.671033;-0.525124;-0.523411;,
-0.671033;-0.525124;-0.523411;,
-0.671033;-0.525124;-0.523411;,
-0.671033;-0.525123;-0.523412;,
0.768256;0.010451;-0.640057;,
0.768256;0.010451;-0.640057;,
0.768256;0.010451;-0.640058;,
0.768256;0.010451;-0.640057;,
-0.768256;-0.010451;0.640057;,
-0.768256;-0.010451;0.640057;,
-0.768256;-0.010451;0.640057;,
-0.768256;-0.010450;0.640057;,
-0.516971;0.599798;-0.610723;,
-0.516971;0.599798;-0.610723;,
-0.516973;0.599797;-0.610723;,
-0.516969;0.599800;-0.610724;,
0.516971;-0.599798;0.610723;,
0.516971;-0.599798;0.610723;,
0.516972;-0.599800;0.610721;,
0.516970;-0.599796;0.610726;,
-0.211080;0.041771;0.976576;,
-0.211080;0.041771;0.976576;,
-0.211080;0.041771;0.976576;,
-0.211080;0.041771;0.976576;,
0.211080;-0.041771;-0.976576;,
0.211080;-0.041771;-0.976576;,
0.211080;-0.041771;-0.976576;,
0.211080;-0.041771;-0.976576;,
-0.777423;0.598433;-0.193628;,
-0.777423;0.598433;-0.193628;,
-0.777424;0.598432;-0.193627;,
-0.777422;0.598434;-0.193629;,
0.777424;-0.598431;0.193629;,
0.777424;-0.598431;0.193629;,
0.777424;-0.598431;0.193629;,
0.777424;-0.598432;0.193629;,
0.648121;0.741472;0.173664;,
0.648121;0.741472;0.173664;,
0.648120;0.741472;0.173664;,
0.648121;0.741472;0.173663;,
-0.648121;-0.741472;-0.173664;,
-0.648121;-0.741472;-0.173664;,
-0.648121;-0.741472;-0.173664;,
-0.648120;-0.741472;-0.173663;,
-0.060235;0.638469;0.767287;,
-0.060235;0.638469;0.767287;,
-0.060235;0.638469;0.767286;,
-0.060235;0.638469;0.767287;,
0.060235;-0.638469;-0.767287;,
0.060235;-0.638469;-0.767287;,
0.060235;-0.638469;-0.767287;,
0.060235;-0.638469;-0.767287;,
-0.027498;0.832864;-0.552794;,
-0.027498;0.832864;-0.552794;,
-0.027494;0.832867;-0.552789;,
-0.027502;0.832862;-0.552798;,
0.027498;-0.832864;0.552794;,
0.027498;-0.832864;0.552794;,
0.027493;-0.832862;0.552797;,
0.027503;-0.832867;0.552790;,
-0.462639;0.880769;-0.101047;,
-0.462639;0.880769;-0.101047;,
-0.462640;0.880769;-0.101047;,
-0.462639;0.880769;-0.101047;,
0.462639;-0.880769;0.101047;,
0.462639;-0.880769;0.101047;,
0.462639;-0.880769;0.101047;,
0.462640;-0.880769;0.101047;,
0.886747;0.451567;0.098827;,
0.886747;0.451567;0.098827;,
0.886748;0.451565;0.098824;,
0.886746;0.451570;0.098829;,
-0.886747;-0.451567;-0.098827;,
-0.886747;-0.451567;-0.098827;,
-0.886746;-0.451570;-0.098824;,
-0.886748;-0.451565;-0.098829;,
0.442291;0.008003;0.896836;,
0.442291;0.008003;0.896836;,
0.442291;0.008003;0.896836;,
0.442291;0.008003;0.896836;,
-0.999982;0.006004;0.000000;,
-0.999982;0.006005;0.000000;,
-0.999982;0.006004;0.000000;,
-0.999982;0.006004;0.000001;,
0.442290;0.008003;-0.896836;,
0.442291;0.008003;-0.896836;,
0.442290;0.008003;-0.896836;,
0.442290;0.008003;-0.896836;;

 118;
3;2,1,0;,
3;3,0,1;,
3;6,5,4;,
3;7,4,5;,
3;10,9,8;,
3;11,8,9;,
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
3;123,120,121;,
3;126,125,124;,
3;127,124,125;,
3;130,129,128;,
3;131,128,129;,
3;134,133,132;,
3;135,132,133;,
3;138,137,136;,
3;139,136,137;,
3;142,141,140;,
3;143,140,141;,
3;146,145,144;,
3;147,144,145;,
3;150,149,148;,
3;151,148,149;,
3;154,153,152;,
3;155,152,153;,
3;158,157,156;,
3;159,156,157;,
3;162,161,160;,
3;163,160,161;,
3;166,165,164;,
3;167,164,165;,
3;170,169,168;,
3;171,168,169;,
3;174,173,172;,
3;175,172,173;,
3;178,177,176;,
3;179,176,177;,
3;182,181,180;,
3;183,180,181;,
3;186,185,184;,
3;187,184,185;,
3;190,189,188;,
3;191,188,189;,
3;194,193,192;,
3;195,192,193;,
3;198,197,196;,
3;199,196,197;,
3;202,201,200;,
3;203,200,201;,
3;206,205,204;,
3;207,204,205;,
3;210,209,208;,
3;211,208,209;,
3;214,213,212;,
3;215,212,213;,
3;218,217,216;,
3;219,216,217;,
3;222,221,220;,
3;223,220,221;,
3;226,225,224;,
3;226,224,227;,
3;230,229,228;,
3;230,228,231;,
3;234,233,232;,
3;234,232,235;;
 }
MeshTextureCoords {
 236;
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
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
0.000082;0.499927;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
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
0.000082;0.499927;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
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
0.000082;0.499927;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
1.000020;0.000018;,
0.500033;0.499974;,
0.500021;0.000026;,
1.000040;0.499960;,
0.500026;0.000012;,
1.000030;0.499974;,
1.000030;0.000025;,
0.500198;0.499952;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
1.000010;0.500000;,
0.500025;0.999956;,
0.500013;0.500008;,
1.000030;0.999942;,
0.500017;0.499994;,
1.000020;0.999956;,
1.000020;0.500008;,
0.500189;0.999934;,
0.503423;0.499476;,
0.497101;1.000000;,
0.344837;1.000000;,
0.351160;0.499476;,
0.351160;0.499476;,
0.344837;1.000000;,
0.158156;1.000000;,
0.164478;0.499476;,
0.164478;0.499476;,
0.158156;1.000000;,
0.004796;1.000000;,
0.011119;0.499476;;
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
  45; 4; 0.999914, 0.000000, 0.000000, 0.013090;;,
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
  0; 3; 0.000000, 0.044885, 0.332833;;,
  1; 3; 0.000000, 0.044885, 0.332833;;,
  45; 3; 0.000000, 0.044885, 0.332833;;,
  90; 3; 0.000000, 0.044885, 0.332833;;;
   }
      AnimationOptions {
            0; 0;
      }
  }
 }
