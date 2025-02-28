// The clock, for timing (such as in the game loop).

class Clock
{
	private:
		long int m_previous_time; // Previous time delta() called (in milliseconds).

	public:
		// Sets previous_time to current time.
		Clock();

		// Return time elapsed since delta() was last called.
		// Resets previous time.
		// Units are milliseconds.
		long int delta();

		// Return time elapsed since delta() was last called.
		// Does not reset previous time.
		// Units are milliseconds.
		long int split() const;
};