#include "Raytracing.hlsli"

// レイジェネレーション
[shader("raygeneration")]
void RayGen()
{
   /*インデックスの取得*/
    uint3 index = DispatchRaysIndex();
    /*横幅,縦幅,深度の取得*/
    uint3 dimension = DispatchRaysDimensions();
    
    /*スクリーンのアスペクト比*/
    float aspect = dimension.x / dimension.y;
    
    /*範囲を-1.0f～1.0f*/
    float2 pos = ((index.xy / dimension.xy) * 2.0f) - 1.0f;
    
    RayDesc desc;
    desc.Origin    = float3(0, 0, -2);
    desc.Direction = normalize(float3(pos.x * aspect, -pos.y, 1.0f));
    desc.TMin      = 0.0;
    desc.TMax      = 100000.0;
    
    Payload payload;
    TraceRay(TLAS, 0 /*rayFlags*/, 0xFF, 0 /* ray index*/, 0, 0, desc, payload);

    output[index.xy] = float4(payload.color, 1.0f);
    //output[index.xy] = float4(1.0f, 0.0f, 0.0f, 1.0f);

}

// ミス
[shader("miss")]
void Miss(inout Payload payload)
{
    payload.color = float3(1.0f, 0.0f, 0.0f);
}

// クローゼストヒット
[shader("closesthit")]
void Chs(inout Payload payload, in BuiltInTriangleIntersectionAttributes attribute)
{
    payload.color = float3(1.0f, 1.0f, 1.0f);
}