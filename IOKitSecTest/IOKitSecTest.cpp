/* add your code here */

#include "IOKitSecTest.hpp"
#include <IOKit/IOLib.h>


#define super IOService

OSDefineMetaClassAndStructors(com_osxkernel_driver_IOKitTest, IOService)

bool com_osxkernel_driver_IOKitTest::init(OSDictionary* dict) {
    bool res = super::init(dict);
    printf("IOKitTest::init\n");
    return res;
}



void com_osxkernel_driver_IOKitTest::free(void) {
    printf("IOKitTest::free\n");
    super::free();
}

IOService* com_osxkernel_driver_IOKitTest::probe(IOService* provider, SInt32 *score) {
    IOService *res = super::probe(provider, score);
    printf("IOKitTest::prob\n");
    
    return res;
}


bool com_osxkernel_driver_IOKitTest::start(IOService *provider) {
    bool res = super::start(provider);
    super::registerService();
    printf("IOKitTest::start\n");
    
    return res;
}

void com_osxkernel_driver_IOKitTest::stop(IOService *provider) {
    printf("IOKitTest::stop\n");
    
    OSString* string;
    
    string = OSDynamicCast(OSString, getProperty("StopMessage"));
    
    if (string) {
        IOLog("%s\n" , string->getCStringNoCopy());
    }
    
    
    
    super::stop(provider);
}

IOReturn com_osxkernel_driver_IOKitTest::setProperties(OSObject *properties) {
    
    OSDictionary* propertyDict;
    propertyDict = OSDynamicCast(OSDictionary, properties);
    
    if (propertyDict != NULL) {
        OSString* string;
        
        string = OSDynamicCast(OSString , propertyDict->getObject("StopMessage"));
        
        if (string !=NULL) {
            
            setProperty("StopMessage", string);
            return kIOReturnSuccess;
            
        }
        
    }
    
    
    return kIOReturnUnsupported;
    
}

#define super IOUserClient

OSDefineMetaClassAndStructors(com_osxkernel_driver_IOKitTestClient, super);

bool com_osxkernel_driver_IOKitTestClient::initWithTask(task_t owningTask, void *securityToken, UInt32 type, OSDictionary *properties) {
    
    if (!owningTask) {
        return false;
    }
    
    if (!super::initWithTask(owningTask,securityToken,type,properties)) {
        return false;
    }
    
    m_task = owningTask;
    IOReturn ret = clientHasPrivilege(securityToken, kIOClientPrivilegeAdministrator);
    
    if (ret ==kIOReturnSuccess) {
        //
    }
    
    return true;
    
}

bool com_osxkernel_driver_IOKitTestClient::start(IOService *provider) {
    
    if (!super::start(provider)) {
        return false;
    }
    m_driver = OSDynamicCast(com_osxkernel_driver_IOKitTest, provider);
    if (!m_driver) {
        return false;
    }
    
    return true;
}


IOReturn com_osxkernel_driver_IOKitTestClient::clientClose(void) {
    terminate();
    return kIOReturnSuccess;
}









