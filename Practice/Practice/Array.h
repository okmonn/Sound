#ifndef OKMONN_ARRAY
#define OKMONN_ARRAY

#include <cstring>
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
		}

	public:
		T operator[](const uint32_t& index) const {
			return buffer[index];
		}

	public:
		/*�i�[�T�C�Y�̕ύX
		.�ύX�z��*/
		void ReSize(const std::uint32_t& num) {
			if (this->num != num) {
				T* tmp = new T[num];
				std::memcpy(&tmp[0], &buffer[0], sizeof(T) * num);
				delete buffer;

				buffer    = tmp;
				this->num = num;
			}
		}
		/*�擪�ɒǉ�
		.�ǉ��f�[�^*/
		void PushFront(const T& val) {
			T* tmp = new T[num + 1];
			std::memcpy(&tmp[1], &buffer[0], sizeof(T) * num);
			delete buffer;

			buffer = tmp;
			num = num + 1;

			buffer[0] = val;
		}
		/*�����ɒǉ�
		.�ǉ��f�[�^*/
		void PushBack(const T& val) {
			ReSize(num + 1);

			buffer[num - 1] = val;
		}

	public:
		/*�z��̗v�f���̎擾
		return �v�f��*/
		uint32_t Size(void) const {
			return num;
		}

	private:
		/*�z��̃o�b�t�@*/
		T* buffer;
		/*�z��v�f��*/
		uint32_t num;
	};
}

#endif
