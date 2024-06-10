#pragma once

#define MAIN_WINDOW_WIDTH 800
#define MAIN_WINDOW_HEIGHT 600

namespace mo {
	class Application {
	private:
		static Application* m_instance;
		Application();
	public:
		static Application* instance();
		int run();
	};
}