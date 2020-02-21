#ifndef OKMONN_ARRAY
#define OKMONN_ARRAY

#include <cstring>
#include <cstdint>

namespace okmonn {
	template <typename T>
	class Array {
	public:
		/*コンストラクタ*/
		Array() : bufffer(nullptr), num(0) {}
		/*デストラクタ*/
		~Array() {
			if (buffer != nullptr) {
				delete buffer;
			}
		}

	public:
		T operator[](const uint32_t& index) const {
			return buffer[index];
		}

	public:
		/*格納サイズの変更
		.変更配列数*/
		void ReSize(const std::uint32_t& num) {
			if (this->num != num) {
				T* tmp = new T[num];
				std::memcpy(&tmp[0], &buffer[0], sizeof(T) * num);
				delete buffer;

				buffer    = tmp;
				this->num = num;
			}
		}
		/*先頭に追加
		.追加データ*/
		void PushFront(const T& val) {
			T* tmp = new T[num + 1];
			std::memcpy(&tmp[1], &buffer[0], sizeof(T) * num);
			delete buffer;

			buffer = tmp;
			num = num + 1;

			buffer[0] = val;
		}
		/*末尾に追加
		.追加データ*/
		void PushBack(const T& val) {
			ReSize(num + 1);

			buffer[num - 1] = val;
		}

	public:
		/*配列の要素数の取得
		return 要素数*/
		uint32_t Size(void) const {
			return num;
		}

	private:
		/*配列のバッファ*/
		T* buffer;
		/*配列要素数*/
		uint32_t num;
	};
}

#endif
