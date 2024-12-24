#include "common.hlsl"

SamplerState g_SamplerState : register(s0);

// ピクセルシェーダーのエントリポイント
float4 ps_main(in PS_IN input) : SV_Target
{
    float4 color = input.col;
    
    if (color.a < 0.1)
    {
        discard;    // アルファ値が低ければピクセルを破棄
    }
    
    return color;
}
