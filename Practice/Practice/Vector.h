#pragma once

namespace okmonn {
	template <typename T>
	struct Vector2 {
	public:
		/*コンストラクタ*/
		Vector2() {
			x = y = T(0);
		}
		/*コンストラクタ
		.X & Y要素*/
		Vector2(const T& i) {
			(*this) = Vector2(i, i);
		}
		/*コンストラクタ
		.X要素
		.Y要素*/
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
		/*X要素*/
		T x;
		T y;
	};
}
