// グローバルルートシグネチャ
GlobalRootSignature global =
{
    " "
};

// レイジェネレーション用ルートシグネチャ
LocalRootSignature ray =
{
    "DescriptorTable(UAV(u0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), visibility = SHADER_VISIBILITY_ALL),"
    "DescriptorTable(SRV(t0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), visibility = SHADER_VISIBILITY_ALL)"
};

// レイジェネレーションの関連付け
SubobjectToExportsAssociation rayAsso =
{
    "ray", //サブオブジェクト名
	"RayGen"  //関連付け関数
};

// ミス用ルートシグネチャ
LocalRootSignature miss =
{
    " "
};

// ミスの関連付け
SubobjectToExportsAssociation missAsso =
{
    "miss", //サブオブジェクト名
	"Miss", //関連付け関数
};

// クローゼストヒット用ルートシグネチャ
LocalRootSignature closest =
{
    " "
};

// クリーゼストの関連付け
SubobjectToExportsAssociation closestAsso =
{
    "closest", //サブオブジェクト名
    "Chs"      //関連付け関数
};

// ヒットグループ
TriangleHitGroup hit =
{
    "",  //anyhit
	"Chs"//closesthit
};

// クローゼストヒットの関連付け
SubobjectToExportsAssociation hitAsso =
{
    "closest", //サブオブジェクト名
	"hit"      //関連付け関数
};

// シェーダコンフィグ
RaytracingShaderConfig sConfig =
{
    16, //ペイロードサイズ
	8   //アトリビュートサイズ
};

// シェーダコンフィグの関連付け
SubobjectToExportsAssociation sConfigAsso1 =
{
    "sConfig",
    "RayGen"
};

// シェーダコンフィグの関連付け
SubobjectToExportsAssociation sConfigAsso2 =
{
    "sConfig",
    "Miss"
};

// シェーダコンフィグの関連付け
SubobjectToExportsAssociation sConfigAsso3 =
{
    "sConfig",
    "Chs"
};

// パイプラインコンフィグ
RaytracingPipelineConfig pConfig =
{
    1 //クローゼストヒットの回数
};

// 出力テクスチャ
RWTexture2D<float4> output           : register(u0);
// 加速構造
RaytracingAccelerationStructure TLAS : register(t0);

// ペイロード
struct Payload
{
    float3 color;
};
