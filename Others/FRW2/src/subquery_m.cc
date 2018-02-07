//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/subquery.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "subquery_m.h"

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




Register_Class(SQM);

SQM::SQM(const char *name, int kind) : cPacket(name,kind)
{
    this->source_var = 0;
    this->destination_var = 0;
    this->mtype_var = 0;
    this->extra_var = 0;
}

SQM::SQM(const SQM& other) : cPacket(other)
{
    copy(other);
}

SQM::~SQM()
{
}

SQM& SQM::operator=(const SQM& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void SQM::copy(const SQM& other)
{
    this->source_var = other.source_var;
    this->destination_var = other.destination_var;
    this->mtype_var = other.mtype_var;
    this->extra_var = other.extra_var;
    this->sq_var = other.sq_var;
}

void SQM::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->source_var);
    doPacking(b,this->destination_var);
    doPacking(b,this->mtype_var);
    doPacking(b,this->extra_var);
    doPacking(b,this->sq_var);
}

void SQM::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->source_var);
    doUnpacking(b,this->destination_var);
    doUnpacking(b,this->mtype_var);
    doUnpacking(b,this->extra_var);
    doUnpacking(b,this->sq_var);
}

unsigned int SQM::getSource() const
{
    return source_var;
}

void SQM::setSource(unsigned int source)
{
    this->source_var = source;
}

unsigned int SQM::getDestination() const
{
    return destination_var;
}

void SQM::setDestination(unsigned int destination)
{
    this->destination_var = destination;
}

unsigned int SQM::getMtype() const
{
    return mtype_var;
}

void SQM::setMtype(unsigned int mtype)
{
    this->mtype_var = mtype;
}

unsigned int SQM::getExtra() const
{
    return extra_var;
}

void SQM::setExtra(unsigned int extra)
{
    this->extra_var = extra;
}

subQuery& SQM::getSq()
{
    return sq_var;
}

void SQM::setSq(const subQuery& sq)
{
    this->sq_var = sq;
}

class SQMDescriptor : public cClassDescriptor
{
  public:
    SQMDescriptor();
    virtual ~SQMDescriptor();

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

Register_ClassDescriptor(SQMDescriptor);

SQMDescriptor::SQMDescriptor() : cClassDescriptor("SQM", "cPacket")
{
}

SQMDescriptor::~SQMDescriptor()
{
}

bool SQMDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SQM *>(obj)!=NULL;
}

const char *SQMDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SQMDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int SQMDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *SQMDescriptor::getFieldName(void *object, int field) const
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
        "extra",
        "sq",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int SQMDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "mtype")==0) return base+2;
    if (fieldName[0]=='e' && strcmp(fieldName, "extra")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sq")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SQMDescriptor::getFieldTypeString(void *object, int field) const
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
        "unsigned int",
        "subQuery",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *SQMDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SQMDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SQM *pp = (SQM *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SQMDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SQM *pp = (SQM *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSource());
        case 1: return ulong2string(pp->getDestination());
        case 2: return ulong2string(pp->getMtype());
        case 3: return ulong2string(pp->getExtra());
        case 4: {std::stringstream out; out << pp->getSq(); return out.str();}
        default: return "";
    }
}

bool SQMDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SQM *pp = (SQM *)object; (void)pp;
    switch (field) {
        case 0: pp->setSource(string2ulong(value)); return true;
        case 1: pp->setDestination(string2ulong(value)); return true;
        case 2: pp->setMtype(string2ulong(value)); return true;
        case 3: pp->setExtra(string2ulong(value)); return true;
        default: return false;
    }
}

const char *SQMDescriptor::getFieldStructName(void *object, int field) const
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
        "subQuery",
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *SQMDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SQM *pp = (SQM *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getSq()); break;
        default: return NULL;
    }
}


