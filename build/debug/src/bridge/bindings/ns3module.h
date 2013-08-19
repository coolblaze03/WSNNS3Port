/* This file was generated by PyBindGen 0.15.0.795 */
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>


#if PY_VERSION_HEX < 0x020400F0

#define PyEval_ThreadsInitialized() 1

#define Py_CLEAR(op)				\
        do {                            	\
                if (op) {			\
                        PyObject *tmp = (PyObject *)(op);	\
                        (op) = NULL;		\
                        Py_DECREF(tmp);		\
                }				\
        } while (0)


#define Py_VISIT(op)							\
        do { 								\
                if (op) {						\
                        int vret = visit((PyObject *)(op), arg);	\
                        if (vret)					\
                                return vret;				\
                }							\
        } while (0)

#endif



#if PY_VERSION_HEX < 0x020500F0

typedef int Py_ssize_t;
# define PY_SSIZE_T_MAX INT_MAX
# define PY_SSIZE_T_MIN INT_MIN
typedef inquiry lenfunc;
typedef intargfunc ssizeargfunc;
typedef intobjargproc ssizeobjargproc;

#endif


#if     __GNUC__ > 2
# define PYBINDGEN_UNUSED(param) param __attribute__((__unused__))
#elif     __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
# define PYBINDGEN_UNUSED(param) __attribute__((__unused__)) param
#else
# define PYBINDGEN_UNUSED(param) param
#endif  /* !__GNUC__ */

typedef enum _PyBindGenWrapperFlags {
   PYBINDGEN_WRAPPER_FLAG_NONE = 0,
   PYBINDGEN_WRAPPER_FLAG_OBJECT_NOT_OWNED = (1<<0),
} PyBindGenWrapperFlags;


#include "ns3/bridge-module.h"
#include <ostream>
#include <sstream>
#include <typeinfo>
#include <map>
#include <iostream>
/* --- forward declarations --- */


typedef struct {
    PyObject_HEAD
    ns3::Address *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Address;


extern PyTypeObject *_PyNs3Address_Type;
#define PyNs3Address_Type (*_PyNs3Address_Type)

extern std::map<void*, PyObject*> *_PyNs3Address_wrapper_registry;
#define PyNs3Address_wrapper_registry (*_PyNs3Address_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::AttributeConstructionList *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3AttributeConstructionList;


extern PyTypeObject *_PyNs3AttributeConstructionList_Type;
#define PyNs3AttributeConstructionList_Type (*_PyNs3AttributeConstructionList_Type)

extern std::map<void*, PyObject*> *_PyNs3AttributeConstructionList_wrapper_registry;
#define PyNs3AttributeConstructionList_wrapper_registry (*_PyNs3AttributeConstructionList_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::AttributeConstructionList::Item *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3AttributeConstructionListItem;


extern PyTypeObject *_PyNs3AttributeConstructionListItem_Type;
#define PyNs3AttributeConstructionListItem_Type (*_PyNs3AttributeConstructionListItem_Type)

extern std::map<void*, PyObject*> *_PyNs3AttributeConstructionListItem_wrapper_registry;
#define PyNs3AttributeConstructionListItem_wrapper_registry (*_PyNs3AttributeConstructionListItem_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::CallbackBase *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3CallbackBase;


extern PyTypeObject *_PyNs3CallbackBase_Type;
#define PyNs3CallbackBase_Type (*_PyNs3CallbackBase_Type)

extern std::map<void*, PyObject*> *_PyNs3CallbackBase_wrapper_registry;
#define PyNs3CallbackBase_wrapper_registry (*_PyNs3CallbackBase_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::Ipv4Address *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv4Address;


extern PyTypeObject *_PyNs3Ipv4Address_Type;
#define PyNs3Ipv4Address_Type (*_PyNs3Ipv4Address_Type)

extern std::map<void*, PyObject*> *_PyNs3Ipv4Address_wrapper_registry;
#define PyNs3Ipv4Address_wrapper_registry (*_PyNs3Ipv4Address_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::Ipv4Mask *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv4Mask;


extern PyTypeObject *_PyNs3Ipv4Mask_Type;
#define PyNs3Ipv4Mask_Type (*_PyNs3Ipv4Mask_Type)

extern std::map<void*, PyObject*> *_PyNs3Ipv4Mask_wrapper_registry;
#define PyNs3Ipv4Mask_wrapper_registry (*_PyNs3Ipv4Mask_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::Ipv6Address *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv6Address;


extern PyTypeObject *_PyNs3Ipv6Address_Type;
#define PyNs3Ipv6Address_Type (*_PyNs3Ipv6Address_Type)

extern std::map<void*, PyObject*> *_PyNs3Ipv6Address_wrapper_registry;
#define PyNs3Ipv6Address_wrapper_registry (*_PyNs3Ipv6Address_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::Ipv6Prefix *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv6Prefix;


extern PyTypeObject *_PyNs3Ipv6Prefix_Type;
#define PyNs3Ipv6Prefix_Type (*_PyNs3Ipv6Prefix_Type)

extern std::map<void*, PyObject*> *_PyNs3Ipv6Prefix_wrapper_registry;
#define PyNs3Ipv6Prefix_wrapper_registry (*_PyNs3Ipv6Prefix_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::Mac48Address *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Mac48Address;


extern PyTypeObject *_PyNs3Mac48Address_Type;
#define PyNs3Mac48Address_Type (*_PyNs3Mac48Address_Type)

extern std::map<void*, PyObject*> *_PyNs3Mac48Address_wrapper_registry;
#define PyNs3Mac48Address_wrapper_registry (*_PyNs3Mac48Address_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::NetDeviceContainer *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3NetDeviceContainer;


extern PyTypeObject *_PyNs3NetDeviceContainer_Type;
#define PyNs3NetDeviceContainer_Type (*_PyNs3NetDeviceContainer_Type)

extern std::map<void*, PyObject*> *_PyNs3NetDeviceContainer_wrapper_registry;
#define PyNs3NetDeviceContainer_wrapper_registry (*_PyNs3NetDeviceContainer_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::ObjectBase *obj;
    PyObject *inst_dict;
    PyBindGenWrapperFlags flags:8;
} PyNs3ObjectBase;


