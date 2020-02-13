xof 0303txt 0032

// DirectX file
// Creator: Ultimate Unwrap3D v2.26
// Time: Mon Mar 27 02:34:32 2006

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
       -0.999994, 0.000000, 0.003367, 0.000000,
       0.003367, 0.000000, 0.999994, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
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
       167;
       0.004490; 6.400789; -0.000015;,
       3.149546; 5.698985; 0.915914;,
       -3.134315; 5.698985; 0.937069;,
       3.101846; 6.617794; -0.010443;,
       -3.092869; 6.617794; 0.010412;,
       3.319787; 4.775560; 1.841857;,
       -3.298321; 4.775560; 1.864138;,
       -3.528963; 4.437738; 2.853582;,
       3.557086; 4.437738; 2.829726;,
       0.004490; 6.400789; -0.000015;,
       -3.140554; 5.698986; -0.915944;,
       3.143308; 5.698986; -0.937099;,
       -3.092869; 6.617794; 0.010412;,
       3.307310; 4.775559; -1.864168;,
       -3.310797; 4.775559; -1.841888;,
       -3.548096; 4.437738; -2.829757;,
       3.537952; 4.437738; -2.853612;,
       3.101846; 6.617794; -0.010443;,
       3.143515; 5.908169; 1.099139;,
       0.004490; 6.702011; -0.000015;,
       -3.127046; 5.908169; 1.120249;,
       3.074139; 7.007803; -0.010349;,
       3.320341; 5.003235; 2.006507;,
       -3.297767; 5.003235; 2.028787;,
       -3.528963; 4.437738; 2.853582;,
       3.557086; 4.437738; 2.829726;,
       -3.065169; 7.007803; 0.010319;,
       0.004490; 6.702011; -0.000015;,
       3.136044; 5.908169; -1.120279;,
       -3.134518; 5.908169; -1.099169;,
       3.074139; 7.007803; -0.010349;,
       3.306756; 5.003235; -2.028818;,
       -3.311352; 5.003235; -2.006537;,
       -3.548096; 4.437738; -2.829757;,
       3.537952; 4.437738; -2.853612;,
       -3.065169; 7.007803; 0.010319;,
       -3.298321; 4.775560; 1.864138;,
       -3.297767; 5.003235; 2.028787;,
       -3.134315; 5.698985; 0.937069;,
       -3.528963; 4.437738; 2.853582;,
       -3.127046; 5.908169; 1.120249;,
       -3.092869; 6.617794; 0.010412;,
       -3.065169; 7.007803; 0.010319;,
       -3.134518; 5.908169; -1.099169;,
       -3.140554; 5.698986; -0.915944;,
       -3.311352; 5.003235; -2.006537;,
       -3.310797; 4.775559; -1.841888;,
       -3.548096; 4.437738; -2.829757;,
       3.320341; 5.003235; 2.006507;,
       3.319787; 4.775560; 1.841857;,
       3.149546; 5.698985; 0.915914;,
       3.557086; 4.437738; 2.829726;,
       3.143515; 5.908169; 1.099139;,
       3.101846; 6.617794; -0.010443;,
       3.074139; 7.007803; -0.010349;,
       3.136044; 5.908169; -1.120279;,
       3.143308; 5.698986; -0.937099;,
       3.306756; 5.003235; -2.028818;,
       3.307310; 4.775559; -1.864168;,
       3.537952; 4.437738; -2.853612;,
       -2.846608; 4.782759; 1.880265;,
       -2.859210; 4.782759; -1.863206;,
       -2.937509; 2.530884; 1.214179;,
       -2.852909; 6.630759; 0.008530;,
       -2.934603; 2.530884; 2.077238;,
       -3.040072; -0.072857; 1.214524;,
       -3.050862; -0.072857; -1.990490;,
       2.836626; 2.530884; 1.194740;,
       2.928353; -0.072857; -2.010619;,
       2.750165; 4.782759; 1.861424;,
       2.939143; -0.072857; 1.194395;,
       2.743864; 6.630759; -0.010312;,
       2.737562; 4.782759; -1.882048;,
       2.839531; 2.530884; 2.057799;,
       -2.937509; 2.530884; 1.214179;,
       2.839531; 2.530884; 2.057799;,
       -2.934603; 2.530884; 2.077238;,
       2.836626; 2.530884; 1.194740;,
       2.939143; -0.072857; 1.194395;,
       -2.937509; 2.530884; 1.214179;,
       -3.040072; -0.072857; 1.214524;,
       2.836626; 2.530884; 1.194740;,
       2.750165; 4.782759; 1.861424;,
       -2.934603; 2.530884; 2.077238;,
       2.839531; 2.530884; 2.057799;,
       -2.846608; 4.782759; 1.880265;,
       -3.050862; -0.072857; -1.990490;,
       2.737562; 4.782759; -1.882048;,
       2.928353; -0.072857; -2.010619;,
       -2.859210; 4.782759; -1.863206;,
       2.510094; 1.668577; 1.017950;,
       2.512146; 2.586298; 1.627454;,
       2.509486; 1.849124; 0.837404;,
       2.513006; 2.586298; 1.882786;,
       -2.920194; 1.668448; 1.036232;,
       -2.918142; 2.586169; 1.645736;,
       -2.920801; 1.848995; 0.855685;,
       -2.917282; 2.586169; 1.901067;,
       -0.057650; 5.706759; -0.936759;,
       -2.859210; 4.782759; -1.863206;,
       2.743864; 6.630759; -0.010312;,
       2.510094; 1.668577; 1.017950;,
       2.765425; 1.668577; 1.017091;,
       2.513006; 2.586298; 1.882786;,
       2.765425; 1.668577; 1.017091;,
       2.768336; 2.586298; 1.881926;,
       2.513006; 2.586298; 1.882786;,
       2.764818; 1.849124; 0.836544;,
       2.767477; 2.586298; 1.626595;,
       2.765425; 1.668577; 1.017091;,
       2.765425; 1.668577; 1.017091;,
       2.768336; 2.586298; 1.881926;,
       2.764818; 1.849124; 0.836544;,
       2.509486; 1.849124; 0.837404;,
       2.767477; 2.586298; 1.626595;,
       2.509486; 1.849124; 0.837404;,
       2.512146; 2.586298; 1.627454;,
       -2.920194; 1.668448; 1.036232;,
       -2.664862; 1.668448; 1.035372;,
       -2.917282; 2.586169; 1.901067;,
       -2.664862; 1.668448; 1.035372;,
       -2.661951; 2.586169; 1.900208;,
       -2.917282; 2.586169; 1.901067;,
       -2.665470; 1.848995; 0.854826;,
       -2.662811; 2.586169; 1.644876;,
       -2.664862; 1.668448; 1.035372;,
       -2.664862; 1.668448; 1.035372;,
       -2.661951; 2.586169; 1.900208;,
       -2.665470; 1.848995; 0.854826;,
       -2.920801; 1.848995; 0.855685;,
       -2.662811; 2.586169; 1.644876;,
       -2.920801; 1.848995; 0.855685;,
       -2.918142; 2.586169; 1.645736;,
       -2.390786; 5.632423; 0.524556;,
       -3.314781; 8.162012; 0.527667;,
       -3.314781; 5.632423; 0.527666;,
       -2.390786; 8.162012; 0.524556;,
       -2.389661; 4.663078; 0.858719;,
       -3.313656; 4.663078; 0.861829;,
       -2.389661; -0.070971; 0.858718;,
       -3.544654; -0.070971; 0.862606;,
       -3.317892; 5.632423; -0.396328;,
       -2.393897; 8.162011; -0.399439;,
       -2.393897; 5.632423; -0.399439;,
       -3.317892; 8.162011; -0.396328;,
       -3.319016; 4.663078; -0.730537;,
       -2.395022; 4.663078; -0.733648;,
       -2.395022; -0.070971; -0.733649;,
       -3.550015; -0.070971; -0.729760;,
       -3.313656; 4.663078; 0.861829;,
       -3.317892; 5.632423; -0.396328;,
       -3.319016; 4.663078; -0.730537;,
       -3.314781; 5.632423; 0.527666;,
       -3.544654; -0.070971; 0.862606;,
       -3.550015; -0.070971; -0.729760;,
       -2.393897; 5.632423; -0.399439;,
       -2.390786; 8.162012; 0.524556;,
       -2.390786; 5.632423; 0.524556;,
       -2.393897; 8.162011; -0.399439;,
       -3.314781; 5.632423; 0.527666;,
       -3.317892; 8.162011; -0.396328;,
       -3.317892; 5.632423; -0.396328;,
       -3.314781; 8.162012; 0.527667;,
       -2.393897; 8.162011; -0.399439;,
       -3.314781; 8.162012; 0.527667;,
       -2.390786; 8.162012; 0.524556;,
       -3.317892; 8.162011; -0.396328;;
       117;
       3;0, 1, 2;,
       3;0, 3, 1;,
       3;2, 4, 0;,
       3;5, 2, 1;,
       3;5, 6, 2;,
       3;5, 6, 5;,
       3;5, 7, 6;,
       3;8, 7, 5;,
       3;9, 10, 11;,
       3;9, 12, 10;,
       3;10, 13, 11;,
       3;10, 13, 13;,
       3;14, 13, 10;,
       3;14, 13, 13;,
       3;15, 13, 14;,
       3;15, 16, 13;,
       3;11, 17, 9;,
       3;18, 19, 20;,
       3;18, 21, 19;,
       3;20, 22, 18;,
       3;20, 22, 22;,
       3;23, 22, 20;,
       3;23, 22, 22;,
       3;24, 22, 23;,
       3;24, 25, 22;,
       3;20, 19, 26;,
       3;27, 28, 29;,
       3;27, 30, 28;,
       3;31, 29, 28;,
       3;31, 32, 29;,
       3;31, 32, 31;,
       3;31, 33, 32;,
       3;34, 33, 31;,
       3;27, 29, 35;,
       3;36, 37, 38;,
       3;36, 39, 37;,
       3;40, 38, 37;,
       3;40, 41, 38;,
       3;42, 41, 40;,
       3;42, 41, 41;,
       3;43, 41, 42;,
       3;43, 44, 41;,
       3;45, 44, 43;,
       3;45, 46, 44;,
       3;47, 46, 45;,
       3;48, 49, 50;,
       3;48, 51, 49;,
       3;50, 52, 48;,
       3;50, 52, 52;,
       3;53, 52, 50;,
       3;53, 54, 52;,
       3;53, 54, 53;,
       3;53, 55, 54;,
       3;56, 55, 53;,
       3;56, 57, 55;,
       3;58, 57, 56;,
       3;58, 59, 57;,
       3;60, 61, 62;,
       3;60, 63, 61;,
       3;64, 60, 62;,
       3;61, 65, 62;,
       3;61, 66, 65;,
       3;67, 68, 69;,
       3;67, 70, 68;,
       3;68, 71, 69;,
       3;68, 72, 71;,
       3;67, 69, 73;,
       3;74, 75, 76;,
       3;74, 77, 75;,
       3;78, 79, 80;,
       3;78, 81, 79;,
       3;82, 83, 84;,
       3;82, 85, 83;,
       3;86, 87, 88;,
       3;86, 89, 87;,
       3;90, 91, 92;,
       3;90, 93, 91;,
       3;94, 95, 96;,
       3;94, 97, 95;,
       3;98, 99, 100;,
       3;101, 102, 103;,
       3;104, 105, 106;,
       3;107, 108, 109;,
       3;110, 108, 111;,
       3;112, 113, 114;,
       3;115, 116, 114;,
       3;117, 118, 119;,
       3;120, 121, 122;,
       3;123, 124, 125;,
       3;126, 124, 127;,
       3;128, 129, 130;,
       3;131, 132, 130;,
       3;133, 134, 135;,
       3;133, 136, 134;,
       3;135, 137, 133;,
       3;135, 137, 137;,
       3;138, 137, 135;,
       3;138, 139, 137;,
       3;140, 139, 138;,
       3;141, 142, 143;,
       3;141, 144, 142;,
       3;143, 145, 141;,
       3;143, 145, 145;,
       3;146, 145, 143;,
       3;146, 145, 145;,
       3;147, 145, 146;,
       3;147, 148, 145;,
       3;149, 150, 151;,
       3;149, 152, 150;,
       3;151, 153, 149;,
       3;151, 154, 153;,
       3;155, 156, 157;,
       3;155, 158, 156;,
       3;159, 160, 161;,
       3;159, 162, 160;,
       3;163, 164, 165;,
       3;163, 166, 164;;

      MeshNormals {
       167;
       -0.002265; -0.739797; -0.672827;,
       0.014306; -0.739501; -0.673004;,
       -0.014718; -0.731844; -0.681313;,
       0.047230; -0.707984; -0.704648;,
       -0.051973; -0.707984; -0.704313;,
       -0.001778; -0.849112; -0.528209;,
       -0.001778; -0.849112; -0.528209;,
       -0.001089; -0.946283; -0.323339;,
       -0.001089; -0.946283; -0.323339;,
       0.002265; -0.739797; 0.672827;,
       -0.010131; -0.731844; 0.681397;,
       0.018838; -0.739501; 0.672892;,
       -0.047230; -0.707984; 0.704647;,
       0.001778; -0.849112; 0.528209;,
       0.001778; -0.849112; 0.528209;,
       0.001089; -0.946283; 0.323339;,
       0.001089; -0.946283; 0.323339;,
       0.051973; -0.707984; 0.704313;,
       -0.021298; 0.745298; 0.666391;,
       0.002244; 0.745520; 0.666480;,
       0.019924; 0.736263; 0.676403;,
       -0.068007; 0.706480; 0.704458;,
       0.002150; 0.769594; 0.638530;,
       0.002150; 0.769594; 0.638530;,
       0.001905; 0.824514; 0.565839;,
       0.001905; 0.824514; 0.565839;,
       0.072748; 0.706481; 0.703983;,
       -0.002244; 0.745520; -0.666480;,
       -0.025785; 0.745298; -0.666232;,
       0.015369; 0.736263; -0.676521;,
       -0.072748; 0.706480; -0.703984;,
       -0.002150; 0.769594; -0.638530;,
       -0.002150; 0.769594; -0.638530;,
       -0.001905; 0.824514; -0.565838;,
       -0.001905; 0.824514; -0.565838;,
       0.068006; 0.706481; -0.704457;,
       -0.984442; 0.104533; -0.141235;,
       -0.987065; 0.104900; -0.121238;,
       -0.995335; 0.073495; -0.062497;,
       -0.974274; 0.133617; -0.181485;,
       -0.997111; 0.072047; -0.024050;,
       -0.998470; 0.055196; 0.003362;,
       -0.997482; 0.070845; 0.003358;,
       -0.996927; 0.072047; 0.030763;,
       -0.994892; 0.073495; 0.069197;,
       -0.986226; 0.104900; 0.127882;,
       -0.983469; 0.104533; 0.147860;,
       -0.973030; 0.133617; 0.188041;,
       0.986227; 0.104893; -0.127884;,
       0.983469; 0.104533; -0.147859;,
       0.994892; 0.073487; -0.069207;,
       0.973030; 0.133617; -0.188041;,
       0.996926; 0.072045; -0.030775;,
       0.998470; 0.055203; -0.003361;,
       0.997480; 0.070863; -0.003358;,
       0.997111; 0.072045; 0.024062;,
       0.995335; 0.073487; 0.062506;,
       0.987065; 0.104894; 0.121240;,
       0.984442; 0.104534; 0.141233;,
       0.974274; 0.133619; 0.181485;,
       -0.999650; 0.026231; 0.003366;,
       -0.999559; 0.029517; 0.003369;,
       -0.999220; 0.039347; 0.003369;,
       -0.999994; 0.000000; 0.003367;,
       -0.999220; 0.039340; 0.003364;,
       -0.999220; 0.039356; 0.003371;,
       -0.999220; 0.039351; 0.003364;,
       0.999219; 0.039357; -0.003370;,
       0.999346; 0.035286; -0.007898;,
       0.999428; 0.033587; 0.003878;,
       0.999220; 0.039343; -0.003364;,
       0.999436; 0.031213; -0.012425;,
       0.998250; 0.040368; -0.043217;,
       0.999219; 0.039361; -0.003364;,
       0.000000; -1.000000; 0.000000;,
       0.000000; -1.000000; 0.000000;,
       0.000000; -1.000000; 0.000000;,
       0.000000; -1.000000; 0.000000;,
       0.003367; -0.000000; 0.999994;,
       0.003367; -0.000000; 0.999994;,
       0.003367; -0.000000; 0.999994;,
       0.003367; -0.000000; 0.999994;,
       0.003354; 0.087007; 0.996202;,
       0.003354; 0.087007; 0.996202;,
       0.003354; 0.087007; 0.996202;,
       0.003354; 0.087007; 0.996202;,
       -0.003365; 0.026337; -0.999647;,
       -0.003365; 0.026337; -0.999647;,
       -0.003365; 0.026337; -0.999647;,
       -0.003365; 0.026337; -0.999647;,
       -0.999994; -0.000000; 0.003367;,
       -0.999994; -0.000000; 0.003367;,
       -0.999994; -0.000000; 0.003367;,
       -0.999994; -0.000000; 0.003367;,
       -0.999994; 0.000000; 0.003366;,
       -0.999994; 0.000000; 0.003366;,
       -0.999994; 0.000001; 0.003365;,
       -0.999994; -0.000000; 0.003367;,
       -0.004460; 0.714746; -0.699370;,
       -0.004460; 0.714746; -0.699370;,
       -0.004460; 0.714746; -0.699370;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.999994; -0.000001; -0.003365;,
       0.999994; -0.000001; -0.003365;,
       0.999994; -0.000001; -0.003365;,
       0.999994; -0.000001; -0.003365;,
       0.999994; -0.000001; -0.003365;,
       -0.002296; 0.731153; -0.682210;,
       -0.002296; 0.731153; -0.682210;,
       -0.002297; 0.731153; -0.682210;,
       -0.002297; 0.731153; -0.682210;,
       -0.002297; 0.731153; -0.682210;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.002450; -0.685828; 0.727759;,
       0.999994; 0.000001; -0.003367;,
       0.999994; 0.000001; -0.003367;,
       0.999994; 0.000001; -0.003367;,
       0.999994; 0.000001; -0.003367;,
       0.999994; 0.000001; -0.003367;,
       -0.002297; 0.731153; -0.682210;,
       -0.002297; 0.731153; -0.682210;,
       -0.002297; 0.731153; -0.682210;,
       -0.002296; 0.731153; -0.682210;,
       -0.002296; 0.731153; -0.682210;,
       0.003346; 0.109979; 0.993928;,
       0.003367; -0.000000; 0.999994;,
       0.003284; 0.219959; 0.975504;,
       0.003367; -0.000000; 0.999994;,
       0.003284; 0.219959; 0.975504;,
       0.003346; 0.109979; 0.993928;,
       0.003367; -0.000000; 0.999994;,
       0.003367; -0.000000; 0.999994;,
       -0.003346; 0.109993; -0.993927;,
       -0.003367; 0.000000; -0.999994;,
       -0.003284; 0.219987; -0.975497;,
       -0.003367; 0.000000; -0.999994;,
       -0.003320; 0.165247; -0.986247;,
       -0.003320; 0.165247; -0.986247;,
       -0.003367; 0.000000; -0.999994;,
       -0.003367; 0.000000; -0.999994;,
       -0.999862; 0.016250; 0.003366;,
       -0.999994; -0.000000; 0.003367;,
       -0.999466; 0.032500; 0.003365;,
       -0.999994; 0.000000; 0.003367;,
       -0.998806; 0.048737; 0.003362;,
       -0.998806; 0.048737; 0.003362;,
       0.999994; 0.000000; -0.003366;,
       0.999994; 0.000000; -0.003366;,
       0.999994; 0.000000; -0.003366;,
       0.999994; 0.000000; -0.003366;,
       -0.999994; -0.000000; 0.003367;,
       -0.999994; -0.000000; 0.003367;,
       -0.999994; -0.000000; 0.003367;,
       -0.999994; -0.000000; 0.003367;,
       -0.000000; 1.000000; -0.000001;,
       -0.000000; 1.000000; -0.000001;,
       -0.000000; 1.000000; -0.000001;,
       -0.000000; 1.000000; -0.000001;;
       117;
       3;0, 1, 2;,
       3;0, 3, 1;,
       3;2, 4, 0;,
       3;5, 2, 1;,
       3;5, 6, 2;,
       3;5, 6, 5;,
       3;5, 7, 6;,
       3;8, 7, 5;,
       3;9, 10, 11;,
       3;9, 12, 10;,
       3;10, 13, 11;,
       3;10, 13, 13;,
       3;14, 13, 10;,
       3;14, 13, 13;,
       3;15, 13, 14;,
       3;15, 16, 13;,
       3;11, 17, 9;,
       3;18, 19, 20;,
       3;18, 21, 19;,
       3;20, 22, 18;,
       3;20, 22, 22;,
       3;23, 22, 20;,
       3;23, 22, 22;,
       3;24, 22, 23;,
       3;24, 25, 22;,
       3;20, 19, 26;,
       3;27, 28, 29;,
       3;27, 30, 28;,
       3;31, 29, 28;,
       3;31, 32, 29;,
       3;31, 32, 31;,
       3;31, 33, 32;,
       3;34, 33, 31;,
       3;27, 29, 35;,
       3;36, 37, 38;,
       3;36, 39, 37;,
       3;40, 38, 37;,
       3;40, 41, 38;,
       3;42, 41, 40;,
       3;42, 41, 41;,
       3;43, 41, 42;,
       3;43, 44, 41;,
       3;45, 44, 43;,
       3;45, 46, 44;,
       3;47, 46, 45;,
       3;48, 49, 50;,
       3;48, 51, 49;,
       3;50, 52, 48;,
       3;50, 52, 52;,
       3;53, 52, 50;,
       3;53, 54, 52;,
       3;53, 54, 53;,
       3;53, 55, 54;,
       3;56, 55, 53;,
       3;56, 57, 55;,
       3;58, 57, 56;,
       3;58, 59, 57;,
       3;60, 61, 62;,
       3;60, 63, 61;,
       3;64, 60, 62;,
       3;61, 65, 62;,
       3;61, 66, 65;,
       3;67, 68, 69;,
       3;67, 70, 68;,
       3;68, 71, 69;,
       3;68, 72, 71;,
       3;67, 69, 73;,
       3;74, 75, 76;,
       3;74, 77, 75;,
       3;78, 79, 80;,
       3;78, 81, 79;,
       3;82, 83, 84;,
       3;82, 85, 83;,
       3;86, 87, 88;,
       3;86, 89, 87;,
       3;90, 91, 92;,
       3;90, 93, 91;,
       3;94, 95, 96;,
       3;94, 97, 95;,
       3;98, 99, 100;,
       3;101, 102, 103;,
       3;104, 105, 106;,
       3;107, 108, 109;,
       3;110, 108, 111;,
       3;112, 113, 114;,
       3;115, 116, 114;,
       3;117, 118, 119;,
       3;120, 121, 122;,
       3;123, 124, 125;,
       3;126, 124, 127;,
       3;128, 129, 130;,
       3;131, 132, 130;,
       3;133, 134, 135;,
       3;133, 136, 134;,
       3;135, 137, 133;,
       3;135, 137, 137;,
       3;138, 137, 135;,
       3;138, 139, 137;,
       3;140, 139, 138;,
       3;141, 142, 143;,
       3;141, 144, 142;,
       3;143, 145, 141;,
       3;143, 145, 145;,
       3;146, 145, 143;,
       3;146, 145, 145;,
       3;147, 145, 146;,
       3;147, 148, 145;,
       3;149, 150, 151;,
       3;149, 152, 150;,
       3;151, 153, 149;,
       3;151, 154, 153;,
       3;155, 156, 157;,
       3;155, 158, 156;,
       3;159, 160, 161;,
       3;159, 162, 160;,
       3;163, 164, 165;,
       3;163, 166, 164;;
      }

      MeshTextureCoords {
       167;
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
       0.367539; 0.539797;,
       0.024200; 0.539797;,
       0.306420; 0.746330;,
       0.195869; 0.370305;,
       0.385577; 0.746330;,
       0.306420; 0.985135;,
       0.012467; 0.985135;,
       0.306420; 0.746330;,
       0.012467; 0.985135;,
       0.367539; 0.539797;,
       0.306420; 0.985135;,
       0.195869; 0.370305;,
       0.024200; 0.539797;,
       0.385577; 0.746330;,
       0.455929; 0.753819;,
       0.985514; 0.674662;,
       0.455929; 0.674662;,
       0.985514; 0.753819;,
       0.994866; 0.992613;,
       0.455879; 0.753808;,
       0.446472; 0.992613;,
       0.985463; 0.753808;,
       0.977486; 0.468077;,
       0.456037; 0.674611;,
       0.985622; 0.674611;,
       0.464168; 0.468077;,
       0.444809; 0.453201;,
       0.975665; 0.007863;,
       0.993204; 0.453201;,
       0.462348; 0.007863;,
       0.837228; 0.662309;,
       0.532842; 0.694383;,
       0.837568; 0.695586;,
       0.516565; 0.656768;,
       0.837228; 0.662309;,
       0.532842; 0.694383;,
       0.837568; 0.695586;,
       0.516565; 0.656768;,
       0.394995; 0.237250;,
       0.293710; 0.337250;,
       0.496280; 0.137250;,
       0.523034; 0.698087;,
       0.837813; 0.697291;,
       0.520745; 0.661267;,
       0.837813; 0.699375;,
       0.833439; 0.658385;,
       0.522829; 0.663351;,
       0.837228; 0.662309;,
       0.531992; 0.657037;,
       0.835483; 0.695586;,
       0.831314; 0.693501;,
       0.517415; 0.694113;,
       0.833439; 0.658386;,
       0.524914; 0.661267;,
       0.833913; 0.696456;,
       0.522829; 0.661267;,
       0.521219; 0.697253;,
       0.523034; 0.698087;,
       0.837813; 0.697291;,
       0.520745; 0.661267;,
       0.837813; 0.699375;,
       0.833439; 0.658385;,
       0.522829; 0.663351;,
       0.837228; 0.662309;,
       0.531992; 0.657037;,
       0.835483; 0.695586;,
       0.831314; 0.693501;,
       0.517415; 0.694113;,
       0.833439; 0.658386;,
       0.524914; 0.661267;,
       0.833913; 0.696456;,
       0.522829; 0.661267;,
       0.521219; 0.697253;,
       0.986710; 0.369081;,
       0.886710; 0.095316;,
       0.886710; 0.369081;,
       0.986710; 0.095316;,
       0.986710; 0.473988;,
       0.886710; 0.473988;,
       0.986710; 0.986331;,
       0.861710; 0.986331;,
       0.886710; 0.369081;,
       0.986710; 0.095316;,
       0.986710; 0.369081;,
       0.886710; 0.095316;,
       0.886710; 0.473988;,
       0.986710; 0.473988;,
       0.986710; 0.986331;,
       0.861710; 0.986331;,
       0.848928; 0.473776;,
       0.712763; 0.368869;,
       0.676593; 0.473776;,
       0.812763; 0.368869;,
       0.848928; 0.986119;,
       0.676593; 0.986119;,
       0.712614; 0.368825;,
       0.812614; 0.095060;,
       0.812614; 0.368825;,
       0.712614; 0.095060;,
       0.812614; 0.368825;,
       0.712614; 0.095060;,
       0.712614; 0.368825;,
       0.812614; 0.095060;,
       0.683140; 0.120125;,
       0.583140; 0.020125;,
       0.683140; 0.020125;,
       0.583140; 0.120125;;
      }

      MeshVertexColors {
       167;
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
       119; 1.000000; 1.000000; 1.000000; 1.000000;,
       120; 1.000000; 1.000000; 1.000000; 1.000000;,
       121; 1.000000; 1.000000; 1.000000; 1.000000;,
       122; 1.000000; 1.000000; 1.000000; 1.000000;,
       123; 1.000000; 1.000000; 1.000000; 1.000000;,
       124; 1.000000; 1.000000; 1.000000; 1.000000;,
       125; 1.000000; 1.000000; 1.000000; 1.000000;,
       126; 1.000000; 1.000000; 1.000000; 1.000000;,
       127; 1.000000; 1.000000; 1.000000; 1.000000;,
       128; 1.000000; 1.000000; 1.000000; 1.000000;,
       129; 1.000000; 1.000000; 1.000000; 1.000000;,
       130; 1.000000; 1.000000; 1.000000; 1.000000;,
       131; 1.000000; 1.000000; 1.000000; 1.000000;,
       132; 1.000000; 1.000000; 1.000000; 1.000000;,
       133; 1.000000; 1.000000; 1.000000; 1.000000;,
       134; 1.000000; 1.000000; 1.000000; 1.000000;,
       135; 1.000000; 1.000000; 1.000000; 1.000000;,
       136; 1.000000; 1.000000; 1.000000; 1.000000;,
       137; 1.000000; 1.000000; 1.000000; 1.000000;,
       138; 1.000000; 1.000000; 1.000000; 1.000000;,
       139; 1.000000; 1.000000; 1.000000; 1.000000;,
       140; 1.000000; 1.000000; 1.000000; 1.000000;,
       141; 1.000000; 1.000000; 1.000000; 1.000000;,
       142; 1.000000; 1.000000; 1.000000; 1.000000;,
       143; 1.000000; 1.000000; 1.000000; 1.000000;,
       144; 1.000000; 1.000000; 1.000000; 1.000000;,
       145; 1.000000; 1.000000; 1.000000; 1.000000;,
       146; 1.000000; 1.000000; 1.000000; 1.000000;,
       147; 1.000000; 1.000000; 1.000000; 1.000000;,
       148; 1.000000; 1.000000; 1.000000; 1.000000;,
       149; 1.000000; 1.000000; 1.000000; 1.000000;,
       150; 1.000000; 1.000000; 1.000000; 1.000000;,
       151; 1.000000; 1.000000; 1.000000; 1.000000;,
       152; 1.000000; 1.000000; 1.000000; 1.000000;,
       153; 1.000000; 1.000000; 1.000000; 1.000000;,
       154; 1.000000; 1.000000; 1.000000; 1.000000;,
       155; 1.000000; 1.000000; 1.000000; 1.000000;,
       156; 1.000000; 1.000000; 1.000000; 1.000000;,
       157; 1.000000; 1.000000; 1.000000; 1.000000;,
       158; 1.000000; 1.000000; 1.000000; 1.000000;,
       159; 1.000000; 1.000000; 1.000000; 1.000000;,
       160; 1.000000; 1.000000; 1.000000; 1.000000;,
       161; 1.000000; 1.000000; 1.000000; 1.000000;,
       162; 1.000000; 1.000000; 1.000000; 1.000000;,
       163; 1.000000; 1.000000; 1.000000; 1.000000;,
       164; 1.000000; 1.000000; 1.000000; 1.000000;,
       165; 1.000000; 1.000000; 1.000000; 1.000000;,
       166; 1.000000; 1.000000; 1.000000; 1.000000;;
      }

      MeshMaterialList {
       3;
       117;
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
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
       2;

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
         "humans4.jpg";
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
