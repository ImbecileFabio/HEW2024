//--------------------------------------------------------------------------------------
// ピクセルシェーダー
//--------------------------------------------------------------------------------------

// ピクセルの情報の構造体（受け取り用）
struct PS_IN
{
    // float4型　→　float型が４つの構造体
    float4 pos : SV_POSITION; // ピクセルの画面上の座標
    float4 col : COLOR0;
    float2 tex : TEXCOORD;    // ピクセルのUV座標
};

// グローバル変数
// ※C言語側からデータを渡されたときにセットされる変数
Texture2D myTexture : register(t0); // テクスチャー
SamplerState mySampler: register(s0); // サンプラー

// ピクセルシェーダーのエントリポイント
float4 ps_main(PS_IN input) : SV_Target
{
    // Sample関数→テクスチャから街頭のUV位置のピクセルを色を取って来る
    float4 color = myTexture.Sample(mySampler, input.tex);

    // テクスチャの色に頂点データの色をかける
    color = color * input.col;

    // 決定した色をreturnする。
    return color;
}
