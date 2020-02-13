#include <fstream>

namespace {
	/*�t�@�C����*/
	const std::string fileName = "SinTbl.h";
	/*�f�[�^�^*/
	const std::string type = "std::uint8_t";
	/*�T�C���g�T���v����*/
	const std::uint32_t sample = 0x1000;
}

int main() {
	std::ofstream file(fileName, std::ios::out | std::ios::trunc);
	if (!file) {
		return 0;
	}

	file << "#pragma once" << std::endl;
	file << "#include <vector>" << std::endl;
	file << std::endl;
	file << "namespace {" << std::endl;
	file << "	const std::vector<" << type << ">sinTbl = {" << std::endl;
	
	std::uint32_t index = 0;
	while (index < sample) {
		file << "		";
		for (std::uint32_t i = 0; i < 8; ++i) {
			if (index >= sample) {
				break;
			}

			std::int32_t val = 0;
			if (type == "std::uint8_t") {
				val = std::int32_t((0x7f * std::sin(2.0f * std::acos(-1.0f) * index / sample)) + 0x7f);
			}
			else if(type == "std::int16_t") {
				val = std::int32_t(0x7fff * std::sin(2.0f * std::acos(-1.0f) * index / sample));
			}
			file << val << ",";

			++index;
		}
		file << std::endl;
	}

	file << "	};" << std::endl;
	file << "}" << std::endl;

	file.close();

	return 0;
}