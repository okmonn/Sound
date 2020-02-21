#ifndef OKMONN_ARRAY
#define OKMONN_ARRAY

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
		};

	public:
		/*格納サイズの変更
		.変更配列数*/
		void ReSize(const std::uint32_t& num) {

		}

	private:
		/*配列のバッファ*/
		T* buffer;
		/*配列要素数*/
		uint32_t num;
	};
}

#endif
