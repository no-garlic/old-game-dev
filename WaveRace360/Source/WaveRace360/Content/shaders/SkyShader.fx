
matrix m_viewMatrix;
matrix m_projectionMatrix;
texture m_texture;


sampler linear_sampler = sampler_state
{
    Texture   = (m_texture);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = Clamp;
    ADDRESSV = Clamp;
};


void VS ( in  float3 v0   : POSITION,
          out float4 oPos : POSITION,
          out float3 oT0  : TEXCOORD0 )
{
    // Strip any translation off of the view matrix
    // Use only rotations & the projection matrix
    float4x4 m_viewMatrixNoTrans =
    {
        m_viewMatrix[0],
        m_viewMatrix[1],
        m_viewMatrix[2],
        float4( 0.f, 0.f, 0.f, 1.f )
    };

    // Output the position
    oPos = mul( float4(v0,1.f), mul( m_viewMatrixNoTrans, m_projectionMatrix ) );
    
    // Calculate the cube map texture coordinates
    // Because this is a cube-map, the 3-D texture coordinates are calculated
    // from the world-position of the skybox vertex.
    // v0 (from the skybox mesh) is considered to be pre-transformed into world space
    oT0 = v0;
}


void PS( in  float3 t0 : TEXCOORD0,
         out float4 r0 : COLOR0 )
{
    // The skybox texture is pre-lit, so simply output the texture color
    r0 = texCUBE( linear_sampler, t0 );
}


technique tec0
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_1_4 PS();
        
        ZEnable = FALSE;
        ZWriteEnable = FALSE;
        AlphaBlendEnable = FALSE;
        CullMode = CCW;
        AlphaTestEnable = FALSE;
    }
}

