// �O���[�o�����[�g�V�O�l�`��
GlobalRootSignature global =
{
    " "
};

// ���C�W�F�l���[�V�����p���[�g�V�O�l�`��
LocalRootSignature ray =
{
    "DescriptorTable(UAV(u0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), visibility = SHADER_VISIBILITY_ALL),"
    "DescriptorTable(SRV(t0, numDescriptors = 1, space = 0, offset = DESCRIPTOR_RANGE_OFFSET_APPEND), visibility = SHADER_VISIBILITY_ALL)"
};

// ���C�W�F�l���[�V�����̊֘A�t��
SubobjectToExportsAssociation rayAsso =
{
    "ray", //�T�u�I�u�W�F�N�g��
	"RayGen"  //�֘A�t���֐�
};

// �~�X�p���[�g�V�O�l�`��
LocalRootSignature miss =
{
    " "
};

// �~�X�̊֘A�t��
SubobjectToExportsAssociation missAsso =
{
    "miss", //�T�u�I�u�W�F�N�g��
	"Miss", //�֘A�t���֐�
};

// �N���[�[�X�g�q�b�g�p���[�g�V�O�l�`��
LocalRootSignature closest =
{
    " "
};

// �N���[�[�X�g�̊֘A�t��
SubobjectToExportsAssociation closestAsso =
{
    "closest", //�T�u�I�u�W�F�N�g��
    "Chs"      //�֘A�t���֐�
};

// �q�b�g�O���[�v
TriangleHitGroup hit =
{
    "",  //anyhit
	"Chs"//closesthit
};

// �N���[�[�X�g�q�b�g�̊֘A�t��
SubobjectToExportsAssociation hitAsso =
{
    "closest", //�T�u�I�u�W�F�N�g��
	"hit"      //�֘A�t���֐�
};

// �V�F�[�_�R���t�B�O
RaytracingShaderConfig sConfig =
{
    16, //�y�C���[�h�T�C�Y
	8   //�A�g���r���[�g�T�C�Y
};

// �V�F�[�_�R���t�B�O�̊֘A�t��
SubobjectToExportsAssociation sConfigAsso1 =
{
    "sConfig",
    "RayGen"
};

// �V�F�[�_�R���t�B�O�̊֘A�t��
SubobjectToExportsAssociation sConfigAsso2 =
{
    "sConfig",
    "Miss"
};

// �V�F�[�_�R���t�B�O�̊֘A�t��
SubobjectToExportsAssociation sConfigAsso3 =
{
    "sConfig",
    "Chs"
};

// �p�C�v���C���R���t�B�O
RaytracingPipelineConfig pConfig =
{
    1 //�N���[�[�X�g�q�b�g�̉�
};

// �o�̓e�N�X�`��
RWTexture2D<float4> output           : register(u0);
// �����\��
RaytracingAccelerationStructure TLAS : register(t0);

// �y�C���[�h
struct Payload
{
    float3 color;
};
