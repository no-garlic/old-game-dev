
texture tex0 < string name = ""; >;

technique t0
{
    pass p0
    {
        // Set up reasonable material defaults
        MaterialAmbient = {1.0, 1.0, 1.0, 1.0}; 
        MaterialDiffuse = {1.0, 1.0, 1.0, 1.0}; 
        MaterialSpecular = {1.0, 1.0, 1.0, 1.0}; 
        MaterialPower = 40.0f;
        
        LightEnable[0]  = False;
        Lighting        = False;
        
        // Set up texture stage 0
        Texture[0]      = <tex0>;
        ColorOp[0]      = Modulate;
        ColorArg1[0]    = Texture;
        ColorArg2[0]    = Diffuse;
        
        AlphaOp[0]      = Modulate;
        AlphaArg1[0]    = Texture;
        AlphaArg2[0]    = Diffuse;
        
        AlphaBlendEnable = True;
        SrcBlend        = SrcAlpha;
        DestBlend       = InvSrcAlpha;
        
        AddressU[0]     = Wrap;
        AddressV[0]     = Wrap;
        MinFilter[0]    = Linear;
        MagFilter[0]    = Linear;
        MipFilter[0]    = Linear;
        
        // Disable texture stage 1
        ColorOp[1]      = Disable;
        AlphaOp[1]      = Disable;
    }
}
