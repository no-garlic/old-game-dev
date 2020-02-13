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
 219;
-3.263300;0.139150;-1.249860;,
-1.867080;1.231050;-1.540130;,
-3.262830;1.224480;-1.259860;,
-1.866440;0.000000;-1.381710;,
0.375875;1.225030;-1.298080;,
0.375665;0.135830;-1.252600;,
2.054590;1.226620;-1.498790;,
2.054540;0.102370;-1.283090;,
3.664020;1.226820;-1.478300;,
3.662300;0.065620;-1.318700;,
5.523880;1.223940;-1.216330;,
5.265820;0.170800;-1.218120;,
-1.861180;2.346030;-1.214840;,
-3.261870;2.346030;-1.214600;,
0.377265;2.347530;-1.258790;,
2.059720;2.350370;-1.388690;,
3.661910;2.346810;-1.225520;,
5.449120;2.346030;-1.214600;,
-1.860520;4.025820;-1.377950;,
-3.262570;4.025840;-1.275740;,
0.377655;4.027880;-1.214600;,
2.060270;4.027860;-1.219230;,
3.661640;4.027880;-1.360840;,
5.264360;4.027880;-1.360840;,
-1.859380;5.274330;-1.425340;,
-3.265820;5.273570;-1.522830;,
0.377655;5.275830;-1.216490;,
2.060320;5.275810;-1.332540;,
3.661640;5.275850;-1.214600;,
5.473460;5.275850;-1.214600;,
5.558220;6.574850;-1.215090;,
3.887290;7.715820;-1.253560;,
3.663320;6.575330;-1.299230;,
5.264390;7.970370;-1.214650;,
-4.211010;8.096970;-1.214600;,
-5.322500;6.574850;-1.214600;,
-4.256020;6.574880;-1.216080;,
-5.328530;7.970270;-1.214600;,
0.378315;6.575570;-1.261960;,
-0.846403;8.610070;-1.214600;,
-0.845477;6.582720;-1.530830;,
0.377655;8.768550;-1.214600;,
-1.450620;6.577390;-1.348340;,
-1.861180;7.970270;-1.214600;,
-1.860540;6.575970;-1.282470;,
-1.353950;8.575970;-1.214600;,
-3.262240;6.579010;-1.355100;,
-3.230130;6.579710;-1.361070;,
-3.151000;8.588770;-1.214600;,
-2.596190;7.988270;-1.214600;,
0.851135;6.574860;-1.359140;,
0.851135;8.653090;-1.214600;,
1.514090;6.575130;-1.471610;,
1.514390;8.340970;-1.310210;,
2.060110;6.576170;-1.269130;,
2.080920;7.974370;-1.219240;,
2.740550;6.576100;-1.280130;,
2.739240;7.913230;-1.214630;,
-4.385140;1.224160;-1.234260;,
-5.334520;0.174450;-1.214600;,
-4.385550;0.159121;-1.229920;,
-5.334520;1.223920;-1.214600;,
-4.384480;2.346030;-1.214600;,
-5.334520;2.346030;-1.214600;,
-4.384690;4.026960;-1.242300;,
-5.334370;4.027830;-1.216540;,
-4.375070;5.274840;-1.350300;,
-5.334520;5.275850;-1.214600;,
-3.263560;0.132890;1.157340;,
-5.334520;1.223920;1.115880;,
-3.263440;1.223480;1.172590;,
-5.334520;0.174450;1.115880;,
-1.866100;0.007760;1.275360;,
-1.866760;1.212950;1.457070;,
0.375105;0.127390;1.162210;,
0.375825;1.224450;1.205060;,
2.053440;0.083200;1.203580;,
2.056130;1.226420;1.677680;,
3.663340;1.225930;1.523010;,
5.267270;0.167200;1.122900;,
3.662300;0.061880;1.224320;,
5.524350;1.223960;1.118800;,
-5.334520;2.346030;1.115880;,
-3.265640;2.344520;1.234030;,
-1.862390;2.342550;1.347610;,
0.382515;2.353400;1.378070;,
2.059970;2.354080;1.472090;,
3.662270;2.346890;1.132430;,
5.449120;2.346030;1.115880;,
-5.334070;4.027850;1.121760;,
-3.275620;4.019600;1.617610;,
-1.847300;4.029280;1.683190;,
0.377795;4.029130;1.185990;,
2.060480;4.027080;1.158370;,
3.661640;4.027880;1.115880;,
5.264360;4.027880;1.115880;,
-5.334520;5.275850;1.115880;,
-3.268250;5.280350;1.506560;,
-1.857410;5.275900;1.454810;,
0.377265;5.275920;1.315230;,
2.011270;5.424380;1.422400;,
3.661640;5.275850;1.115880;,
5.473460;5.275850;1.115880;,
3.666510;6.579280;1.397960;,
5.558220;6.574850;1.116380;,
3.887510;7.717120;1.156240;,
5.264390;7.970370;1.115930;,
-4.256030;6.574880;1.117580;,
-3.151000;8.588770;1.115880;,
-3.262300;6.580750;1.278600;,
-4.211010;8.096970;1.115880;,
-5.322500;6.574850;1.115880;,
-5.328530;7.970270;1.115880;,
-0.845482;6.582660;1.412230;,
0.377655;8.768550;1.115880;,
0.377635;6.576720;1.166040;,
-0.846403;8.610070;1.115880;,
-1.449350;6.577310;1.234270;,
-1.353950;8.575970;1.115880;,
-1.860060;6.576900;1.204670;,
-1.861180;7.970270;1.115880;,
-3.228460;6.581690;1.429730;,
-2.596190;7.988270;1.259110;,
0.851135;8.653090;1.115880;,
0.851125;6.574870;1.116330;,
1.513110;6.576450;1.140660;,
2.080950;7.974470;1.120550;,
2.060350;6.581640;1.174360;,
1.514390;8.340970;1.115880;,
2.743820;6.580070;1.377820;,
2.739240;7.913230;1.115890;,
5.265820;0.170800;-1.218120;,
5.524350;1.223960;1.118800;,
5.523880;1.223940;-1.216330;,
5.267270;0.167200;1.122900;,
-5.334520;1.223920;1.115880;,
-5.334520;0.174450;-1.214600;,
-5.334520;1.223920;-1.214600;,
-5.334520;0.174450;1.115880;,
5.449120;2.346030;1.115880;,
5.449120;2.346030;-1.214600;,
-5.334520;2.346030;-1.214600;,
-5.334520;2.346030;1.115880;,
5.264360;4.027880;1.115880;,
5.264360;4.027880;-1.360840;,
-5.334370;4.027830;-1.216540;,
-5.334070;4.027850;1.121760;,
5.473460;5.275850;1.115880;,
5.473460;5.275850;-1.214600;,
-5.334520;5.275850;-1.214600;,
-5.334520;5.275850;1.115880;,
5.558220;6.574850;1.116380;,
5.558220;6.574850;-1.215090;,
-5.322500;6.574850;-1.214600;,
-5.322500;6.574850;1.115880;,
3.887290;7.715820;-1.253560;,
5.264390;8.279020;-0.489568;,
3.887360;8.024870;-0.528478;,
5.264390;7.970370;-1.214650;,
-4.211010;8.405620;-0.489518;,
-5.328530;7.970270;-1.214600;,
-4.211010;8.096970;-1.214600;,
-5.328530;8.278920;-0.489518;,
-3.151000;8.897420;-0.489518;,
-3.151000;8.588770;-1.214600;,
-0.846403;8.610070;-1.214600;,
0.377655;9.077200;-0.489518;,
-0.846403;8.918720;-0.489518;,
0.377655;8.768550;-1.214600;,
-1.861180;7.970270;-1.214600;,
-1.353950;8.884620;-0.489518;,
-1.861180;8.278920;-0.489518;,
-1.353950;8.575970;-1.214600;,
-2.596190;8.296920;-0.489518;,
-2.596190;7.988270;-1.214600;,
0.851135;8.961740;-0.489518;,
0.851135;8.653090;-1.214600;,
1.514390;8.649620;-0.585128;,
1.514390;8.340970;-1.310210;,
2.080930;8.283050;-0.494158;,
2.080920;7.974370;-1.219240;,
2.739240;8.221880;-0.489548;,
2.739240;7.913230;-1.214630;,
5.264390;8.434510;0.478584;,
3.887510;7.717120;1.156240;,
3.887450;8.180880;0.439674;,
5.264390;7.970370;1.115930;,
5.264390;7.970370;-1.214650;,
5.264390;8.279020;-0.489568;,
5.264390;7.970370;1.115930;,
5.264390;8.434510;0.478584;,
-5.328530;7.970270;-1.214600;,
-5.328530;7.970270;1.115880;,
-5.328530;8.278920;-0.489518;,
-5.328530;8.278920;0.478634;,
-4.211010;8.405620;0.478634;,
-5.328530;8.278920;0.478634;,
-4.211010;8.096970;1.115880;,
-5.328530;7.970270;1.115880;,
-3.151000;8.897420;0.478634;,
-3.151000;8.588770;1.115880;,
0.377655;9.077200;0.478634;,
-0.846403;8.610070;1.115880;,
-0.846403;8.918720;0.478634;,
0.377655;8.768550;1.115880;,
-1.353950;8.884620;0.478634;,
-1.861180;7.970270;1.115880;,
-1.861180;8.278920;0.478634;,
-1.353950;8.575970;1.115880;,
-2.596190;8.296920;0.478634;,
-2.596190;7.988270;1.259110;,
0.851135;8.961740;0.478634;,
0.851135;8.653090;1.115880;,
1.514390;8.649620;0.383025;,
1.514390;8.340970;1.115880;,
2.080940;8.283090;0.473994;,
2.080950;7.974470;1.120550;,
2.739240;8.221880;0.478604;,
2.739240;7.913230;1.115890;;

 301;
