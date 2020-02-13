xof 0303txt 0032
template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename;
 [...]
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName;
 DWORD nFloats;
 array FLOAT Floats[nFloats];
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName;
 STRING Value;
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName;
 DWORD Value;
}


Material Wall {
 0.588000;0.588000;0.588000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "corridor08.jpg";
 }
}

Frame Box01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-90.000000,0.000000,1.000000;;
  }

  Mesh  {
   20;
   -30.000000;0.000000;-30.000000;,
   30.000000;0.000000;-30.000000;,
   -30.000000;0.000000;30.000000;,
   30.000000;0.000000;30.000000;,
   -30.000000;180.000000;-30.000000;,
   30.000000;180.000000;-30.000000;,
   -30.000000;180.000000;30.000000;,
   30.000000;180.000000;30.000000;,
   30.000000;180.000000;-30.000000;,
   30.000000;0.000000;-30.000000;,
   -30.000000;180.000000;-30.000000;,
   30.000000;0.000000;-30.000000;,
   30.000000;0.000000;30.000000;,
   30.000000;180.000000;-30.000000;,
   30.000000;0.000000;30.000000;,
   -30.000000;180.000000;30.000000;,
   30.000000;180.000000;30.000000;,
   -30.000000;0.000000;30.000000;,
   -30.000000;180.000000;-30.000000;,
   -30.000000;0.000000;-30.000000;;
   12;
   3;0,3,2;,
   3;3,0,1;,
   3;4,7,5;,
   3;7,4,6;,
   3;0,8,9;,
   3;8,0,10;,
   3;11,7,12;,
   3;7,11,13;,
   3;14,15,2;,
   3;15,14,16;,
   3;17,18,19;,
   3;18,17,6;;

   MeshNormals  {
    6;
    0.000000;-1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;;
    12;
    3;0,0,0;,
    3;0,0,0;,
    3;1,1,1;,
    3;1,1,1;,
    3;2,2,2;,
    3;2,2,2;,
    3;3,3,3;,
    3;3,3,3;,
    3;4,4,4;,
    3;4,4,4;,
    3;5,5,5;,
    3;5,5,5;;
   }

   MeshMaterialList  {
    1;
    12;
    0,
    0,
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
    { Wall }
   }

   MeshTextureCoords  {
    20;
    0.000000;1.000000;,
    0.000000;-2.000000;,
    1.000000;1.000000;,
    1.000000;-2.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;-2.000000;,
    1.000000;-2.000000;,
    1.000000;-2.000000;,
    1.000000;1.000000;,
    0.000000;-2.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;-2.000000;,
    0.000000;1.000000;,
    1.000000;-2.000000;,
    0.000000;-2.000000;,
    0.000000;1.000000;,
    1.000000;-2.000000;,
    1.000000;1.000000;;
   }
  }
 }
}