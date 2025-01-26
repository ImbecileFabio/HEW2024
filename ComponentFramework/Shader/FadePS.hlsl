#include "common.hlsl"

Texture2D sceneTexture : register(t0); // �V�[���̕`�挋��

Texture2D maskTexture : register(t1); // �}�X�N�摜

SamplerState samplerState : register(s0);

float4 ps_main(float4 position : SV_POSITION, float2 uv : TEXCOORD0) : SV_TARGET
{
    // ���S����̋������v�Z
    float2 diff = uv - center;
    float distance = length(diff);

    // ���݂̃t�F�[�h���a���v�Z
    float fadeRadius = isFadeOut ? (1.0 - fadeProgress) : fadeProgress;

    // �t�F�[�h�̃X���[�Y�Ȑi�s���v�Z
    float fadeValue = smoothstep(fadeRadius - edgeWidth, fadeRadius + edgeWidth, distance);

    // �V�[���̐F���擾
    float4 sceneColor = sceneTexture.Sample(samplerState, uv);

    // �}�X�N�̐F���擾�i�I�v�V�����A�Ȃ��ꍇ��1���g�p�j
    float maskValue = maskTexture.Sample(samplerState, uv).r;

    // �ŏI�t�F�[�h�l�Ƀ}�X�N�̉e������Z
    fadeValue *= maskValue;

    // �t�F�[�h����: ���Ƃ̐��`���
    return lerp(float4(0, 0, 0, 1), sceneColor, 1.0f - fadeValue);
}
