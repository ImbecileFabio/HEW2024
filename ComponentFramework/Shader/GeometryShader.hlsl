// Geometry Shader (HLSL)

// 定数バッファ
cbuffer GeometryShaderBuffer : register(b0)
{
    float2 position;    // 中心位置
    float4 color;       // 色
    float thickness;    // 太さ
};


// 頂点シェーダの出力
struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

struct GS_OUTPUT
{
    float4 pos : SV_POSITION;   // 頂点位置（スクリーン座標系）
    float4 color : COLOR;       // 色
};

// ジオメトリシェーダ
[maxvertexcount(8)] // 最大8つの頂点を生成
void gs_main(point VS_OUTPUT input[1], inout LineStream<GS_OUTPUT> OutputStream)
{
    // 四角形の頂点データ(例：左、右、上、下)
    float left = input[0].pos.x - 0.5;
    float right = input[0].pos.x + 0.5;
    float top = input[0].pos.y + 0.5;
    float bottom = input[0].pos.y - 0.5;
    
    
    GS_OUTPUT v;
 
 // 上辺
    v.pos = float4(left, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(right, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);

    // 右辺
    v.pos = float4(right, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(right, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);

    // 下辺
    v.pos = float4(right, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(left, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);

    // 左辺
    v.pos = float4(left, bottom, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
    v.pos = float4(left, top, 0.5f, 1.0f);
    v.color = color;
    OutputStream.Append(v);
}
