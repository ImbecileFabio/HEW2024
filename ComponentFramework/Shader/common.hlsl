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
    bool Enable; //�g�p���邩�ۂ�
    bool3 Dummy; // PADDING
    float4 Direction; // ����
    float4 Diffuse; // �g�U���ˌ��p�̌��̋���
    float4 Ambient; // �����p�̌��̋���
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
    float fadeProgress; // �t�F�[�h�i�s�x (0.0 �` 1.0)
    float2 center; // �t�F�[�h�̒��S���W�i0.5, 0.5 �͉�ʒ����j
    float edgeWidth; // �t�F�[�h�̋��E���i�X���[�Y�ȑJ�ڂɉe���j
    bool isFadeOut; // �t�F�[�h�A�E�g���t�F�[�h�C�����itrue: �t�F�[�h�A�E�g�Afalse: �t�F�[�h�C���j
};