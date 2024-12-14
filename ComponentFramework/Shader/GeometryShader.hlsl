// Geometry Shader (HLSL)

// �萔�o�b�t�@
cbuffer GeometryShaderBuffer : register(b0)
{
    float4x4 viewProjMatrix; // �r���[�~�v���W�F�N�V�����s��
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
    
    // �l���̍��W���v�Z
    float4 topLeft = mul(float4(left, top, 0.0, 1.0), viewProjMatrix);
    float4 topRight = mul(float4(right, top, 0.0, 1.0), viewProjMatrix);
    float4 bottomLeft = mul(float4(left, bottom, 0.0, 1.0), viewProjMatrix);
    float4 bottomRight = mul(float4(right, top, 0.0, 1.0), viewProjMatrix);
    
    GS_OUTPUT v;
 
    // ���
    v.pos = topLeft; v.color = input[0].color; OutputStream.Append(v);
    v.pos = topRight; v.color = input[0].color; OutputStream.Append(v);
    
    // �E��
    v.pos = topRight; v.color = input[0].color; OutputStream.Append(v);
    v.pos = bottomRight; v.color = input[0].color; OutputStream.Append(v);

    // ����
    v.pos = bottomRight; v.color = input[0].color; OutputStream.Append(v);
    v.pos = bottomLeft; v.color = input[0].color; OutputStream.Append(v);

    // ����
    v.pos = bottomLeft; v.color = input[0].color; OutputStream.Append(v);
    v.pos = topLeft; v.color = input[0].color; OutputStream.Append(v);
}
