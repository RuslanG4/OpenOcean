#ifndef EVENT_H
#define EVENT_H

namespace gpp {
	class Events
	{
	public:
		Events();
		~Events();

		enum class Event
		{
			NONE,
			IDLE,
			DAMAGE_TAKEN,
			DAMAGE_TAKEN_STOP,
			SWIM_FAST,
			SWIM_RIGHT_START_EVENT,
			SWIM_RIGHT_STOP_EVENT,
			Count
		};

		void setCurrent(Event);
		Event getCurrent();

	private:
		Event m_current;
	};
}

#endif
