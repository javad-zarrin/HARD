//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/rd_message.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "rd_message_m.h"

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




Register_Class(rdMessage);

rdMessage::rdMessage(const char *name, int kind) : cMessage(name,kind)
{
    this->ID_var = 0;
    this->flag_var = true;
    this->source_var = 0;
    this->destination_var = 0;
    this->hopCount_var = 0;
    this->mtype_var = 0;
    this->intContent_var = 0;
    this->intContentSD_var = 0;
    this->intValue_var = 0;
    this->mainContent_var = DEFULT_STC;
    this->stringContent_var = DEFULT_STC;
}

rdMessage::rdMessage(const rdMessage& other) : cMessage(other)
{
    copy(other);
}

rdMessage::~rdMessage()
{
}

rdMessage& rdMessage::operator=(const rdMessage& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void rdMessage::copy(const rdMessage& other)
{
    this->ID_var = other.ID_var;
    this->flag_var = other.flag_var;
    this->source_var = other.source_var;
    this->destination_var = other.destination_var;
    this->hopCount_var = other.hopCount_var;
    this->mtype_var = other.mtype_var;
    this->intContent_var = other.intContent_var;
    this->intContentSD_var = other.intContentSD_var;
    this->intValue_var = other.intValue_var;
    this->mainContent_var = other.mainContent_var;
    this->stringContent_var = other.stringContent_var;
}

void rdMessage::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->ID_var);
    doPacking(b,this->flag_var);
    doPacking(b,this->source_var);
    doPacking(b,this->destination_var);
    doPacking(b,this->hopCount_var);
    doPacking(b,this->mtype_var);
    doPacking(b,this->intContent_var);
    doPacking(b,this->intContentSD_var);
    doPacking(b,this->intValue_var);
    doPacking(b,this->mainContent_var);
    doPacking(b,this->stringContent_var);
}

void rdMessage::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->ID_var);
    doUnpacking(b,this->flag_var);
    doUnpacking(b,this->source_var);
    doUnpacking(b,this->destination_var);
    doUnpacking(b,this->hopCount_var);
    doUnpacking(b,this->mtype_var);
    doUnpacking(b,this->intContent_var);
    doUnpacking(b,this->intContentSD_var);
    doUnpacking(b,this->intValue_var);
    doUnpacking(b,this->mainContent_var);
    doUnpacking(b,this->stringContent_var);
}

unsigned int rdMessage::getID() const
{
    return ID_var;
}

void rdMessage::setID(unsigned int ID)
{
    this->ID_var = ID;
}

bool rdMessage::getFlag() const
{
    return flag_var;
}

void rdMessage::setFlag(bool flag)
{
    this->flag_var = flag;
}

int rdMessage::getSource() const
{
    return source_var;
}

void rdMessage::setSource(int source)
{
    this->source_var = source;
}

int rdMessage::getDestination() const
{
    return destination_var;
}

void rdMessage::setDestination(int destination)
{
    this->destination_var = destination;
}

int rdMessage::getHopCount() const
{
    return hopCount_var;
}

void rdMessage::setHopCount(int hopCount)
{
    this->hopCount_var = hopCount;
}

int rdMessage::getMtype() const
{
    return mtype_var;
}

void rdMessage::setMtype(int mtype)
{
    this->mtype_var = mtype;
}

int rdMessage::getIntContent() const
{
    return intContent_var;
}

void rdMessage::setIntContent(int intContent)
{
    this->intContent_var = intContent;
}

int rdMessage::getIntContentSD() const
{
    return intContentSD_var;
}

void rdMessage::setIntContentSD(int intContentSD)
{
    this->intContentSD_var = intContentSD;
}

int rdMessage::getIntValue() const
{
    return intValue_var;
}

void rdMessage::setIntValue(int intValue)
{
    this->intValue_var = intValue;
}

strtype& rdMessage::getMainContent()
{
    return mainContent_var;
}

void rdMessage::setMainContent(const strtype& mainContent)
{
    this->mainContent_var = mainContent;
}

strtype& rdMessage::getStringContent()
{
    return stringContent_var;
}

void rdMessage::setStringContent(const strtype& stringContent)
{
    this->stringContent_var = stringContent;
}

class rdMessageDescriptor : public cClassDescriptor
{
  public:
    rdMessageDescriptor();
    virtual ~rdMessageDescriptor();

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

Register_ClassDescriptor(rdMessageDescriptor);

rdMessageDescriptor::rdMessageDescriptor() : cClassDescriptor("rdMessage", "cMessage")
{
}

rdMessageDescriptor::~rdMessageDescriptor()
{
}

bool rdMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<rdMessage *>(obj)!=NULL;
}

const char *rdMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int rdMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount(object) : 11;
}

unsigned int rdMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *rdMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ID",
        "flag",
        "source",
        "destination",
        "hopCount",
        "mtype",
        "intContent",
        "intContentSD",
        "intValue",
        "mainContent",
        "stringContent",
    };
    return (field>=0 && field<11) ? fieldNames[field] : NULL;
}

int rdMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='I' && strcmp(fieldName, "ID")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "flag")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+3;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "mtype")==0) return base+5;
    if (fieldName[0]=='i' && strcmp(fieldName, "intContent")==0) return base+6;
    if (fieldName[0]=='i' && strcmp(fieldName, "intContentSD")==0) return base+7;
    if (fieldName[0]=='i' && strcmp(fieldName, "intValue")==0) return base+8;
    if (fieldName[0]=='m' && strcmp(fieldName, "mainContent")==0) return base+9;
    if (fieldName[0]=='s' && strcmp(fieldName, "stringContent")==0) return base+10;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *rdMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "bool",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "strtype",
        "strtype",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : NULL;
}

const char *rdMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int rdMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    rdMessage *pp = (rdMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string rdMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    rdMessage *pp = (rdMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getID());
        case 1: return bool2string(pp->getFlag());
        case 2: return long2string(pp->getSource());
        case 3: return long2string(pp->getDestination());
        case 4: return long2string(pp->getHopCount());
        case 5: return long2string(pp->getMtype());
        case 6: return long2string(pp->getIntContent());
        case 7: return long2string(pp->getIntContentSD());
        case 8: return long2string(pp->getIntValue());
        case 9: {std::stringstream out; out << pp->getMainContent(); return out.str();}
        case 10: {std::stringstream out; out << pp->getStringContent(); return out.str();}
        default: return "";
    }
}

bool rdMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    rdMessage *pp = (rdMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setID(string2ulong(value)); return true;
        case 1: pp->setFlag(string2bool(value)); return true;
        case 2: pp->setSource(string2long(value)); return true;
        case 3: pp->setDestination(string2long(value)); return true;
        case 4: pp->setHopCount(string2long(value)); return true;
        case 5: pp->setMtype(string2long(value)); return true;
        case 6: pp->setIntContent(string2long(value)); return true;
        case 7: pp->setIntContentSD(string2long(value)); return true;
        case 8: pp->setIntValue(string2long(value)); return true;
        default: return false;
    }
}

const char *rdMessageDescriptor::getFieldStructName(void *object, int field) const
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
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        "strtype",
        "strtype",
    };
    return (field>=0 && field<11) ? fieldStructNames[field] : NULL;
}

void *rdMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    rdMessage *pp = (rdMessage *)object; (void)pp;
    switch (field) {
        case 9: return (void *)(&pp->getMainContent()); break;
        case 10: return (void *)(&pp->getStringContent()); break;
        default: return NULL;
    }
}


