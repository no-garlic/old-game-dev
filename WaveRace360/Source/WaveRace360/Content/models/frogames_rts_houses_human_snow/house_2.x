xof 0303txt 0032

// DirectX file
// Creator: Ultimate Unwrap3D v2.26
// Time: Mon Mar 27 02:34:25 2006

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
       -1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 0.002806, 0.999996, 0.000000,
       0.000000, 0.999996, -0.002805, 0.000000,
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
       120;
       -2.372616; -0.071745; 3.363690;,
       -1.862081; 4.783744; -3.005976;,
       -2.157381; -0.071885; -3.476336;,
       -1.862081; 4.783744; -3.005976;,
       -2.372616; -0.071745; 3.363690;,
       -2.048167; 4.783864; 2.907711;,
       -1.862081; 4.783744; -3.005976;,
       0.112740; 6.631747; -2.851704;,
       -2.157381; -0.071885; -3.476336;,
       1.907329; 4.783867; 3.032178;,
       -0.067492; 6.631864; 2.875947;,
       -2.048167; 4.783864; 2.907711;,
       0.112740; 6.631747; -2.851704;,
       2.093415; 4.783746; -2.881509;,
       -2.157381; -0.071885; -3.476336;,
       -2.157381; -0.071885; -3.476336;,
       2.093415; 4.783746; -2.881509;,
       2.417709; -0.071882; -3.332372;,
       1.907329; 4.783867; 3.032178;,
       2.417709; -0.071882; -3.332372;,
       2.093415; 4.783746; -2.881509;,
       2.417709; -0.071882; -3.332372;,
       1.907329; 4.783867; 3.032178;,
       2.202475; -0.071743; 3.507654;,
       -2.048167; 4.783864; 2.907711;,
       2.202475; -0.071743; 3.507654;,
       1.907329; 4.783867; 3.032178;,
       2.202475; -0.071743; 3.507654;,
       -2.048167; 4.783864; 2.907711;,
       -2.372616; -0.071745; 3.363690;,
       0.000000; 6.417260; -0.001549;,
       1.030727; 5.715387; -3.378710;,
       0.816359; 5.715527; 3.433749;,
       0.105663; 6.634196; -3.359459;,
       -0.105663; 6.634333; 3.356355;,
       1.959971; 4.791958; -3.530810;,
       1.734201; 4.792105; 3.644012;,
       2.711714; 4.454289; 3.928681;,
       2.953446; 4.454133; -3.753445;,
       0.000000; 6.417260; -0.001549;,
       -1.030726; 5.715525; 3.375627;,
       -0.816359; 5.715386; -3.436832;,
       -0.105663; 6.634333; 3.356355;,
       -1.734200; 4.791956; -3.647055;,
       -1.959970; 4.792102; 3.527768;,
       -2.953445; 4.454286; 3.750416;,
       -2.711713; 4.454129; -3.931711;,
       0.105663; 6.634196; -3.359459;,
       1.213117; 5.924571; -3.365762;,
       0.000000; 6.718482; -0.001555;,
       0.999203; 5.924710; 3.432280;,
       0.104718; 7.024206; -3.329430;,
       2.124093; 5.019633; -3.525651;,
       1.898324; 5.019781; 3.649172;,
       2.711714; 4.454289; 3.928681;,
       2.953446; 4.454133; -3.753445;,
       -0.104718; 7.024342; 3.326317;,
       0.000000; 6.718482; -0.001555;,
       -0.999203; 5.924570; -3.435377;,
       -1.213115; 5.924708; 3.362665;,
       0.104718; 7.024206; -3.329430;,
       -1.898324; 5.019631; -3.652224;,
       -2.124093; 5.019778; 3.522599;,
       -2.953445; 4.454286; 3.750416;,
       -2.711713; 4.454129; -3.931711;,
       -0.104718; 7.024342; 3.326317;,
       1.734201; 4.792105; 3.644012;,
       1.898324; 5.019781; 3.649172;,
       0.816359; 5.715527; 3.433749;,
       2.711714; 4.454289; 3.928681;,
       0.999203; 5.924710; 3.432280;,
       -0.105663; 6.634333; 3.356355;,
       -0.104718; 7.024342; 3.326317;,
       -1.213115; 5.924708; 3.362665;,
       -1.030726; 5.715525; 3.375627;,
       -2.124093; 5.019778; 3.522599;,
       -1.959970; 4.792102; 3.527768;,
       -2.953445; 4.454286; 3.750416;,
       2.124093; 5.019633; -3.525651;,
       1.959971; 4.791958; -3.530810;,
       1.030727; 5.715387; -3.378710;,
       2.953446; 4.454133; -3.753445;,
       1.213117; 5.924571; -3.365762;,
       0.105663; 6.634196; -3.359459;,
       0.104718; 7.024206; -3.329430;,
       -0.999203; 5.924570; -3.435377;,
       -0.816359; 5.715386; -3.436832;,
       -1.898324; 5.019631; -3.652224;,
       -1.734200; 4.791956; -3.647055;,
       -2.711713; 4.454129; -3.931711;,
       0.586359; 6.387393; -1.730185;,
       0.618353; 6.387372; -2.746937;,
       0.570876; 7.959118; -1.683084;,
       0.601991; 7.959098; -2.671866;,
       0.570876; 7.959118; -1.683084;,
       0.618353; 6.387372; -2.746937;,
       0.618353; 6.387372; -2.746937;,
       -0.398401; 6.387372; -2.778931;,
       0.601991; 7.959098; -2.671866;,
       -0.386792; 7.959097; -2.702980;,
       0.601991; 7.959098; -2.671866;,
       -0.398401; 6.387372; -2.778931;,
       -0.398401; 6.387372; -2.778931;,
       -0.430395; 6.387392; -1.762179;,
       -0.386792; 7.959097; -2.702980;,
       -0.417905; 7.959117; -1.714198;,
       -0.386792; 7.959097; -2.702980;,
       -0.430395; 6.387392; -1.762179;,
       -0.430395; 6.387392; -1.762179;,
       0.586359; 6.387393; -1.730185;,
       -0.417905; 7.959117; -1.714198;,
       0.570876; 7.959118; -1.683084;,
       -0.417905; 7.959117; -1.714198;,
       0.586359; 6.387393; -1.730185;,
       0.601991; 7.959098; -2.671866;,
       -0.386792; 7.959097; -2.702980;,
       0.570876; 7.959118; -1.683084;,
       -0.417905; 7.959117; -1.714198;,
       0.570876; 7.959118; -1.683084;,
       -0.386792; 7.959097; -2.702980;;
       77;
       3;0, 1, 2;,
       3;3, 4, 5;,
       3;6, 7, 8;,
       3;9, 10, 11;,
       3;12, 13, 14;,
       3;15, 16, 17;,
       3;18, 19, 20;,
       3;21, 22, 23;,
       3;24, 25, 26;,
       3;27, 28, 29;,
       3;30, 31, 32;,
       3;30, 33, 31;,
       3;32, 34, 30;,
       3;35, 32, 31;,
       3;35, 36, 32;,
       3;35, 36, 35;,
       3;35, 37, 36;,
       3;38, 37, 35;,
       3;39, 40, 41;,
       3;39, 42, 40;,
       3;40, 43, 41;,
       3;40, 43, 43;,
       3;44, 43, 40;,
       3;44, 43, 43;,
       3;45, 43, 44;,
       3;45, 46, 43;,
       3;41, 47, 39;,
       3;48, 49, 50;,
       3;48, 51, 49;,
       3;50, 52, 48;,
       3;50, 52, 52;,
       3;53, 52, 50;,
       3;53, 52, 52;,
       3;54, 52, 53;,
       3;54, 55, 52;,
       3;50, 49, 56;,
       3;57, 58, 59;,
       3;57, 60, 58;,
       3;61, 59, 58;,
       3;61, 62, 59;,
       3;61, 62, 61;,
       3;61, 63, 62;,
       3;64, 63, 61;,
       3;57, 59, 65;,
       3;66, 67, 68;,
       3;66, 69, 67;,
       3;70, 68, 67;,
       3;70, 71, 68;,
       3;72, 71, 70;,
       3;72, 71, 71;,
       3;73, 71, 72;,
       3;73, 74, 71;,
       3;75, 74, 73;,
       3;75, 76, 74;,
       3;77, 76, 75;,
       3;78, 79, 80;,
       3;78, 81, 79;,
       3;80, 82, 78;,
       3;80, 82, 82;,
       3;83, 82, 80;,
       3;83, 84, 82;,
       3;83, 84, 83;,
       3;83, 85, 84;,
       3;86, 85, 83;,
       3;86, 87, 85;,
       3;88, 87, 86;,
       3;88, 89, 87;,
       3;90, 91, 92;,
       3;93, 94, 95;,
       3;96, 97, 98;,
       3;99, 100, 101;,
       3;102, 103, 104;,
       3;105, 106, 107;,
       3;108, 109, 110;,
       3;111, 112, 113;,
       3;114, 115, 116;,
       3;117, 118, 119;;

      MeshNormals {
       120;
       -0.997475; 0.063703; -0.031389;,
       -0.997475; 0.063703; -0.031389;,
       -0.997475; 0.063703; -0.031389;,
       -0.997475; 0.063703; -0.031389;,
       -0.997475; 0.063703; -0.031389;,
       -0.997475; 0.063703; -0.031389;,
       -0.013221; 0.097206; -0.995176;,
       -0.013221; 0.097206; -0.995176;,
       -0.013221; 0.097206; -0.995176;,
       -0.031411; 0.050823; 0.998214;,
       -0.031411; 0.050823; 0.998214;,
       -0.031411; 0.050823; 0.998214;,
       0.054396; 0.074361; -0.995747;,
       0.054396; 0.074361; -0.995747;,
       0.054396; 0.074361; -0.995747;,
       0.031311; 0.094484; -0.995034;,
       0.031311; 0.094484; -0.995034;,
       0.031311; 0.094484; -0.995034;,
       0.997475; 0.063704; 0.031386;,
       0.997475; 0.063704; 0.031386;,
       0.997475; 0.063704; 0.031386;,
       0.997475; 0.063704; 0.031386;,
       0.997475; 0.063704; 0.031386;,
       0.997475; 0.063704; 0.031386;,
       -0.031307; 0.095524; 0.994935;,
       -0.031307; 0.095524; 0.994935;,
       -0.031307; 0.095524; 0.994935;,
       -0.031308; 0.095524; 0.994935;,
       -0.031308; 0.095524; 0.994935;,
       -0.031308; 0.095524; 0.994935;,
       -0.673492; -0.738891; -0.021178;,
       -0.673145; -0.738612; -0.036435;,
       -0.682374; -0.730935; -0.010010;,
       -0.703791; -0.707161; -0.067832;,
       -0.706664; -0.707160; 0.023478;,
       -0.528880; -0.848534; -0.016625;,
       -0.528880; -0.848534; -0.016625;,
       -0.323967; -0.946014; -0.010175;,
       -0.323966; -0.946014; -0.010175;,
       0.673492; -0.738890; 0.021208;,
       0.681654; -0.730934; 0.032911;,
       0.674105; -0.738611; 0.005959;,
       0.703791; -0.707159; 0.067861;,
       0.528879; -0.848533; 0.016659;,
       0.528880; -0.848533; 0.016660;,
       0.323967; -0.946013; 0.010213;,
       0.323966; -0.946013; 0.010213;,
       0.706665; -0.707160; -0.023449;,
       0.666330; 0.744437; 0.042644;,
       0.667157; 0.744622; 0.020978;,
       0.677646; 0.735371; 0.005048;,
       0.703062; 0.705792; 0.086963;,
       0.639227; 0.768756; 0.020099;,
       0.639227; 0.768755; 0.020099;,
       0.566605; 0.823797; 0.017812;,
       0.566605; 0.823797; 0.017813;,
       0.707138; 0.705790; -0.042617;,
       -0.667157; 0.744621; -0.021008;,
       -0.667693; 0.744436; 0.000667;,
       -0.676624; 0.735370; -0.037566;,
       -0.707139; 0.705791; 0.042588;,
       -0.639227; 0.768755; -0.020130;,
       -0.639227; 0.768755; -0.020130;,
       -0.566605; 0.823796; -0.017846;,
       -0.566605; 0.823796; -0.017846;,
       -0.703061; 0.705789; -0.086991;,
       -0.187472; 0.113027; 0.975745;,
       -0.165973; 0.113495; 0.979577;,
       -0.102760; 0.079649; 0.991512;,
       -0.230393; 0.144272; 0.962343;,
       -0.061093; 0.078106; 0.995071;,
       -0.031395; 0.059870; 0.997712;,
       -0.031358; 0.076828; 0.996551;,
       -0.001590; 0.078106; 0.996944;,
       0.040219; 0.079648; 0.996011;,
       0.104057; 0.113495; 0.988074;,
       0.125754; 0.113028; 0.985602;,
       0.169433; 0.144272; 0.974925;,
       -0.104059; 0.113449; -0.988079;,
       -0.125753; 0.112987; -0.985606;,
       -0.040229; 0.079600; -0.996015;,
       -0.169433; 0.144233; -0.974930;,
       0.001577; 0.078064; -0.996947;,
       0.031395; 0.059836; -0.997714;,
       0.031358; 0.076806; -0.996553;,
       0.061106; 0.078064; -0.995074;,
       0.102769; 0.079601; -0.991515;,
       0.165974; 0.113451; -0.979582;,
       0.187469; 0.112990; -0.975750;,
       0.230392; 0.144236; -0.962349;,
       0.999466; 0.008903; 0.031450;,
       0.999466; 0.008903; 0.031450;,
       0.999466; 0.008903; 0.031450;,
       0.999466; 0.008903; 0.031450;,
       0.999466; 0.008903; 0.031450;,
       0.999466; 0.008903; 0.031450;,
       0.031415; 0.048012; -0.998353;,
       0.031415; 0.048012; -0.998353;,
       0.031415; 0.048012; -0.998353;,
       0.031415; 0.048012; -0.998353;,
       0.031415; 0.048012; -0.998353;,
       0.031415; 0.048012; -0.998353;,
       -0.999466; 0.008902; -0.031450;,
       -0.999466; 0.008902; -0.031450;,
       -0.999466; 0.008902; -0.031450;,
       -0.999466; 0.008902; -0.031450;,
       -0.999466; 0.008902; -0.031450;,
       -0.999466; 0.008902; -0.031450;,
       -0.031437; -0.030248; 0.999048;,
       -0.031437; -0.030248; 0.999048;,
       -0.031437; -0.030248; 0.999048;,
       -0.031437; -0.030248; 0.999048;,
       -0.031437; -0.030248; 0.999048;,
       -0.031437; -0.030248; 0.999048;,
       -0.000000; 1.000000; -0.000020;,
       -0.000000; 1.000000; -0.000020;,
       -0.000000; 1.000000; -0.000020;,
       -0.000000; 1.000000; -0.000020;,
       -0.000000; 1.000000; -0.000020;,
       -0.000000; 1.000000; -0.000020;;
       77;
       3;0, 1, 2;,
       3;3, 4, 5;,
       3;6, 7, 8;,
       3;9, 10, 11;,
       3;12, 13, 14;,
       3;15, 16, 17;,
       3;18, 19, 20;,
       3;21, 22, 23;,
       3;24, 25, 26;,
       3;27, 28, 29;,
       3;30, 31, 32;,
       3;30, 33, 31;,
       3;32, 34, 30;,
       3;35, 32, 31;,
       3;35, 36, 32;,
       3;35, 36, 35;,
       3;35, 37, 36;,
       3;38, 37, 35;,
       3;39, 40, 41;,
       3;39, 42, 40;,
       3;40, 43, 41;,
       3;40, 43, 43;,
       3;44, 43, 40;,
       3;44, 43, 43;,
       3;45, 43, 44;,
       3;45, 46, 43;,
       3;41, 47, 39;,
       3;48, 49, 50;,
       3;48, 51, 49;,
       3;50, 52, 48;,
       3;50, 52, 52;,
       3;53, 52, 50;,
       3;53, 52, 52;,
       3;54, 52, 53;,
       3;54, 55, 52;,
       3;50, 49, 56;,
       3;57, 58, 59;,
       3;57, 60, 58;,
       3;61, 59, 58;,
       3;61, 62, 59;,
       3;61, 62, 61;,
       3;61, 63, 62;,
       3;64, 63, 61;,
       3;57, 59, 65;,
       3;66, 67, 68;,
       3;66, 69, 67;,
       3;70, 68, 67;,
       3;70, 71, 68;,
       3;72, 71, 70;,
       3;72, 71, 71;,
       3;73, 71, 72;,
       3;73, 74, 71;,
       3;75, 74, 73;,
       3;75, 76, 74;,
       3;77, 76, 75;,
       3;78, 79, 80;,
       3;78, 81, 79;,
       3;80, 82, 78;,
       3;80, 82, 82;,
       3;83, 82, 80;,
       3;83, 84, 82;,
       3;83, 84, 83;,
       3;83, 85, 84;,
       3;86, 85, 83;,
       3;86, 87, 85;,
       3;88, 87, 86;,
       3;88, 89, 87;,
       3;90, 91, 92;,
       3;93, 94, 95;,
       3;96, 97, 98;,
       3;99, 100, 101;,
       3;102, 103, 104;,
       3;105, 106, 107;,
       3;108, 109, 110;,
       3;111, 112, 113;,
       3;114, 115, 116;,
       3;117, 118, 119;;
      }

      MeshTextureCoords {
       120;
       0.012858; 0.012630;,
       0.567546; 0.434623;,
       0.607605; 0.012630;,
       0.567546; 0.434623;,
       0.012858; 0.012630;,
       0.053345; 0.434623;,
       0.624152; 0.333032;,
       0.793933; 0.172426;,
       0.597557; 0.755025;,
       0.963720; 0.333032;,
       0.793933; 0.172426;,
       0.624152; 0.333032;,
       0.793933; 0.172426;,
       0.963720; 0.333032;,
       0.597557; 0.755025;,
       0.597557; 0.755025;,
       0.963720; 0.333032;,
       0.990315; 0.755025;,
       0.052326; 0.566258;,
       0.606586; 0.988250;,
       0.566527; 0.566258;,
       0.606586; 0.988250;,
       0.052326; 0.566258;,
       0.011839; 0.988250;,
       0.624152; 0.333032;,
       0.990315; 0.755025;,
       0.963720; 0.333032;,
       0.990315; 0.755025;,
       0.624152; 0.333032;,
       0.597557; 0.755025;,
       0.453915; 0.663347;,
       0.960162; 0.642472;,
       0.035000; 0.638555;,
       0.961469; 0.674881;,
       0.035947; 0.665831;,
       0.963131; 0.614751;,
       0.033743; 0.610509;,
       0.037094; 0.584770;,
       0.962460; 0.586282;,
       0.453915; 0.663347;,
       0.037344; 0.640901;,
       0.958600; 0.648724;,
       0.035947; 0.665831;,
       0.963913; 0.613191;,
       0.038431; 0.609730;,
       0.039438; 0.584770;,
       0.953084; 0.583939;,
       0.961469; 0.674881;,
       0.933594; 0.320313;,
       0.511719; 0.167969;,
       0.089844; 0.320313;,
       0.921875; 0.167969;,
       0.957031; 0.441406;,
       0.066406; 0.441406;,
       0.035156; 0.550781;,
       0.988281; 0.550781;,
       0.097656; 0.167969;,
       0.511719; 0.167969;,
       0.933594; 0.316406;,
       0.089844; 0.316406;,
       0.921875; 0.167969;,
       0.957031; 0.437500;,
       0.066406; 0.437500;,
       0.035156; 0.546875;,
       0.988281; 0.546875;,
       0.097656; 0.167969;,
       0.752877; 0.025998;,
       0.809731; 0.088753;,
       0.429909; 0.044004;,
       0.956740; 0.113043;,
       0.426609; 0.096999;,
       0.126943; 0.019334;,
       0.034845; 0.124732;,
       0.426101; 0.095859;,
       0.429401; 0.042864;,
       0.809223; 0.087613;,
       0.752370; 0.024858;,
       0.956232; 0.111903;,
       0.809731; 0.088753;,
       0.752878; 0.025997;,
       0.429909; 0.044004;,
       0.956740; 0.113043;,
       0.426609; 0.096999;,
       0.126944; 0.019334;,
       0.034845; 0.124732;,
       0.426102; 0.095859;,
       0.429402; 0.042864;,
       0.809224; 0.087613;,
       0.752370; 0.024858;,
       0.956232; 0.111903;,
       0.875201; 0.269560;,
       0.978030; 0.269560;,
       0.873940; 0.087913;,
       0.973940; 0.087913;,
       0.873940; 0.087913;,
       0.978030; 0.269560;,
       0.821205; 0.271335;,
       0.718376; 0.271335;,
       0.816241; 0.089688;,
       0.716241; 0.089688;,
       0.816241; 0.089688;,
       0.718376; 0.271335;,
       0.978030; 0.269560;,
       0.875201; 0.269560;,
       0.973940; 0.087913;,
       0.873940; 0.087913;,
       0.973940; 0.087913;,
       0.875201; 0.269560;,
       0.718376; 0.271335;,
       0.821205; 0.271335;,
       0.716241; 0.089688;,
       0.816241; 0.089688;,
       0.716241; 0.089688;,
       0.821205; 0.271335;,
       0.686670; 0.016915;,
       0.686670; 0.116915;,
       0.586670; 0.016915;,
       0.586670; 0.116915;,
       0.586670; 0.016915;,
       0.686670; 0.116915;;
      }

      MeshVertexColors {
       120;
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
       20; 1.000000; 1.000000; 1.000000; 1.000000;,
       21; 1.000000; 1.000000; 1.000000; 1.000000;,
       22; 1.000000; 1.000000; 1.000000; 1.000000;,
       23; 1.000000; 1.000000; 1.000000; 1.000000;,
       24; 1.000000; 1.000000; 1.000000; 1.000000;,
       25; 1.000000; 1.000000; 1.000000; 1.000000;,
       26; 1.000000; 1.000000; 1.000000; 1.000000;,
       27; 1.000000; 1.000000; 1.000000; 1.000000;,
       28; 1.000000; 1.000000; 1.000000; 1.000000;,
       29; 1.000000; 1.000000; 1.000000; 1.000000;,
       30; 1.000000; 1.000000; 1.000000; 1.000000;,
       31; 1.000000; 1.000000; 1.000000; 1.000000;,
       32; 1.000000; 1.000000; 1.000000; 1.000000;,
       33; 1.000000; 1.000000; 1.000000; 1.000000;,
       34; 1.000000; 1.000000; 1.000000; 1.000000;,
       35; 1.000000; 1.000000; 1.000000; 1.000000;,
       36; 1.000000; 1.000000; 1.000000; 1.000000;,
       37; 1.000000; 1.000000; 1.000000; 1.000000;,
       38; 1.000000; 1.000000; 1.000000; 1.000000;,
       39; 1.000000; 1.000000; 1.000000; 1.000000;,
       40; 1.000000; 1.000000; 1.000000; 1.000000;,
       41; 1.000000; 1.000000; 1.000000; 1.000000;,
       42; 1.000000; 1.000000; 1.000000; 1.000000;,
       43; 1.000000; 1.000000; 1.000000; 1.000000;,
       44; 1.000000; 1.000000; 1.000000; 1.000000;,
       45; 1.000000; 1.000000; 1.000000; 1.000000;,
       46; 1.000000; 1.000000; 1.000000; 1.000000;,
       47; 1.000000; 1.000000; 1.000000; 1.000000;,
       48; 1.000000; 1.000000; 1.000000; 1.000000;,
       49; 1.000000; 1.000000; 1.000000; 1.000000;,
       50; 1.000000; 1.000000; 1.000000; 1.000000;,
       51; 1.000000; 1.000000; 1.000000; 1.000000;,
       52; 1.000000; 1.000000; 1.000000; 1.000000;,
       53; 1.000000; 1.000000; 1.000000; 1.000000;,
       54; 1.000000; 1.000000; 1.000000; 1.000000;,
       55; 1.000000; 1.000000; 1.000000; 1.000000;,
       56; 1.000000; 1.000000; 1.000000; 1.000000;,
       57; 1.000000; 1.000000; 1.000000; 1.000000;,
       58; 1.000000; 1.000000; 1.000000; 1.000000;,
       59; 1.000000; 1.000000; 1.000000; 1.000000;,
       60; 1.000000; 1.000000; 1.000000; 1.000000;,
       61; 1.000000; 1.000000; 1.000000; 1.000000;,
       62; 1.000000; 1.000000; 1.000000; 1.000000;,
       63; 1.000000; 1.000000; 1.000000; 1.000000;,
       64; 1.000000; 1.000000; 1.000000; 1.000000;,
       65; 1.000000; 1.000000; 1.000000; 1.000000;,
       66; 1.000000; 1.000000; 1.000000; 1.000000;,
       67; 1.000000; 1.000000; 1.000000; 1.000000;,
       68; 1.000000; 1.000000; 1.000000; 1.000000;,
       69; 1.000000; 1.000000; 1.000000; 1.000000;,
       70; 1.000000; 1.000000; 1.000000; 1.000000;,
       71; 1.000000; 1.000000; 1.000000; 1.000000;,
       72; 1.000000; 1.000000; 1.000000; 1.000000;,
       73; 1.000000; 1.000000; 1.000000; 1.000000;,
       74; 1.000000; 1.000000; 1.000000; 1.000000;,
       75; 1.000000; 1.000000; 1.000000; 1.000000;,
       76; 1.000000; 1.000000; 1.000000; 1.000000;,
       77; 1.000000; 1.000000; 1.000000; 1.000000;,
       78; 1.000000; 1.000000; 1.000000; 1.000000;,
       79; 1.000000; 1.000000; 1.000000; 1.000000;,
       80; 1.000000; 1.000000; 1.000000; 1.000000;,
       81; 1.000000; 1.000000; 1.000000; 1.000000;,
       82; 1.000000; 1.000000; 1.000000; 1.000000;,
       83; 1.000000; 1.000000; 1.000000; 1.000000;,
       84; 1.000000; 1.000000; 1.000000; 1.000000;,
       85; 1.000000; 1.000000; 1.000000; 1.000000;,
       86; 1.000000; 1.000000; 1.000000; 1.000000;,
       87; 1.000000; 1.000000; 1.000000; 1.000000;,
       88; 1.000000; 1.000000; 1.000000; 1.000000;,
       89; 1.000000; 1.000000; 1.000000; 1.000000;,
       90; 1.000000; 1.000000; 1.000000; 1.000000;,
       91; 1.000000; 1.000000; 1.000000; 1.000000;,
       92; 1.000000; 1.000000; 1.000000; 1.000000;,
       93; 1.000000; 1.000000; 1.000000; 1.000000;,
       94; 1.000000; 1.000000; 1.000000; 1.000000;,
       95; 1.000000; 1.000000; 1.000000; 1.000000;,
       96; 1.000000; 1.000000; 1.000000; 1.000000;,
       97; 1.000000; 1.000000; 1.000000; 1.000000;,
       98; 1.000000; 1.000000; 1.000000; 1.000000;,
       99; 1.000000; 1.000000; 1.000000; 1.000000;,
       100; 1.000000; 1.000000; 1.000000; 1.000000;,
       101; 1.000000; 1.000000; 1.000000; 1.000000;,
       102; 1.000000; 1.000000; 1.000000; 1.000000;,
       103; 1.000000; 1.000000; 1.000000; 1.000000;,
       104; 1.000000; 1.000000; 1.000000; 1.000000;,
       105; 1.000000; 1.000000; 1.000000; 1.000000;,
       106; 1.000000; 1.000000; 1.000000; 1.000000;,
       107; 1.000000; 1.000000; 1.000000; 1.000000;,
       108; 1.000000; 1.000000; 1.000000; 1.000000;,
       109; 1.000000; 1.000000; 1.000000; 1.000000;,
       110; 1.000000; 1.000000; 1.000000; 1.000000;,
       111; 1.000000; 1.000000; 1.000000; 1.000000;,
       112; 1.000000; 1.000000; 1.000000; 1.000000;,
       113; 1.000000; 1.000000; 1.000000; 1.000000;,
       114; 1.000000; 1.000000; 1.000000; 1.000000;,
       115; 1.000000; 1.000000; 1.000000; 1.000000;,
       116; 1.000000; 1.000000; 1.000000; 1.000000;,
       117; 1.000000; 1.000000; 1.000000; 1.000000;,
       118; 1.000000; 1.000000; 1.000000; 1.000000;,
       119; 1.000000; 1.000000; 1.000000; 1.000000;;
      }

      MeshMaterialList {
       3;
       77;
       0,
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
       2,
       2,
       2,
       2,
       2,
       2,
       2,
       2,
       2,
       2;

       Material {
        1.000000; 1.000000; 1.000000; 1.000000;;
        128.000000;
        0.000000; 0.000000; 0.000000;;
        0.000000; 0.000000; 0.000000;;

        TextureFilename {
         "humans5.jpg";
        }
       }

       Material {
        1.000000; 1.000000; 1.000000; 1.000000;;
        128.000000;
        0.000000; 0.000000; 0.000000;;
        0.000000; 0.000000; 0.000000;;

        TextureFilename {
         "humans8.jpg";
        }
       }

       Material {
        1.000000; 1.000000; 1.000000; 1.000000;;
        128.000000;
        0.000000; 0.000000; 0.000000;;
        0.000000; 0.000000; 0.000000;;

        TextureFilename {
         "humans2.jpg";
        }
       }

      }
     }
   }
}
