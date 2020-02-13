
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
        ColorOp[0]      = SelectArg1;
        ColorArg1[0]    = Diffuse;
        
        AlphaOp[0]      = Disable;

        MinFilter[0]    = Linear;
        MagFilter[0]    = Linear;
        MipFilter[0]    = Linear;
        
        // Disable texture stage 1
        ColorOp[1]      = Disable;
        AlphaOp[1]      = Disable;
    }
}
