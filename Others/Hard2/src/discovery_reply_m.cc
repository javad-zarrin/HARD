//
// Generated file, do not edit! Created by opp_msgc 4.5 from src/discovery_reply.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "discovery_reply_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(LSM);

LSM::LSM(const char *name, int kind) : ::cPacket(name,kind)
{
    this->source_var = 0;
    this->destination_var = 0;
    this->mtype_var = 0;
}

LSM::LSM(const LSM& other) : ::cPacket(other)
{
    copy(other);
}

LSM::~LSM()
{
}

LSM& LSM::operator=(const LSM& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void LSM::copy(const LSM& other)
{
    this->source_var = other.source_var;
    this->destination_var = other.destination_var;
    this->mtype_var = other.mtype_var;
    this->mq_result_var = other.mq_result_var;
}

void LSM::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->source_var);
    doPacking(b,this->destination_var);
    doPacking(b,this->mtype_var);
    doPacking(b,this->mq_result_var);
}

void LSM::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->source_var);
    doUnpacking(b,this->destination_var);
    doUnpacking(b,this->mtype_var);
    doUnpacking(b,this->mq_result_var);
}

unsigned int LSM::getSource() const
{
    return source_var;
}

void LSM::setSource(unsigned int source)
{
    this->source_var = source;
}

unsigned int LSM::getDestination() const
{
    return destination_var;
}

void LSM::setDestination(unsigned int destination)
{
    this->destination_var = destination;
}

unsigned int LSM::getMtype() const
{
    return mtype_var;
}

void LSM::setMtype(unsigned int mtype)
{
    this->mtype_var = mtype;
}

Light_MQ_Status& LSM::getMq_result()
{
    return mq_result_var;
}

void LSM::setMq_result(const Light_MQ_Status& mq_result)
{
    this->mq_result_var = mq_result;
}

class LSMDescriptor : public cClassDescriptor
{
  public:
    LSMDescriptor();
    virtual ~LSMDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(LSMDescriptor);

LSMDescriptor::LSMDescriptor() : cClassDescriptor("LSM", "cPacket")
{
}

LSMDescriptor::~LSMDescriptor()
{
}

bool LSMDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<LSM *>(obj)!=NULL;
}

const char *LSMDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LSMDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int LSMDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *LSMDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "source",
        "destination",
        "mtype",
        "mq_result",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int LSMDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "mtype")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "mq_result")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *LSMDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "Light_MQ_Status",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *LSMDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int LSMDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LSM *pp = (LSM *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string LSMDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    LSM *pp = (LSM *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSource());
        case 1: return ulong2string(pp->getDestination());
        case 2: return ulong2string(pp->getMtype());
        case 3: {std::stringstream out; out << pp->getMq_result(); return out.str();}
        default: return "";
    }
}

bool LSMDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LSM *pp = (LSM *)object; (void)pp;
    switch (field) {
        case 0: pp->setSource(string2ulong(value)); return true;
        case 1: pp->setDestination(string2ulong(value)); return true;
        case 2: pp->setMtype(string2ulong(value)); return true;
        default: return false;
    }
}

const char *LSMDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(Light_MQ_Status));
        default: return NULL;
    };
}

void *LSMDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LSM *pp = (LSM *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getMq_result()); break;
        default: return NULL;
    }
}


