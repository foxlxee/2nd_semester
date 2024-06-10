#include <iostream>

#define _matrix_template template <typename T, unsigned char rows, unsigned char columns>

_matrix_template
// Только для примитивных типов
class Matrix {
private:
	T m_arr[rows][columns];

	void copy(const T* arr) {
		std::copy(arr, arr + rows * columns, &m_arr);
	}
public:
	Matrix() {
		std::fill((T*)m_arr, (T*)m_arr + rows * columns, 0);
	}

	_matrix_template
	Matrix(const Matrix <T, rows, columns>& matrix) {
		copy(&matrix.m_arr);
	}

	Matrix <T, rows, columns> add(const Matrix <T, rows, columns>& matrix) {
		Matrix <T, rows, columns> result;

		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				result.m_arr[i][j] = m_arr[i][j] + matrix.m_arr[i][j];
			}
		}

		return result;
	}

	// Только для квадратных матриц
	Matrix <T, rows, columns> multiply(const Matrix <T, rows, columns>& matrix) {
		Matrix <T, rows, columns> result;

		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				for (size_t k = 0; k < rows; k++) {
					result.m_arr[i][j] += m_arr[i][k] * matrix.m_arr[k][j];
				}
			}
		}

		return result;
	}

	T getElement(unsigned char rowIndex, unsigned char columnIndex) {
		return m_arr[rowIndex][columnIndex];
	}
	void setElement(unsigned char rowIndex, unsigned char columnIndex, T element) {
		m_arr[rowIndex][columnIndex] = element;
	}

	double determinant() {
		if (rows == 2 && columns == 2) {
			return (double)m_arr[0][0] * m_arr[1][1] - (double)m_arr[0][1] * m_arr[1][0];
		}
		if (rows == 3 && columns == 3) {
			return
				((double)m_arr[0][0] * m_arr[1][1] * m_arr[2][2]) +
				((double)m_arr[0][1] * m_arr[1][2] * m_arr[2][0]) +
				((double)m_arr[1][0] * m_arr[2][1] * m_arr[0][2]) -
				((double)m_arr[0][2] * m_arr[1][1] * m_arr[2][0]) -
				((double)m_arr[1][2] * m_arr[2][1] * m_arr[0][0]) -
				((double)m_arr[1][0] * m_arr[0][1] * m_arr[2][2]);
		}

		throw std::exception("Determinant is not defined");
	}

	Matrix <T, rows, columns> operator +(const Matrix <T, rows, columns>& matrix) {
		return add(matrix);
	}
	Matrix <T, rows, columns> operator *(const Matrix <T, rows, columns>& matrix) {
		return multiply(matrix);
	}
	
	void operator *=(const Matrix <T, rows, columns>& matrix) {
		return *this = multiply(matrix);
	}
	void operator += (const Matrix <T, rows, columns>& matrix) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				m_arr[i][j] = m_arr[i][j] + matrix.m_arr[i][j];
			}
		}
	}
	void operator =(const Matrix <T, rows, columns>& matrix) {
		copy(&matrix.m_arr);
	}
	void operator ++() {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				m_arr[i][j]++;
			}
		}
	}

	friend std::ostream& operator <<(std::ostream& os, const Matrix <T, rows, columns>& matrix) {
		os << std::endl;

		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				os << matrix.m_arr[i][j] << ' ';
			}

			os << std::endl;
		}

		return os;
	}
	friend std::istream& operator >>(std::istream& is, Matrix <T, rows, columns>& matrix) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < columns; j++) {
				is >> matrix.m_arr[i][j];
			}
		}
		return is;
	}
};

using Matrix22i = Matrix<int, 2, 2>;
using Matrix33i = Matrix<int, 3, 3>;
using Vector2i = Matrix<int, 1, 2>;
using Vector3i = Matrix<int, 1, 3>;

int main() {
	Matrix33i matrix33i_1;
	std::cin >> matrix33i_1;

	Matrix33i matrix33i_2;
	std::cin >> matrix33i_2;

	Matrix33i matrix33i_3 = matrix33i_1 * matrix33i_2;

	std::cout << matrix33i_3 << std::endl;
	std::cout << matrix33i_3.determinant() << std::endl;
}