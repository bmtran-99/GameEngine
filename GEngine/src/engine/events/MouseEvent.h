#pragma once

#include "Event.h"
#include "engine\core\MouseCodes.h"

namespace GEngine
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const double x, const double y) : m_PosX(x), m_PosY(y) {}

		inline double GetMouseX() const { return m_PosX; }
		inline double GetMouseY() const { return m_PosY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse moved: " << GetMouseX() << ", " << GetMouseY() << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);
	private:
		double m_PosX, m_PosY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const double x, const double y) : m_OffsetX(x), m_OffsetY(y) {}

		inline double GetXOffset() const { return m_OffsetX; }
		inline double GetYOffset() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse scrolled: " << GetXOffset() << ", " << GetYOffset() << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);
	private:
		double m_OffsetX, m_OffsetY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(MouseCode code) : m_Button(code) {}

		MouseCode m_Button;
	};

	class MousePressedEvent : public MouseButtonEvent
	{
	public: 
		MousePressedEvent(MouseCode code) : MouseButtonEvent(code) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Pressed: " << m_Button << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MousePressed);
	};

	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(MouseCode code) : MouseButtonEvent(code) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Released: " << m_Button << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseReleased);
	};
}