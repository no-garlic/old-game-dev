//------------------------------------------------------------
// Microsoft® XNA Game Studio Creator's Guide  
// by Stephen Cawood and Pat McGee 
// Copyright (c) McGraw-Hill/Osborne. All rights reserved.
// http://www.mhprofessional.com/product.php?isbn=007149071X
//------------------------------------------------------------
float4x4 fx_WVP : WORLDVIEWPROJ; 

struct gtVertex
{
    float4 f4Position : POSITION0;
    float4 f4Color : COLOR0;
};

struct gtPixelFormat
{
    float4 f4Position : POSITION0;
    float4 f4Color : COLOR0;
};

struct tScreenOutput
{
    float4 f4Color : COLOR0;
};

// alter vertex inputs
void vertex_shader(in gtVertex IN, out gtPixelFormat OUT)
{
     // transform vertex
    OUT.f4Position = mul(IN.f4Position, fx_WVP);
    OUT.f4Color = IN.f4Color;
}
// alter vs output and send to hardware one pixel at a time
void pixel_shader(in gtPixelFormat IN, out tScreenOutput OUT)
{
    float4 fColor = IN.f4Color;
    
	// set f4Color range between 0 and 1
    OUT.f4Color = clamp(fColor, 0, 1);
}

// the shader starts here
technique simple
{
    pass p0
    {
        vertexshader = compile vs_1_1 vertex_shader(); // declare and initialize vs
        pixelshader = compile ps_1_1 pixel_shader();   // declare and initialize ps
    }
}