extern PyTypeObject *_PyNs3ObjectBase_Type;
#define PyNs3ObjectBase_Type (*_PyNs3ObjectBase_Type)

class PyNs3ObjectBase__PythonHelper : public ns3::ObjectBase
{
public:
    PyObject *m_pyself;

    void set_pyobj(PyObject *pyobj)
    {
        Py_XDECREF(m_pyself);
        Py_INCREF(pyobj);
        m_pyself = pyobj;
    }

    virtual ~PyNs3ObjectBase__PythonHelper()
    {
        Py_CLEAR(m_pyself);
    }

};

extern std::map<void*, PyObject*> *_PyNs3ObjectBase_wrapper_registry;
#define PyNs3ObjectBase_wrapper_registry (*_PyNs3ObjectBase_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::ObjectDeleter *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3ObjectDeleter;


extern PyTypeObject *_PyNs3ObjectDeleter_Type;
#define PyNs3ObjectDeleter_Type (*_PyNs3ObjectDeleter_Type)

extern std::map<void*, PyObject*> *_PyNs3ObjectDeleter_wrapper_registry;
#define PyNs3ObjectDeleter_wrapper_registry (*_PyNs3ObjectDeleter_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::ObjectFactory *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3ObjectFactory;


extern PyTypeObject *_PyNs3ObjectFactory_Type;
#define PyNs3ObjectFactory_Type (*_PyNs3ObjectFactory_Type)

extern std::map<void*, PyObject*> *_PyNs3ObjectFactory_wrapper_registry;
#define PyNs3ObjectFactory_wrapper_registry (*_PyNs3ObjectFactory_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter > *obj;
    PyObject *inst_dict;
    PyBindGenWrapperFlags flags:8;
} PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter;


extern PyTypeObject *_PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_Type;
#define PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_Type (*_PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_Type)



#include <map>
#include <string>
#include <typeinfo>
#if defined(__GNUC__) && __GNUC__ >= 3
# include <cxxabi.h>
#endif

#define PBG_TYPEMAP_DEBUG 0

namespace pybindgen {

class TypeMap
{
   std::map<std::string, PyTypeObject *> m_map;

public:

   TypeMap() {}

   void register_wrapper(const std::type_info &cpp_type_info, PyTypeObject *python_wrapper)
   {

#if PBG_TYPEMAP_DEBUG
   std::cerr << "register_wrapper(this=" << this << ", type_name=" << cpp_type_info.name()
             << ", python_wrapper=" << python_wrapper->tp_name << ")" << std::endl;
#endif

       m_map[std::string(cpp_type_info.name())] = python_wrapper;
   }



