#include <complex>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <utility>


template <typename T>
class Matrix {
public:
	Matrix();
	Matrix(int rows, int cols, T init_value);
	Matrix(int rows, int cols, T lower_bound, T upper_bound, bool is_complex = false);
	Matrix(const Matrix<T>& other);

	void Swap(Matrix<T>& other) noexcept;
	Matrix<T>& operator=(const Matrix<T> other);

	~Matrix();

	T& operator()(int row, int col);
	const T& operator()(int row, int col) const;

	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T> operator-(const Matrix<T>& other) const;
	Matrix<T> operator*(const Matrix<T>& other) const;
	Matrix<T> operator*(const T scalar) const;
	Matrix<double> operator/(const T scalar) const;

	int get_rows() const;
	int get_cols() const;

	T Trace() const;
	void Print() const;

	
private:
	T** data_;
	int rows_;
	int cols_;
	bool is_complex_;
};

template <typename T>
Matrix<T>::Matrix() : data_(nullptr), rows_(0), cols_(0), is_complex_(false) {}

template <typename T>
Matrix<T>::Matrix(int rows, int cols, T init_value) : rows_(rows), cols_(cols), is_complex_(false) {
	data_ = new T * [rows];
	for (int i = 0; i < rows; i++) {
		data_[i] = new T[cols];
		for (int j = 0; j < cols; j++) {
			data_[i][j] = init_value;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols, T lower_bound, T upper_bound, bool is_complex) : rows_(rows), cols_(cols), is_complex_(is_complex) {
	std::random_device rd;
	std::mt19937 gen(rd());

	if constexpr (std::is_integral_v<T>) {
		std::uniform_int_distribution<T> dist(lower_bound, upper_bound);

		data_ = new T * [rows];
		for (int i = 0; i < rows; ++i) {
			data_[i] = new T[cols];
			for (int j = 0; j < cols; ++j) {
				data_[i][j] = dist(gen);
			}
		}
	}
	else if constexpr (std::is_floating_point_v<T>) {
		std::uniform_real_distribution<T> dist(lower_bound, upper_bound);

		data_ = new T * [rows];
		for (int i = 0; i < rows; ++i) {
			data_[i] = new T[cols];
			for (int j = 0; j < cols; ++j) {
				data_[i][j] = dist(gen);
			}
		}
	}
	else if (is_complex_) {
		std::uniform_real_distribution<T> dist_real(lower_bound, upper_bound);
		std::uniform_real_distribution<T> dist_imag(lower_bound, upper_bound);
		data_ = new T * [rows];
		for (int i = 0; i < rows; ++i) {
			data_[i] = new T[cols];
			for (int j = 0; j < cols; ++j) {
				T real_part = dist_real(gen);
				T imag_part = dist_imag(gen);

				data_[i][j] = std::complex<T>(real_part, imag_part);
			}
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : rows_(other.rows_), cols_(other.cols_), is_complex_(false) {
	data_ = new T * [rows_];
	for (int i = 0; i < rows_; ++i) {
		data_[i] = new T[cols_];
		for (int j = 0; j < cols_; ++j) {
			data_[i][j] = other.data_[i][j];
		}
	}
}

template <typename T>
Matrix<T>::~Matrix() {
	for (int i = 0; i < rows_; ++i) {
		delete[] data_[i];
	}
	delete[] data_;
	data_ = nullptr;
}