#ifndef OKMONN_ARRAY
#define OKMONN_ARRAY

#include <cstdint>

namespace okmonn {
	template <typename T>
	class Array {
	public:
		/*�R���X�g���N�^*/
		Array() : bufffer(nullptr), num(0) {}
		/*�f�X�g���N�^*/
		~Array() {
			if (buffer != nullptr) {
				delete buffer;
			}
		};

	public:
		/*�i�[�T�C�Y�̕ύX
		.�ύX�z��*/
		void ReSize(const std::uint32_t& num) {

		}

	private:
		/*�z��̃o�b�t�@*/
		T* buffer;
		/*�z��v�f��*/
		uint32_t num;
	};
}

#endif
