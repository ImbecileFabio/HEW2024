#include "common.hlsl"

Texture2D sceneTexture : register(t0); // シーンの描画結果

Texture2D maskTexture : register(t1); // マスク画像

SamplerState samplerState : register(s0);

float4 ps_main(float4 position : SV_POSITION, float2 uv : TEXCOORD0) : SV_TARGET
{
    // 中心からの距離を計算
    float2 diff = uv - center;
    float distance = length(diff);

    // 現在のフェード半径を計算
    float fadeRadius = isFadeOut ? (1.0 - fadeProgress) : fadeProgress;

    // フェードのスムーズな進行を計算
    float fadeValue = smoothstep(fadeRadius - edgeWidth, fadeRadius + edgeWidth, distance);

    // シーンの色を取得
    float4 sceneColor = sceneTexture.Sample(samplerState, uv);

    // マスクの色を取得（オプション、ない場合は1を使用）
    float maskValue = maskTexture.Sample(samplerState, uv).r;

    // 最終フェード値にマスクの影響を乗算
    fadeValue *= maskValue;

    // フェード処理: 黒との線形補間
    return lerp(float4(0, 0, 0, 1), sceneColor, 1.0f - fadeValue);
}
