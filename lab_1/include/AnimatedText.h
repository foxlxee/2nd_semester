#pragma once
#include <iostream>
#include <chrono>

namespace mo {
	class AnimatedText {
	private:
		float m_singleCharacterDelay;
		long m_startTime;
		int m_currentIndex;
		std::string m_initialText;

		long getCurrentTime();
		void restart();
	public:
		AnimatedText(const std::string& text, int duration);
		bool update();
		std::string getCurrentText();
	};
}