#pragma once

#include <cstdint>
#include <cstdarg>

#include <string>
#include <vector>


class DisplayLine {
public:
	DisplayLine(uint32_t time, const std::string& message);

	uint32_t m_time;
	std::string m_text;
};

class Logger {
public:
	void logMessage(const char *message, ...);

	void updateDisplay(uint32_t currentTime);

private:
	std::vector<DisplayLine> m_lines;
	uint32_t m_frame;
	static const double MIN_WEIGHT;
	static const double SCALE;

	typedef std::vector<DisplayLine>::iterator LinesIterator;

	LinesIterator findMessage(const std::string& message);

	double frameToWeight(uint32_t frame) const;

	uint32_t weightToFrame(double weight) const;

	void increaseWeight(DisplayLine& line, bool increase = true) const;

	void Logger::drawMessages(const DisplayLine& line, double threshold, int positon) const;
};

extern Logger LOGGER;
