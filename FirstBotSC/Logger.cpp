#include "Logger.h"

#include <BWAPI.h>
#include <cstdarg>

using namespace BWAPI;

DisplayLine::DisplayLine(uint32_t time, const std::string& message)
	: m_time(time), m_text(message)
{
}


void Logger::updateDisplay(uint32_t currentTime) {
	m_frame = currentTime;
	std::for_each(m_lines.begin(), m_lines.end(), [this](DisplayLine& line) { increaseWeight(line, false); } );
	for (LinesIterator line = m_lines.begin(); line != m_lines.end(); ) {
		if (frameToWeight(line->m_time) < MIN_WEIGHT) {
			line = m_lines.erase(line);
		} else {
			drawMessages(*line, 0.3, line - m_lines.begin());
			++line;
		}
	}
}

Logger::LinesIterator Logger::findMessage(const std::string& message)
{
	for (LinesIterator line = m_lines.begin(); line != m_lines.end(); ++line) {
		if (message == line->m_text) {
			return line;
		}
	}
	return m_lines.end();
}

double Logger::frameToWeight(uint32_t frame) const {
	double age = m_frame - frame;
	return SCALE / (age + 1.0);
}

uint32_t Logger::weightToFrame(double weight) const {
	return (uint32_t)(m_frame - SCALE / weight + 1.0);
}

void Logger::increaseWeight(DisplayLine& line, bool increase) const {
	double newWeight = increase + frameToWeight(line.m_time);
	line.m_time = weightToFrame(newWeight);
}

const double Logger::MIN_WEIGHT = 0.1;
const double Logger::SCALE = 9.5;

void Logger::logMessage(const char *format, ...)
{
	char buf[500];
	va_list args;
	va_start(args, format);
	int result = vsnprintf(buf, sizeof (buf) - 1, format, args);
	buf[sizeof (buf) - 1] = '\0';
	va_end(args);
		
	if (result < 0) {
		// error condition
		return;
	}
	std::string message(buf, (char*)memchr(buf, 0, sizeof(buf)));

	LinesIterator line = findMessage(message);
	if (line == m_lines.end()) {
		m_lines.push_back(DisplayLine(m_frame, message));
	} else {
		increaseWeight(*line);
	}
}

void Logger::drawMessages(const DisplayLine& line, double threshold, int positon) const
{
	const double weight = frameToWeight(line.m_time);
	Text::Enum color;
	if (weight > 8*threshold) {
		color = Text::BrightRed;
	} else if (weight > 4*threshold) {
		color = Text::Red;
	} else if (weight > 2*threshold) {
		color = Text::Orange;
	} else {
		color = Text::Tan;
	}

	if (weight > threshold) {
		Broodwar->setTextSize(BWAPI::Text::Size::Large);
	}
	int x = 20;
	int y = 10 + 18 * positon;
#if 0
	Broodwar->drawTextScreen(20, 10 + 18 * positon,  "%c%f %s", color, weight, line.m_text.c_str());
#else
	Broodwar->drawTextScreen(20, 10 + 18 * positon,  "%c%s", color, line.m_text.c_str());
#endif
	if (weight > threshold) {
		Broodwar->setTextSize(BWAPI::Text::Size::Large);
	}
}

Logger LOGGER;
