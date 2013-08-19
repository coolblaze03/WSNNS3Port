

#ifndef SIMPLEROUTING_HELPER_H_
#define SIMPLEROUTING_HELPER_H_

#include "ns3/object-factory.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/ipv4-routing-helper.h"
#include "ns3/pointer.h"
#include "simplerouting.h"

namespace ns3
{
namespace SimpleRouting {

class RoutingHelper : public Ipv4RoutingHelper
{
public:
  RoutingHelper();

  RoutingHelper* Copy (void) const;

  virtual Ptr<Ipv4RoutingProtocol> Create (Ptr<Node> node) const;

  void Set (std::string name, const AttributeValue &value);
  
private:
  ObjectFactory m_agentFactory;
};


RoutingHelper::RoutingHelper ()
 : Ipv4RoutingHelper ()
{
  m_agentFactory.SetTypeId ("ns3::SimpleRouting::RoutingProtocol");
}

RoutingHelper*
RoutingHelper::Copy (void) const
{
  return new RoutingHelper (*this);
}

Ptr<Ipv4RoutingProtocol>
RoutingHelper::Create (Ptr<Node> node) const
{
  Ptr<ns3::SimpleRouting::RoutingProtocol> agent = m_agentFactory.Create<ns3::SimpleRouting::RoutingProtocol> ();
  node->AggregateObject (agent);
  return agent;
}

void
RoutingHelper::Set (std::string name, const AttributeValue &value)
{
  m_agentFactory.Set (name, value);
}

}}
#endif 
