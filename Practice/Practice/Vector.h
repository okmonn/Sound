#pragma once

namespace okmonn {
	template <typename T>
	struct Vector2 {
	public:
		/*�R���X�g���N�^*/
		Vector2() {
			x = y = T(0);
		}
		/*�R���X�g���N�^
		.X & Y�v�f*/
		Vector2(const T& i) {
			(*this) = Vector2(i, i);
		}
		/*�R���X�g���N�^
		.X�v�f
		.Y�v�f*/
		Vector2(const T& x, const T& y) : x(x), y(y) {}

	public:
		void operator=(const T& i) {
			(*this) = Vector2(i);
		}
		void operator+=(const T& i) {
			(*this) = Vector2(x + i, y + i);
		}
		void operator-=(const T& i) {
			(*this) = Vector2(x - i, y - i);
		}
		void operator*=(const T& i) {
			(*this) = Vector2(x * i, y * i);
		}
		void operator/=(const T& i) {
			(*this) = Vector2(x / i, y / i);
		}
		
	public:
		void operator=(const Vector2& vec) {
			(*this) = Vector2(vec.x, vec.y);
		}
		void operator+=(const Vector2& vec) {
			(*this) = Vector2(x + vec.x, y + vec.y);
		}
		void operator-=(const Vector2& vec) {
			(*this) = Vector2(x - vec.x, y - vec.y);
		}
		void operator*=(const Vector2& vec) {
			(*this) = Vector2(x * vec.x, y * vec.y);
		}
		void operator/=(const Vector2& vec) {
			(*this) = Vector2(x / vec.x, y / vec.y);
		}
		Vector2 operator+(const Vector2& vec) {
			return Vector2(x + vec.x, y + vec.y);
		}
		Vector2 operator-(const Vector2& vec) {
			return Vector2(x - vec.x, y - vec.y);
		}
		Vector2 operator*(const Vector2& vec) {
			return Vector2(x * vec.x, y * vec.y);
		}
		Vector2 operator/(const Vector2& vec) {
			return Vector2(x / vec.x, y / vec.y);
		}

	public:
		/*X�v�f*/
		T x;
		T y;
	};
}
