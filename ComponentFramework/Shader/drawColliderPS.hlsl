#include "common.hlsl"

SamplerState g_SamplerState : register(s0);

// �s�N�Z���V�F�[�_�[�̃G���g���|�C���g
float4 ps_main(in PS_IN input) : SV_Target
{
    float4 color = input.col;
    
    if (color.a < 0.1)
    {
        discard;    // �A���t�@�l���Ⴏ��΃s�N�Z����j��
    }
    
    return color;
}