   PyTypeObject * lookup_wrapper(const std::type_info &cpp_type_info, PyTypeObject *fallback_wrapper)
   {

#if PBG_TYPEMAP_DEBUG
   std::cerr << "lookup_wrapper(this=" << this << ", type_name=" << cpp_type_info.name() << ")" << std::endl;
#endif

       PyTypeObject *python_wrapper = m_map[cpp_type_info.name()];
       if (python_wrapper)
           return python_wrapper;
       else {
#if defined(__GNUC__) && __GNUC__ >= 3

           // Get closest (in the single inheritance tree provided by cxxabi.h)
           // registered python wrapper.
           const abi::__si_class_type_info *_typeinfo =
               dynamic_cast<const abi::__si_class_type_info*> (&cpp_type_info);
#if PBG_TYPEMAP_DEBUG
          std::cerr << "  -> looking at C++ type " << _typeinfo->name() << std::endl;
#endif
           while (_typeinfo && (python_wrapper = m_map[std::string(_typeinfo->name())]) == 0) {
               _typeinfo = dynamic_cast<const abi::__si_class_type_info*> (_typeinfo->__base_type);
#if PBG_TYPEMAP_DEBUG
               std::cerr << "  -> looking at C++ type " << _typeinfo->name() << std::endl;
#endif
           }

#if PBG_TYPEMAP_DEBUG
          if (python_wrapper) {
              std::cerr << "  -> found match " << std::endl;
          } else {
              std::cerr << "  -> return fallback wrapper" << std::endl;
          }
#endif

           return python_wrapper? python_wrapper : fallback_wrapper;

#else // non gcc 3+ compilers can only match against explicitly registered classes, not hidden subclasses
           return fallback_wrapper;
#endif
       }
   }
};

}


extern pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map;

#define PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map (*_PyNs3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter__typeid_map)


typedef struct {
    PyObject_HEAD
    ns3::TagBuffer *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TagBuffer;


extern PyTypeObject *_PyNs3TagBuffer_Type;
#define PyNs3TagBuffer_Type (*_PyNs3TagBuffer_Type)

extern std::map<void*, PyObject*> *_PyNs3TagBuffer_wrapper_registry;
#define PyNs3TagBuffer_wrapper_registry (*_PyNs3TagBuffer_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::TypeId *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TypeId;


extern PyTypeObject *_PyNs3TypeId_Type;
#define PyNs3TypeId_Type (*_PyNs3TypeId_Type)

extern std::map<void*, PyObject*> *_PyNs3TypeId_wrapper_registry;
#define PyNs3TypeId_wrapper_registry (*_PyNs3TypeId_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::TypeId::AttributeInformation *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TypeIdAttributeInformation;


extern PyTypeObject *_PyNs3TypeIdAttributeInformation_Type;
#define PyNs3TypeIdAttributeInformation_Type (*_PyNs3TypeIdAttributeInformation_Type)

extern std::map<void*, PyObject*> *_PyNs3TypeIdAttributeInformation_wrapper_registry;
#define PyNs3TypeIdAttributeInformation_wrapper_registry (*_PyNs3TypeIdAttributeInformation_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::TypeId::TraceSourceInformation *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TypeIdTraceSourceInformation;


extern PyTypeObject *_PyNs3TypeIdTraceSourceInformation_Type;
#define PyNs3TypeIdTraceSourceInformation_Type (*_PyNs3TypeIdTraceSourceInformation_Type)

extern std::map<void*, PyObject*> *_PyNs3TypeIdTraceSourceInformation_wrapper_registry;
#define PyNs3TypeIdTraceSourceInformation_wrapper_registry (*_PyNs3TypeIdTraceSourceInformation_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::empty *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Empty;


extern PyTypeObject *_PyNs3Empty_Type;
#define PyNs3Empty_Type (*_PyNs3Empty_Type)

extern std::map<void*, PyObject*> *_PyNs3Empty_wrapper_registry;
#define PyNs3Empty_wrapper_registry (*_PyNs3Empty_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::int64x64_t *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Int64x64_t;


extern PyTypeObject *_PyNs3Int64x64_t_Type;
#define PyNs3Int64x64_t_Type (*_PyNs3Int64x64_t_Type)

extern std::map<void*, PyObject*> *_PyNs3Int64x64_t_wrapper_registry;
#define PyNs3Int64x64_t_wrapper_registry (*_PyNs3Int64x64_t_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::Object *obj;
    PyObject *inst_dict;
    PyBindGenWrapperFlags flags:8;
} PyNs3Object;


