#include "IkLink.h"

void EdgeDemo::IkLink::setParentLink(IkLink* link)
{
	EDGE_ASSERT(!m_parent);
	EDGE_ASSERT(!link->m_child);

	m_parent = link;
	link->m_child = this;
}
