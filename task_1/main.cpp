#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>

#define WORDS_LIMIT 30

// Класс, который генерирует последовательность Фибоначчи
class FibonacciSequenceGenerator {
public:
	// Удаляем конструктор, потому что класс статический
	FibonacciSequenceGenerator() = delete;

	// Метод, который заполняет массив числами из последовательности Фибоначчи
	static void fill(size_t* arr, size_t length) {
		if (length == 0) throw std::exception("length should not be zero");

		size_t index = 0;
		size_t firstValue = 0;
		size_t secondValue = 0;

		for (size_t i = 1; i <= length; i++) {
			if (i == 1) {
				arr[index++] = firstValue = i;
				continue;
			} else if (i == 2) {
				arr[index++] = secondValue = i;
				continue;
			}

			arr[index] = firstValue + secondValue;
			firstValue = secondValue;
			secondValue = arr[index];

			index++;
		}
	}
};

// Класс, который содержит ключ
class StringEncryptionKey {
private:
	size_t* m_key;
	size_t m_length;
public:
	StringEncryptionKey(size_t* key, size_t length) :
		m_key(key), m_length(length) {

		// Проверяем корректность ключа
		if (m_length == 0) throw std::exception("key length should not be zero");

		std::unique_ptr<size_t[]> fibonacciSequence(new size_t[m_length]);
		FibonacciSequenceGenerator::fill(fibonacciSequence.get(), m_length);

		std::unique_ptr<size_t[]> sortedKey(new size_t[m_length]);
		std::copy(m_key, m_key + m_length, sortedKey.get());
		std::sort(sortedKey.get(), sortedKey.get() + m_length);

		if (!std::equal(sortedKey.get(), sortedKey.get() + m_length,
			fibonacciSequence.get())) throw std::exception("key is not valid");
	}

	size_t* getKey() const {
		return m_key;
	}

	size_t getLength() const {
		return m_length;
	}
};

// Класс, который шифрует строки
class StringEncryptor {
private:
	// Метод, который заполняет вектор строк словами считанными из строки
	static void getWords(
		const std::string& string,
		std::vector<std::string>& words,
		size_t sequenceLength) {
		// Выбрасываем исключение если строка пустая
		if (string.empty()) throw std::exception("string is empty");

		std::string word;
		bool inWord = false;
		size_t length = string.length();
		for (size_t i = 0; i < length; i++) {
			char c = string[i];

			if (c == ' ' || c == '\t') {
				if (inWord) {
					words.push_back(word);
					word.clear();
					inWord = false;
				}
				continue;
			} else if (!inWord) {
				inWord = true;
			}

			word.push_back(c);

			if (i == length - 1) {
				words.push_back(word);
				break;
			}
		}

		// Выбрасываем исключение если превышен лимит слов
		if (words.size() > WORDS_LIMIT) throw std::exception("word limit exceeded");

		// Выбрасываем исключение если количество слов в строке не соответствует количеству чисел в ключе
		if (words.size() != sequenceLength) throw std::exception("the number of words does not match the number of numbers in the key");
	}

	// Метод, который формирует новую строку
	static std::string getString(
		const std::string& string, // Строка, которую шифруем или дешифруем
		const size_t* initialSequence, // Исходная последовательность
		const size_t* currentSequence, // Текущая последовательность
		size_t sequenceLength /* Длина последовательности */) {

		// Получаем последовательность Фибоначчи
		std::unique_ptr<size_t[]> fibonacciSequence(new size_t[sequenceLength]);
		FibonacciSequenceGenerator::fill(fibonacciSequence.get(), sequenceLength);
		if (initialSequence == nullptr) {
			initialSequence = fibonacciSequence.get();
		} else if (currentSequence == nullptr) {
			currentSequence = fibonacciSequence.get();
		}

		// Получаем слова
		std::vector<std::string> words;
		getWords(string, words, sequenceLength);

		// Отображаем числа из последовательности на слова
		std::map<size_t, std::string> map;
		for (size_t i = 0; i < sequenceLength; i++) {
			map[initialSequence[i]] = words[i];
		}

		// Записываем в строку слова из отображения
		std::stringstream stream;
		for (size_t i = 0; i < sequenceLength; i++) {
			stream << map[currentSequence[i]];

			if (i != sequenceLength - 1) {
				stream << ' ';
			}
		}

		// Возвращаем строку
		return stream.str();
	}
public:
	// Удаляем конструктор, потому что класс статический
	StringEncryptor() = delete;

	// Метод, который шифрует строку
	static std::string Encode(const std::string& stringToEncode, const StringEncryptionKey& stringEncryptionKey) {
		return getString(stringToEncode, nullptr, stringEncryptionKey.getKey(), stringEncryptionKey.getLength());
	}
	
	// Метод, который дешифрует строку
	static std::string Decode(const std::string& stringToDecode, const StringEncryptionKey& stringEncryptionKey) {
		return getString(stringToDecode, stringEncryptionKey.getKey(), nullptr, stringEncryptionKey.getLength());
	}
};

int main() {
	std::cout << "Enter string: ";
	
	std::string string;
	std::getline(std::cin, string);

	std::cout << "Enter encryption key: ";
	std::stringstream stream(string);
	stream.rdbuf()->pubsetbuf((char*)string.c_str(), string.length());
	size_t amountOfWords = std::distance(
		std::istream_iterator<std::string>(stream),
		std::istream_iterator<std::string>());
	
	std::unique_ptr<size_t[]> sequence(new size_t[amountOfWords]);
	for (size_t i = 0; i < amountOfWords; i++) {
		std::cin >> sequence.get()[i];
	}

	StringEncryptionKey key(sequence.get(), amountOfWords);

	std::string encodedString = StringEncryptor::Encode(string, key);

	std::cout << "Encryption result: " << encodedString << std::endl;
	std::cout << "Decryption result: " <<
		StringEncryptor::Decode(encodedString, key) << std::endl;
}