#include "AnimatedText.h"

namespace mo {
	long AnimatedText::getCurrentTime() {
		auto now = std::chrono::system_clock::now();
		auto milliseconds = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
		return milliseconds.time_since_epoch().count();
	}

	AnimatedText::AnimatedText(const std::string& text, int duration) : m_currentIndex(-1) {
		if (text.length() == 0) {
			throw new std::exception("string is empty");
		}

		if (duration <= 0) {
			throw new std::exception("duration should be more than zero");
		}

		m_initialText = text;

		m_singleCharacterDelay = ((float)duration / (float)text.length()) * 1000;

		restart();
	}

	void AnimatedText::restart() {
		m_startTime = getCurrentTime();
	}

	bool AnimatedText::update() {
		if ((getCurrentTime() - m_startTime) >= m_singleCharacterDelay) {
			if (++m_currentIndex == m_initialText.length()) {
				m_currentIndex = -1;
			}

			restart();

			return true;
		}

		return false;
	}

	std::string AnimatedText::getCurrentText() {
		return m_initialText.substr(0, m_currentIndex);
	}
}