#include <cstdarg>
#include <stdio.h>

#include "LogManager.h"
#include "GameManager.h"

using namespace df;

LogManager::LogManager()
{
	setType("LogManager");

	m_p_f = NULL;
	m_do_flush = false;
}

LogManager::~LogManager()
{
	// Only closes logfile if it exists.
	if (m_p_f != NULL)
	{
		fclose(m_p_f);
	}
}

LogManager &LogManager::getInstance()
{
	static LogManager single;
	return single;
}

int LogManager::startUp()
{
	// Visual Studio wants me to use fopen_s instead. Having looked into it, I am not sure this is actually a good/necessary idea, so I simply suppressed the warning.
	#pragma warning(suppress : 4996)
	m_p_f = fopen("dragonfly.log", "w");

	Manager::startUp();

	return 0;
}

void LogManager::shutDown()
{
	writeLog("LogManager shutdown");

	// Closes logfile
	fclose(m_p_f);

	Manager::shutDown();
}

void LogManager::setFlush(bool do_flush)
{
	m_do_flush = do_flush;
}

int LogManager::writeLog(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	fprintf(m_p_f, "[%d] ", GM.getCurrentFrame());
	vfprintf(m_p_f, fmt, args);
	fprintf(m_p_f, "\n");

	// Only flushes immediately if the user has called the setFlush function and set it to true.
	if (m_do_flush)
	{
		fflush(m_p_f);
	}

	va_end(args);

	return 0;
}