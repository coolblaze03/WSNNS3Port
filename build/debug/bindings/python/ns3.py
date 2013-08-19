import warnings
warnings.warn("the ns3 module is a compatibility layer and should not be used in newly written code", DeprecationWarning, stacklevel=2)

from ns.core import *
from ns.network import *
from ns.config_store import *
from ns.internet import *
from ns.propagation import *
from ns.point_to_point import *
from ns.csma import *
from ns.emu import *
from ns.bridge import *
from ns.tap_bridge import *
from ns.applications import *
from ns.nix_vector_routing import *
from ns.olsr import *
from ns.aodv import *
from ns.dsdv import *
from ns.mobility import *
from ns.wifi import *
from ns.netanim import *
from ns.stats import *
from ns.uan import *
from ns.spectrum import *
from ns.mesh import *
from ns.flow_monitor import *
from ns.wimax import *
from ns.lte import *
from ns.mpi import *
from ns.topology_read import *
from ns.energy import *
from ns.tools import *
from ns.visualizer import *
from ns.point_to_point_layout import *
