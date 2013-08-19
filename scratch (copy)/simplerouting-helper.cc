
#include "ns3/pointer.h"
#include "simplerouting-helper.h"

namespace ns3
{ namespace SimpleRouting {
RoutingHelper::RoutingHelper ()
 : Ipv4RoutingHelper ()
{
  m_agentFactory.SetTypeId ("ns3::SimplerRouting::RoutingHelper");
}

RoutingHelper* 
RoutingHelper::Copy (void) const 
{
  return new RoutingHelper (*this);
}

Ptr<Ipv4RoutingProtocol> 
RoutingHelper::Create (Ptr<Node> node) const
{
  Ptr<RoutingProtocol> agent = m_agentFactory.Create<RoutingProtocol> ();
  node->AggregateObject (agent);
  return agent;
}

void 
RoutingHelper::Set (std::string name, const AttributeValue &value)
{
  m_agentFactory.Set (name, value);
}

}}
