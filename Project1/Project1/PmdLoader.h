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
	/*モデル情報ヘッダ*/
	struct PmdInfoHeader {
		union {
			struct {
				/*フォーマット種別*/
				char fmt_type[3];
				/*バージョン*/
				float version;
				/*モデル名*/
				char model_name[20];
				/*モデルに関するコメント*/
				char comment[256];
			};
			std::uint8_t buffer[283];
		};
	};
	/*モデル頂点データ*/
	struct PmdVertexData {
		union {
			struct {
				/*座標*/
				Vec3f pos;
				/*法線ベクトル*/
				Vec3f normal;
				/*UV座標*/
				Vec2f uv;
				/*移動時影響ボーン番号*/
				std::uint16_t born_number[2];
				/*born_number[0]与える影響度(born_number[1] = 100 - born_weight)*/
				std::uint8_t born_weight;
				/*輪郭線フラグ*/
				uint8_t edge_flag;
			};
			std::uint8_t buffer[38];
		};
	};
	/*モデルマテリアルデータ*/
	struct PmdMaterialData {
		union {
			struct {
				/*減衰色*/
				Vec3f diffuse;
				/*減衰色の不透明度*/
				float diffuse_alpha;
				/*鏡面性*/
				float specularity;
				/*光沢色*/
				Vec3f specular;
				/*環境色*/
				Vec3f ambient;
				/*トゥーンテクスチャ番号*/
				std::uint8_t toon_index;
				/*輪郭線フラグ*/
				std::uint8_t edge_flag;
				/*インデックスリスト数*/
				std::uint32_t index_use_num;
				/*テクスチャファイル名*/
				char texture_file_name[20];
			};
			std::uint8_t buffer[70];
		};
	};
	/*モデルボーンデータ*/
	struct PmdBornData {
		union {
			struct {
				/*ボーン名*/
				char born_name[20];
				/*親ボーン番号*/
				std::uint16_t parent_born_index;
				/*末尾に接するボーン番号*/
				std::uint16_t tail_born_index;
				/*ボーン種別*/
				std::uint8_t born_type;
				/*IKボーン番号*/
				std::uint16_t ik_born_index;
				/*先頭ボーン座標*/
				Vec3f head_born_pos;
			};
			std::uint8_t buffer[39];
		};
	};
	/*モデルIKデータ*/
	struct PmdIkBornData {
		union {
			struct {
				/*IKボーン番号*/
				std::uint16_t ik_born_index;
				/*IKボーンが最初に接続するボーン*/
				std::uint16_t ik_target_born_index;
				/*子ボーンの数*/
				std::uint8_t child_born_num;
				/*再帰演算回数*/
				std::uint16_t iterations;
				/*演算1回当たりの制限角度*/
				float control_weight;
				/*子ボーン番号*/
				std::vector<std::uint16_t>child_born_index;
			};
			std::uint8_t buffer[11];
		};
	};
	/*モデル表情データ*/
	struct PmdSkinData {
		union {
			struct {
				/*表情名*/
				char skin_name[20];
				/*表情の頂点数*/
				std::uint32_t skin_vertex_num;
				/*表情の種別*/
				std::uint8_t skin_type;
				struct {

				};
			};
		};
	};

	/*ファイルの読み込み
	.ファイルパス
	return オープンチェック*/
	uint8_t LoadPmdFromFile(const std::string& file_path) {
		std::ifstream file(file_path.c_str(), std::ios::binary);
		if (!file.is_open()) {
			return 1;
		}

		/*フォーマット確認*/
		/*モデル情報ヘッダ部分の読み込み*/
		PmdInfoHeader info_header{};
		file.read((char*)&info_header, sizeof(info_header.buffer));
		/*頂点データ部分の読み込み*/
		uint32_t vertex_num = 0;
		file.read((char*)&vertex_num, sizeof(std::uint32_t));
		std::vector<PmdVertexData>vertex(vertex_num);
		file.read((char*)vertex.data(), sizeof(vertex[0].buffer) * vertex.size());
		/*インデックスデータ部分の読み込み*/
		std::uint32_t index_num = 0;
		file.read((char*)&index_num, sizeof(std::uint32_t));
		std::vector<std::uint16_t>index(index_num);
		file.read((char*)index.data(), sizeof(std::uint16_t) * index.size());
		/*マテリアルデータ部分の読み込み*/
		std::uint32_t material_num = 0;
		file.read((char*)&material_num, sizeof(std::uint32_t));
		std::vector<PmdMaterialData>material(material_num);
		file.read((char*)material.data(), sizeof(material[0].buffer) * material.size());
		/*ボーンデータ部分の読み込み*/
		std::uint32_t born_num = 0;
		file.read((char*)&born_num, sizeof(std::uint32_t));
		std::vector<PmdBornData>born(born_num);
		file.read((char*)born.data(), sizeof(born[0].buffer) * born.size());
		/*IKボーン部分の読み込み*/
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
