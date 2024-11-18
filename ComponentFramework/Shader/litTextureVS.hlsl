#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;

	//positoin=============================
	// ���[���h�A�r���[�A�v���W�F�N�V�����s����|�����킹�č��W�ϊ����s��
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
    output.pos = mul(input.pos, wvp);
	
	//color=============================
	// �@���x�N�g���̕ϊ��Ɛ��K�����s��
	// ���͂��ꂽ�@�������[���h��Ԃɕϊ����A���K������
	float4 worldNormal;
	worldNormal = mul(input.nrm, World);	// �@�������[���h��Ԃɕϊ�
	worldNormal = normalize(worldNormal);	// �@���x�N�g���𐳋K��

	// ���������Ɩ@���x�N�g���̂Ȃ��Ȃ��v�Z���Ċg�U�������߂�
	float d = -dot(Light.Direction.xyz, worldNormal.xyz);	// ���̕����Ɩ@���̓��ς��v�Z

	d = saturate(d);	// d�̒l��0~1�ɃN�����v

    output.col.xyz = input.col.xyz * d * Light.Diffuse.xyz; // �g�U���̉e������Z
    output.col.xyz += input.col.xyz * Light.Ambient.xyz; // �A���r�G���g�������Z
    output.col.xyz += Material.Emission.xyz; // �G�~�b�V���������Z
    output.col.a = input.col.a * Material.Diffuse.a; // �A���t�@�l
	
	//texture=============================
	// �e�N�X�`�����W�͂��̂܂܎g�p
    output.tex = input.tex;
	
    return output;
}

