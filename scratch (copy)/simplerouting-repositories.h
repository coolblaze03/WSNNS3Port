

///
/// \file	simplerouting-repositories.h
///

#ifndef SIMPLEROUTING_REPOSITORIES_H
#define SIMPLEROUTING_REPOSITORIES_H

#include <set>
#include <vector>

#include "ns3/ipv4-address.h"
#include "ns3/nstime.h"

namespace ns3 { namespace SimpleRouting {



/// A Neighbor Tuple.
                struct Neighbor
                {
                  /// Main address of a neighbor node.
                  Ipv4Address neighborMainAddr;
                  /// Neighbor Type and Link Type at the four less significative digits.
                  int ID;
                };

                static inline bool
                operator == (const Neighbor &a, const Neighbor &b)
                {
                  return (a.neighborMainAddr == b.neighborMainAddr
                          && a.ID == b.ID);
                }

                static inline std::ostream&
                operator << (std::ostream &os, const Neighbor &tuple)
                {
                  os << "Neighbor(neighborMainAddr=" << tuple.neighborMainAddr
                  << ", ID =" << (tuple.ID);
                  return os;
                }


                typedef std::vector<Neighbor>              NeighborSet; ///< Neighbor Set type.
  

  
/// A Child Tuple.
                struct Child
                {
                  /// Main address of a Child node.
                  Ipv4Address childMainAddr;
                  /// Child Type and Link Type at the four less significative digits.
                  int ID;
                };

                static inline bool
                operator == (const Child &a, const Child &b)
                {
                  return (a.childMainAddr == b.childMainAddr
                          && a.ID == b.ID);
                }

                static inline std::ostream&
                operator << (std::ostream &os, const Child &tuple)
                {
                  os << "Child(childMainAddr=" << tuple.childMainAddr
                  << ", ID =" << (tuple.ID);
                  return os;
                }


                typedef std::vector<Child>              ChildSet; ///< Child Set type.
				
				
			/// A parent Tuple.
                struct Parent
                {
                  /// Main address of a Parent node.
                  Ipv4Address parentMainAddr;
                  /// Parent Type and Link Type at the four less significative digits.
                  int ID;
                };

                static inline bool
                operator == (const Parent &a, const Parent &b)
                {
                  return (a.parentMainAddr == b.parentMainAddr
                          && a.ID == b.ID);
                }

                static inline std::ostream&
                operator << (std::ostream &os, const Parent &tuple)
                {
                  os << "Parent(parentMainAddr=" << tuple.parentMainAddr
                  << ", ID =" << (tuple.ID);
                  return os;
                }

					
				

                }} // namespace ns3, olsr

#endif /* OLSR_REPOSITORIES_H */