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
 292;
-2.054700;1.712473;0.080259;,
-2.215040;1.719762;0.080259;,
-2.054700;1.712473;-0.080251;,
-2.215040;1.719762;-0.080251;,
-1.900080;0.000000;0.120739;,
-1.900080;0.241490;0.120739;,
-1.900080;0.000000;-0.120739;,
-1.900080;0.241490;-0.120739;,
-2.141570;0.000000;0.120739;,
-1.900080;0.000000;0.120739;,
-2.141570;0.000000;-0.120739;,
-1.900080;0.000000;-0.120739;,
-2.141570;0.241490;0.120739;,
-2.141570;0.000000;0.120739;,
-2.141570;0.241490;-0.120739;,
-2.141570;0.000000;-0.120739;,
-1.900080;0.241490;0.120739;,
-2.141570;0.241490;0.120739;,
-2.141570;0.241490;-0.120739;,
-1.900080;0.241490;-0.120739;,
-2.165220;0.457980;-0.120739;,
-1.925410;0.486340;-0.120739;,
-2.165220;0.457980;0.120739;,
-2.165220;0.457980;-0.120739;,
-1.925410;0.486340;0.120739;,
-2.165220;0.457980;0.120739;,
-2.237760;1.014500;-0.120739;,
-1.997440;1.038160;-0.120739;,
-2.237760;1.014500;0.120739;,
-2.237760;1.014500;-0.120739;,
-1.997440;1.038160;0.120739;,
-2.237760;1.014500;0.120739;,
-2.267240;1.458752;-0.120739;,
-2.025780;1.461304;-0.120739;,
-2.267240;1.458752;0.120739;,
-2.267240;1.458752;-0.120739;,
-2.025780;1.461304;0.120739;,
-2.267240;1.458752;0.120739;,
-2.257490;1.677541;-0.120739;,
-2.016260;1.666575;-0.120739;,
-2.257490;1.677541;0.120739;,
-2.257490;1.677541;-0.120739;,
-2.016260;1.666575;0.120739;,
-2.257490;1.677541;0.120739;,
-2.215040;1.719762;-0.080251;,
-2.054700;1.712473;-0.080251;,
-2.215040;1.719762;0.080259;,
-2.054700;1.712473;0.080259;,
-2.025780;1.396000;0.062489;,
-2.025780;1.461304;0.120739;,
-2.025780;1.396000;-0.038431;,
-2.016260;1.666575;0.120739;,
-2.025780;1.461304;-0.120739;,
-2.016260;1.666575;-0.120739;,
-2.009350;1.260028;-0.038431;,
-1.997440;1.038160;-0.038431;,
-1.997440;1.038160;-0.120739;,
2.090450;1.292879;0.062489;,
2.085040;1.429732;0.062489;,
2.090450;1.292879;-0.038431;,
2.085040;1.429732;-0.038431;,
-1.932330;1.402258;0.062489;,
-2.025780;1.396000;0.062489;,
-1.932330;1.402258;-0.038431;,
-2.025780;1.396000;-0.038431;,
-1.915900;1.266286;-0.038431;,
-2.009350;1.260028;-0.038431;,
-1.915900;1.266286;0.062489;,
-2.009350;1.260028;0.062489;,
-1.915900;1.266286;-0.038431;,
-2.009350;1.260028;-0.038431;,
-1.915900;1.266286;0.062489;,
-2.009350;1.260028;0.062489;,
-1.498308;1.268666;-0.038431;,
-1.498308;1.268666;0.062489;,
-1.496135;1.405608;-0.038431;,
-1.498308;1.268666;-0.038431;,
-1.932330;1.402258;0.062489;,
-1.932330;1.402258;-0.038431;,
-1.496135;1.405608;0.062489;,
-1.496135;1.405608;-0.038431;,
-1.498308;1.268666;0.062489;,
-1.496135;1.405608;0.062489;,
-1.216147;1.257808;-0.038431;,
-1.216147;1.257808;0.062489;,
-1.213514;1.394743;-0.038431;,
-1.216147;1.257808;-0.038431;,
-1.213514;1.394743;0.062489;,
-1.213514;1.394743;-0.038431;,
-1.216147;1.257808;0.062489;,
-1.213514;1.394743;0.062489;,
-0.784124;1.257817;-0.038431;,
-0.784124;1.257817;0.062489;,
-0.787503;1.394735;-0.038431;,
-0.784124;1.257817;-0.038431;,
-0.787503;1.394735;0.062489;,
-0.787503;1.394735;-0.038431;,
-0.784124;1.257817;0.062489;,
-0.787503;1.394735;0.062489;,
-0.343588;1.279559;-0.038431;,
-0.343588;1.279559;0.062489;,
-0.348283;1.416438;-0.038431;,
-0.343588;1.279559;-0.038431;,
-0.348283;1.416438;0.062489;,
-0.348283;1.416438;-0.038431;,
-0.343588;1.279559;0.062489;,
-0.348283;1.416438;0.062489;,
-0.062886;1.284952;-0.038431;,
-0.062886;1.284952;0.062489;,
-0.064203;1.421905;-0.038431;,
-0.062886;1.284952;-0.038431;,
-0.064203;1.421905;0.062489;,
-0.064203;1.421905;-0.038431;,
-0.062886;1.284952;0.062489;,
-0.064203;1.421905;0.062489;,
0.289440;1.284950;-0.038431;,
0.289440;1.284950;0.062489;,
0.289440;1.421908;-0.038431;,
0.289440;1.284950;-0.038431;,
0.289440;1.421908;0.062489;,
0.289440;1.421908;-0.038431;,
0.289440;1.284950;0.062489;,
0.289440;1.421908;0.062489;,
1.091720;1.287397;-0.038431;,
1.091720;1.287397;0.062489;,
1.092800;1.424354;-0.038431;,
1.091720;1.287397;-0.038431;,
1.092810;1.424354;0.062489;,
1.092800;1.424354;-0.038431;,
1.091720;1.287397;0.062489;,
1.092810;1.424354;0.062489;,
1.668610;1.276538;-0.038431;,
1.668610;1.276538;0.062489;,
1.667200;1.413491;-0.038431;,
1.668610;1.276538;-0.038431;,
1.667200;1.413491;0.062489;,
1.667200;1.413491;-0.038431;,
1.668610;1.276538;0.062489;,
1.667200;1.413491;0.062489;,
2.090450;1.292879;-0.038431;,
2.090450;1.292879;0.062489;,
2.085040;1.429732;0.062489;,
2.085040;1.429732;-0.038431;,
-1.997440;1.038160;0.062489;,
-1.997440;1.038160;0.120739;,
-2.009350;1.260028;0.062489;,
-1.925410;0.486340;-0.120739;,
-1.925410;0.486340;0.120739;,
-1.925410;0.486340;-0.070201;,
-1.925410;0.486340;0.054769;,
-1.957250;0.709370;0.058179;,
-1.957200;0.709000;-0.056181;,
-1.981300;0.859570;0.060759;,
-1.981320;0.859760;-0.045541;,
2.033740;0.897160;0.060679;,
2.033750;0.897350;-0.045621;,
2.030730;0.741200;0.058099;,
2.030710;0.740820;-0.056261;,
-1.893220;0.708190;-0.056181;,
-1.957200;0.709000;-0.056181;,
-1.893270;0.708560;0.058179;,
-1.957250;0.709370;0.058179;,
-1.893270;0.708560;0.058179;,
-1.957250;0.709370;0.058179;,
-1.917310;0.862690;0.060759;,
-1.981300;0.859570;0.060759;,
-1.917340;0.862880;-0.045541;,
-1.981320;0.859760;-0.045541;,
-1.893220;0.708190;-0.056181;,
-1.957200;0.709000;-0.056181;,
-1.917310;0.862690;0.060759;,
-1.917340;0.862880;-0.045541;,
-1.611031;0.868580;0.060749;,
-1.611028;0.868770;-0.045551;,
-1.609714;0.712590;0.058169;,
-1.611031;0.868580;0.060749;,
-1.609721;0.712210;-0.056191;,
-1.609714;0.712590;0.058169;,
-1.611028;0.868770;-0.045551;,
-1.609721;0.712210;-0.056191;,
-1.262280;0.868580;0.060739;,
-1.262275;0.868770;-0.045551;,
-1.262273;0.712580;0.058169;,
-1.262280;0.868580;0.060739;,
-1.262283;0.712210;-0.056191;,
-1.262273;0.712580;0.058169;,
-1.262275;0.868770;-0.045551;,
-1.262283;0.712210;-0.056191;,
-1.019709;0.866840;0.060739;,
-1.019708;0.867030;-0.045561;,
-1.016650;0.710870;0.058159;,
-1.019709;0.866840;0.060739;,
-1.016652;0.710500;-0.056201;,
-1.016650;0.710870;0.058159;,
-1.019708;0.867030;-0.045561;,
-1.016652;0.710500;-0.056201;,
-0.477844;0.891910;0.060729;,
-0.477845;0.892100;-0.045571;,
-0.473462;0.735980;0.058149;,
-0.477844;0.891910;0.060729;,
-0.473461;0.735600;-0.056211;,
-0.473462;0.735980;0.058149;,
-0.477845;0.892100;-0.045571;,
-0.473461;0.735600;-0.056211;,
0.318410;0.899800;0.060709;,
0.318420;0.899990;-0.045591;,
0.318390;0.743800;0.058139;,
0.318410;0.899800;0.060709;,
0.318380;0.743430;-0.056221;,
0.318390;0.743800;0.058139;,
0.318420;0.899990;-0.045591;,
0.318380;0.743430;-0.056221;,
0.926350;0.893520;0.060699;,
0.926350;0.893710;-0.045601;,
0.927210;0.737530;0.058119;,
0.926350;0.893520;0.060699;,
0.927210;0.737150;-0.056241;,
0.927210;0.737530;0.058119;,
0.926350;0.893710;-0.045601;,
0.927210;0.737150;-0.056241;,
1.538960;0.906590;0.060689;,
1.538960;0.906780;-0.045611;,
1.539120;0.750590;0.058109;,
1.538960;0.906590;0.060689;,
1.539110;0.750220;-0.056251;,
1.539120;0.750590;0.058109;,
1.538960;0.906780;-0.045611;,
1.539110;0.750220;-0.056251;,
2.033740;0.897160;0.060679;,
2.033750;0.897350;-0.045621;,
2.030730;0.741200;0.058099;,
2.033740;0.897160;0.060679;,
1.539110;0.750220;-0.056251;,
1.539120;0.750590;0.058109;,
2.033750;0.897350;-0.045621;,
2.030710;0.740820;-0.056261;,
2.242330;1.722920;0.089459;,
2.083770;1.731043;0.089459;,
2.242330;1.722920;-0.089452;,
2.083770;1.731043;-0.089452;,
2.231760;0.000000;0.120739;,
2.231760;0.241490;0.120739;,
2.231760;0.000000;-0.120739;,
2.231760;0.241490;-0.120739;,
2.013610;0.000000;0.120739;,
2.231760;0.000000;0.120739;,
2.013610;0.000000;-0.120739;,
2.231760;0.000000;-0.120739;,
2.013610;0.241490;0.120739;,
2.013610;0.000000;0.120739;,
2.013610;0.241490;-0.120739;,
2.013610;0.000000;-0.120739;,
2.231760;0.241490;0.120739;,
2.013610;0.241490;0.120739;,
2.013610;0.241490;-0.120739;,
2.231760;0.241490;-0.120739;,
2.028840;0.457980;-0.120739;,
2.233650;0.486340;-0.120739;,
2.028840;0.457980;0.120739;,
2.028840;0.457980;-0.120739;,
2.233650;0.486340;0.120739;,
2.028840;0.457980;0.120739;,
2.233650;0.486340;-0.120739;,
2.233650;0.486340;0.120739;,
2.030190;1.014500;-0.120739;,
2.235510;1.038160;-0.120739;,
2.030190;1.014500;0.120739;,
2.030190;1.014500;-0.120739;,
2.235510;1.038160;0.120739;,
2.030190;1.014500;0.120739;,
2.235510;1.038160;-0.120739;,
2.235510;1.038160;0.120739;,
2.043480;1.458752;-0.120739;,
2.257720;1.461304;-0.120739;,
2.043480;1.458752;0.120739;,
2.043480;1.458752;-0.120739;,
2.257720;1.461304;0.120739;,
2.043480;1.458752;0.120739;,
2.257720;1.461304;-0.120739;,
2.257720;1.461304;0.120739;,
2.053230;1.677541;-0.120739;,
2.267240;1.666575;-0.120739;,
2.053230;1.677541;0.120739;,
2.053230;1.677541;-0.120739;,
2.267240;1.666575;0.120739;,
2.053230;1.677541;0.120739;,
2.267240;1.666575;-0.120739;,
2.267240;1.666575;0.120739;,
2.083770;1.731043;-0.089452;,
2.242330;1.722920;-0.089452;,
2.083770;1.731043;0.089459;,
2.242330;1.722920;0.089459;;

 280;
