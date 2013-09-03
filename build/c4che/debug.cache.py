AR = '/usr/bin/ar'
ARFLAGS = 'rcs'
BINDIR = '/usr/local/bin'
BOOST = False
CC = ['/usr/bin/gcc']
CCDEFINES = ['_DEBUG', '_DEBUG', 'NS3_ASSERT_ENABLE', 'NS3_LOG_ENABLE', 'NETWORK_SIMULATION_CRADLE']
CCDEFINES_ST = '-D%s'
CCFLAGS = ['-O0', '-ggdb', '-g3', '-Wall', '-Werror', '-O0', '-ggdb', '-g3', '-Wall', '-Werror', '-Wno-error=deprecated-declarations', '-fstrict-aliasing', '-Wstrict-aliasing']
CCFLAGS_DEBUG = ['-g']
CCFLAGS_MACBUNDLE = ['-fPIC']
CCFLAGS_PTHREAD = '-pthread'
CCFLAGS_PYEMBED = ['-fno-strict-aliasing']
CCFLAGS_PYEXT = ['-fno-strict-aliasing', '-fvisibility=hidden']
CCFLAGS_RELEASE = ['-O2']
CCLNK_SRC_F = ''
CCLNK_TGT_F = ['-o', '']
CC_NAME = 'gcc'
CC_SRC_F = ''
CC_TGT_F = ['-c', '-o', '']
CC_VERSION = ('4', '4', '3')
COMPILER_CC = 'gcc'
COMPILER_CXX = 'g++'
CPP = '/usr/bin/cpp'
CPPPATH_PYEMBED = ['/usr/include/python2.6']
CPPPATH_PYEXT = ['/usr/include/python2.6']
CPPPATH_ST = '-I%s'
CXX = ['/usr/bin/g++']
CXXDEFINES = ['_DEBUG', 'NS3_ASSERT_ENABLE', 'NS3_LOG_ENABLE', 'NETWORK_SIMULATION_CRADLE']
CXXDEFINES_ST = '-D%s'
CXXFLAGS = ['-O0', '-ggdb', '-g3', '-Wall', '-Werror', '-Wno-error=deprecated-declarations', '-fstrict-aliasing', '-Wstrict-aliasing']
CXXFLAGS_DEBUG = ['-g']
CXXFLAGS_PTHREAD = '-pthread'
CXXFLAGS_PYEMBED = ['-fno-strict-aliasing']
CXXFLAGS_PYEXT = ['-fno-strict-aliasing', '-fvisibility=hidden']
CXXFLAGS_RELEASE = ['-O2']
CXXLNK_SRC_F = ''
CXXLNK_TGT_F = ['-o', '']
CXX_NAME = 'gcc'
CXX_SRC_F = ''
CXX_TGT_F = ['-c', '-o', '']
DATADIR = '/usr/local/share'
DATAROOTDIR = '/usr/local/share'
DEST_BINFMT = 'elf'
DEST_CPU = 'x86'
DEST_OS = 'linux'
DOCDIR = '/usr/local/share/doc/ns'
DOXYGEN = ''
DVIDIR = '/usr/local/share/doc/ns'
ENABLE_EMU = True
ENABLE_EXAMPLES = False
ENABLE_GSL = False
ENABLE_GTK_CONFIG_STORE = False
ENABLE_LIBXML2 = False
ENABLE_NSC = False
ENABLE_PYTHON_BINDINGS = True
ENABLE_REAL_TIME = True
ENABLE_STATIC_NS3 = False
ENABLE_SUDO = False
ENABLE_TAP = True
ENABLE_TESTS = False
ENABLE_THREADING = True
EXAMPLE_DIRECTORIES = ['udp-client-server', 'stats', 'wireless', 'mobility', 'tcp', 'naming', 'routing', 'tutorial', 'realtime', 'energy', 'matrix-topology', 'socket', 'udp', 'ipv6', 'error-model']
EXEC_PREFIX = '/usr/local'
FULLSTATIC_MARKER = '-static'
GCC_RTTI_ABI_COMPLETE = 'True'
GSL = False
GTK_CONFIG_STORE = False
HAVE_DIRENT_H = 1
HAVE_GETENV = 1
HAVE_IF_TUN_H = 1
HAVE_INTTYPES_H = 1
HAVE_NETINET_IN_H = 1
HAVE_PACKET_H = 1
HAVE_PTHREAD_H = 1
HAVE_PYTHON_H = 1
HAVE_SIGNAL_H = 1
HAVE_STDINT_H = 1
HAVE_STDLIB_H = 1
HAVE_SYS_INT_TYPES_H = ()
HAVE_SYS_SOCKET_H = 1
HAVE_SYS_STAT_H = 1
HAVE_SYS_TYPES_H = 1
HAVE_UINT128_T = ()
HAVE___UINT128_T = ()
HTMLDIR = '/usr/local/share/doc/ns'
INCLUDEDIR = '/usr/local/include'
INFODIR = '/usr/local/share/info'
INT64X64_USE_CAIRO = 1
LIBDIR = '/usr/local/lib'
LIBEXECDIR = '/usr/local/libexec'
LIBPATH_PYEMBED = ['/usr/lib']
LIBPATH_PYTHON2.6 = ['/usr/lib']
LIBPATH_ST = '-L%s'
LIBXML2 = False
LIB_DL = ['dl']
LIB_PYEMBED = ['m', 'pthread', 'dl', 'util', 'python2.6']
LIB_PYTHON2.6 = ['python2.6']
LIB_RT = ['rt']
LIB_ST = '-l%s'
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINKFLAGS_PTHREAD = '-pthread'
LINKFLAGS_PYEMBED = ['-Wl,-Bsymbolic-functions']
LINK_CC = ['/usr/bin/gcc']
LINK_CXX = ['/usr/bin/g++']
LOCALEDIR = '/usr/local/share/locale'
LOCALSTATEDIR = '/usr/local/var'
MANDIR = '/usr/local/share/man'
MODULES_NOT_BUILT = ['click', 'openflow']
MPI = '/usr/bin/mpic++'
NS3_ACTIVE_VARIANT = 'debug'
NS3_BUILDDIR = '/home/chabli/tarballs/ns-allinone-3.12.1/ns-3.12.1/build'
NS3_ENABLED_MODULES = ['ns3-core', 'ns3-network', 'ns3-config-store', 'ns3-internet', 'ns3-propagation', 'ns3-point-to-point', 'ns3-csma', 'ns3-emu', 'ns3-bridge', 'ns3-tap-bridge', 'ns3-virtual-net-device', 'ns3-applications', 'ns3-nix-vector-routing', 'ns3-olsr', 'ns3-aodv', 'ns3-dsdv', 'ns3-mobility', 'ns3-wifi', 'ns3-netanim', 'ns3-stats', 'ns3-uan', 'ns3-spectrum', 'ns3-mesh', 'ns3-test', 'ns3-ns3tcp', 'ns3-ns3wifi', 'ns3-flow-monitor', 'ns3-wimax', 'ns3-lte', 'ns3-mpi', 'ns3-topology-read', 'ns3-energy', 'ns3-tools', 'ns3-visualizer', 'ns3-point-to-point-layout', 'ns3-csma-layout', 'ns3-template']
NS3_EXECUTABLE_PATH = ['/home/chabli/tarballs/ns-allinone-3.12.1/ns-3.12.1/build/debug/src/emu', '/home/chabli/tarballs/ns-allinone-3.12.1/ns-3.12.1/build/debug/src/tap-bridge']
NS3_MODULES = ['ns3-core', 'ns3-network', 'ns3-config-store', 'ns3-internet', 'ns3-propagation', 'ns3-point-to-point', 'ns3-csma', 'ns3-emu', 'ns3-bridge', 'ns3-tap-bridge', 'ns3-virtual-net-device', 'ns3-applications', 'ns3-nix-vector-routing', 'ns3-olsr', 'ns3-aodv', 'ns3-dsdv', 'ns3-mobility', 'ns3-wifi', 'ns3-netanim', 'ns3-stats', 'ns3-uan', 'ns3-spectrum', 'ns3-mesh', 'ns3-test', 'ns3-ns3tcp', 'ns3-ns3wifi', 'ns3-flow-monitor', 'ns3-wimax', 'ns3-lte', 'ns3-mpi', 'ns3-topology-read', 'ns3-energy', 'ns3-tools', 'ns3-visualizer', 'ns3-point-to-point-layout', 'ns3-csma-layout', 'ns3-template']
NS3_MODULE_PATH = ['/usr/lib/gcc/i486-linux-gnu/4.4.3', '/home/chabli/tarballs/ns-allinone-3.12.1/nsc-0.5.2/lib', '/home/chabli/tarballs/ns-allinone-3.12.1/nsc-0.5.2/linux-2.6.26', '/home/chabli/tarballs/ns-allinone-3.12.1/ns-3.12.1/build/debug']
NS3_OPTIONAL_FEATURES = [('static', 'Static build', False, 'option --enable-static not selected'), ('Threading', 'Threading Primitives', True, '<pthread.h> include not detected'), ('RealTime', 'Real Time Simulator', True, 'threading not enabled'), ('EmuNetDevice', 'Emulated Net Device', True, '<netpacket/packet.h> include not detected'), ('TapBridge', 'Tap Bridge', True, '<linux/if_tun.h> include not detected'), ('GtkConfigStore', 'GtkConfigStore', False, "library 'gtk+-2.0 >= 2.12' not found"), ('XmlIo', 'XmlIo', False, "library 'libxml-2.0 >= 2.7' not found"), ('nsc', 'Network Simulation Cradle', True, ''), ('nsclick', 'NS-3 Click Integration', False, 'nsclick not enabled (see option --with-nsclick)'), ('openflow', 'NS-3 OpenFlow Integration', False, 'Required boost libraries not found'), ('SqliteDataOutput', 'SQlite stats data output', False, "library 'sqlite3' not found"), ('python', 'Python Bindings', True, None), ('pygccxml', 'Python API Scanning Support', False, "Missing 'pygccxml' Python module"), ('mpi', 'MPI Support', False, 'option --enable-mpi not selected'), ('ENABLE_SUDO', 'Use sudo to set suid bit', False, 'option --enable-sudo not selected'), ('ENABLE_TESTS', 'Build tests', False, 'defaults to disabled'), ('ENABLE_EXAMPLES', 'Build examples', False, 'defaults to disabled'), ('GSL', 'GNU Scientific Library (GSL)', False, 'GSL not found')]
NSC_ENABLED = True
OLDINCLUDEDIR = '/usr/include'
PACKAGE = 'ns'
PDFDIR = '/usr/local/share/doc/ns'
PKG_CONFIG = '/usr/bin/pkg-config'
PLATFORM = 'linux2'
PREFIX = '/usr/local'
PSDIR = '/usr/local/share/doc/ns'
PYC = 1
PYCMD = '"import sys, py_compile;py_compile.compile(sys.argv[1], sys.argv[2])"'
PYFLAGS = ''
PYFLAGS_OPT = '-O'
PYO = 1
PYTHON = '/usr/bin/python'
PYTHONDIR = '/usr/local/lib/python2.6/dist-packages'
PYTHON_BINDINGS_APIDEFS = 'gcc-ILP32'
PYTHON_CONFIG = '/usr/bin/python2.6-config'
PYTHON_VERSION = '2.6'
RANLIB = '/usr/bin/ranlib'
RPATH_ST = '-Wl,-rpath,%s'
SBINDIR = '/usr/local/sbin'
SHAREDSTATEDIR = '/usr/local/com'
SHLIB_MARKER = '-Wl,-Bdynamic'
SONAME_ST = '-Wl,-h,%s'
SQLITE_STATS = False
STATICLIBPATH_ST = '-L%s'
STATICLIB_MARKER = '-Wl,-Bstatic'
STATICLIB_ST = '-l%s'
SUDO = '/usr/bin/sudo'
SYSCONFDIR = '/usr/local/etc'
VALGRIND = ''
WITH_NSC = '/home/chabli/tarballs/ns-allinone-3.12.1/nsc-0.5.2'
WITH_PYBINDGEN = '/home/chabli/tarballs/ns-allinone-3.12.1/pybindgen-0.15.0.795'
WL_SONAME_SUPPORTED = True
_VARIANT_ = 'debug'
cfg_files = ['ns3/core-config.h', 'ns3/config-store-config.h', 'ns3/netanim-config.h']
defines = {'HAVE_PACKET_H': 1, 'HAVE_GETENV': 1, 'HAVE_SYS_STAT_H': 1, 'HAVE_PYTHON_H': 1, 'HAVE_SYS_INT_TYPES_H': (), 'HAVE_SYS_SOCKET_H': 1, 'HAVE_SIGNAL_H': 1, 'HAVE_NETINET_IN_H': 1, 'HAVE___UINT128_T': (), 'HAVE_IF_TUN_H': 1, 'INT64X64_USE_CAIRO': 1, 'HAVE_SYS_TYPES_H': 1, 'HAVE_INTTYPES_H': 1, 'PYTHONDIR': '"/usr/local/lib/python2.6/dist-packages"', 'HAVE_UINT128_T': (), 'HAVE_STDLIB_H': 1, 'HAVE_PTHREAD_H': 1, 'HAVE_DIRENT_H': 1, 'HAVE_STDINT_H': 1}
macbundle_PATTERN = '%s.bundle'
program_PATTERN = '%s'
pyext_PATTERN = '%s.so'
shlib_CCFLAGS = ['-fPIC', '-DPIC']
shlib_CXXFLAGS = ['-fPIC', '-DPIC']
shlib_LINKFLAGS = ['-shared']
shlib_PATTERN = 'lib%s.so'
staticlib_LINKFLAGS = ['-Wl,-Bstatic']
staticlib_PATTERN = 'lib%s.a'
