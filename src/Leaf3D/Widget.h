
#ifndef __OAK3D_INCLUDE_LEAF3D_WIDGET_H__
#define __OAK3D_INCLUDE_LEAF3D_WIDGET_H__

#include <cstdint>
#include <list>

#include "ScreenPosition.h"
#include "ScreenSize2D.h"
#include "Core/Interface/IUpdatable.h"
#include "IListenForEvents.h"
#include "IListenForMouseEvents.h"
#include "IFocusable.h"

namespace ro3d
{
	namespace Leaf3D
	{
		class Widget : public Core::IUpdatable, public IFocusable, public virtual IListenForMouseEvents
		{
		public:
			Widget();
			virtual ~Widget();

			inline ScreenPosition2D GetPosition();
			inline void SetPosition(const ScreenPosition2D &position);
			inline void SetPosition(uint32_t x, uint32_t y);

			inline ScreenSize2D GetSize();
			inline void SetSize(const ScreenSize2D &size);
			inline void SetSize(uint32_t width, uint32_t height);

			inline uint32_t GetDepth();
			inline void SetDepth(uint32_t depth);

			inline bool IsVisible();
			inline void SetVisible(bool visible);
									
			static inline std::list<Widget *>* GetWidgetList();
			static inline void ReleaseWidgetList();

			virtual void OnMouseLeftButtonPressed(MouseEvent *mev);
			virtual void OnMouseLeftButtonReleased(MouseEvent *mev);
			virtual void OnMouseLeftButtonHeld(MouseEvent *mev);

			virtual FocusZone GetFocusZone();
		protected:
			ScreenPosition2D m_position;
			ScreenSize2D m_size;
			uint32_t m_depth; // 0 is on top
			bool m_bVisible;

		private:
			// Global list of all widgets
			static std::list< Widget * > *s_widgets;
			static bool s_bDeleteListIfEmpty;
		};

		// --------------------------------------------------------------------------------
		std::list<Widget *>* Widget::GetWidgetList()
		{
			if( s_widgets == nullptr )
				s_widgets = new std::list<Widget *>();

			return s_widgets;
		}

		// --------------------------------------------------------------------------------
		void Widget::ReleaseWidgetList()
		{
			if( s_widgets != nullptr )
			{
				if(s_widgets->size() == 0)
					delete s_widgets;
				else
					s_bDeleteListIfEmpty = true;
			}
		}

		// --------------------------------------------------------------------------------
		ScreenPosition2D Widget::GetPosition()
		{
			return m_position;
		}

		// --------------------------------------------------------------------------------
		void Widget::SetPosition(const ScreenPosition2D &position)
		{
			m_position = position;
		}

		// --------------------------------------------------------------------------------
		void Widget::SetPosition(uint32_t x, uint32_t y)
		{
			m_position.x = x;
			m_position.y = y;
		}

		// --------------------------------------------------------------------------------
		ScreenSize2D Widget::GetSize()
		{
			return m_size;
		}

		// --------------------------------------------------------------------------------
		void Widget::SetSize(const ScreenSize2D &size)
		{
			m_size = size;
		}

		// --------------------------------------------------------------------------------
		void Widget::SetSize(uint32_t width, uint32_t height)
		{
			m_size.width = width;
			m_size.height = height;
		}

		// --------------------------------------------------------------------------------
		uint32_t Widget::GetDepth()
		{
			return m_depth;
		}

		// --------------------------------------------------------------------------------
		void Widget::SetDepth(uint32_t depth)
		{
			m_depth = depth;
		}

		// --------------------------------------------------------------------------------
		bool Widget::IsVisible()
		{
			return m_bVisible;
		}
		
		// --------------------------------------------------------------------------------
		void Widget::SetVisible(bool bVisible)
		{
			m_bVisible = bVisible;
		}
	}
}

#endif