extern PyTypeObject *_PyNs3Object_Type;
#define PyNs3Object_Type (*_PyNs3Object_Type)

class PyNs3Object__PythonHelper : public ns3::Object
{
public:
    PyObject *m_pyself;

    void set_pyobj(PyObject *pyobj)
    {
        Py_XDECREF(m_pyself);
        Py_INCREF(pyobj);
        m_pyself = pyobj;
    }

    virtual ~PyNs3Object__PythonHelper()
    {
        Py_CLEAR(m_pyself);
    }

};


typedef struct {
    PyObject_HEAD
    ns3::Object::AggregateIterator *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3ObjectAggregateIterator;


extern PyTypeObject *_PyNs3ObjectAggregateIterator_Type;
#define PyNs3ObjectAggregateIterator_Type (*_PyNs3ObjectAggregateIterator_Type)

extern std::map<void*, PyObject*> *_PyNs3ObjectAggregateIterator_wrapper_registry;
#define PyNs3ObjectAggregateIterator_wrapper_registry (*_PyNs3ObjectAggregateIterator_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> > *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt__;


extern PyTypeObject *_PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___Type;
#define PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___Type (*_PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___Type)


extern pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt____typeid_map;

#define PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt____typeid_map (*_PyNs3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt____typeid_map)


typedef struct {
    PyObject_HEAD
    ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> > *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt__;


extern PyTypeObject *_PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___Type;
#define PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___Type (*_PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___Type)


extern pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt____typeid_map;

#define PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt____typeid_map (*_PyNs3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt____typeid_map)


typedef struct {
    PyObject_HEAD
    ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> > *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt__;


extern PyTypeObject *_PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___Type;
#define PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___Type (*_PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___Type)


extern pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt____typeid_map;

#define PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt____typeid_map (*_PyNs3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt____typeid_map)


typedef struct {
    PyObject_HEAD
    ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> > *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt__;


extern PyTypeObject *_PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___Type;
#define PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___Type (*_PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___Type)


extern pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt____typeid_map;

#define PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt____typeid_map (*_PyNs3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt____typeid_map)


typedef struct {
    PyObject_HEAD
    ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> > *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt__;


extern PyTypeObject *_PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___Type;
#define PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___Type (*_PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___Type)


extern pybindgen::TypeMap *_PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt____typeid_map;

#define PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt____typeid_map (*_PyNs3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt____typeid_map)


typedef struct {
    PyObject_HEAD
    ns3::Time *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Time;


extern PyTypeObject *_PyNs3Time_Type;
#define PyNs3Time_Type (*_PyNs3Time_Type)

extern std::map<void*, PyObject*> *_PyNs3Time_wrapper_registry;
#define PyNs3Time_wrapper_registry (*_PyNs3Time_wrapper_registry)

typedef struct {
    PyObject_HEAD
    ns3::TraceSourceAccessor *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TraceSourceAccessor;


extern PyTypeObject *_PyNs3TraceSourceAccessor_Type;
#define PyNs3TraceSourceAccessor_Type (*_PyNs3TraceSourceAccessor_Type)


typedef struct {
    PyObject_HEAD
    ns3::AttributeAccessor *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3AttributeAccessor;


extern PyTypeObject *_PyNs3AttributeAccessor_Type;
#define PyNs3AttributeAccessor_Type (*_PyNs3AttributeAccessor_Type)


typedef struct {
    PyObject_HEAD
    ns3::AttributeChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3AttributeChecker;


extern PyTypeObject *_PyNs3AttributeChecker_Type;
#define PyNs3AttributeChecker_Type (*_PyNs3AttributeChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::AttributeValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3AttributeValue;


extern PyTypeObject *_PyNs3AttributeValue_Type;
#define PyNs3AttributeValue_Type (*_PyNs3AttributeValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::CallbackChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3CallbackChecker;


extern PyTypeObject *_PyNs3CallbackChecker_Type;
#define PyNs3CallbackChecker_Type (*_PyNs3CallbackChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::CallbackImplBase *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3CallbackImplBase;


extern PyTypeObject *_PyNs3CallbackImplBase_Type;
#define PyNs3CallbackImplBase_Type (*_PyNs3CallbackImplBase_Type)


typedef struct {
    PyObject_HEAD
    ns3::CallbackValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3CallbackValue;


extern PyTypeObject *_PyNs3CallbackValue_Type;
#define PyNs3CallbackValue_Type (*_PyNs3CallbackValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::Channel *obj;
    PyObject *inst_dict;
    PyBindGenWrapperFlags flags:8;
} PyNs3Channel;


extern PyTypeObject *_PyNs3Channel_Type;
#define PyNs3Channel_Type (*_PyNs3Channel_Type)

class PyNs3Channel__PythonHelper : public ns3::Channel
{
public:
    PyObject *m_pyself;

    void set_pyobj(PyObject *pyobj)
    {
        Py_XDECREF(m_pyself);
        Py_INCREF(pyobj);
        m_pyself = pyobj;
    }

    virtual ~PyNs3Channel__PythonHelper()
    {
        Py_CLEAR(m_pyself);
    }

};


typedef struct {
    PyObject_HEAD
    ns3::EmptyAttributeValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3EmptyAttributeValue;


extern PyTypeObject *_PyNs3EmptyAttributeValue_Type;
#define PyNs3EmptyAttributeValue_Type (*_PyNs3EmptyAttributeValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv4AddressChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv4AddressChecker;


extern PyTypeObject *_PyNs3Ipv4AddressChecker_Type;
#define PyNs3Ipv4AddressChecker_Type (*_PyNs3Ipv4AddressChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv4AddressValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv4AddressValue;


extern PyTypeObject *_PyNs3Ipv4AddressValue_Type;
#define PyNs3Ipv4AddressValue_Type (*_PyNs3Ipv4AddressValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv4MaskChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv4MaskChecker;


extern PyTypeObject *_PyNs3Ipv4MaskChecker_Type;
#define PyNs3Ipv4MaskChecker_Type (*_PyNs3Ipv4MaskChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv4MaskValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv4MaskValue;


extern PyTypeObject *_PyNs3Ipv4MaskValue_Type;
#define PyNs3Ipv4MaskValue_Type (*_PyNs3Ipv4MaskValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv6AddressChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv6AddressChecker;


extern PyTypeObject *_PyNs3Ipv6AddressChecker_Type;
#define PyNs3Ipv6AddressChecker_Type (*_PyNs3Ipv6AddressChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv6AddressValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv6AddressValue;


extern PyTypeObject *_PyNs3Ipv6AddressValue_Type;
#define PyNs3Ipv6AddressValue_Type (*_PyNs3Ipv6AddressValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv6PrefixChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv6PrefixChecker;


extern PyTypeObject *_PyNs3Ipv6PrefixChecker_Type;
#define PyNs3Ipv6PrefixChecker_Type (*_PyNs3Ipv6PrefixChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::Ipv6PrefixValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Ipv6PrefixValue;


extern PyTypeObject *_PyNs3Ipv6PrefixValue_Type;
#define PyNs3Ipv6PrefixValue_Type (*_PyNs3Ipv6PrefixValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::Mac48AddressChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Mac48AddressChecker;


extern PyTypeObject *_PyNs3Mac48AddressChecker_Type;
#define PyNs3Mac48AddressChecker_Type (*_PyNs3Mac48AddressChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::Mac48AddressValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3Mac48AddressValue;


extern PyTypeObject *_PyNs3Mac48AddressValue_Type;
#define PyNs3Mac48AddressValue_Type (*_PyNs3Mac48AddressValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::NetDevice *obj;
    PyObject *inst_dict;
    PyBindGenWrapperFlags flags:8;
} PyNs3NetDevice;


extern PyTypeObject *_PyNs3NetDevice_Type;
#define PyNs3NetDevice_Type (*_PyNs3NetDevice_Type)


typedef struct {
    PyObject_HEAD
    ns3::ObjectFactoryChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3ObjectFactoryChecker;


extern PyTypeObject *_PyNs3ObjectFactoryChecker_Type;
#define PyNs3ObjectFactoryChecker_Type (*_PyNs3ObjectFactoryChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::ObjectFactoryValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3ObjectFactoryValue;


extern PyTypeObject *_PyNs3ObjectFactoryValue_Type;
#define PyNs3ObjectFactoryValue_Type (*_PyNs3ObjectFactoryValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::TimeChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TimeChecker;


extern PyTypeObject *_PyNs3TimeChecker_Type;
#define PyNs3TimeChecker_Type (*_PyNs3TimeChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::TimeValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TimeValue;


extern PyTypeObject *_PyNs3TimeValue_Type;
#define PyNs3TimeValue_Type (*_PyNs3TimeValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::TypeIdChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TypeIdChecker;


extern PyTypeObject *_PyNs3TypeIdChecker_Type;
#define PyNs3TypeIdChecker_Type (*_PyNs3TypeIdChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::TypeIdValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3TypeIdValue;


extern PyTypeObject *_PyNs3TypeIdValue_Type;
#define PyNs3TypeIdValue_Type (*_PyNs3TypeIdValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::AddressChecker *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3AddressChecker;


extern PyTypeObject *_PyNs3AddressChecker_Type;
#define PyNs3AddressChecker_Type (*_PyNs3AddressChecker_Type)


typedef struct {
    PyObject_HEAD
    ns3::AddressValue *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3AddressValue;


extern PyTypeObject *_PyNs3AddressValue_Type;
#define PyNs3AddressValue_Type (*_PyNs3AddressValue_Type)


typedef struct {
    PyObject_HEAD
    ns3::BridgeHelper *obj;
    PyBindGenWrapperFlags flags:8;
} PyNs3BridgeHelper;


extern PyTypeObject PyNs3BridgeHelper_Type;

extern std::map<void*, PyObject*> PyNs3BridgeHelper_wrapper_registry;

typedef struct {
    PyObject_HEAD
    ns3::BridgeChannel *obj;
    PyObject *inst_dict;
    PyBindGenWrapperFlags flags:8;
} PyNs3BridgeChannel;


extern PyTypeObject PyNs3BridgeChannel_Type;

class PyNs3BridgeChannel__PythonHelper : public ns3::BridgeChannel
{
public:
    PyObject *m_pyself;
    PyNs3BridgeChannel__PythonHelper()
        : ns3::BridgeChannel(), m_pyself(NULL)
        {}


    void set_pyobj(PyObject *pyobj)
    {
        Py_XDECREF(m_pyself);
        Py_INCREF(pyobj);
        m_pyself = pyobj;
    }

    virtual ~PyNs3BridgeChannel__PythonHelper()
    {
        Py_CLEAR(m_pyself);
    }


    static PyObject * _wrap_NotifyConstructionCompleted(PyNs3BridgeChannel *self);
    inline void NotifyConstructionCompleted__parent_caller()
    { ns3::ObjectBase::NotifyConstructionCompleted(); }

    static PyObject * _wrap_NotifyNewAggregate(PyNs3BridgeChannel *self);
    inline void NotifyNewAggregate__parent_caller()
    { ns3::Object::NotifyNewAggregate(); }

    static PyObject * _wrap_GetInstanceTypeId(PyNs3BridgeChannel *self);
    inline ns3::TypeId GetInstanceTypeId__parent_caller()
    { return ns3::Object::GetInstanceTypeId(); }

    static PyObject * _wrap_DoStart(PyNs3BridgeChannel *self);
    inline void DoStart__parent_caller()
    { ns3::Object::DoStart(); }

    static PyObject * _wrap_GetNDevices(PyNs3BridgeChannel *self);
    inline uint32_t GetNDevices__parent_caller()
    { return ns3::BridgeChannel::GetNDevices(); }

    static PyObject * _wrap_DoDispose(PyNs3BridgeChannel *self);
    inline void DoDispose__parent_caller()
    { ns3::Object::DoDispose(); }

    static PyObject * _wrap_GetDevice(PyNs3BridgeChannel *self, PyObject *args, PyObject *kwargs);
    inline ns3::Ptr< ns3::NetDevice > GetDevice__parent_caller(uint32_t i)
    { return ns3::BridgeChannel::GetDevice(i); }

    virtual uint32_t GetNDevices() const;

    virtual ns3::Ptr< ns3::NetDevice > GetDevice(uint32_t i) const;

    virtual ns3::TypeId GetInstanceTypeId() const;

    virtual void DoDispose();

    virtual void DoStart();

    virtual void NotifyNewAggregate();

    virtual void NotifyConstructionCompleted();

    static ns3::TypeId GetTypeId (void)
    {
      static ns3::TypeId tid = ns3::TypeId ("PyNs3BridgeChannel__PythonHelper")
        .SetParent< ns3::BridgeChannel > ()
        ;
      return tid;
    }
};

NS_OBJECT_ENSURE_REGISTERED (PyNs3BridgeChannel__PythonHelper);


typedef struct {
    PyObject_HEAD
    ns3::BridgeNetDevice *obj;
    PyObject *inst_dict;
    PyBindGenWrapperFlags flags:8;
} PyNs3BridgeNetDevice;


extern PyTypeObject PyNs3BridgeNetDevice_Type;

