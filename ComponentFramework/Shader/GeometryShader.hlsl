// Geometry Shader (HLSL)

// 定数バッファ
cbuffer GeometryShaderBuffer : register(b0)
{
    float4x4 viewProjMatrix; // ビュー×プロジェクション行列
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
    
    // 四隅の座標を計算
    float4 topLeft = mul(float4(left, top, 0.0, 1.0), viewProjMatrix);
    float4 topRight = mul(float4(right, top, 0.0, 1.0), viewProjMatrix);
    float4 bottomLeft = mul(float4(left, bottom, 0.0, 1.0), viewProjMatrix);
    float4 bottomRight = mul(float4(right, top, 0.0, 1.0), viewProjMatrix);
    
    GS_OUTPUT v;
 
    // 上辺
    v.pos = topLeft; v.color = input[0].color; OutputStream.Append(v);
    v.pos = topRight; v.color = input[0].color; OutputStream.Append(v);
    
    // 右辺
    v.pos = topRight; v.color = input[0].color; OutputStream.Append(v);
    v.pos = bottomRight; v.color = input[0].color; OutputStream.Append(v);

    // 下辺
    v.pos = bottomRight; v.color = input[0].color; OutputStream.Append(v);
    v.pos = bottomLeft; v.color = input[0].color; OutputStream.Append(v);

    // 左辺
    v.pos = bottomLeft; v.color = input[0].color; OutputStream.Append(v);
    v.pos = topLeft; v.color = input[0].color; OutputStream.Append(v);
}
