

#ifndef SIMPLEROUTING_HELPER_H_
#define SIMPLEROUTING_HELPER_H_

#include "ns3/object-factory.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/ipv4-routing-helper.h"
#include "ns3/pointer.h"
#include "ns3/simplerouting.h"

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



}}
#endif 
