#pragma once
#include <iomanip>
#include <sstream>

namespace TimeUtils
{
	static std::string GetTimeAsString(const float time)
	{
		float a, b;

		a = modf(time, &b);

		float pi = a;
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << pi;
		std::string s = stream.str();

		s.erase(0, 2);

		std::string string(std::to_string((int)b).c_str());
		if (string.size() == 1)
			string.insert(0, "0");
		string.append(":");
		string.append(s.c_str());

		return string;
	}

	static float SecondsToMinutes(const int seconds)
	{
		int min = seconds / 60;
		if (min < 1)
			return seconds * 0.01f;
		else
		{
			float e = seconds % 60;
			float out = min;
			out += e * 0.01f;
			return out;
		}
	}
}
