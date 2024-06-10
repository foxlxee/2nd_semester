#include <iostream>
#include <string>

template <typename T>
class Stack {
private:
	T* m_arr;
	int m_currentIndex;
	size_t m_size;
public:
	Stack(size_t size) : m_currentIndex(-1) , m_size(size) {
		if (size == 0) {
			throw std::bad_alloc();
		}

		m_arr = new T[size];
	}

	~Stack() {
		delete[] m_arr;
	}

	size_t size() {
		return m_size;
	}

	size_t amount() {
		m_currentIndex + 1;
	}

	bool empty() {
		return m_currentIndex == -1;
	}

	void push(const T& element) {
		if (++m_currentIndex == m_size) {
			throw std::overflow_error("overflow error exception");
		}

		m_arr[m_currentIndex] = element;
	}

	T pop() {
		if (empty()) {
			throw std::out_of_range("out of range exception");
		}

		return m_arr[m_currentIndex--];
	}

	T& top() {
		if (empty()) {
			throw std::logic_error("stack is empty");
		}

		return m_arr[m_currentIndex];
	}
};

int main() {
	Stack<std::string> stack(3);

	stack.push("one");
	stack.push("two");
	stack.push("three");

	stack.pop();
	stack.pop();
	stack.pop();

	stack.top();
}