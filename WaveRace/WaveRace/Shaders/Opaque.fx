
// Textures
texture tex0 < string name = "Sea Doo.bmp"; >;

// Effect Edit Stuff
string XFile = "sea-doo.x";
DWORD  BCLR = 0xff202080;


technique tec0
{
    pass p0
    {
        // Set up reasonable material defaults
        MaterialAmbient = {1.0, 1.0, 1.0, 1.0}; 
        MaterialDiffuse = {1.0, 1.0, 1.0, 1.0}; 
        MaterialSpecular = {1.0, 1.0, 1.0, 1.0}; 
        MaterialPower = 40.0f;
        
        // Turn lighting on and use light 0
        LightEnable[0] = False;
        Lighting = False;
        
        // Set up texture stage 0
        Texture[0]      = <tex0>;
        ColorOp[0]      = Modulate;
        ColorArg1[0]    = Texture;
        ColorArg2[0]    = Diffuse;
        
        AlphaOp[0]      = Disable;

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
