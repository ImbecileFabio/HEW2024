cbuffer WorldBuffer : register(b0)
{
    matrix World;
}
cbuffer ViewBuffer : register(b1)
{
    matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

struct VS_IN
{
    float4 pos : POSITION0;
    float4 nrm : NORMAL0;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 tex : TEXCOORD0;
};

struct LIGHT
{
    bool Enable; //使用するか否か
    bool3 Dummy; // PADDING
    float4 Direction; // 方向
    float4 Diffuse; // 拡散反射光用の光の強さ
    float4 Ambient; // 環境光用の光の強さ
};

cbuffer LigntBuffer : register(b3)
{
    LIGHT Light;
}

struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    bool TextureEnable;
    bool2 Dummy;
};

cbuffer MaterialBuffer : register(b4)
{
    MATERIAL Material;
}

cbuffer FadeParams : register(b5)
{
    float fadeProgress; // フェード進行度 (0.0 ～ 1.0)
    float2 center; // フェードの中心座標（0.5, 0.5 は画面中央）
    float edgeWidth; // フェードの境界幅（スムーズな遷移に影響）
    bool isFadeOut; // フェードアウトかフェードインか（true: フェードアウト、false: フェードイン）
};