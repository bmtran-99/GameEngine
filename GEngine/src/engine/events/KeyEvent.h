#pragma once

#include "Event.h"
#include "engine\core\KeyCodes.h"

namespace GEngine
{
	class KeyEvent : public Event
	{
	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard);

	protected:
		KeyEvent(const KeyCode keycode) : m_KeyCode(keycode)
		{}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const unsigned int repeated_count) : KeyEvent(keycode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	};

	class KeyReleasedEvent: public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode)
		{}

		EVENT_CLASS_TYPE(KeyReleased);
	};
}