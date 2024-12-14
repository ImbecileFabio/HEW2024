// Geometry Shader (HLSL)

// �萔�o�b�t�@
cbuffer GeometryShaderBuffer : register(b0)
{
    float2 position;    // ���S�ʒu
    float4 color;       // �F
    float thickness;    // ����
};


// ���_�V�F�[�_�̏o��
struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

struct GS_OUTPUT
{
    float4 pos : SV_POSITION;   // ���_�ʒu�i�X�N���[�����W�n�j
    float4 color : COLOR;       // �F
};

// �W�I���g���V�F�[�_
[maxvertexcount(8)] // �ő�8�̒��_�𐶐�
void gs_main(point VS_OUTPUT input[1], inout LineStream<GS_OUTPUT> OutputStream)
{
    // �l�p�`�̒��_�f�[�^(��F���A�E�A��A��)
    float left = input[0].pos.x - 0.5;
    float right = input[0].pos.x + 0.5;
    float top = input[0].pos.y + 0.5;
    float bottom = input[0].pos.y - 0.5;
    
    
    GS_OUTPUT v;
 
 // ���
    v.pos = float4(left, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(right, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);

    // �E��
    v.pos = float4(right, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(right, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);

    // ����
    v.pos = float4(right, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(left, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);

    // ����
    v.pos = float4(left, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(left, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
}
