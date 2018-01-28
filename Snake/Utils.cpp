#include "Utils.hpp"

#pragma warning (disable : 4996)
namespace Utils
{
	const char* GetFullTimeDayString() {
		time_t current_time;
		struct tm *time_info = {};
		static char buffer[10];
		std::string bufferString = "";
		static char* timeString;

		time(&current_time);
		time_info = localtime(&current_time);

		strftime(buffer, sizeof(buffer), "%X", time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%A", time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%d", time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%B", time_info);
		bufferString.append(buffer);
		bufferString.append(" ");

		strftime(buffer, sizeof(buffer), "%Y", time_info);
		bufferString.append(buffer);

		timeString = _strdup(bufferString.c_str());
		return timeString;
	}
}