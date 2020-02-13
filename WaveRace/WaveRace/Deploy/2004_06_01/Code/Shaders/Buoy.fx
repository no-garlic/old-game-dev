
// Textures
texture tex0 < string name = "buoyr.bmp"; >;

// Effect Edit Stuff
string XFile = "buoy.x";
DWORD  BCLR = 0xff202080;

// The light
float3 lightDir
<
    string UIDirectional = "Light Direction";
> = {0.14, 0.43, -0.89};


technique tec0
{
    pass p0
    {
        // Set up reasonable material defaults
        MaterialAmbient = {1.0, 1.0, 1.0, 1.0}; 
        MaterialDiffuse = {1.0, 1.0, 1.0, 1.0}; 
        MaterialSpecular = {1.0, 1.0, 1.0, 1.0}; 
        MaterialPower = 30.0f;
        
        // Set up one directional light
        LightType[0]      = DIRECTIONAL;
        LightDiffuse[0]   = {1.0, 1.0, 1.0, 1.0};
        LightSpecular[0]  = {0.75, 0.75, 0.75, 1.0}; 
        LightAmbient[0]   = {1.0, 1.0, 1.0, 1.0};
        LightDirection[0] = <lightDir>;
        LightRange[0]     = 100000.0;
        
        // Turn lighting on and use light 0
        LightEnable[0] = True;
        Lighting = True;
        ShadeMode = GOURAUD;
        SpecularEnable = True;
        
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
