#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define ELECTRICITY_MONITOR 0
#define DISCRETE_SIGNAL_INPUT_BLOCK 1
#define HEATING_CONTROL_BLOCK 2

// Абстрактный класс описывающий прибор
class Appliance {
protected:
	std::string m_name;
public:
	virtual ~Appliance() {}

	virtual void poll() = 0;

	virtual void setName(const std::string& name) {
		m_name = name;
	}

	virtual const std::string& getName() {
		return m_name;
	}
};

// Класс, описывающий счетчик электрической энергии
class ElectricityMonitor : public Appliance {
public:
	void poll() override {
		std::cout << "Electricity monitor: " << m_name << std::endl;
	}
};

// Класс, описывающий блок ввода дискретных сигналов
class DiscreteSignalInputBlock : public Appliance {
public:
	void poll() override {
		std::cout << "Discrete signal input block: " << m_name << std::endl;
	}
};

// Класс, описывающий блок управления отоплением
class HeatingControlBlock : public Appliance {
public:
	void poll() override {
		std::cout << "Heating control block: " << m_name << std::endl;
	}
};

// Класс, описывающий дом
class Home {
private:
	std::vector<Appliance*> m_appliances;
public:
	Home(const std::string& filePath) {
		std::ifstream fileStream;
		fileStream.open(filePath);
		if (!fileStream.is_open())
			throw std::exception();

		char applianceType = -1;

		std::string line;
		while (!fileStream.eof()) {
			std::getline(fileStream, line);

			if (line == "Electricity monitors") {
				applianceType = ELECTRICITY_MONITOR;
				continue;
			}

			if (line == "Discrete signal input blocks") {
				applianceType = DISCRETE_SIGNAL_INPUT_BLOCK;
				continue;
			}

			if (line == "Heating control blocks") {
				applianceType = HEATING_CONTROL_BLOCK;
				continue;
			}

			Appliance* appliance = nullptr;

			switch (applianceType) {
			case ELECTRICITY_MONITOR:
				appliance = new ElectricityMonitor;
				break;
			case DISCRETE_SIGNAL_INPUT_BLOCK:
				appliance = new DiscreteSignalInputBlock;
				break;
			case HEATING_CONTROL_BLOCK:
				appliance = new HeatingControlBlock;
				break;

			default:
				continue;
			}

			appliance->setName(line);
			m_appliances.push_back(appliance);
		}

		fileStream.close();
	}

	~Home() {
		for (Appliance* appliance : m_appliances) {
			delete appliance;
		}
	}

	const std::vector<Appliance*>& getAppliances() {
		return m_appliances;
	}
};

int main() {
	Home home("appliances.txt");

	const std::vector<Appliance*>& appliances = home.getAppliances();

	for (Appliance* appliance : appliances) {
		appliance->poll();
	}
}