#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int32_t ReadFile(const std::string& file_path, std::vector<uint8_t>& buffer) {
	std::ifstream file(file_path.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		return -1;
	}
	do {
		char tmp = 0;
		file.read(&tmp, sizeof(tmp));
		buffer.push_back((uint8_t)tmp);
	} while (!file.eof());
	file.close();
	return 0;
}

int32_t WriteFile(const std::string& file_path, const std::vector<uint8_t>buffer) {
	std::ofstream file(file_path.c_str(), std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		return -1;
	}
	file.write((const char*)buffer.data(), sizeof(buffer[0]) * buffer.size());
	file.close();
	return 0;
}

int32_t CreateBackup(void) {
	/*カレントでディレクトリの取得*/
	auto current_dir = std::filesystem::current_path();
	/*ディレクトリ内のファイルを取得*/
	for (auto& i : filesystem::directory_iterator(current_dir)) {
		/*絶対パスで表示*/
		cout << filesystem::absolute(i.path()).string() << endl;
		/*パスの状態を取得*/
		auto st = filesystem::status(i.path());
		if (st.type() == filesystem::file_type::directory) {
			/*ディレクトリ内のファイルを取得*/
			for (auto& n : filesystem::directory_iterator(i.path())) {
				/*相対パスで表示*/
				cout << "	" << filesystem::relative(n.path()).string() << endl;
				std::vector<uint8_t>buffer;
				ReadFile(n.path().string(), buffer);
				WriteFile(current_dir.string() + "\\Backup\\" + filesystem::relative(n.path()).string(), buffer);
			}
		}
		else if (st.type() == filesystem::file_type::regular) {
			std::vector<uint8_t>buffer;
			ReadFile(i.path().string(), buffer);
			WriteFile(current_dir.string() + "\\Backup\\" + filesystem::relative(i.path()).string(), buffer);
		}
	}
	return 0;
}

int main() {
	/*カレントでディレクトリの取得*/
	auto current_dir = std::filesystem::current_path();
	/*ディレクトリ内のファイルを取得*/
	for (auto& i : filesystem::directory_iterator(current_dir)) {
		/*絶対パスで表示*/
		cout << filesystem::absolute(i.path()).string() << endl;
		/*パスの状態を取得*/
		auto st = filesystem::status(i.path());
		if (st.type() == filesystem::file_type::directory) {
			/*ディレクトリ内のファイルを取得*/
			for (auto& n : filesystem::directory_iterator(i.path())) {
				/*相対パスで表示*/
				cout << "	" << filesystem::relative(n.path()).string() << endl;
			}
		}
	}
	CreateBackup();
	return 0;
}