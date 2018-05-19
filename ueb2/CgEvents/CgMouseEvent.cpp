#include "CgMouseEvent.h"


CgMouseEvent::CgMouseEvent(Cg::EventType type, glm::vec2 localPos, Cg::MouseButtons button)
{
    m_type=type;
    m_localPos = localPos;
    m_button = button;
}

CgMouseEvent::~CgMouseEvent()
{

}

Cg::EventType  CgMouseEvent::getType()
{
    return m_type;
}

CgBaseEvent* CgMouseEvent::clone()
{
    return new CgMouseEvent(m_type,m_localPos, m_button);
}

glm::vec2 CgMouseEvent::getWindowPos() const
{
    return m_windowPos;
}

void CgMouseEvent::setWindowPos(const glm::vec2 &windowPos)
{
    m_windowPos = windowPos;
}

glm::vec2 CgMouseEvent::getLocalPos() const
{
    return m_localPos;
}

void CgMouseEvent::setLocalPos(const glm::vec2 &localPos)
{
    m_localPos = localPos;
}

std::ostream& operator<<(std::ostream& os,const CgMouseEvent& e)
{
    os << "Mouse-Event of Type: "<< e.m_type <<", LocalPos:(" << e.m_localPos.x << "," << e.m_localPos.y <<"), Button: "<< e.m_button;
    return os;
}
