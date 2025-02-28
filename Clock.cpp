#include <Windows.h>

#include "Clock.h"

Clock::Clock()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	m_previous_time = (st.wDay * 24 * 3600 * 1000) + (st.wHour * 3600 * 1000) + (st.wMinute * 60 * 1000) + (st.wSecond * 1000) + (st.wMilliseconds);
}

long int Clock::delta()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	long int m_current_time = (st.wDay * 24 * 3600 * 1000) + (st.wHour * 3600 * 1000) + (st.wMinute * 60 * 1000) + (st.wSecond * 1000) + (st.wMilliseconds);

	// Computes elapsed time and resets previous time.
	int elapsed_time = m_current_time - m_previous_time;
	m_previous_time = m_current_time;

	return elapsed_time;
}

long int Clock::split() const
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	long int m_current_time = (st.wDay * 24 * 3600 * 1000) + (st.wHour * 3600 * 1000) + (st.wMinute * 60 * 1000) + (st.wSecond * 1000) + (st.wMilliseconds);

	// Computes elapsed time and resets previous time.
	int elapsed_time = m_current_time - m_previous_time;

	return elapsed_time;
}