3;2,1,0;,
3;2,3,1;,
3;6,5,4;,
3;6,7,5;,
3;10,9,8;,
3;10,11,9;,
3;14,13,12;,
3;14,15,13;,
3;16,8,9;,
3;16,17,8;,
3;18,11,10;,
3;18,19,11;,
3;20,19,18;,
3;20,21,19;,
3;22,14,12;,
3;22,23,14;,
3;24,17,16;,
3;24,25,17;,
3;26,21,20;,
3;26,27,21;,
3;28,23,22;,
3;28,29,23;,
3;30,25,24;,
3;30,31,25;,
3;32,27,26;,
3;32,33,27;,
3;34,29,28;,
3;34,35,29;,
3;36,31,30;,
3;36,37,31;,
3;38,33,32;,
3;38,39,33;,
3;40,35,34;,
3;40,41,35;,
3;42,37,36;,
3;42,43,37;,
3;44,39,38;,
3;44,45,39;,
3;46,38,43;,
3;46,44,38;,
3;47,43,42;,
3;47,46,43;,
3;45,42,39;,
3;45,47,42;,
3;50,49,48;,
3;50,51,49;,
3;52,51,50;,
3;52,53,51;,
3;55,50,54;,
3;55,52,50;,
3;56,52,55;,
3;59,58,57;,
3;59,60,58;,
3;63,62,61;,
3;63,64,62;,
3;65,64,63;,
3;65,66,64;,
3;61,68,67;,
3;61,62,68;,
3;71,70,69;,
3;71,72,70;,
3;73,71,69;,
3;73,74,71;,
3;75,65,63;,
3;75,76,65;,
3;79,78,77;,
3;79,80,78;,
3;81,61,67;,
3;81,82,61;,
3;83,74,73;,
3;83,84,74;,
3;85,76,75;,
3;85,86,76;,
3;87,80,79;,
3;87,88,80;,
3;89,82,81;,
3;89,90,82;,
3;91,84,83;,
3;91,92,84;,
3;93,86,85;,
3;93,94,86;,
3;95,88,87;,
3;95,96,88;,
3;97,90,89;,
3;97,98,90;,
3;99,92,91;,
3;99,100,92;,
3;101,94,93;,
3;101,102,94;,
3;103,96,95;,
3;103,104,96;,
3;105,98,97;,
3;105,106,98;,
3;107,100,99;,
3;107,108,100;,
3;109,102,101;,
3;109,110,102;,
3;111,104,103;,
3;111,112,104;,
3;113,106,105;,
3;113,114,106;,
3;115,108,107;,
3;115,116,108;,
3;117,110,109;,
3;117,118,110;,
3;119,112,111;,
3;119,120,112;,
3;121,114,113;,
3;121,122,114;,
3;123,116,115;,
3;123,124,116;,
3;125,118,117;,
3;125,126,118;,
3;127,120,119;,
3;127,128,120;,
3;129,122,121;,
3;129,130,122;,
3;131,124,123;,
3;131,132,124;,
3;133,126,125;,
3;133,134,126;,
3;135,128,127;,
3;135,136,128;,
3;137,130,129;,
3;137,138,130;,
3;139,132,131;,
3;139,140,132;,
3;60,134,133;,
3;60,59,134;,
3;141,136,135;,
3;141,142,136;,
3;57,138,137;,
3;57,58,138;,
3;145,144,143;,
3;145,49,144;,
3;48,49,145;,
3;143,54,145;,
3;143,55,54;,
3;146,5,7;,
3;146,147,5;,
3;148,147,146;,
3;148,149,147;,
3;149,151,150;,
3;149,148,151;,
3;150,147,149;,
3;150,144,147;,
3;152,144,150;,
3;152,143,144;,
3;153,143,152;,
3;153,55,143;,
3;156,155,154;,
3;156,157,155;,
3;151,55,153;,
3;151,56,55;,
3;148,56,151;,
3;148,146,56;,
3;160,159,158;,
3;160,161,159;,
3;164,163,162;,
3;164,165,163;,
3;168,167,166;,
3;168,169,167;,
3;166,165,164;,
3;166,167,165;,
3;172,171,170;,
3;172,173,171;,
3;174,164,162;,
3;174,175,164;,
3;176,160,158;,
3;176,177,160;,
3;178,168,166;,
3;178,179,168;,
3;180,173,172;,
3;180,181,173;,
3;182,175,174;,
3;182,183,175;,
3;184,177,176;,
3;184,185,177;,
3;186,179,178;,
3;186,187,179;,
3;188,181,180;,
3;188,189,181;,
3;190,183,182;,
3;190,191,183;,
3;192,185,184;,
3;192,193,185;,
3;194,187,186;,
3;194,195,187;,
3;196,189,188;,
3;196,197,189;,
3;198,191,190;,
3;198,199,191;,
3;200,193,192;,
3;200,201,193;,
3;202,195,194;,
3;202,203,195;,
3;204,197,196;,
3;204,205,197;,
3;206,199,198;,
3;206,207,199;,
3;208,201,200;,
3;208,209,201;,
3;210,203,202;,
3;210,211,203;,
3;212,205,204;,
3;212,213,205;,
3;214,207,206;,
3;214,215,207;,
3;216,209,208;,
3;216,217,209;,
3;218,211,210;,
3;218,219,211;,
3;220,213,212;,
3;220,221,213;,
3;222,215,214;,
3;222,223,215;,
3;224,217,216;,
3;224,225,217;,
3;226,219,218;,
3;226,227,219;,
3;228,221,220;,
3;228,229,221;,
3;230,223,222;,
3;230,231,223;,
3;157,233,232;,
3;157,156,233;,
3;234,227,226;,
3;234,235,227;,
3;238,237,236;,
3;238,239,237;,
3;242,241,240;,
3;242,243,241;,
3;246,245,244;,
3;246,247,245;,
3;250,249,248;,
3;250,251,249;,
3;252,244,245;,
3;252,253,244;,
3;254,247,246;,
3;254,255,247;,
3;256,255,254;,
3;256,257,255;,
3;258,250,248;,
3;258,259,250;,
3;260,253,252;,
3;260,261,253;,
3;262,241,243;,
3;262,263,241;,
3;264,257,256;,
3;264,265,257;,
3;266,259,258;,
3;266,267,259;,
3;268,261,260;,
3;268,269,261;,
3;270,263,262;,
3;270,271,263;,
3;272,265,264;,
3;272,273,265;,
3;274,267,266;,
3;274,275,267;,
3;276,269,268;,
3;276,277,269;,
3;278,271,270;,
3;278,279,271;,
3;280,273,272;,
3;280,281,273;,
3;282,275,274;,
3;282,283,275;,
3;284,277,276;,
3;284,285,277;,
3;286,279,278;,
3;286,287,279;,
3;288,281,280;,
3;288,289,281;,
3;290,280,285;,
3;290,288,280;,
3;291,285,284;,
3;291,290,285;,
3;289,284,281;,
3;289,291,284;;
MeshMaterialList {
 1;
 280;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
"fence3.bmp";
}
 }
}

 MeshNormals {
 292;
0.327567;0.900389;0.286356;,
-0.244507;0.926401;0.286353;,
0.327563;0.900401;-0.286324;,
-0.244501;0.926412;-0.286321;,
0.577350;-0.577350;0.577350;,
0.705698;0.036405;0.707576;,
0.577350;-0.577350;-0.577350;,
0.705698;0.036405;-0.707576;,
-0.577350;-0.577350;0.577350;,
0.577350;-0.577350;0.577350;,
-0.577350;-0.577350;-0.577350;,
0.577350;-0.577350;-0.577350;,
-0.705538;-0.038423;0.707630;,
-0.577350;-0.577350;0.577350;,
-0.705538;-0.038423;-0.707630;,
-0.577350;-0.577350;-0.577350;,
0.705698;0.036405;0.707576;,
-0.705538;-0.038423;0.707630;,
-0.705538;-0.038423;-0.707630;,
0.705698;0.036405;-0.707576;,
-0.702069;-0.084095;-0.707126;,
0.703803;0.068199;-0.707114;,
-0.702069;-0.084095;0.707126;,
-0.702069;-0.084095;-0.707126;,
0.702287;0.082147;0.707138;,
-0.702069;-0.084095;0.707126;,
-0.703542;-0.069125;-0.707284;,
0.719240;0.075907;-0.690603;,
-0.703542;-0.069125;0.707284;,
-0.703542;-0.069125;-0.707284;,
0.703516;0.069405;0.707282;,
-0.703542;-0.069125;0.707284;,
-0.706522;-0.007676;-0.707649;,
0.730812;0.026922;-0.682047;,
-0.706522;-0.007676;0.707649;,
-0.706522;-0.007676;-0.707649;,
0.697146;0.007183;0.716894;,
-0.706522;-0.007676;0.707649;,
-0.596957;0.509776;-0.619493;,
0.647831;0.458861;-0.608080;,
-0.596957;0.509748;0.619515;,
-0.596957;0.509776;-0.619493;,
0.633140;0.448430;0.630907;,
-0.596957;0.509748;0.619515;,
-0.244501;0.926412;-0.286321;,
0.327563;0.900401;-0.286324;,
-0.244507;0.926401;0.286353;,
0.327567;0.900389;0.286356;,
0.796489;0.420571;0.434425;,
0.697146;0.007183;0.716894;,
0.814017;0.454254;-0.361980;,
0.633140;0.448430;0.630907;,
0.730812;0.026922;-0.682047;,
0.647831;0.458861;-0.608080;,
0.858893;-0.344922;-0.378593;,
0.995807;0.088356;0.023714;,
0.719240;0.075907;-0.690603;,
0.599407;-0.554258;0.577503;,
0.554353;0.599589;0.577223;,
0.599407;-0.554258;-0.577503;,
0.554353;0.599589;-0.577223;,
-0.026344;0.706461;0.707262;,
0.796489;0.420571;0.434425;,
-0.026344;0.706461;-0.707262;,
0.814017;0.454254;-0.361980;,
0.025644;-0.706476;-0.707272;,
0.858893;-0.344922;-0.378593;,
0.025644;-0.706476;0.707272;,
0.840436;-0.357389;0.407357;,
0.025644;-0.706476;-0.707272;,
0.858893;-0.344922;-0.378593;,
0.025644;-0.706476;0.707272;,
0.840436;-0.357389;0.407357;,
-0.011582;-0.706926;-0.707193;,
-0.011582;-0.706926;0.707193;,
0.010868;0.706929;-0.707201;,
-0.011582;-0.706926;-0.707193;,
-0.026344;0.706461;0.707262;,
-0.026344;0.706461;-0.707262;,
0.010868;0.706929;0.707201;,
0.010868;0.706929;-0.707201;,
-0.011582;-0.706926;0.707193;,
0.010868;0.706929;0.707201;,
-0.013589;-0.706911;-0.707172;,
-0.013589;-0.706911;0.707172;,
0.013590;0.706911;-0.707172;,
-0.013589;-0.706911;-0.707172;,
0.013590;0.706911;0.707172;,
0.013590;0.706911;-0.707172;,
-0.013589;-0.706911;0.707172;,
0.013590;0.706911;0.707172;,
0.017438;-0.706784;-0.707214;,
0.017438;-0.706784;0.707214;,
-0.017445;0.706784;-0.707215;,
0.017438;-0.706784;-0.707214;,
-0.017445;0.706784;0.707215;,
-0.017445;0.706784;-0.707215;,
0.017438;-0.706784;0.707214;,
-0.017445;0.706784;0.707215;,
0.024221;-0.706652;-0.707147;,
0.024221;-0.706652;0.707147;,
-0.024253;0.706651;-0.707147;,
0.024221;-0.706652;-0.707147;,
-0.024253;0.706651;0.707147;,
-0.024253;0.706651;-0.707147;,
0.024221;-0.706652;0.707147;,
-0.024253;0.706651;0.707147;,
0.006790;-0.707058;-0.707123;,
0.006790;-0.707058;0.707123;,
-0.006806;0.707058;-0.707123;,
0.006790;-0.707058;-0.707123;,
-0.006806;0.707058;0.707123;,
-0.006806;0.707058;-0.707123;,
0.006790;-0.707058;0.707123;,
-0.006806;0.707058;0.707123;,
0.001076;-0.707106;-0.707107;,
0.001076;-0.707106;0.707107;,
-0.001079;0.707106;-0.707107;,
0.001076;-0.707106;-0.707107;,
-0.001079;0.707106;0.707107;,
-0.001079;0.707106;-0.707107;,
0.001076;-0.707106;0.707107;,
-0.001079;0.707106;0.707107;,
-0.005576;-0.707064;-0.707128;,
-0.005576;-0.707064;0.707128;,
0.005609;0.707063;-0.707128;,
-0.005576;-0.707064;-0.707128;,
0.005609;0.707064;0.707128;,
0.005609;0.707063;-0.707128;,
-0.005576;-0.707064;0.707128;,
0.005609;0.707064;0.707128;,
0.007033;-0.706925;-0.707253;,
0.007033;-0.706925;0.707253;,
-0.007048;0.706924;-0.707255;,
0.007033;-0.706925;-0.707253;,
-0.007048;0.706924;0.707254;,
-0.007048;0.706924;-0.707255;,
0.007033;-0.706925;0.707253;,
-0.007048;0.706924;0.707254;,
0.599407;-0.554258;-0.577503;,
0.599407;-0.554258;0.577503;,
0.554353;0.599589;0.577223;,
0.554353;0.599589;-0.577223;,
0.996381;0.085003;0.000000;,
0.703516;0.069405;0.707282;,
0.840436;-0.357389;0.407357;,
0.703803;0.068199;-0.707114;,
0.702287;0.082147;0.707138;,
0.993771;0.111439;-0.000008;,
0.992210;0.124576;-0.000008;,
0.844152;-0.320029;0.430103;,
0.851063;-0.301881;-0.429604;,
0.778313;0.482195;0.402141;,
0.772002;0.496952;-0.396296;,
0.591042;0.559294;0.581258;,
0.576514;0.592371;-0.562786;,
0.562275;-0.594019;0.575316;,
0.580830;-0.562753;-0.588171;,
-0.001050;-0.683364;-0.730077;,
0.851063;-0.301881;-0.429604;,
0.000591;-0.711906;0.702274;,
0.844152;-0.320029;0.430103;,
0.000591;-0.711906;0.702274;,
0.844152;-0.320029;0.430103;,
-0.024152;0.699997;0.713737;,
0.778313;0.482195;0.402141;,
-0.024756;0.731320;-0.681585;,
0.772002;0.496952;-0.396296;,
-0.001050;-0.683364;-0.730077;,
0.851063;-0.301881;-0.429604;,
-0.024152;0.699997;0.713737;,
-0.024756;0.731320;-0.681585;,
-0.006712;0.700522;0.713599;,
-0.006927;0.731363;-0.681953;,
0.005099;-0.711777;0.702387;,
-0.006712;0.700522;0.713599;,
0.004834;-0.683763;-0.729688;,
0.005099;-0.711777;0.702387;,
-0.006927;0.731363;-0.681953;,
0.004834;-0.683763;-0.729688;,
0.002523;0.700603;0.713547;,
0.002604;0.731290;-0.682062;,
-0.002479;-0.711761;0.702417;,
0.002523;0.700603;0.713547;,
-0.002406;-0.683904;-0.729568;,
-0.002479;-0.711761;0.702417;,
0.002604;0.731290;-0.682062;,
-0.002406;-0.683904;-0.729568;,
-0.013672;0.700349;0.713670;,
-0.014303;0.731039;-0.682185;,
0.013965;-0.711523;0.702524;,
-0.013672;0.700349;0.713670;,
0.013391;-0.683629;-0.729707;,
0.013965;-0.711523;0.702524;,
-0.014303;0.731039;-0.682185;,
0.013391;-0.683629;-0.729707;,
-0.019647;0.700263;0.713614;,
-0.020533;0.730957;-0.682114;,
0.019966;-0.711443;0.702460;,
-0.019647;0.700263;0.713614;,
0.019158;-0.683575;-0.729629;,
0.019966;-0.711443;0.702460;,
-0.020533;0.730957;-0.682114;,
0.019158;-0.683575;-0.729629;,
0.000163;0.700591;0.713563;,
0.000138;0.731270;-0.682088;,
-0.000136;-0.711750;0.702433;,
0.000163;0.700591;0.713563;,
-0.000161;-0.683901;-0.729574;,
-0.000136;-0.711750;0.702433;,
0.000138;0.731270;-0.682088;,
-0.000161;-0.683901;-0.729574;,
-0.003842;0.700554;0.713589;,
-0.004041;0.731233;-0.682115;,
0.003941;-0.711713;0.702459;,
-0.003842;0.700554;0.713589;,
0.003757;-0.683864;-0.729600;,
0.003941;-0.711713;0.702459;,
-0.004041;0.731233;-0.682115;,
0.003757;-0.683864;-0.729600;,
-0.000784;0.700524;0.713628;,
-0.000844;0.731230;-0.682131;,
0.000811;-0.711708;0.702475;,
-0.000784;0.700524;0.713628;,
0.000753;-0.683832;-0.729639;,
0.000811;-0.711708;0.702475;,
-0.000844;0.731230;-0.682131;,
0.000753;-0.683832;-0.729639;,
0.591042;0.559294;0.581258;,
0.576514;0.592371;-0.562786;,
0.562275;-0.594019;0.575316;,
0.591042;0.559294;0.581258;,
0.000753;-0.683832;-0.729639;,
0.000811;-0.711708;0.702475;,
0.576514;0.592371;-0.562786;,
0.580830;-0.562753;-0.588171;,
0.429054;0.821161;0.376308;,
-0.342873;0.860717;0.376304;,
0.429047;0.821176;-0.376283;,
-0.342864;0.860731;-0.376279;,
0.577350;-0.577350;0.577350;,
0.707099;-0.002729;0.707109;,
0.577350;-0.577350;-0.577350;,
0.707099;-0.002729;-0.707109;,
-0.577350;-0.577350;0.577350;,
0.577350;-0.577350;0.577350;,
-0.577350;-0.577350;-0.577350;,
0.577350;-0.577350;-0.577350;,
-0.706453;0.024819;0.707325;,
-0.577350;-0.577350;0.577350;,
-0.706453;0.024819;-0.707325;,
-0.577350;-0.577350;-0.577350;,
0.707099;-0.002729;0.707109;,
-0.706453;0.024819;0.707325;,
-0.706453;0.024819;-0.707325;,
0.707099;-0.002729;-0.707109;,
-0.706437;0.025676;-0.707310;,
0.707095;-0.003921;-0.707108;,
-0.706437;0.025676;0.707310;,
-0.706437;0.025676;-0.707310;,
0.707095;-0.003921;0.707108;,
-0.706437;0.025676;0.707310;,
0.707095;-0.003921;-0.707108;,
0.707095;-0.003921;0.707108;,
-0.706981;0.011430;-0.707140;,
0.706725;-0.019727;-0.707213;,
-0.706981;0.011430;0.707140;,
-0.706981;0.011430;-0.707140;,
0.706725;-0.019727;0.707213;,
-0.706981;0.011430;0.707140;,
0.706725;-0.019727;-0.707213;,
0.706725;-0.019727;0.707213;,
-0.706608;0.026312;-0.707116;,
0.706243;-0.034911;-0.707108;,
-0.706608;0.026312;0.707116;,
-0.706608;0.026312;-0.707116;,
0.706243;-0.034911;0.707108;,
-0.706608;0.026312;0.707116;,
0.706243;-0.034911;-0.707108;,
0.706243;-0.034911;0.707108;,
-0.653072;0.366596;-0.662650;,
0.686400;0.301577;-0.661744;,
-0.653073;0.366570;0.662663;,
-0.653072;0.366596;-0.662650;,
0.686398;0.301551;0.661758;,
-0.653073;0.366570;0.662663;,
0.686400;0.301577;-0.661744;,
0.686398;0.301551;0.661758;,
-0.342864;0.860731;-0.376279;,
0.429047;0.821176;-0.376283;,
-0.342873;0.860717;0.376304;,
0.429054;0.821161;0.376308;;

 280;
3;2,1,0;,
3;2,3,1;,
3;6,5,4;,
3;6,7,5;,
3;10,9,8;,
3;10,11,9;,
3;14,13,12;,
3;14,15,13;,
3;16,8,9;,
3;16,17,8;,
3;18,11,10;,
3;18,19,11;,
3;20,19,18;,
3;20,21,19;,
3;22,14,12;,
3;22,23,14;,
3;24,17,16;,
3;24,25,17;,
3;26,21,20;,
3;26,27,21;,
3;28,23,22;,
3;28,29,23;,
3;30,25,24;,
3;30,31,25;,
3;32,27,26;,
3;32,33,27;,
3;34,29,28;,
3;34,35,29;,
3;36,31,30;,
3;36,37,31;,
3;38,33,32;,
3;38,39,33;,
3;40,35,34;,
3;40,41,35;,
3;42,37,36;,
3;42,43,37;,
3;44,39,38;,
3;44,45,39;,
3;46,38,43;,
3;46,44,38;,
3;47,43,42;,
3;47,46,43;,
3;45,42,39;,
3;45,47,42;,
3;50,49,48;,
3;50,51,49;,
3;52,51,50;,
3;52,53,51;,
3;55,50,54;,
3;55,52,50;,
3;56,52,55;,
3;59,58,57;,
3;59,60,58;,
3;63,62,61;,
3;63,64,62;,
3;65,64,63;,
3;65,66,64;,
3;61,68,67;,
3;61,62,68;,
3;71,70,69;,
3;71,72,70;,
3;73,71,69;,
3;73,74,71;,
3;75,65,63;,
3;75,76,65;,
3;79,78,77;,
3;79,80,78;,
3;81,61,67;,
3;81,82,61;,
3;83,74,73;,
3;83,84,74;,
3;85,76,75;,
3;85,86,76;,
3;87,80,79;,
3;87,88,80;,
3;89,82,81;,
3;89,90,82;,
3;91,84,83;,
3;91,92,84;,
3;93,86,85;,
3;93,94,86;,
3;95,88,87;,
3;95,96,88;,
3;97,90,89;,
3;97,98,90;,
3;99,92,91;,
3;99,100,92;,
3;101,94,93;,
3;101,102,94;,
3;103,96,95;,
3;103,104,96;,
3;105,98,97;,
3;105,106,98;,
3;107,100,99;,
3;107,108,100;,
3;109,102,101;,
3;109,110,102;,
3;111,104,103;,
3;111,112,104;,
3;113,106,105;,
3;113,114,106;,
3;115,108,107;,
3;115,116,108;,
3;117,110,109;,
3;117,118,110;,
3;119,112,111;,
3;119,120,112;,
3;121,114,113;,
3;121,122,114;,
3;123,116,115;,
3;123,124,116;,
3;125,118,117;,
3;125,126,118;,
3;127,120,119;,
3;127,128,120;,
3;129,122,121;,
3;129,130,122;,
3;131,124,123;,
3;131,132,124;,
3;133,126,125;,
3;133,134,126;,
3;135,128,127;,
3;135,136,128;,
3;137,130,129;,
3;137,138,130;,
3;139,132,131;,
3;139,140,132;,
3;60,134,133;,
3;60,59,134;,
3;141,136,135;,
3;141,142,136;,
3;57,138,137;,
3;57,58,138;,
3;145,144,143;,
3;145,49,144;,
3;48,49,145;,
3;143,54,145;,
3;143,55,54;,
3;146,5,7;,
3;146,147,5;,
3;148,147,146;,
3;148,149,147;,
3;149,151,150;,
3;149,148,151;,
3;150,147,149;,
3;150,144,147;,
3;152,144,150;,
3;152,143,144;,
3;153,143,152;,
3;153,55,143;,
3;156,155,154;,
3;156,157,155;,
3;151,55,153;,
3;151,56,55;,
3;148,56,151;,
3;148,146,56;,
3;160,159,158;,
3;160,161,159;,
3;164,163,162;,
3;164,165,163;,
3;168,167,166;,
3;168,169,167;,
3;166,165,164;,
3;166,167,165;,
3;172,171,170;,
3;172,173,171;,
3;174,164,162;,
3;174,175,164;,
3;176,160,158;,
3;176,177,160;,
3;178,168,166;,
3;178,179,168;,
3;180,173,172;,
3;180,181,173;,
3;182,175,174;,
3;182,183,175;,
3;184,177,176;,
3;184,185,177;,
3;186,179,178;,
3;186,187,179;,
3;188,181,180;,
3;188,189,181;,
3;190,183,182;,
3;190,191,183;,
3;192,185,184;,
3;192,193,185;,
3;194,187,186;,
3;194,195,187;,
3;196,189,188;,
3;196,197,189;,
3;198,191,190;,
3;198,199,191;,
3;200,193,192;,
3;200,201,193;,
3;202,195,194;,
3;202,203,195;,
3;204,197,196;,
3;204,205,197;,
3;206,199,198;,
3;206,207,199;,
3;208,201,200;,
3;208,209,201;,
3;210,203,202;,
3;210,211,203;,
3;212,205,204;,
3;212,213,205;,
3;214,207,206;,
3;214,215,207;,
3;216,209,208;,
3;216,217,209;,
3;218,211,210;,
3;218,219,211;,
3;220,213,212;,
3;220,221,213;,
3;222,215,214;,
3;222,223,215;,
3;224,217,216;,
3;224,225,217;,
3;226,219,218;,
3;226,227,219;,
3;228,221,220;,
3;228,229,221;,
3;230,223,222;,
3;230,231,223;,
3;157,233,232;,
3;157,156,233;,
3;234,227,226;,
3;234,235,227;,
3;238,237,236;,
3;238,239,237;,
3;242,241,240;,
3;242,243,241;,
3;246,245,244;,
3;246,247,245;,
3;250,249,248;,
3;250,251,249;,
3;252,244,245;,
3;252,253,244;,
3;254,247,246;,
3;254,255,247;,
3;256,255,254;,
3;256,257,255;,
3;258,250,248;,
3;258,259,250;,
3;260,253,252;,
3;260,261,253;,
3;262,241,243;,
3;262,263,241;,
3;264,257,256;,
3;264,265,257;,
3;266,259,258;,
3;266,267,259;,
3;268,261,260;,
3;268,269,261;,
3;270,263,262;,
3;270,271,263;,
3;272,265,264;,
3;272,273,265;,
3;274,267,266;,
3;274,275,267;,
3;276,269,268;,
3;276,277,269;,
3;278,271,270;,
3;278,279,271;,
3;280,273,272;,
3;280,281,273;,
3;282,275,274;,
3;282,283,275;,
3;284,277,276;,
3;284,285,277;,
3;286,279,278;,
3;286,287,279;,
3;288,281,280;,
3;288,289,281;,
3;290,280,285;,
3;290,288,280;,
3;291,285,284;,
3;291,290,285;,
3;289,284,281;,
3;289,291,284;;
 }
