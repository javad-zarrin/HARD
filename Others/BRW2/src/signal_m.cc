//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/signal.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "signal_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(Signal);

Signal::Signal(const char *name, int kind) : cPacket(name,kind)
{
    this->source_var = 0;
    this->destination_var = 0;
    this->mtype_var = 0;
    this->value_var = 0;
}

Signal::Signal(const Signal& other) : cPacket(other)
{
    copy(other);
}

Signal::~Signal()
{
}

Signal& Signal::operator=(const Signal& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Signal::copy(const Signal& other)
{
    this->source_var = other.source_var;
    this->destination_var = other.destination_var;
    this->mtype_var = other.mtype_var;
    this->value_var = other.value_var;
}

void Signal::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->source_var);
    doPacking(b,this->destination_var);
    doPacking(b,this->mtype_var);
    doPacking(b,this->value_var);
}

void Signal::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->source_var);
    doUnpacking(b,this->destination_var);
    doUnpacking(b,this->mtype_var);
    doUnpacking(b,this->value_var);
}

unsigned int Signal::getSource() const
{
    return source_var;
}

void Signal::setSource(unsigned int source)
{
    this->source_var = source;
}

unsigned int Signal::getDestination() const
{
    return destination_var;
}

void Signal::setDestination(unsigned int destination)
{
    this->destination_var = destination;
}

unsigned int Signal::getMtype() const
{
    return mtype_var;
}

void Signal::setMtype(unsigned int mtype)
{
    this->mtype_var = mtype;
}

long Signal::getValue() const
{
    return value_var;
}

void Signal::setValue(long value)
{
    this->value_var = value;
}

class SignalDescriptor : public cClassDescriptor
{
  public:
    SignalDescriptor();
    virtual ~SignalDescriptor();

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

Register_ClassDescriptor(SignalDescriptor);

SignalDescriptor::SignalDescriptor() : cClassDescriptor("Signal", "cPacket")
{
}

SignalDescriptor::~SignalDescriptor()
{
}

bool SignalDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Signal *>(obj)!=NULL;
}

const char *SignalDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SignalDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int SignalDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *SignalDescriptor::getFieldName(void *object, int field) const
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
        "value",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int SignalDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "mtype")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SignalDescriptor::getFieldTypeString(void *object, int field) const
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
        "long",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *SignalDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SignalDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Signal *pp = (Signal *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SignalDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Signal *pp = (Signal *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSource());
        case 1: return ulong2string(pp->getDestination());
        case 2: return ulong2string(pp->getMtype());
        case 3: return long2string(pp->getValue());
        default: return "";
    }
}

bool SignalDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Signal *pp = (Signal *)object; (void)pp;
    switch (field) {
        case 0: pp->setSource(string2ulong(value)); return true;
        case 1: pp->setDestination(string2ulong(value)); return true;
        case 2: pp->setMtype(string2ulong(value)); return true;
        case 3: pp->setValue(string2long(value)); return true;
        default: return false;
    }
}

const char *SignalDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *SignalDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Signal *pp = (Signal *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


