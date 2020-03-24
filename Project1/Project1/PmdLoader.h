#ifndef OKMONN_PMD_LOADER
#define OKMONN_PMD_LOADER

#include <string>
#include <vector>
#include <fstream>

struct Vec2f {

};
struct Vec3f {
	float a, b, c;
};

namespace okmonn {
	/*���f�����w�b�_*/
	struct PmdInfoHeader {
		union {
			struct {
				/*�t�H�[�}�b�g���*/
				char fmt_type[3];
				/*�o�[�W����*/
				float version;
				/*���f����*/
				char model_name[20];
				/*���f���Ɋւ���R�����g*/
				char comment[256];
			};
			std::uint8_t buffer[283];
		};
	};
	/*���f�����_�f�[�^*/
	struct PmdVertexData {
		union {
			struct {
				/*���W*/
				Vec3f pos;
				/*�@���x�N�g��*/
				Vec3f normal;
				/*UV���W*/
				Vec2f uv;
				/*�ړ����e���{�[���ԍ�*/
				std::uint16_t born_number[2];
				/*born_number[0]�^����e���x(born_number[1] = 100 - born_weight)*/
				std::uint8_t born_weight;
				/*�֊s���t���O*/
				uint8_t edge_flag;
			};
			std::uint8_t buffer[38];
		};
	};
	/*���f���}�e���A���f�[�^*/
	struct PmdMaterialData {
		union {
			struct {
				/*�����F*/
				Vec3f diffuse;
				/*�����F�̕s�����x*/
				float diffuse_alpha;
				/*���ʐ�*/
				float specularity;
				/*����F*/
				Vec3f specular;
				/*���F*/
				Vec3f ambient;
				/*�g�D�[���e�N�X�`���ԍ�*/
				std::uint8_t toon_index;
				/*�֊s���t���O*/
				std::uint8_t edge_flag;
				/*�C���f�b�N�X���X�g��*/
				std::uint32_t index_use_num;
				/*�e�N�X�`���t�@�C����*/
				char texture_file_name[20];
			};
			std::uint8_t buffer[70];
		};
	};
	/*���f���{�[���f�[�^*/
	struct PmdBornData {
		union {
			struct {
				/*�{�[����*/
				char born_name[20];
				/*�e�{�[���ԍ�*/
				std::uint16_t parent_born_index;
				/*�����ɐڂ���{�[���ԍ�*/
				std::uint16_t tail_born_index;
				/*�{�[�����*/
				std::uint8_t born_type;
				/*IK�{�[���ԍ�*/
				std::uint16_t ik_born_index;
				/*�擪�{�[�����W*/
				Vec3f head_born_pos;
			};
			std::uint8_t buffer[39];
		};
	};
	/*���f��IK�f�[�^*/
	struct PmdIkBornData {
		union {
			struct {
				/*IK�{�[���ԍ�*/
				std::uint16_t ik_born_index;
				/*IK�{�[�����ŏ��ɐڑ�����{�[��*/
				std::uint16_t ik_target_born_index;
				/*�q�{�[���̐�*/
				std::uint8_t child_born_num;
				/*�ċA���Z��*/
				std::uint16_t iterations;
				/*���Z1�񓖂���̐����p�x*/
				float control_weight;
				/*�q�{�[���ԍ�*/
				std::vector<std::uint16_t>child_born_index;
			};
			std::uint8_t buffer[11];
		};
	};
	/*���f���\��f�[�^*/
	struct PmdSkinData {
		union {
			struct {
				/*�\�*/
				char skin_name[20];
				/*�\��̒��_��*/
				std::uint32_t skin_vertex_num;
				/*�\��̎��*/
				std::uint8_t skin_type;
				struct {

				};
			};
		};
	};

	/*�t�@�C���̓ǂݍ���
	.�t�@�C���p�X
	return �I�[�v���`�F�b�N*/
	uint8_t LoadPmdFromFile(const std::string& file_path) {
		std::ifstream file(file_path.c_str(), std::ios::binary);
		if (!file.is_open()) {
			return 1;
		}

		/*�t�H�[�}�b�g�m�F*/
		/*���f�����w�b�_�����̓ǂݍ���*/
		PmdInfoHeader info_header{};
		file.read((char*)&info_header, sizeof(info_header.buffer));
		/*���_�f�[�^�����̓ǂݍ���*/
		uint32_t vertex_num = 0;
		file.read((char*)&vertex_num, sizeof(std::uint32_t));
		std::vector<PmdVertexData>vertex(vertex_num);
		file.read((char*)vertex.data(), sizeof(vertex[0].buffer) * vertex.size());
		/*�C���f�b�N�X�f�[�^�����̓ǂݍ���*/
		std::uint32_t index_num = 0;
		file.read((char*)&index_num, sizeof(std::uint32_t));
		std::vector<std::uint16_t>index(index_num);
		file.read((char*)index.data(), sizeof(std::uint16_t) * index.size());
		/*�}�e���A���f�[�^�����̓ǂݍ���*/
		std::uint32_t material_num = 0;
		file.read((char*)&material_num, sizeof(std::uint32_t));
		std::vector<PmdMaterialData>material(material_num);
		file.read((char*)material.data(), sizeof(material[0].buffer) * material.size());
		/*�{�[���f�[�^�����̓ǂݍ���*/
		std::uint32_t born_num = 0;
		file.read((char*)&born_num, sizeof(std::uint32_t));
		std::vector<PmdBornData>born(born_num);
		file.read((char*)born.data(), sizeof(born[0].buffer) * born.size());
		/*IK�{�[�������̓ǂݍ���*/
		std::uint32_t ik_born_num = 0;
		file.read((char*)&ik_born_num, sizeof(std::uint32_t));
		std::vector<PmdIkBornData>ik_born(ik_born_num);
		for (auto& i : ik_born) {
			file.read((char*)&i, sizeof(i.buffer));
			i.child_born_index.resize(i.child_born_num);
			file.read((char*)i.child_born_index.data(), sizeof(i.child_born_index[0]) * i.child_born_index.size());
		}
		return 0;
	}

}

#endif