3;2,1,0;,
3;1,3,0;,
3;1,4,3;,
3;4,5,3;,
3;4,6,5;,
3;6,7,5;,
3;6,8,7;,
3;8,9,7;,
3;8,10,9;,
3;10,11,9;,
3;13,12,2;,
3;12,1,2;,
3;12,14,1;,
3;14,4,1;,
3;14,15,4;,
3;15,6,4;,
3;15,16,6;,
3;16,8,6;,
3;16,17,8;,
3;17,10,8;,
3;19,18,13;,
3;18,12,13;,
3;18,20,12;,
3;20,14,12;,
3;20,21,14;,
3;21,15,14;,
3;21,22,15;,
3;22,16,15;,
3;22,23,16;,
3;23,17,16;,
3;25,24,19;,
3;24,18,19;,
3;24,26,18;,
3;26,20,18;,
3;26,27,20;,
3;27,21,20;,
3;27,28,21;,
3;28,22,21;,
3;28,29,22;,
3;29,23,22;,
3;32,31,30;,
3;31,33,30;,
3;32,30,28;,
3;30,29,28;,
3;36,35,34;,
3;35,37,34;,
3;40,39,38;,
3;39,41,38;,
3;44,43,42;,
3;43,45,42;,
3;42,45,40;,
3;45,39,40;,
3;40,38,42;,
3;38,26,42;,
3;42,26,44;,
3;26,24,44;,
3;47,44,46;,
3;44,24,46;,
3;46,24,25;,
3;46,48,47;,
3;48,49,47;,
3;47,49,44;,
3;49,43,44;,
3;38,41,50;,
3;41,51,50;,
3;50,51,52;,
3;51,53,52;,
3;52,53,54;,
3;53,55,54;,
3;52,54,50;,
3;54,27,50;,
3;50,27,38;,
3;27,26,38;,
3;54,55,56;,
3;55,57,56;,
3;56,57,32;,
3;57,31,32;,
3;56,32,54;,
3;32,28,54;,
3;54,28,27;,
3;60,59,58;,
3;59,61,58;,
3;60,58,0;,
3;58,2,0;,
3;58,61,62;,
3;61,63,62;,
3;58,62,2;,
3;62,13,2;,
3;62,63,64;,
3;63,65,64;,
3;62,64,13;,
3;64,19,13;,
3;64,65,66;,
3;65,67,66;,
3;64,66,19;,
3;66,25,19;,
3;66,67,36;,
3;67,35,36;,
3;66,36,25;,
3;36,46,25;,
3;36,34,46;,
3;34,48,46;,
3;70,69,68;,
3;69,71,68;,
3;73,70,72;,
3;70,68,72;,
3;75,73,74;,
3;73,72,74;,
3;77,75,76;,
3;75,74,76;,
3;80,79,78;,
3;79,81,78;,
3;78,77,80;,
3;77,76,80;,
3;83,82,70;,
3;82,69,70;,
3;84,83,73;,
3;83,70,73;,
3;85,84,75;,
3;84,73,75;,
3;86,85,77;,
3;85,75,77;,
3;78,81,87;,
3;81,88,87;,
3;87,86,78;,
3;86,77,78;,
3;90,89,83;,
3;89,82,83;,
3;91,90,84;,
3;90,83,84;,
3;92,91,85;,
3;91,84,85;,
3;93,92,86;,
3;92,85,86;,
3;87,88,94;,
3;88,95,94;,
3;94,93,87;,
3;93,86,87;,
3;97,96,90;,
3;96,89,90;,
3;98,97,91;,
3;97,90,91;,
3;99,98,92;,
3;98,91,92;,
3;100,99,93;,
3;99,92,93;,
3;94,95,101;,
3;95,102,101;,
3;101,100,94;,
3;100,93,94;,
3;101,102,103;,
3;102,104,103;,
3;103,104,105;,
3;104,106,105;,
3;109,108,107;,
3;108,110,107;,
3;107,110,111;,
3;110,112,111;,
3;107,111,109;,
3;111,96,109;,
3;109,96,97;,
3;115,114,113;,
3;114,116,113;,
3;113,116,117;,
3;116,118,117;,
3;117,118,119;,
3;118,120,119;,
3;117,119,113;,
3;119,98,113;,
3;113,98,115;,
3;98,99,115;,
3;121,109,119;,
3;109,97,119;,
3;119,97,98;,
3;119,120,121;,
3;120,122,121;,
3;121,122,109;,
3;122,108,109;,
3;124,123,115;,
3;123,114,115;,
3;127,126,125;,
3;126,128,125;,
3;125,128,124;,
3;128,123,124;,
3;124,115,125;,
3;115,99,125;,
3;125,99,127;,
3;99,100,127;,
3;103,105,129;,
3;105,130,129;,
3;129,130,127;,
3;130,126,127;,
3;129,127,103;,
3;127,100,103;,
3;103,100,101;,
3;133,132,131;,
3;132,134,131;,
3;137,136,135;,
3;136,138,135;,
3;140,139,133;,
3;139,132,133;,
3;137,135,141;,
3;135,142,141;,
3;144,143,140;,
3;143,139,140;,
3;141,142,145;,
3;142,146,145;,
3;148,147,144;,
3;147,143,144;,
3;145,146,149;,
3;146,150,149;,
3;152,151,148;,
3;151,147,148;,
3;149,150,153;,
3;150,154,153;,
3;157,156,155;,
3;156,158,155;,
3;161,160,159;,
3;160,162,159;,
3;159,163,161;,
3;163,164,161;,
3;167,166,165;,
3;166,168,165;,
3;171,170,169;,
3;170,172,169;,
3;170,167,172;,
3;167,165,172;,
3;163,173,164;,
3;173,174,164;,
3;173,171,174;,
3;171,169,174;,
3;166,175,168;,
3;175,176,168;,
3;175,177,176;,
3;177,178,176;,
3;177,179,178;,
3;179,180,178;,
3;179,181,180;,
3;181,182,180;,
3;181,157,182;,
3;157,155,182;,
3;185,184,183;,
3;184,186,183;,
3;185,183,157;,
3;183,156,157;,
3;152,187,151;,
3;187,188,151;,
3;151,188,189;,
3;188,190,189;,
3;153,154,191;,
3;154,192,191;,
3;191,192,193;,
3;192,194,193;,
3;159,162,195;,
3;162,196,195;,
3;195,196,197;,
3;196,198,197;,
3;195,197,199;,
3;197,200,199;,
3;195,199,159;,
3;199,163,159;,
3;203,202,201;,
3;202,204,201;,
3;203,201,167;,
3;201,166,167;,
3;207,206,205;,
3;206,208,205;,
3;207,205,171;,
3;205,170,171;,
3;205,208,203;,
3;208,202,203;,
3;205,203,170;,
3;203,167,170;,
3;199,200,209;,
3;200,210,209;,
3;199,209,163;,
3;209,173,163;,
3;209,210,207;,
3;210,206,207;,
3;209,207,173;,
3;207,171,173;,
3;201,204,211;,
3;204,212,211;,
3;201,211,166;,
3;211,175,166;,
3;211,212,213;,
3;212,214,213;,
3;211,213,175;,
3;213,177,175;,
3;213,214,215;,
3;214,216,215;,
3;213,215,177;,
3;215,179,177;,
3;215,216,217;,
3;216,218,217;,
3;215,217,179;,
3;217,181,179;,
3;217,218,185;,
3;218,184,185;,
3;217,185,181;,
3;185,157,181;;
MeshMaterialList {
 3;
 301;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
Material Material {
 0.988235;0.996078;1.000000;1.000000;;
128.000015;
 0.988235;0.996078;1.000000;;
 0.000000;0.000000;0.000000;;
TextureFilename {
"wall3.bmp";
}
 }
Material Material1 {
 0.976471;1.000000;0.996078;1.000000;;
128.000015;
 0.976471;1.000000;0.996078;;
 0.000000;0.000000;0.000000;;
TextureFilename {
"wall3.bmp";
}
 }
Material Material2 {
 0.988235;0.992157;1.000000;1.000000;;
128.000015;
 1.000000;1.000000;1.000000;;
 0.000000;0.000000;0.000000;;
TextureFilename {
"wall3.bmp";
}
 }
}

 MeshNormals {
 219;
-0.109395;-0.065044;-0.991868;,
-0.027349;0.037733;-0.998914;,
-0.055231;0.042678;-0.997561;,
-0.044382;-0.084442;-0.995440;,
-0.026691;-0.024243;-0.999350;,
-0.004719;-0.115354;-0.993313;,
-0.020678;-0.001652;-0.999785;,
-0.052035;-0.162050;-0.985410;,
0.065014;0.013275;-0.997796;,
0.076248;-0.084602;-0.993493;,
0.726582;-0.068711;-0.683636;,
0.734735;-0.177791;-0.654641;,
-0.004912;0.061899;-0.998070;,
-0.025858;0.046683;-0.998575;,
-0.006617;0.064951;-0.997867;,
-0.017142;0.085076;-0.996227;,
0.004455;0.013796;-0.999895;,
0.707032;0.032352;-0.706441;,
0.040744;-0.027482;-0.998792;,
-0.046748;-0.058916;-0.997168;,
0.023713;0.008787;-0.999680;,
-0.021673;0.011687;-0.999697;,
-0.003737;0.016584;-0.999856;,
0.705440;-0.009365;-0.708708;,
0.108809;0.008860;-0.994023;,
-0.041633;0.025555;-0.998806;,
0.148469;-0.020333;-0.988708;,
0.084166;0.001691;-0.996450;,
0.024243;0.041215;-0.998856;,
0.712851;-0.041202;-0.700104;,
0.697805;0.059097;-0.713846;,
-0.005218;0.566064;-0.824345;,
0.004962;0.004113;-0.999979;,
0.409812;0.561185;-0.719114;,
-0.150798;0.533425;-0.832297;,
-0.732498;0.002128;-0.680766;,
-0.070251;0.029229;-0.997101;,
-0.553831;0.456449;-0.696366;,
0.138684;0.047462;-0.989199;,
-0.059253;0.595040;-0.801509;,
0.063832;0.062818;-0.995982;,
0.025274;0.584282;-0.811157;,
0.051020;0.027297;-0.998325;,
-0.238839;0.522549;-0.818473;,
0.054394;0.056772;-0.996904;,
-0.266558;0.510218;-0.817695;,
-0.002575;0.072783;-0.997344;,
0.043631;0.092370;-0.994768;,
0.124278;0.506926;-0.852984;,
0.244632;0.530860;-0.811383;,
0.082298;0.046337;-0.995530;,
0.139617;0.553985;-0.820736;,
0.153087;0.069176;-0.985789;,
0.299483;0.532418;-0.791733;,
0.139509;0.026649;-0.989862;,
0.256916;0.539477;-0.801847;,
-0.011971;0.006490;-0.999907;,
0.063900;0.565949;-0.821960;,
-0.014913;0.003364;-0.999883;,
-0.712791;0.000000;-0.701377;,
-0.019472;-0.002033;-0.999808;,
-0.713591;0.000000;-0.700562;,
-0.012628;-0.000026;-0.999920;,
-0.710776;-0.000312;-0.703418;,
-0.052664;-0.025087;-0.998297;,
-0.711939;0.000107;-0.702242;,
-0.115061;0.008289;-0.993324;,
-0.736618;0.003990;-0.676297;,
-0.113950;-0.006865;0.993463;,
-0.721908;0.000000;0.691989;,
-0.091393;-0.017137;0.995667;,
-0.716719;0.000000;0.697362;,
-0.044886;-0.082077;0.995615;,
-0.046243;-0.030309;0.998470;,
-0.081298;-0.094643;0.992186;,
-0.058001;-0.060884;0.996458;,
-0.094032;-0.216422;0.971761;,
-0.008421;-0.102582;0.994689;,
0.145815;-0.051665;0.987962;,
0.709643;-0.169983;0.683749;,
0.077527;-0.200331;0.976656;,
0.749789;-0.054883;0.659397;,
-0.758166;-0.001016;0.652060;,
-0.104509;-0.070829;0.991999;,
0.019334;-0.094889;0.995300;,
0.040926;-0.033760;0.998592;,
0.048708;0.081671;0.995468;,
0.114057;0.095021;0.988920;,
0.744202;0.065192;0.664765;,
-0.777897;0.000364;0.628392;,
-0.107964;-0.034069;0.993571;,
0.068583;-0.037720;0.996932;,
0.059997;-0.000297;0.998199;,
0.038272;0.004468;0.999257;,
0.050400;0.001943;0.998727;,
0.705123;-0.019505;0.708817;,
-0.740907;0.004563;0.671592;,
-0.331917;0.039730;0.942472;,
-0.282844;0.148840;0.947547;,
0.009828;0.095653;0.995366;,
-0.016897;0.011655;0.999789;,
-0.029193;0.008856;0.999535;,
0.701934;-0.081632;0.707548;,
-0.033075;0.114736;0.992845;,
0.743120;0.059976;0.666465;,
0.041923;0.555021;0.830779;,
0.481533;0.522280;0.703811;,
-0.013395;0.028013;0.999518;,
0.044858;0.542101;0.839115;,
-0.323881;0.083294;0.942424;,
-0.154457;0.532059;0.832500;,
-0.707400;0.002144;0.706810;,
-0.546401;0.442497;0.711086;,
-0.027904;0.118917;0.992512;,
0.028341;0.531818;0.846384;,
0.007657;0.081539;0.996641;,
-0.054403;0.564793;0.823437;,
-0.051813;0.132020;0.989892;,
-0.263143;0.515758;0.815322;,
-0.279179;0.107078;0.954250;,
-0.164579;0.526277;0.834234;,
-0.366924;0.111082;0.923595;,
0.256157;0.547375;0.796721;,
0.181516;0.511578;0.839845;,
0.037035;0.042619;0.998405;,
0.042533;0.055332;0.997562;,
0.187139;0.563883;0.804372;,
-0.033627;0.141141;0.989418;,
0.276726;0.501719;0.819574;,
-0.084957;0.206339;0.974785;,
0.069758;0.612028;0.787754;,
0.734735;-0.177791;-0.654641;,
0.749789;-0.054883;0.659397;,
0.726582;-0.068711;-0.683636;,
0.709643;-0.169983;0.683749;,
-0.721908;0.000000;0.691989;,
-0.712791;0.000000;-0.701377;,
-0.713591;0.000000;-0.700562;,
-0.716719;0.000000;0.697362;,
0.744202;0.065192;0.664765;,
0.707032;0.032352;-0.706441;,
-0.710776;-0.000312;-0.703418;,
-0.758166;-0.001016;0.652060;,
0.705123;-0.019505;0.708817;,
0.705440;-0.009365;-0.708708;,
-0.711939;0.000107;-0.702242;,
-0.777897;0.000364;0.628392;,
0.701934;-0.081632;0.707548;,
0.712851;-0.041202;-0.700104;,
-0.736618;0.003990;-0.676297;,
-0.740907;0.004563;0.671592;,
0.743120;0.059976;0.666465;,
0.697805;0.059097;-0.713846;,
-0.732498;0.002128;-0.680766;,
-0.707400;0.002144;0.706810;,
-0.005218;0.566064;-0.824345;,
0.283127;0.918089;-0.277402;,
-0.040283;0.960030;-0.276982;,
0.409812;0.561185;-0.719114;,
-0.265615;0.944487;-0.193371;,
-0.553831;0.456449;-0.696366;,
-0.150798;0.533425;-0.832297;,
-0.530460;0.830514;-0.169880;,
0.195167;0.960449;-0.198616;,
0.124278;0.506926;-0.852984;,
-0.059253;0.595040;-0.801509;,
0.054208;0.978326;-0.199850;,
-0.095815;0.975299;-0.199027;,
0.025274;0.584282;-0.811157;,
-0.238839;0.522549;-0.818473;,
-0.450047;0.874640;-0.180174;,
-0.409839;0.893403;-0.184020;,
-0.266558;0.510218;-0.817695;,
0.408973;0.893803;-0.184003;,
0.244632;0.530860;-0.811383;,
0.315501;0.929417;-0.191423;,
0.139617;0.553985;-0.820736;,
0.477334;0.860715;-0.176980;,
0.299483;0.532418;-0.791733;,
0.334091;0.923560;-0.188201;,
0.256916;0.539477;-0.801847;,
0.089716;0.967128;-0.237940;,
0.063900;0.565949;-0.821960;,
0.310366;0.940553;0.137963;,
0.041923;0.555021;0.830779;,
-0.038722;0.983814;0.174961;,
0.481533;0.522280;0.703811;,
0.409812;0.561185;-0.719114;,
0.283127;0.918089;-0.277402;,
0.481533;0.522280;0.703811;,
0.310366;0.940553;0.137963;,
-0.553831;0.456449;-0.696366;,
-0.546401;0.442497;0.711086;,
-0.530460;0.830514;-0.169880;,
-0.531719;0.825353;0.189914;,
-0.264406;0.939771;0.216612;,
-0.531719;0.825353;0.189914;,
-0.154457;0.532059;0.832500;,
-0.546401;0.442497;0.711086;,
0.179551;0.957354;0.226353;,
0.044858;0.542101;0.839115;,
0.053953;0.973169;0.223677;,
-0.054403;0.564793;0.823437;,
-0.095317;0.970214;0.222711;,
0.028341;0.531818;0.846384;,
-0.449113;0.870299;0.202180;,
-0.164579;0.526277;0.834234;,
-0.391008;0.901016;0.187836;,
-0.263143;0.515758;0.815322;,
0.409055;0.892684;0.189180;,
0.256157;0.547375;0.796721;,
0.325684;0.921263;0.212615;,
0.181516;0.511578;0.839845;,
0.476846;0.858739;0.187576;,
0.276726;0.501719;0.819574;,
0.323206;0.924936;0.200079;,
0.187139;0.563883;0.804372;,
0.089840;0.979158;0.182150;,
0.069758;0.612028;0.787754;;

 301;
3;2,1,0;,
3;1,3,0;,
3;1,4,3;,
3;4,5,3;,
3;4,6,5;,
3;6,7,5;,
3;6,8,7;,
3;8,9,7;,
3;8,10,9;,
3;10,11,9;,
3;13,12,2;,
3;12,1,2;,
3;12,14,1;,
3;14,4,1;,
3;14,15,4;,
3;15,6,4;,
3;15,16,6;,
3;16,8,6;,
3;16,17,8;,
3;17,10,8;,
3;19,18,13;,
3;18,12,13;,
3;18,20,12;,
3;20,14,12;,
3;20,21,14;,
3;21,15,14;,
3;21,22,15;,
3;22,16,15;,
3;22,23,16;,
3;23,17,16;,
3;25,24,19;,
3;24,18,19;,
3;24,26,18;,
3;26,20,18;,
3;26,27,20;,
3;27,21,20;,
3;27,28,21;,
3;28,22,21;,
3;28,29,22;,
3;29,23,22;,
3;32,31,30;,
3;31,33,30;,
3;32,30,28;,
3;30,29,28;,
3;36,35,34;,
3;35,37,34;,
3;40,39,38;,
3;39,41,38;,
3;44,43,42;,
3;43,45,42;,
3;42,45,40;,
3;45,39,40;,
3;40,38,42;,
3;38,26,42;,
3;42,26,44;,
3;26,24,44;,
3;47,44,46;,
3;44,24,46;,
3;46,24,25;,
3;46,48,47;,
3;48,49,47;,
3;47,49,44;,
3;49,43,44;,
3;38,41,50;,
3;41,51,50;,
3;50,51,52;,
3;51,53,52;,
3;52,53,54;,
3;53,55,54;,
3;52,54,50;,
3;54,27,50;,
3;50,27,38;,
3;27,26,38;,
3;54,55,56;,
3;55,57,56;,
3;56,57,32;,
3;57,31,32;,
3;56,32,54;,
3;32,28,54;,
3;54,28,27;,
3;60,59,58;,
3;59,61,58;,
3;60,58,0;,
3;58,2,0;,
3;58,61,62;,
3;61,63,62;,
3;58,62,2;,
3;62,13,2;,
3;62,63,64;,
3;63,65,64;,
3;62,64,13;,
3;64,19,13;,
3;64,65,66;,
3;65,67,66;,
3;64,66,19;,
3;66,25,19;,
3;66,67,36;,
3;67,35,36;,
3;66,36,25;,
3;36,46,25;,
3;36,34,46;,
3;34,48,46;,
3;70,69,68;,
3;69,71,68;,
3;73,70,72;,
3;70,68,72;,
3;75,73,74;,
3;73,72,74;,
3;77,75,76;,
3;75,74,76;,
3;80,79,78;,
3;79,81,78;,
3;78,77,80;,
3;77,76,80;,
3;83,82,70;,
3;82,69,70;,
3;84,83,73;,
3;83,70,73;,
3;85,84,75;,
3;84,73,75;,
3;86,85,77;,
3;85,75,77;,
3;78,81,87;,
3;81,88,87;,
3;87,86,78;,
3;86,77,78;,
3;90,89,83;,
3;89,82,83;,
3;91,90,84;,
3;90,83,84;,
3;92,91,85;,
3;91,84,85;,
3;93,92,86;,
3;92,85,86;,
3;87,88,94;,
3;88,95,94;,
3;94,93,87;,
3;93,86,87;,
3;97,96,90;,
3;96,89,90;,
3;98,97,91;,
3;97,90,91;,
3;99,98,92;,
3;98,91,92;,
3;100,99,93;,
3;99,92,93;,
3;94,95,101;,
3;95,102,101;,
3;101,100,94;,
3;100,93,94;,
3;101,102,103;,
3;102,104,103;,
3;103,104,105;,
3;104,106,105;,
3;109,108,107;,
3;108,110,107;,
3;107,110,111;,
3;110,112,111;,
3;107,111,109;,
3;111,96,109;,
3;109,96,97;,
3;115,114,113;,
3;114,116,113;,
3;113,116,117;,
3;116,118,117;,
3;117,118,119;,
3;118,120,119;,
3;117,119,113;,
3;119,98,113;,
3;113,98,115;,
3;98,99,115;,
3;121,109,119;,
3;109,97,119;,
3;119,97,98;,
3;119,120,121;,
3;120,122,121;,
3;121,122,109;,
3;122,108,109;,
3;124,123,115;,
3;123,114,115;,
3;127,126,125;,
3;126,128,125;,
3;125,128,124;,
3;128,123,124;,
3;124,115,125;,
3;115,99,125;,
3;125,99,127;,
3;99,100,127;,
3;103,105,129;,
3;105,130,129;,
3;129,130,127;,
3;130,126,127;,
3;129,127,103;,
3;127,100,103;,
3;103,100,101;,
3;133,132,131;,
3;132,134,131;,
3;137,136,135;,
3;136,138,135;,
3;140,139,133;,
3;139,132,133;,
3;137,135,141;,
3;135,142,141;,
3;144,143,140;,
3;143,139,140;,
3;141,142,145;,
3;142,146,145;,
3;148,147,144;,
3;147,143,144;,
3;145,146,149;,
3;146,150,149;,
3;152,151,148;,
3;151,147,148;,
3;149,150,153;,
3;150,154,153;,
3;157,156,155;,
3;156,158,155;,
3;161,160,159;,
3;160,162,159;,
3;159,163,161;,
3;163,164,161;,
3;167,166,165;,
3;166,168,165;,
3;171,170,169;,
3;170,172,169;,
3;170,167,172;,
3;167,165,172;,
3;163,173,164;,
3;173,174,164;,
3;173,171,174;,
3;171,169,174;,
3;166,175,168;,
3;175,176,168;,
3;175,177,176;,
3;177,178,176;,
3;177,179,178;,
3;179,180,178;,
3;179,181,180;,
3;181,182,180;,
3;181,157,182;,
3;157,155,182;,
3;185,184,183;,
3;184,186,183;,
3;185,183,157;,
3;183,156,157;,
3;152,187,151;,
3;187,188,151;,
3;151,188,189;,
3;188,190,189;,
3;153,154,191;,
3;154,192,191;,
3;191,192,193;,
3;192,194,193;,
3;159,162,195;,
3;162,196,195;,
3;195,196,197;,
3;196,198,197;,
3;195,197,199;,
3;197,200,199;,
3;195,199,159;,
3;199,163,159;,
3;203,202,201;,
3;202,204,201;,
3;203,201,167;,
3;201,166,167;,
3;207,206,205;,
3;206,208,205;,
3;207,205,171;,
3;205,170,171;,
3;205,208,203;,
3;208,202,203;,
3;205,203,170;,
3;203,167,170;,
3;199,200,209;,
3;200,210,209;,
3;199,209,163;,
3;209,173,163;,
3;209,210,207;,
3;210,206,207;,
3;209,207,173;,
3;207,171,173;,
3;201,204,211;,
3;204,212,211;,
3;201,211,166;,
3;211,175,166;,
3;211,212,213;,
3;212,214,213;,
3;211,213,175;,
3;213,177,175;,
3;213,214,215;,
3;214,216,215;,
3;213,215,177;,
3;215,179,177;,
3;215,216,217;,
3;216,218,217;,
3;215,217,179;,
3;217,181,179;,
3;217,218,185;,
3;218,184,185;,
3;217,185,181;,
3;185,157,181;;
 }
