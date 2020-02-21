#ifndef OKMONN_VECTOR
#define OKMONN_VECTOR

#include <cmath>
#include <cstdint>

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
		Vector2 operator+(const T& i) const {
			return Vector2(x + i, y + i);
		}
		Vector2 operator-(const T& i) const {
			return Vector2(x - i, y - i);
		}
		Vector2 operator*(const T& i) const {
			return Vector2(x * i, y * i);
		}
		Vector2 operator/(const T& i) const {
			return Vector2(x / i, y / i);
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
		Vector2 operator+(const Vector2& vec) const {
			return Vector2(x + vec.x, y + vec.y);
		}
		Vector2 operator-(const Vector2& vec) const {
			return Vector2(x - vec.x, y - vec.y);
		}
		Vector2 operator*(const Vector2& vec) const {
			return Vector2(x * vec.x, y * vec.y);
		}
		Vector2 operator/(const Vector2& vec) const {
			return Vector2(x / vec.x, y / vec.y);
		}

	public:
		Vector2 operator-(void) const {
			return Vector2(-x, -y);
		}
		bool operator==(const T& i) const {
			return (x == i && y == i);
		}
		bool operator==(const Vector2& vec) {
			return (x == vec.x && y == vec.y);
		}
		bool operator!=(const T& i) const {
			return !((*this) == i);
		}
		bool operator!=(const Vector3& vec) const {
			return !((*this) == vec);
		}

	public:
		/*大きさの取得
		return ベクトルの大きさ*/
		T Dimensions(void) const {
			return std::sqrt(std::pow(x, T(2)) + std::pow(y, T(2)));
		}
		/*正規化
		return 1.0以下の値*/
		T Normalization(void) const {
			return (*this) / Dimensions();
		}

	public:
		/*X要素*/
		T x;
		T y;
	};
	/*内積
	.ベクトル1
	.ベクトル2
	return 内積*/
	template <typename T>
	T DotProduct(const Vector2<T>& vec1, const Vector2<T>& vec2) {
		return (vec1.x * vec2.x) + (vec1.y * vec2.y);
	}
	/*外積
	.ベクトル1
	.ベクトル2
	return 外積*/
	template <typename T>
	T CrossProduct(const Vector2<T>& vec1, const Vector2<T>& vec2) {
		return (vec1.x * vec2.y) - (vec1.y *vec2.x);
	}

	using Vec2  = Vector2<int32_t>;
	using Vec2f = Vector2<float>;

	template <typename T>
	struct Vector3 {
	public:
		/*コンストラクタ*/
		Vector3() {
			x = y = z = T(0);
		}
		/*コンストラクタ
		.X & Y & Z要素*/
		Vector3(const T& i) {
			(*this) = Vector3(i, i, i);
		}
		/*コンストラクタ
		.Vector2*/
		Vector3(const Vector2<T>& vec) {
			(*this) = Vector3(vec.x, vec.y, 0);
		}
		/*コンストラクタ
		.Vector2
		.Z要素*/
		Vector3(const Vector2<T>& vec, const T& z) {
			(*this) = Vector3(vec.x, vec.y, z);
		}
		/*コンストラクタ
		.X要素
		.Y要素
		.Z要素*/
		Vector3(const T& x, const T& y, const T& z) :
			x(x), y(y), z(z) {}

	public:
		void operator=(const T& i) {
			(*this) = Vector3(i);
		}
		void operator+=(const T& i) {
			(*this) = Vector3(x + i, y + i, z + i);
		}
		void operator-=(const T& i) {
			(*this) = Vector3(x - i, y - i, z - i);
		}
		void operator*=(const T& i) {
			(*this) = Vector3(x * i, y * i, z * i);
		}
		void operator/=(const T& i) {
			(*this) = Vector3(x / i, y / i, z / i);
		}
		Vector3 operator+(const T& i) const {
			return Vector3(x + i, y + i, z + i);
		}
		Vector3 operator-(const T& i) const {
			return Vector3(x - i, y - i, z - i);
		}
		Vector3 operator*(const T& i) const {
			return Vector3(x * i, y * i, z * i);
		}
		Vector3 operator/(const T& i) const {
			return Vector3(x / i, y / i, z / i);
		}

	public:
		void operator=(const Vector2<T>& vec) {
			(*this) = Vector3(vec);
		}
		void operator+=(const Vector2<T>& vec) {
			(*this) = Vector3(x + vec.x, y + vec.y, z);
		}
		void operator-=(const Vector2<T>& vec) {
			(*this) = Vector3(x - vec.x, y - vec.y, z);
		}
		void operator*=(const Vector2<T>& vec) {
			(*this) = Vector3(x * vec.x, y * vec.y, z);
		}
		void operator/=(const Vector2<T>& vec) {
			(*this) = Vector3(x / vec.x, y / vec.y, z);
		}
		Vector3 operator+(const Vector2<T>& vec) const {
			return Vector3(x + vec.x, y + vec.y, z);
		}
		Vector3 operator-(const Vector2<T>& vec) const {
			return Vector3(x - vec.x, y - vec.y, z);
		}
		Vector3 operator*(const Vector2<T>& vec) const {
			return Vector3(x * vec.x, y * vec.y, z);
		}
		Vector3 operator/(const Vector2<T>& vec) const {
			return Vector3(x / vec.x, y / vec.y, z);
		}

	public:
		void operator=(const Vector3& vec) {
			(*this) = Vector3(vec.x, vec.y, vec.z);
		}
		void operator+=(const Vector3& vec) {
			(*this) = Vector3(x + vec.x, y + vec.y, z + vec.z);
		}
		void operator-=(const Vector3& vec) {
			(*this) = Vector3(x - vec.x, y - vec.y, z - vec.z);
		}
		void operator*=(const Vector3& vec) {
			(*this) = Vector3(x * vec.x, y * vec.y, z * vec.z);
		}
		void operator/=(const Vector3& vec) {
			(*this) = Vector3(x / vec.x, y / vec.y, z / vec.z);
		}
		Vector3 operator+(const Vector3& vec) const {
			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}
		Vector3 operator-(const Vector3& vec) const {
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}
		Vector3 operator*(const Vector3& vec) const {
			return Vector3(x * vec.x, y * vec.y, z * vec.z);
		}
		Vector3 operator/(const Vector3& vec) const {
			return Vector3(x / vec.x, y / vec.y, z / vec.z);
		}

	public:
		Vector3 operator-(void) const {
			return Vector3(-x, -y, -z);
		}
		bool operator==(const T& i) const {
			return (x == i && y == i && z == i);
		}
		bool operator==(const Vector3& vec) const {
			return (x == vec.x && y == vec.y && z == vec.z);
		}
		bool operator!=(const T& i) const {
			return !((*this) == i);
		}
		bool operator!=(const Vector3& vec) const {
			return !((*this) == vec);
		}

	public:
		/*大きさの取得
		return ベクトルの大きさ*/
		T Dimensions(void) const {
			return std::sqrt(std::pow(x, T(2)) + std::pow(y, T(2)) + std::pow(z, T(2)));
		}
		/*正規化
		return 1.0以下の値*/
		T Normalization(void) const {
			return (*this) / Dimensions();
		}

	public:
		/*X & Yの取得
		return Vector2*/
		Vector2<T> xy(void) const {
			return Vector2<T>(x, y);
		}
		/*X & Zの取得
		return Vector2*/
		Vector2<T> xz(void) const {
			return Vector2<T>(x, z);
		}
		/*Y & Xの取得
		return Vector2*/
		Vector2<T> yx(void) const {
			return Vector2<T>(y, x);
		}
		/*Y & Zの取得
		return Vector2*/
		Vector2<T> yz(void) const {
			return Vector2<T>(y, z);
		}
		/*Z & Xの取得
		return Vector2*/
		Vector2<T> zx(void) const {
			return Vector2<T>(z, x);
		}
		/*Z & Yの取得
		return Vector2*/
		Vector2<T> zy(void) const {
			return Vector2<T>(z, y);
		}

	public:
		/*X要素*/
		T x;
		/*Y要素*/
		T y;
		/*Z要素*/
		T z;
	};
	template <typename T>
	T DotProduct(const Vector3<T>& vec1, const Vector3<T>& vec2) {
		return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	}
	/*外積
	.ベクトル1
	.ベクトル2
	return 外積*/
	template <typename T>
	Vector3<T> CrossProduct(const Vector3<T>& vec1, const Vector3<T>& vec2) {
		return Vector3<T>((vec1.y * vec2.z) - (vec1.z * vec2.y),
						  (vec1.z * vec2.x) - (vec1.z * vec2.z), 
						  (vec1.x * vec2.y) - (vec1.y * vec2.x));
	}

	using Vec3  = Vector3<int32_t>;
	using Vec3f = Vector3<float>;
}

#endif
