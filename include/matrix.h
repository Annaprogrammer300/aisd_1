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

	int get_rows() const;
	int get_cols() const;

	
private:
	T** data_;
	int rows_;
	int cols_;
	bool is_complex_;
};

