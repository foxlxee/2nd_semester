#include <iostream>
#include <vector>

#define SET_BIT(byte,index) byte |= 1 << index
#define RESET_BIT(byte,index) byte &= ~(1 << index)
#define CHECK_BIT(byte,index) ((byte) & (1<<(index))) != 0
#define PRINT(t) std::cout << t << std::endl

typedef unsigned char BYTE;

typedef struct BitInfo {
	size_t byteIndex;
	unsigned char bitIndex;
} BitInfo;

template<>
class std::vector<bool> {
private:
	BYTE* m_arr;
	size_t m_amountOfAllocatedBytes;
	size_t m_amountOfUsedBits;

	BitInfo getBitInfo(size_t bitIndex) {
		return BitInfo{
			(size_t)(bitIndex / 8.0),
			(BYTE)(bitIndex % 8)
		};
	}

	void setBit(BYTE* array, size_t bitIndex, bool value) {
		BitInfo bitInfo = getBitInfo(bitIndex);

		BYTE* byte = &array[bitInfo.byteIndex];

		if (value) {
			*byte = SET_BIT(*byte, bitInfo.bitIndex);
		} else {
			*byte = RESET_BIT(*byte, bitInfo.bitIndex);
		}
	}

	bool getBit(BYTE* array, size_t bitIndex) {
		BitInfo bitInfo = getBitInfo(bitIndex);
		return CHECK_BIT(array[bitInfo.byteIndex], bitInfo.bitIndex);
	}
public:
	std::vector<bool>() :
		m_arr(new BYTE[1]),
		m_amountOfAllocatedBytes(1),
		m_amountOfUsedBits(0) {
	}

	void add(bool value) {
		// Записываем бит
		setBit(m_amountOfUsedBits, value);
		
		// Если необходимо, выделяем еще 1 байт
		if (++m_amountOfUsedBits == m_amountOfAllocatedBytes * 8) {
			BYTE* temp = new BYTE[++m_amountOfAllocatedBytes];

			for (size_t i = 0; i < m_amountOfAllocatedBytes - 1; i++) {
				temp[i] = m_arr[i];
			}

			delete[] m_arr;
			m_arr = temp;
		}
	}

	void insert(size_t bitIndex, bool value) {
		if (m_amountOfUsedBits + 1 == m_amountOfAllocatedBytes * 8) {
			m_amountOfAllocatedBytes++;
		}

		BYTE* newArr = new BYTE[m_amountOfAllocatedBytes];

		size_t currentIndex = 0;

		for (; currentIndex != bitIndex; currentIndex++) {
			setBit(newArr, currentIndex, getBit(m_arr, currentIndex));
		}

		setBit(newArr, currentIndex++, value);

		for (size_t j = bitIndex; j < m_amountOfUsedBits; j++) {
			setBit(newArr, currentIndex++, getBit(m_arr, j));
		}

		m_amountOfUsedBits++;

		delete[] m_arr;
		m_arr = newArr;
	}

	void erase(size_t startIndex, size_t endIndex) {
		// Проверяем что индексы правильные
		if (m_amountOfUsedBits == 0 ||
			endIndex >= m_amountOfUsedBits ||
			endIndex < startIndex) {
			throw std::exception();
		}
		//

		size_t amountOfBitsToRemove = endIndex - startIndex + 1;
		size_t newAmountOfUsedBits = m_amountOfUsedBits - amountOfBitsToRemove;
		size_t newAmountOfAllocatedBytes = (size_t)std::ceill(newAmountOfUsedBits / 8.0);

		BYTE* newArr = new BYTE[newAmountOfAllocatedBytes];

		for (size_t i = 0; i < startIndex; i++) {
			setBit(newArr, i, getBit(m_arr, i));
		}
		
		for (size_t i = endIndex + 1; i < m_amountOfUsedBits; i++) {
			setBit(newArr, i, getBit(m_arr, i));
		}

		delete[] m_arr;

		m_arr = newArr;
		m_amountOfAllocatedBytes = newAmountOfAllocatedBytes;
		m_amountOfUsedBits = newAmountOfUsedBits;
	}

	size_t size() {
		return m_amountOfUsedBits;
	}

	void setBit(size_t bitIndex, bool value) {
		setBit(m_arr, bitIndex, value);
	}

	bool getBit(size_t bitIndex) {
		return getBit(m_arr, bitIndex);
	}
};

int main() {
	std::vector<bool> vector;

	// 1-ый байт
	vector.add(true); // индекс бита = 0
	vector.add(true);
	vector.add(true);
	vector.add(false);
	vector.add(false);
	vector.add(true);
	vector.add(true);
	vector.add(true);
	//

	// 2-ой байт
	vector.add(false); // индекс бита = 8
	vector.add(false);
	vector.add(false);
	vector.add(false);
	vector.add(false);
	vector.add(false);
	vector.add(false);
	vector.add(false); // индекс бита = 15
	//

	// 3-ий байт
	vector.add(true);
	vector.add(true);
	//

	vector.setBit(8, true);
	vector.setBit(15, true);

	for (size_t i = 0; i < vector.size(); i++) {
		PRINT((vector.getBit(i) ? "true" : "false"));
	}
}