MeshTextureCoords {
 219;
0.190416;0.952825;,
0.323396;0.848829;,
0.190461;0.849455;,
0.323458;0.966079;,
0.537023;0.849402;,
0.537003;0.953142;,
0.696910;0.849251;,
0.696905;0.956328;,
0.850197;0.849232;,
0.850033;0.959829;,
1.001050;0.849506;,
1.001240;0.949811;,
0.323958;0.742635;,
0.190552;0.742635;,
0.537156;0.742492;,
0.697398;0.742221;,
0.849996;0.742560;,
1.000870;0.742635;,
0.324021;0.582646;,
0.190485;0.582644;,
0.537193;0.582449;,
0.697450;0.582451;,
0.849971;0.582449;,
1.000870;0.582449;,
0.324130;0.463733;,
0.190177;0.463806;,
0.537193;0.463590;,
0.697456;0.463592;,
0.849971;0.463588;,
1.000870;0.463588;,
1.000920;0.339867;,
0.850598;0.203267;,
0.850130;0.339822;,
1.000880;0.206953;,
0.100154;0.159894;,
0.001430;0.339867;,
0.095866;0.339865;,
0.001430;0.206963;,
0.537256;0.339799;,
0.420609;0.146026;,
0.420698;0.339118;,
0.537193;0.206963;,
0.363062;0.339625;,
0.323958;0.206963;,
0.324019;0.339761;,
0.372269;0.149274;,
0.190516;0.339471;,
0.193575;0.339404;,
0.227677;0.148055;,
0.253953;0.205248;,
0.582289;0.339866;,
0.582289;0.173361;,
0.645430;0.339841;,
0.645460;0.171656;,
0.697435;0.339742;,
0.699418;0.206572;,
0.762242;0.339748;,
0.762119;0.177418;,
0.083569;0.849485;,
0.001430;0.949463;,
0.083529;0.950923;,
0.001430;0.849508;,
0.083632;0.742635;,
0.001430;0.742635;,
0.083612;0.582537;,
0.001239;0.582454;,
0.084527;0.463685;,
0.001430;0.463588;,
0.189403;0.975814;,
0.000584;0.850886;,
0.189414;0.850937;,
0.000584;0.971055;,
0.322401;0.990142;,
0.322338;0.852142;,
0.535699;0.976444;,
0.535768;0.850826;,
0.695428;0.981504;,
0.695685;0.850600;,
0.848644;0.850657;,
1.000000;0.971885;,
0.848545;0.983945;,
0.999562;0.850882;,
0.000584;0.722400;,
0.189205;0.722573;,
0.322754;0.722799;,
0.536404;0.721556;,
0.696051;0.721478;,
0.848543;0.722301;,
0.999270;0.722400;,
0.000000;0.529824;,
0.188255;0.530769;,
0.324190;0.529660;,
0.535955;0.529678;,
0.696098;0.529913;,
0.848484;0.529821;,
0.999270;0.529821;,
0.000584;0.386923;,
0.188956;0.386407;,
0.323228;0.386917;,
0.535905;0.386915;,
0.691415;0.369916;,
0.848484;0.386923;,
0.999270;0.386923;,
0.848946;0.237674;,
0.999319;0.238182;,
0.849131;0.073809;,
0.999276;0.078389;,
0.094948;0.238178;,
0.226660;0.007580;,
0.189523;0.237507;,
0.099233;0.021813;,
0.000584;0.238182;,
0.000584;0.078400;,
0.419534;0.237288;,
0.535942;0.078400;,
0.535940;0.237968;,
0.419447;0.005140;,
0.362063;0.237900;,
0.371143;0.009045;,
0.322976;0.237947;,
0.322869;0.078400;,
0.192744;0.237399;,
0.252917;0.076339;,
0.581004;0.038003;,
0.581003;0.238179;,
0.644004;0.237999;,
0.698046;0.077919;,
0.696087;0.237404;,
0.644127;0.035953;,
0.761133;0.237584;,
0.760697;0.042881;,
1.283110;1.014434;,
0.983631;0.879469;,
1.282880;0.879471;,
0.983101;1.014895;,
-0.968527;0.873677;,
-0.678553;0.998874;,
-0.678553;0.873677;,
-0.968527;0.998874;,
0.984001;0.735672;,
1.282660;0.735672;,
-0.678553;0.739816;,
-0.968527;0.739816;,
0.984001;0.520138;,
1.282660;0.520138;,
-0.678312;0.539186;,
-0.969255;0.539183;,
0.984001;0.360206;,
1.282660;0.360206;,
-0.678553;0.390305;,
-0.968527;0.390305;,
0.983941;0.193735;,
1.282720;0.193735;,
-0.678553;0.235340;,
-0.968527;0.235340;,
0.846348;-0.005150;,
0.996710;0.067657;,
0.846353;0.063949;,
0.996710;-0.001440;,
0.095488;0.067662;,
-0.003290;-0.001440;,
0.095488;-0.001440;,
-0.003290;0.067662;,
0.223083;0.067662;,
0.223083;-0.001440;,
0.416122;-0.001440;,
0.532770;0.067662;,
0.416122;0.067662;,
0.532770;-0.001440;,
0.319418;-0.001440;,
0.367755;0.067662;,
0.319418;0.067662;,
0.367755;-0.001440;,
0.249374;0.063662;,
0.249374;-0.001440;,
0.577891;0.067662;,
0.577891;-0.001440;,
0.641096;0.064939;,
0.641096;-0.001440;,
0.695085;0.067220;,
0.695085;-0.001880;,
0.757819;0.067659;,
0.757819;-0.001440;,
0.996710;0.159919;,
0.846368;0.224496;,
0.846362;0.156210;,
0.996710;0.220655;,
1.282670;0.014895;,
1.189750;0.014895;,
0.984001;0.014895;,
1.065670;0.014895;,
-0.678553;0.068877;,
-0.968527;0.068877;,
-0.768772;0.068877;,
-0.889235;0.068877;,
0.095488;0.159923;,
-0.003290;0.159923;,
0.095488;0.220650;,
-0.003290;0.220650;,
0.223083;0.159923;,
0.223083;0.220650;,
0.532770;0.159923;,
0.416122;0.220650;,
0.416122;0.159923;,
0.532770;0.220650;,
0.367755;0.159923;,
0.319418;0.220650;,
0.319418;0.159923;,
0.367755;0.220650;,
0.249374;0.150580;,
0.249374;0.220650;,
0.577891;0.159923;,
0.577891;0.220650;,
0.641096;0.153564;,
0.641096;0.220650;,
0.695085;0.159481;,
0.695086;0.221095;,
0.757819;0.159920;,
0.757819;0.220651;;
}
}
 }