MeshTextureCoords {
 292;
0.151718;0.519265;,
0.126106;0.519265;,
0.151718;0.555275;,
0.126106;0.555275;,
0.053061;0.205006;,
0.053061;0.258614;,
0.076525;0.205006;,
0.076525;0.258614;,
0.065017;0.846035;,
0.104338;0.846035;,
0.065017;0.846035;,
0.104338;0.846035;,
0.053061;0.258614;,
0.053061;0.205006;,
0.076525;0.258614;,
0.076525;0.205006;,
0.104338;0.735405;,
0.065017;0.735405;,
0.065017;0.735405;,
0.104338;0.735405;,
0.059971;0.653738;,
0.098933;0.643040;,
0.053061;0.306673;,
0.076525;0.306673;,
0.098933;0.643040;,
0.059971;0.653738;,
0.044493;0.443800;,
0.083564;0.434875;,
0.053061;0.430216;,
0.076525;0.430216;,
0.083564;0.434875;,
0.044493;0.443800;,
0.038202;0.276214;,
0.077517;0.275251;,
0.053061;0.528837;,
0.076525;0.528837;,
0.077517;0.275251;,
0.038202;0.276214;,
0.040283;0.193679;,
0.079548;0.197816;,
0.053061;0.577406;,
0.076525;0.577406;,
0.079548;0.197816;,
0.040283;0.193679;,
0.049340;0.177752;,
0.071346;0.180502;,
0.049340;0.177752;,
0.071346;0.180502;,
0.058721;0.514906;,
0.053061;0.529403;,
0.068527;0.514906;,
0.053061;0.574972;,
0.076525;0.529403;,
0.076525;0.574972;,
0.068527;0.484721;,
0.068527;0.435469;,
0.076525;0.435469;,
0.893515;0.319929;,
0.892360;0.287161;,
0.893515;0.319929;,
0.892360;0.287161;,
0.097456;0.297525;,
0.077517;0.299886;,
0.097456;0.297525;,
0.077517;0.299886;,
0.100962;0.329961;,
0.081022;0.332321;,
0.100962;0.329961;,
0.081022;0.332321;,
0.173890;0.545893;,
0.158962;0.545893;,
0.173890;0.523252;,
0.158962;0.523252;,
0.240594;0.545893;,
0.240594;0.523252;,
0.180763;0.296261;,
0.180300;0.329063;,
0.171265;0.523252;,
0.171265;0.545893;,
0.240941;0.523252;,
0.240941;0.545893;,
0.180300;0.329063;,
0.180763;0.296261;,
0.285665;0.545893;,
0.285665;0.523252;,
0.241067;0.300360;,
0.240506;0.333159;,
0.286086;0.523252;,
0.286086;0.545893;,
0.240506;0.333159;,
0.241067;0.300360;,
0.354675;0.545893;,
0.354675;0.523252;,
0.331967;0.300363;,
0.332688;0.333155;,
0.354135;0.523252;,
0.354135;0.545893;,
0.332688;0.333155;,
0.331967;0.300363;,
0.425044;0.545893;,
0.425044;0.523252;,
0.425685;0.292176;,
0.426687;0.324954;,
0.424294;0.523252;,
0.424294;0.545893;,
0.426687;0.324954;,
0.425685;0.292176;,
0.469882;0.545893;,
0.469882;0.523252;,
0.486301;0.290114;,
0.486582;0.322919;,
0.469672;0.523252;,
0.469672;0.545893;,
0.486582;0.322919;,
0.486301;0.290114;,
0.526161;0.545893;,
0.526161;0.523252;,
0.561759;0.290113;,
0.561759;0.322920;,
0.526161;0.523252;,
0.526161;0.545893;,
0.561759;0.322920;,
0.561759;0.290113;,
0.654313;0.545893;,
0.654313;0.523252;,
0.733175;0.289190;,
0.732945;0.321997;,
0.654487;0.523252;,
0.654486;0.545893;,
0.732945;0.321997;,
0.733177;0.289190;,
0.746463;0.545893;,
0.746463;0.523252;,
0.861841;0.293288;,
0.862142;0.326093;,
0.746238;0.523252;,
0.746238;0.545893;,
0.862142;0.326093;,
0.861841;0.293288;,
0.813846;0.545893;,
0.813846;0.523252;,
0.812981;0.523252;,
0.812981;0.545893;,
0.058721;0.435469;,
0.053061;0.435469;,
0.058721;0.484721;,
0.076525;0.312969;,
0.053061;0.312969;,
0.071614;0.312969;,
0.059471;0.312969;,
0.059140;0.362480;,
0.070252;0.362398;,
0.058889;0.395823;,
0.069218;0.395865;,
0.058897;0.404168;,
0.069226;0.404210;,
0.059147;0.369546;,
0.070260;0.369462;,
0.177512;0.549875;,
0.167293;0.549875;,
0.177504;0.524219;,
0.167285;0.524219;,
0.105791;0.559211;,
0.092139;0.558905;,
0.100661;0.513087;,
0.087007;0.514264;,
0.100655;0.513016;,
0.087003;0.514193;,
0.105801;0.559351;,
0.092150;0.559045;,
0.173664;0.523640;,
0.173660;0.547488;,
0.222588;0.523642;,
0.222589;0.547491;,
0.156529;0.557691;,
0.156248;0.510865;,
0.222797;0.549878;,
0.222798;0.524221;,
0.156248;0.510794;,
0.156527;0.557834;,
0.278296;0.523645;,
0.278297;0.547491;,
0.230664;0.557695;,
0.230662;0.510865;,
0.278296;0.549878;,
0.278297;0.524221;,
0.230663;0.510794;,
0.230661;0.557834;,
0.317044;0.523645;,
0.317044;0.547493;,
0.283073;0.558340;,
0.282420;0.511522;,
0.317532;0.549880;,
0.317532;0.524223;,
0.282421;0.511450;,
0.283073;0.558479;,
0.403599;0.523647;,
0.403599;0.547495;,
0.398975;0.548867;,
0.398040;0.502065;,
0.404299;0.549882;,
0.404299;0.524226;,
0.398040;0.501993;,
0.398976;0.549011;,
0.530788;0.523651;,
0.530790;0.547499;,
0.567936;0.545917;,
0.567940;0.499088;,
0.530784;0.549884;,
0.530785;0.524228;,
0.567943;0.499017;,
0.567934;0.546057;,
0.627898;0.523654;,
0.627898;0.547502;,
0.697843;0.548283;,
0.697659;0.501457;,
0.628035;0.549889;,
0.628035;0.524232;,
0.697659;0.501386;,
0.697843;0.548426;,
0.725753;0.523656;,
0.725753;0.547504;,
0.828408;0.543356;,
0.828374;0.496527;,
0.725777;0.549891;,
0.725779;0.524235;,
0.828374;0.496455;,
0.828406;0.543496;,
0.804787;0.523658;,
0.804789;0.547506;,
0.870712;0.546898;,
0.871354;0.500084;,
0.070259;0.371548;,
0.059146;0.371630;,
0.871356;0.500013;,
0.870708;0.547042;,
0.838106;0.517201;,
0.812779;0.517201;,
0.838106;0.557340;,
0.812779;0.557340;,
0.053061;0.205006;,
0.053061;0.258614;,
0.076525;0.205006;,
0.076525;0.258614;,
0.935756;0.826503;,
0.973759;0.826503;,
0.935756;0.826503;,
0.973759;0.826503;,
0.053061;0.258614;,
0.053061;0.205006;,
0.076525;0.258614;,
0.076525;0.205006;,
0.973759;0.735405;,
0.935756;0.735405;,
0.935756;0.735405;,
0.973759;0.735405;,
0.939005;0.653738;,
0.974162;0.643040;,
0.053061;0.306673;,
0.076525;0.306673;,
0.974162;0.643040;,
0.939005;0.653738;,
0.076525;0.312969;,
0.053061;0.312969;,
0.939294;0.443800;,
0.974559;0.434875;,
0.053061;0.430216;,
0.076525;0.430216;,
0.974559;0.434875;,
0.939294;0.443800;,
0.076525;0.435469;,
0.053061;0.435469;,
0.942129;0.276214;,
0.979298;0.275251;,
0.053061;0.528837;,
0.076525;0.528837;,
0.979298;0.275251;,
0.942129;0.276214;,
0.076525;0.529403;,
0.053061;0.529403;,
0.944210;0.174148;,
0.981329;0.178285;,
0.053061;0.577406;,
0.076525;0.577406;,
0.981329;0.178285;,
0.944210;0.174148;,
0.076525;0.574972;,
0.053061;0.574972;,
0.944623;0.153965;,
0.976014;0.157030;,
0.944623;0.153965;,
0.976014;0.157030;;
}
}
 }
