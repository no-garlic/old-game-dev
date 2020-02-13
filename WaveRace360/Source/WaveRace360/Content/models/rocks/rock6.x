xof 0303txt 0032
template AnimTicksPerSecond {
 <9e415a43-7ba6-4a73-8743-b73d47e88476>
 DWORD AnimTicksPerSecond;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}

template Animation {
 <3d82ab4f-62da-11cf-ab39-0020af71e433>
 [...]
}

template AnimationSet {
 <3d82ab50-62da-11cf-ab39-0020af71e433>
 [Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]
}

template FloatKeys {
 <10dd46a9-775b-11cf-8f52-0040333594a3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <f406b180-7b3b-11cf-8f52-0040333594a3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10dd46a8-775b-11cf-8f52-0040333594a3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}


AnimTicksPerSecond {
 4800;
}

Frame start01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  163;
  -5.794077;1.942400;-4.039944;,
  -5.208506;1.418532;-5.404091;,
  -6.008347;1.336166;-4.203956;,
  -5.208506;1.418532;-5.404091;,
  -6.123903;1.007121;-3.019495;,
  -6.008347;1.336166;-4.203956;,
  -5.208506;1.418532;-5.404091;,
  -4.817724;1.900249;-5.562149;,
  -4.829969;2.423237;-5.112211;,
  -2.637579;1.953142;-7.047701;,
  -4.614990;1.194911;-5.859394;,
  -5.535172;2.592047;-3.839106;,
  -4.719284;3.417915;-3.451506;,
  -4.052086;2.733719;-5.390705;,
  -5.656765;2.621084;-2.220561;,
  -5.851221;2.147559;-1.947585;,
  -5.396992;1.824357;0.665187;,
  -5.232851;3.032337;-1.308054;,
  -6.035303;1.616379;-2.512441;,
  -5.854713;1.517875;-1.559007;,
  -6.008347;1.336166;-4.203956;,
  -4.700827;3.458405;-0.769283;,
  -4.110670;4.610117;-1.599465;,
  -2.955715;4.927986;-1.958762;,
  -2.665208;4.842484;-2.900171;,
  -2.366636;4.722750;-3.831114;,
  -3.167624;3.564695;-4.662819;,
  -3.284950;3.055322;-5.533285;,
  -4.260466;3.479055;0.519059;,
  -3.339420;4.793190;-0.152596;,
  -2.079076;5.131178;-0.967789;,
  0.011328;5.235502;-2.218905;,
  -3.496033;4.178150;1.549026;,
  -2.604682;4.796127;1.298419;,
  -1.750923;5.062664;0.359547;,
  -3.307213;3.798632;2.368904;,
  -1.395167;3.696327;2.807171;,
  -0.814785;5.002327;0.571217;,
  -2.773376;2.807274;3.214041;,
  -3.317482;2.233054;3.010633;,
  -1.540881;1.905476;4.232527;,
  -1.410295;2.796303;3.825785;,
  -3.819529;1.617639;2.536951;,
  -5.048950;1.442499;1.340641;,
  -4.190420;0.537007;0.901105;,
  -3.100389;1.217199;3.135002;,
  -2.439775;0.937624;3.754173;,
  -1.171553;1.190500;4.515169;,
  0.291328;1.357113;4.363297;,
  0.619592;1.856155;4.062126;,
  0.135984;2.495505;3.808947;,
  -2.555961;0.489640;2.877106;,
  -0.754087;0.595971;3.994493;,
  1.043355;1.069215;4.015478;,
  3.226791;1.663147;2.853691;,
  0.821191;2.764042;3.217953;,
  -1.825429;0.761050;1.421308;,
  -0.462298;0.133569;1.541409;,
  0.670958;0.175960;1.799724;,
  0.962224;0.459292;3.201553;,
  1.647421;0.816322;3.538294;,
  -2.149605;0.014303;-0.374854;,
  0.574660;-0.144629;-1.412318;,
  1.771449;0.086785;0.561467;,
  2.537945;0.429256;2.045118;,
  2.992028;0.887239;2.734682;,
  3.224890;0.142643;0.060606;,
  4.154640;0.417647;1.027657;,
  4.201353;0.783006;1.799178;,
  3.483538;0.041194;-1.136373;,
  5.784769;0.447185;-0.551548;,
  4.923117;0.988420;1.337364;,
  5.594646;1.167199;0.607311;,
  6.686098;0.948759;-0.662377;,
  6.716328;1.532063;-1.078821;,
  5.325155;1.564898;0.685326;,
  5.406757;1.990189;0.108334;,
  4.660271;2.288995;0.609053;,
  3.901528;2.693348;0.881845;,
  2.766301;2.736774;1.948405;,
  1.380142;3.042065;2.565590;,
  6.404263;2.183244;-1.410844;,
  5.873568;2.769048;-2.001395;,
  3.732912;3.226149;-0.130463;,
  2.176115;3.470772;0.969515;,
  0.581179;3.662046;1.974219;,
  2.737280;3.735281;-0.902541;,
  1.310990;4.039190;-0.282076;,
  0.215894;4.823416;0.781205;,
  3.012234;3.753576;-1.918526;,
  3.471605;3.680775;-2.864439;,
  5.247910;3.156219;-3.193425;,
  4.911337;3.300150;-3.939811;,
  2.550865;3.934956;-3.592017;,
  2.238092;3.885084;-4.610968;,
  1.125908;4.017466;-4.636395;,
  0.126028;4.713020;-4.943081;,
  -1.020760;4.838531;-4.165799;,
  3.062164;3.448265;-5.644854;,
  1.663474;3.377653;-6.477047;,
  -0.051794;3.552534;-6.052776;,
  -1.647699;3.587656;-5.404815;,
  3.215287;2.982602;-6.497187;,
  2.257859;2.742380;-7.168833;,
  0.745051;2.483191;-7.372782;,
  -0.165667;3.073683;-6.995827;,
  -0.792287;3.380297;-6.573265;,
  3.794226;2.714482;-6.255217;,
  2.743599;2.090298;-7.423553;,
  0.399921;1.985139;-7.602308;,
  -2.168653;2.939100;-6.293514;,
  4.536268;2.408805;-5.972357;,
  4.354193;1.904562;-6.603127;,
  3.846460;1.427102;-7.209272;,
  2.510595;1.359398;-7.832420;,
  0.839993;1.489083;-7.858347;,
  5.213562;2.575892;-4.985460;,
  5.783131;1.754820;-5.200484;,
  4.334087;1.119539;-6.794445;,
  2.251854;0.630891;-7.656874;,
  -0.136720;1.213415;-7.778610;,
  5.559759;2.690780;-3.917535;,
  5.247910;3.156219;-3.193425;,
  5.873569;2.769047;-2.001395;,
  5.998732;2.340294;-3.428273;,
  6.330662;2.042129;-2.729147;,
  6.415850;1.606348;-3.249110;,
  6.261801;1.125237;-3.780507;,
  5.740206;0.948753;-5.051702;,
  4.801092;0.792184;-6.205811;,
  6.404263;2.183244;-1.410844;,
  6.716328;1.532063;-1.078821;,
  6.306494;0.853195;-2.954025;,
  5.312542;0.669120;-4.308267;,
  3.980408;0.377180;-6.141098;,
  6.362225;0.671734;-2.059829;,
  5.697151;0.648580;-2.301540;,
  4.227184;0.066691;-2.375827;,
  3.331184;-0.008186;-3.601622;,
  2.900724;0.099882;-5.106900;,
  6.686098;0.948759;-0.662377;,
  5.784769;0.447184;-0.551548;,
  3.483538;0.041194;-1.136373;,
  0.574660;-0.144629;-1.412318;,
  1.484563;0.111832;-5.342762;,
  0.049830;0.165484;-5.798182;,
  -0.334826;0.474677;-7.167467;,
  -1.056270;0.919767;-7.546165;,
  -1.305584;0.081896;-4.822078;,
  -2.305759;0.456804;-6.360308;,
  -2.688210;1.024750;-7.007059;,
  -2.916315;0.164617;-4.492528;,
  -4.042507;0.473593;-5.535400;,
  -4.022415;0.918900;-6.240515;,
  -3.097788;0.129743;-3.196191;,
  -3.564102;0.174991;-1.743230;,
  -5.058939;0.536023;-1.375865;,
  -5.496998;1.127121;-0.599566;,
  -5.854713;1.517875;-1.559007;,
  -5.397680;1.826555;0.662119;,
  -5.048950;1.442499;1.340641;,
  -2.149605;0.014303;-0.374854;,
  -4.190420;0.537007;0.901105;;
  288;
  3;0,1,2;,
  3;3,4,5;,
  3;6,0,7;,
  3;0,8,7;,
  3;8,9,7;,
  3;9,1,7;,
  3;1,9,10;,
  3;4,1,10;,
  3;8,0,11;,
  3;12,8,11;,
  3;8,12,13;,
  3;9,8,13;,
  3;0,14,11;,
  3;14,12,11;,
  3;14,0,15;,
  3;16,14,15;,
  3;14,16,17;,
  3;12,14,17;,
  3;0,18,15;,
  3;18,16,15;,
  3;16,18,19;,
  3;18,4,19;,
  3;4,18,2;,
  3;18,0,20;,
  3;21,12,17;,
  3;12,21,22;,
  3;23,12,22;,
  3;12,23,24;,
  3;25,12,24;,
  3;12,25,26;,
  3;27,12,26;,
  3;12,27,13;,
  3;16,21,17;,
  3;21,16,28;,
  3;29,21,28;,
  3;21,29,22;,
  3;29,23,22;,
  3;23,29,30;,
  3;31,23,30;,
  3;23,31,24;,
  3;31,25,24;,
  3;16,32,28;,
  3;32,29,28;,
  3;29,32,33;,
  3;34,29,33;,
  3;29,34,30;,
  3;34,31,30;,
  3;32,16,35;,
  3;36,32,35;,
  3;32,36,33;,
  3;36,34,33;,
  3;34,36,37;,
  3;31,34,37;,
  3;16,38,35;,
  3;38,36,35;,
  3;38,16,39;,
  3;40,38,39;,
  3;38,40,41;,
  3;36,38,41;,
  3;16,42,39;,
  3;42,40,39;,
  3;42,16,43;,
  3;44,42,43;,
  3;42,44,45;,
  3;40,42,45;,
  3;44,46,45;,
  3;46,40,45;,
  3;40,46,47;,
  3;48,40,47;,
  3;40,48,49;,
  3;50,40,49;,
  3;40,50,41;,
  3;50,36,41;,
  3;46,44,51;,
  3;52,46,51;,
  3;46,52,47;,
  3;52,48,47;,
  3;48,52,53;,
  3;54,48,53;,
  3;48,54,49;,
  3;54,50,49;,
  3;50,54,55;,
  3;36,50,55;,
  3;44,56,51;,
  3;56,52,51;,
  3;52,56,57;,
  3;58,52,57;,
  3;52,58,59;,
  3;60,52,59;,
  3;52,60,53;,
  3;60,54,53;,
  3;56,44,61;,
  3;62,56,61;,
  3;56,62,57;,
  3;62,58,57;,
  3;58,62,63;,
  3;64,58,63;,
  3;58,64,59;,
  3;64,60,59;,
  3;60,64,65;,
  3;54,60,65;,
  3;62,66,63;,
  3;66,64,63;,
  3;64,66,67;,
  3;68,64,67;,
  3;64,68,65;,
  3;68,54,65;,
  3;66,62,69;,
  3;70,66,69;,
  3;66,70,67;,
  3;70,68,67;,
  3;68,70,71;,
  3;54,68,71;,
  3;70,72,71;,
  3;72,54,71;,
  3;72,70,73;,
  3;74,72,73;,
  3;72,74,75;,
  3;54,72,75;,
  3;74,76,75;,
  3;76,54,75;,
  3;54,76,77;,
  3;78,54,77;,
  3;54,78,79;,
  3;80,54,79;,
  3;54,80,55;,
  3;76,74,81;,
  3;82,76,81;,
  3;76,82,77;,
  3;82,78,77;,
  3;78,82,83;,
  3;84,78,83;,
  3;78,84,79;,
  3;84,80,79;,
  3;80,84,85;,
  3;36,80,85;,
  3;80,36,55;,
  3;82,86,83;,
  3;86,84,83;,
  3;84,86,87;,
  3;88,84,87;,
  3;84,88,85;,
  3;88,36,85;,
  3;36,88,37;,
  3;88,31,37;,
  3;86,82,89;,
  3;31,86,89;,
  3;86,31,87;,
  3;31,88,87;,
  3;82,90,89;,
  3;90,31,89;,
  3;90,82,91;,
  3;92,90,91;,
  3;90,92,93;,
  3;31,90,93;,
  3;94,31,93;,
  3;31,94,95;,
  3;96,31,95;,
  3;31,96,97;,
  3;25,31,97;,
  3;92,94,93;,
  3;94,92,98;,
  3;99,94,98;,
  3;94,99,95;,
  3;99,96,95;,
  3;96,99,100;,
  3;101,96,100;,
  3;96,101,97;,
  3;101,25,97;,
  3;25,101,26;,
  3;101,27,26;,
  3;92,102,98;,
  3;102,99,98;,
  3;99,102,103;,
  3;104,99,103;,
  3;99,104,105;,
  3;106,99,105;,
  3;99,106,100;,
  3;106,101,100;,
  3;102,92,107;,
  3;108,102,107;,
  3;102,108,103;,
  3;108,104,103;,
  3;104,108,109;,
  3;9,104,109;,
  3;104,9,105;,
  3;9,106,105;,
  3;106,9,110;,
  3;101,106,110;,
  3;27,101,110;,
  3;92,111,107;,
  3;111,108,107;,
  3;108,111,112;,
  3;113,108,112;,
  3;108,113,114;,
  3;115,108,114;,
  3;108,115,109;,
  3;115,9,109;,
  3;111,92,116;,
  3;117,111,116;,
  3;111,117,112;,
  3;117,113,112;,
  3;113,117,118;,
  3;119,113,118;,
  3;113,119,114;,
  3;119,115,114;,
  3;115,119,120;,
  3;9,115,120;,
  3;92,121,116;,
  3;121,117,116;,
  3;121,92,122;,
  3;123,121,122;,
  3;121,123,124;,
  3;117,121,124;,
  3;123,125,124;,
  3;125,117,124;,
  3;117,125,126;,
  3;127,117,126;,
  3;117,127,128;,
  3;129,117,128;,
  3;117,129,118;,
  3;129,119,118;,
  3;125,123,130;,
  3;131,125,130;,
  3;125,131,126;,
  3;131,127,126;,
  3;127,131,132;,
  3;133,127,132;,
  3;127,133,128;,
  3;133,129,128;,
  3;129,133,134;,
  3;119,129,134;,
  3;131,135,132;,
  3;135,133,132;,
  3;133,135,136;,
  3;137,133,136;,
  3;133,137,138;,
  3;139,133,138;,
  3;133,139,134;,
  3;139,119,134;,
  3;135,131,140;,
  3;141,135,140;,
  3;135,141,136;,
  3;141,137,136;,
  3;137,141,142;,
  3;143,137,142;,
  3;137,143,138;,
  3;143,139,138;,
  3;139,143,144;,
  3;119,139,144;,
  3;145,119,144;,
  3;119,145,146;,
  3;147,119,146;,
  3;119,147,120;,
  3;143,145,144;,
  3;145,143,148;,
  3;149,145,148;,
  3;145,149,146;,
  3;149,147,146;,
  3;147,149,150;,
  3;9,147,150;,
  3;147,9,120;,
  3;143,151,148;,
  3;151,149,148;,
  3;149,151,152;,
  3;153,149,152;,
  3;149,153,150;,
  3;153,9,150;,
  3;9,153,10;,
  3;153,4,10;,
  3;151,143,154;,
  3;4,151,154;,
  3;151,4,152;,
  3;4,153,152;,
  3;143,155,154;,
  3;155,4,154;,
  3;4,155,156;,
  3;157,4,156;,
  3;4,157,158;,
  3;157,159,158;,
  3;159,157,160;,
  3;155,143,161;,
  3;162,155,161;,
  3;155,162,156;,
  3;162,157,156;,
  3;157,162,160;,
  3;9,27,110;,
  3;27,9,13;;

  MeshNormals {
   163;
   -0.866366;0.409209;-0.286284;,
   -0.733416;-0.093599;-0.673305;,
   -0.959307;0.011282;-0.282140;,
   -0.693162;-0.223958;-0.685105;,
   -0.656279;-0.747729;-0.100994;,
   -0.922360;-0.138912;-0.360494;,
   -0.730222;0.103638;-0.675303;,
   -0.651812;0.413762;-0.635565;,
   -0.592637;0.598826;-0.538692;,
   -0.371876;0.372451;-0.850287;,
   -0.634791;-0.369422;-0.678652;,
   -0.758853;0.594714;-0.265438;,
   -0.564960;0.776949;-0.277796;,
   -0.440800;0.709377;-0.549981;,
   -0.845153;0.533607;0.031290;,
   -0.937083;0.342247;0.068870;,
   -0.835343;0.395176;0.382149;,
   -0.746764;0.654553;0.117918;,
   -0.979900;0.188642;0.064888;,
   -0.981624;0.027755;0.188797;,
   -0.923779;0.321423;-0.208135;,
   -0.766923;0.614132;0.186201;,
   -0.617407;0.786272;-0.024203;,
   -0.273719;0.950969;-0.143999;,
   -0.314770;0.927693;-0.200762;,
   -0.304340;0.858400;-0.412949;,
   -0.365485;0.772403;-0.519436;,
   -0.347474;0.780973;-0.518982;,
   -0.772960;0.596795;0.215332;,
   -0.478800;0.863781;0.156949;,
   -0.144098;0.989404;0.017779;,
   0.196228;0.979678;-0.041545;,
   -0.567983;0.727930;0.384074;,
   -0.198434;0.893942;0.401860;,
   -0.034187;0.974533;0.221622;,
   -0.475055;0.603398;0.640495;,
   0.050315;0.800449;0.597285;,
   0.045185;0.948336;0.314033;,
   -0.479770;0.456788;0.749110;,
   -0.663501;0.168780;0.728889;,
   -0.313819;0.274325;0.908990;,
   -0.106298;0.600935;0.792199;,
   -0.685934;-0.123165;0.717165;,
   -0.679905;-0.141731;0.719473;,
   -0.418476;-0.806832;0.417014;,
   -0.702555;-0.197685;0.683621;,
   -0.540740;-0.482212;0.689254;,
   -0.166882;-0.256627;0.951994;,
   0.244023;0.006257;0.969749;,
   0.246115;0.439318;0.863960;,
   0.220866;0.598561;0.770028;,
   -0.147536;-0.972123;0.182237;,
   -0.011292;-0.887774;0.460140;,
   0.347489;-0.413999;0.841342;,
   0.564082;0.326992;0.758213;,
   0.310343;0.715557;0.625832;,
   -0.087328;-0.991087;0.100599;,
   -0.212785;-0.973113;0.088173;,
   0.045450;-0.987048;0.153855;,
   0.144063;-0.934157;0.326492;,
   0.342350;-0.694449;0.632880;,
   0.044907;-0.925294;0.376582;,
   -0.027752;-0.992840;0.116184;,
   0.076046;-0.988568;0.130192;,
   0.185565;-0.938646;0.290706;,
   0.433206;-0.626047;0.648381;,
   0.102693;-0.986242;0.129542;,
   0.223482;-0.934495;0.277082;,
   0.445571;-0.696132;0.562909;,
   0.099454;-0.989450;0.105350;,
   0.399428;-0.843999;0.357942;,
   0.660921;-0.384937;0.644211;,
   0.753733;-0.001744;0.657179;,
   0.723152;-0.210455;0.657845;,
   0.697127;0.472710;0.539035;,
   0.668792;0.478123;0.569311;,
   0.587128;0.649207;0.483540;,
   0.561547;0.683675;0.466104;,
   0.481373;0.764664;0.428450;,
   0.428739;0.762549;0.484459;,
   0.338638;0.781722;0.523674;,
   0.557282;0.695054;0.454243;,
   0.421790;0.869319;0.257639;,
   0.382131;0.880833;0.279478;,
   0.396631;0.858587;0.324827;,
   0.328748;0.779488;0.533220;,
   0.338628;0.920310;0.195857;,
   0.463578;0.873161;0.150619;,
   0.371798;0.867201;0.331252;,
   0.377725;0.918659;0.115711;,
   0.334151;0.941438;0.045130;,
   0.298679;0.949180;0.099238;,
   0.437554;0.864807;-0.246283;,
   0.316662;0.942180;-0.109649;,
   0.209074;0.945985;-0.247792;,
   0.368866;0.897374;-0.242193;,
   0.090218;0.887110;-0.452654;,
   -0.176797;0.897634;-0.403727;,
   0.256855;0.908126;-0.330656;,
   0.131657;0.857599;-0.497183;,
   -0.109058;0.856442;-0.504592;,
   -0.257836;0.811189;-0.524875;,
   0.384535;0.732831;-0.561331;,
   0.153544;0.642440;-0.750796;,
   -0.020708;0.513271;-0.857977;,
   -0.067176;0.622399;-0.779812;,
   -0.170039;0.839633;-0.515852;,
   0.509436;0.633261;-0.582629;,
   0.287403;0.493245;-0.821041;,
   -0.059596;0.430246;-0.900742;,
   -0.330562;0.764725;-0.553104;,
   0.516155;0.646399;-0.561918;,
   0.558773;0.461238;-0.689226;,
   0.547854;0.070584;-0.833591;,
   0.229472;0.068295;-0.970916;,
   -0.046218;0.202825;-0.978124;,
   0.624318;0.674871;-0.393416;,
   0.827328;0.274616;-0.490015;,
   0.611342;-0.250573;-0.750650;,
   0.146011;-0.722651;-0.675615;,
   -0.136017;-0.084215;-0.987121;,
   0.714703;0.662891;-0.223102;,
   0.691292;0.705577;-0.155811;,
   0.748750;0.650389;-0.127937;,
   0.794053;0.574817;-0.197651;,
   0.868727;0.470508;-0.154710;,
   0.962990;0.170141;-0.209049;,
   0.887387;-0.394756;-0.238145;,
   0.722077;-0.600235;-0.343980;,
   0.570748;-0.637887;-0.517056;,
   0.858850;0.502033;-0.101689;,
   0.990594;-0.020648;-0.135269;,
   0.786504;-0.584595;-0.199150;,
   0.346126;-0.929012;-0.130895;,
   0.274373;-0.930979;-0.240826;,
   0.575842;-0.809728;-0.112898;,
   0.217930;-0.972131;-0.086419;,
   0.218466;-0.974990;-0.040830;,
   0.152312;-0.984530;-0.086609;,
   0.096827;-0.987873;-0.121377;,
   0.808229;-0.584518;-0.071443;,
   0.278956;-0.959888;-0.028261;,
   0.108883;-0.993040;0.044900;,
   -0.015263;-0.999282;-0.034668;,
   0.010907;-0.990287;-0.138610;,
   -0.018120;-0.986772;-0.161096;,
   -0.092407;-0.899592;-0.426843;,
   -0.216487;-0.504820;-0.835637;,
   -0.053105;-0.991401;-0.119600;,
   -0.165415;-0.912233;-0.374793;,
   -0.362319;-0.452990;-0.814570;,
   -0.140897;-0.986332;-0.085427;,
   -0.335676;-0.893608;-0.297970;,
   -0.513839;-0.547359;-0.660581;,
   -0.175533;-0.983708;-0.038821;,
   -0.184625;-0.982793;-0.005549;,
   -0.446228;-0.888596;0.106195;,
   -0.805859;-0.536151;0.251264;,
   -0.934762;-0.259234;0.242935;,
   -0.915411;-0.317145;0.247874;,
   -0.787132;-0.553682;0.271771;,
   -0.135143;-0.990550;0.023378;,
   -0.426964;-0.887692;0.172349;;
   288;
   3;0,1,2;,
   3;3,4,5;,
   3;6,0,7;,
   3;0,8,7;,
   3;8,9,7;,
   3;9,1,7;,
   3;1,9,10;,
   3;4,1,10;,
   3;8,0,11;,
   3;12,8,11;,
   3;8,12,13;,
   3;9,8,13;,
   3;0,14,11;,
   3;14,12,11;,
   3;14,0,15;,
   3;16,14,15;,
   3;14,16,17;,
   3;12,14,17;,
   3;0,18,15;,
   3;18,16,15;,
   3;16,18,19;,
   3;18,4,19;,
   3;4,18,2;,
   3;18,0,20;,
   3;21,12,17;,
   3;12,21,22;,
   3;23,12,22;,
   3;12,23,24;,
   3;25,12,24;,
   3;12,25,26;,
   3;27,12,26;,
   3;12,27,13;,
   3;16,21,17;,
   3;21,16,28;,
   3;29,21,28;,
   3;21,29,22;,
   3;29,23,22;,
   3;23,29,30;,
   3;31,23,30;,
   3;23,31,24;,
   3;31,25,24;,
   3;16,32,28;,
   3;32,29,28;,
   3;29,32,33;,
   3;34,29,33;,
   3;29,34,30;,
   3;34,31,30;,
   3;32,16,35;,
   3;36,32,35;,
   3;32,36,33;,
   3;36,34,33;,
   3;34,36,37;,
   3;31,34,37;,
   3;16,38,35;,
   3;38,36,35;,
   3;38,16,39;,
   3;40,38,39;,
   3;38,40,41;,
   3;36,38,41;,
   3;16,42,39;,
   3;42,40,39;,
   3;42,16,43;,
   3;44,42,43;,
   3;42,44,45;,
   3;40,42,45;,
   3;44,46,45;,
   3;46,40,45;,
   3;40,46,47;,
   3;48,40,47;,
   3;40,48,49;,
   3;50,40,49;,
   3;40,50,41;,
   3;50,36,41;,
   3;46,44,51;,
   3;52,46,51;,
   3;46,52,47;,
   3;52,48,47;,
   3;48,52,53;,
   3;54,48,53;,
   3;48,54,49;,
   3;54,50,49;,
   3;50,54,55;,
   3;36,50,55;,
   3;44,56,51;,
   3;56,52,51;,
   3;52,56,57;,
   3;58,52,57;,
   3;52,58,59;,
   3;60,52,59;,
   3;52,60,53;,
   3;60,54,53;,
   3;56,44,61;,
   3;62,56,61;,
   3;56,62,57;,
   3;62,58,57;,
   3;58,62,63;,
   3;64,58,63;,
   3;58,64,59;,
   3;64,60,59;,
   3;60,64,65;,
   3;54,60,65;,
   3;62,66,63;,
   3;66,64,63;,
   3;64,66,67;,
   3;68,64,67;,
   3;64,68,65;,
   3;68,54,65;,
   3;66,62,69;,
   3;70,66,69;,
   3;66,70,67;,
   3;70,68,67;,
   3;68,70,71;,
   3;54,68,71;,
   3;70,72,71;,
   3;72,54,71;,
   3;72,70,73;,
   3;74,72,73;,
   3;72,74,75;,
   3;54,72,75;,
   3;74,76,75;,
   3;76,54,75;,
   3;54,76,77;,
   3;78,54,77;,
   3;54,78,79;,
   3;80,54,79;,
   3;54,80,55;,
   3;76,74,81;,
   3;82,76,81;,
   3;76,82,77;,
   3;82,78,77;,
   3;78,82,83;,
   3;84,78,83;,
   3;78,84,79;,
   3;84,80,79;,
   3;80,84,85;,
   3;36,80,85;,
   3;80,36,55;,
   3;82,86,83;,
   3;86,84,83;,
   3;84,86,87;,
   3;88,84,87;,
   3;84,88,85;,
   3;88,36,85;,
   3;36,88,37;,
   3;88,31,37;,
   3;86,82,89;,
   3;31,86,89;,
   3;86,31,87;,
   3;31,88,87;,
   3;82,90,89;,
   3;90,31,89;,
   3;90,82,91;,
   3;92,90,91;,
   3;90,92,93;,
   3;31,90,93;,
   3;94,31,93;,
   3;31,94,95;,
   3;96,31,95;,
   3;31,96,97;,
   3;25,31,97;,
   3;92,94,93;,
   3;94,92,98;,
   3;99,94,98;,
   3;94,99,95;,
   3;99,96,95;,
   3;96,99,100;,
   3;101,96,100;,
   3;96,101,97;,
   3;101,25,97;,
   3;25,101,26;,
   3;101,27,26;,
   3;92,102,98;,
   3;102,99,98;,
   3;99,102,103;,
   3;104,99,103;,
   3;99,104,105;,
   3;106,99,105;,
   3;99,106,100;,
   3;106,101,100;,
   3;102,92,107;,
   3;108,102,107;,
   3;102,108,103;,
   3;108,104,103;,
   3;104,108,109;,
   3;9,104,109;,
   3;104,9,105;,
   3;9,106,105;,
   3;106,9,110;,
   3;101,106,110;,
   3;27,101,110;,
   3;92,111,107;,
   3;111,108,107;,
   3;108,111,112;,
   3;113,108,112;,
   3;108,113,114;,
   3;115,108,114;,
   3;108,115,109;,
   3;115,9,109;,
   3;111,92,116;,
   3;117,111,116;,
   3;111,117,112;,
   3;117,113,112;,
   3;113,117,118;,
   3;119,113,118;,
   3;113,119,114;,
   3;119,115,114;,
   3;115,119,120;,
   3;9,115,120;,
   3;92,121,116;,
   3;121,117,116;,
   3;121,92,122;,
   3;123,121,122;,
   3;121,123,124;,
   3;117,121,124;,
   3;123,125,124;,
   3;125,117,124;,
   3;117,125,126;,
   3;127,117,126;,
   3;117,127,128;,
   3;129,117,128;,
   3;117,129,118;,
   3;129,119,118;,
   3;125,123,130;,
   3;131,125,130;,
   3;125,131,126;,
   3;131,127,126;,
   3;127,131,132;,
   3;133,127,132;,
   3;127,133,128;,
   3;133,129,128;,
   3;129,133,134;,
   3;119,129,134;,
   3;131,135,132;,
   3;135,133,132;,
   3;133,135,136;,
   3;137,133,136;,
   3;133,137,138;,
   3;139,133,138;,
   3;133,139,134;,
   3;139,119,134;,
   3;135,131,140;,
   3;141,135,140;,
   3;135,141,136;,
   3;141,137,136;,
   3;137,141,142;,
   3;143,137,142;,
   3;137,143,138;,
   3;143,139,138;,
   3;139,143,144;,
   3;119,139,144;,
   3;145,119,144;,
   3;119,145,146;,
   3;147,119,146;,
   3;119,147,120;,
   3;143,145,144;,
   3;145,143,148;,
   3;149,145,148;,
   3;145,149,146;,
   3;149,147,146;,
   3;147,149,150;,
   3;9,147,150;,
   3;147,9,120;,
   3;143,151,148;,
   3;151,149,148;,
   3;149,151,152;,
   3;153,149,152;,
   3;149,153,150;,
   3;153,9,150;,
   3;9,153,10;,
   3;153,4,10;,
   3;151,143,154;,
   3;4,151,154;,
   3;151,4,152;,
   3;4,153,152;,
   3;143,155,154;,
   3;155,4,154;,
   3;4,155,156;,
   3;157,4,156;,
   3;4,157,158;,
   3;157,159,158;,
   3;159,157,160;,
   3;155,143,161;,
   3;162,155,161;,
   3;155,162,156;,
   3;162,157,156;,
   3;157,162,160;,
   3;9,27,110;,
   3;27,9,13;;
  }

  MeshTextureCoords {
   163;
   0.577080;0.781072;,
   0.643835;0.720219;,
   0.630386;0.810526;,
   0.643835;0.720219;,
   0.683692;0.839979;,
   0.630386;0.810526;,
   0.643835;0.720219;,
   0.623906;0.660339;,
   0.567789;0.689014;,
   0.670733;0.539605;,
   0.677212;0.689792;,
   0.516317;0.763718;,
   0.455554;0.746365;,
   0.563143;0.642985;,
   0.448930;0.809758;,
   0.445619;0.841455;,
   0.314157;0.901838;,
   0.384856;0.824101;,
   0.524976;0.840963;,
   0.498924;0.870908;,
   0.630386;0.810526;,
   0.378459;0.784545;,
   0.410609;0.725899;,
   0.427635;0.618300;,
   0.458620;0.574733;,
   0.493060;0.540343;,
   0.508747;0.608965;,
   0.562742;0.585845;,
   0.339911;0.803635;,
   0.365665;0.705433;,
   0.413676;0.554267;,
   0.461687;0.403101;,
   0.318023;0.758416;,
   0.319955;0.686705;,
   0.367199;0.592170;,
   0.294201;0.784907;,
   0.274246;0.667976;,
   0.367967;0.535538;,
   0.255499;0.734330;,
   0.246125;0.767507;,
   0.178093;0.633176;,
   0.226169;0.650576;,
   0.169201;0.740678;,
   0.164755;0.794429;,
   0.015353;0.687021;,
   0.096723;0.660098;,
   0.098551;0.596971;,
   0.140151;0.551946;,
   0.180816;0.469184;,
   0.220120;0.468418;,
   0.238162;0.534938;,
   0.058781;0.578868;,
   0.102208;0.470715;,
   0.182178;0.387188;,
   0.262148;0.303661;,
   0.268197;0.485819;,
   0.047796;0.472962;,
   0.064017;0.365932;,
   0.089370;0.338566;,
   0.121142;0.377273;,
   0.168144;0.352736;,
   0.020590;0.474086;,
   0.025826;0.261150;,
   0.082952;0.272491;,
   0.140077;0.283832;,
   0.201112;0.293746;,
   0.117896;0.189801;,
   0.163931;0.154126;,
   0.196670;0.203971;,
   0.106805;0.142785;,
   0.187784;0.024420;,
   0.224966;0.164041;,
   0.268529;0.115486;,
   0.271720;0.021399;,
   0.355656;0.018377;,
   0.308902;0.161019;,
   0.354597;0.116709;,
   0.354068;0.165874;,
   0.357454;0.223596;,
   0.313187;0.321350;,
   0.300207;0.436892;,
   0.400822;0.023232;,
   0.445987;0.028088;,
   0.405107;0.183563;,
   0.364227;0.339039;,
   0.319237;0.503507;,
   0.423967;0.256743;,
   0.412957;0.371070;,
   0.366720;0.470039;,
   0.453837;0.215595;,
   0.508587;0.149251;,
   0.532037;0.022326;,
   0.618087;0.016563;,
   0.539887;0.209832;,
   0.572245;0.208319;,
   0.549323;0.304197;,
   0.553529;0.359986;,
   0.511814;0.437333;,
   0.627524;0.110928;,
   0.636960;0.205293;,
   0.599450;0.338428;,
   0.561940;0.471564;,
   0.661645;0.138353;,
   0.683424;0.199248;,
   0.679194;0.312701;,
   0.653847;0.372449;,
   0.623211;0.405487;,
   0.673988;0.104883;,
   0.729889;0.193204;,
   0.700311;0.366404;,
   0.616336;0.505584;,
   0.739854;0.091319;,
   0.800738;0.128697;,
   0.799002;0.187560;,
   0.762709;0.249245;,
   0.732051;0.346032;,
   0.744837;0.040376;,
   0.871587;0.064189;,
   0.833558;0.184738;,
   0.795530;0.305286;,
   0.733132;0.422445;,
   0.820108;0.028355;,
   0.794369;0.010439;,
   0.970651;0.004314;,
   0.921119;0.034252;,
   0.938914;0.134233;,
   0.923046;0.199193;,
   0.909242;0.236259;,
   0.876611;0.187291;,
   0.849584;0.226623;,
   0.972577;0.169255;,
   0.974504;0.334196;,
   0.928069;0.322294;,
   0.881635;0.310393;,
   0.838583;0.307840;,
   0.948936;0.382960;,
   0.936152;0.407342;,
   0.927567;0.480250;,
   0.896016;0.468229;,
   0.862521;0.413915;,
   0.982586;0.419244;,
   0.990668;0.504292;,
   0.950533;0.565179;,
   0.910398;0.626065;,
   0.852964;0.465675;,
   0.827854;0.501630;,
   0.786582;0.439412;,
   0.747966;0.472810;,
   0.844016;0.599801;,
   0.777634;0.573538;,
   0.724183;0.556571;,
   0.790575;0.679861;,
   0.730663;0.706758;,
   0.710686;0.651041;,
   0.797045;0.733022;,
   0.792070;0.798134;,
   0.732906;0.884169;,
   0.673807;0.921121;,
   0.619650;0.917502;,
   0.555608;0.995026;,
   0.668864;0.961692;,
   0.846259;0.777212;,
   0.782120;0.928358;;
  }

  MeshMaterialList {
   1;
   288;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
    1.000000;1.000000;1.000000;1.000000;;
    3.200000;
    0.000000;0.000000;0.000000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "StonesBoulders_19_seamless_256.jpg";
    }
   }
  }

  VertexDuplicationIndices {
   163;
   159;
   0,
   1,
   2,
   1,
   4,
   2,
   1,
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
   2,
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
   162;
  }

  XSkinMeshHeader {
   1;
   1;
   2;
  }

  SkinWeights {
   "start01";
   0;
   ;
   ;
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  SkinWeights {
   "rock2";
   163;
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
   162;
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
   1.000000,
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
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }
 }

 Frame rock2 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }
 }
}

AnimationSet Anim_1 {
 

 Animation {
  

  AnimationKey {
   0;
   1;
   0;4;1.000000,0.000000,0.000000,0.000000;;;
  }

  AnimationKey {
   1;
   1;
   0;3;1.000000,1.000000,1.000000;;;
  }

  AnimationKey {
   2;
   1;
   0;3;0.000000,0.000000,0.000000;;;
  }
  { rock2 }
 }

 Animation {
  

  AnimationKey {
   0;
   1;
   0;4;1.000000,0.000000,0.000000,0.000000;;;
  }

  AnimationKey {
   1;
   1;
   0;3;1.000000,1.000000,1.000000;;;
  }

  AnimationKey {
   2;
   1;
   0;3;0.000000,0.000000,0.000000;;;
  }
  { start01 }
 }
}