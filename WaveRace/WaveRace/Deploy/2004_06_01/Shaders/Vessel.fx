
// Effect Edit Stuff
string XFile = "sea-doo.x";
DWORD  BCLR = 0xff202080;

// Textures
texture tex0 < string name = "Sea Doo.bmp"; >;

// Light direction (view space)
static float3 LightDir < string UIDirectional = "Light Direction"; > = 
    normalize(float3(0.577, -0.577, 0.577)); 

// Light intensity
float4 I_a = { 1.0f, 1.0f, 1.0f, 1.0f };    // ambient
float4 I_d = { 1.0f, 1.0f, 1.0f, 1.0f };    // diffuse
float4 I_s = { 1.0f, 1.0f, 1.0f, 1.0f };    // specular

// Material reflectivity
float4 k_a : MATERIALAMBIENT = { 1.0f, 1.0f, 1.0f, 1.0f };    // ambient
float4 k_d : MATERIALDIFFUSE = { 1.0f, 1.0f, 1.0f, 1.0f };    // diffuse
float4 k_s : MATERIALSPECULAR= { 1.0f, 1.0f, 1.0f, 1.0f };    // specular
int    n   : MATERIALPOWER = 32;                              // power

// Transformations
float4x4 World      : WORLD;
float4x4 View       : VIEW;
float4x4 Projection : PROJECTION;

struct VS_OUTPUT
{
    float4 Pos  : POSITION;
    float4 Diff : COLOR0;
    float4 Spec : COLOR1;
    float2 Tex  : TEXCOORD0;
};

VS_OUTPUT VS(
    float3 Pos  : POSITION, 
    float3 Norm : NORMAL, 
    float2 Tex  : TEXCOORD0)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -LightDir;

    float4x4 WorldView = mul(World, View);

    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);  // position (view space)
    float3 N = normalize(mul(Norm, (float3x3)WorldView)); // normal (view space)

    float3 R = normalize(2 * dot(N, L) * N - L);          // reflection vector (view space)
    float3 V = -normalize(P);                             // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    Out.Diff = I_a * k_a + I_d * k_d * max(0, dot(N, L)); // diffuse + ambient
    Out.Spec = I_s * k_s * pow(max(0, dot(R, V)), n/4);   // specular
    Out.Tex  = Tex;                                       

    return Out;
}

sampler Sampler = sampler_state
{
    Texture   = (tex0);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float4 PS(
    float4 Diff : COLOR0,
    float4 Spec : COLOR1,
    float2 Tex  : TEXCOORD0) : COLOR
{
    return tex2D(Sampler, Tex) * Diff + (Spec * 2);
}

technique tec0
{
    pass p0
    {
        Lighting = False;
        ColorOp[0]      = Disable;
        AlphaOp[0]      = Disable;
        
        // Shaders
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_1_1 PS();
    }
}
