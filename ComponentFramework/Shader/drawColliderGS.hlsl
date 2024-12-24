struct GS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

[maxvertexcount(4)]
void gs_main(line GS_INPUT input[2], inout TriangleStream<PS_INPUT> triStream)
{
    float2 lineDir = normalize(input[1].position.xy - input[0].position.xy);
    float2 perpendicular = float2(-lineDir.y, lineDir.x);

    float lineWidth = 5.0; // ライン幅（ピクセル単位）

    float2 offset = perpendicular * lineWidth * 0.5;

    PS_INPUT vertex;

    // 四角形の頂点を生成
    vertex.position = float4(input[0].position.xy - offset, input[0].position.zw);
    vertex.color = input[0].color;
    triStream.Append(vertex);

    vertex.position = float4(input[0].position.xy + offset, input[0].position.zw);
    vertex.color = input[0].color;
    triStream.Append(vertex);

    vertex.position = float4(input[1].position.xy - offset, input[1].position.zw);
    vertex.color = input[1].color;
    triStream.Append(vertex);

    vertex.position = float4(input[1].position.xy + offset, input[1].position.zw);
    vertex.color = input[1].color;
    triStream.Append(vertex);
}
