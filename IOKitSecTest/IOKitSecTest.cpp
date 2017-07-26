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



const IOExternalMethodDispatch com_osxkernel_driver_IOKitTestClient::sMethods[kTestUserClientMethodCount] = {
    {sStartTimer, 0 , 0 , 0 , 0},
    {sStopTimer, 0 , 0 , 0 , 0},
    {sGetElapsedTimerTime, 0 , 0 , 1 , 0},
    {sGetElapsedTimerValue, 0 , 0 , 0 , sizeof(TimerValue)},
    {sDelayForMs , 1 , 0 , 0 , 0},
    {sDelayForTime, 0 , sizeof(TimerValue) , 0 , 0},
    

                                               
};

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

IOReturn com_osxkernel_driver_IOKitTestClient::externalMethod(uint32_t selector, IOExternalMethodArguments *args, IOExternalMethodDispatch *dispatch, OSObject *target, void *reference) {
    
    if (selector >= kTestUserClientMethodCount) {
        return kIOReturnUnsupported;
    }
    
    dispatch = (IOExternalMethodDispatch*)&sMethods[selector];
    target = this;
    reference = NULL;
    return super::externalMethod(selector, args, dispatch, target, reference);
    

    
    
    
    
}


IOReturn com_osxkernel_driver_IOKitTestClient::sGetElapsedTimerTime(OSObject *target, void *reference, IOExternalMethodArguments *arguments) {
    com_osxkernel_driver_IOKitTestClient *me;
    uint32_t timerTime;
    IOReturn result;
    me = (com_osxkernel_driver_IOKitTestClient*)target;
    
    result = me->getElapsedTimerTime(&timerTime);
    arguments->scalarOutput[0] = timerTime;
    
    return result;
}


IOReturn com_osxkernel_driver_IOKitTestClient::sDelayForTime(OSObject *target, void *reference, IOExternalMethodArguments *arguments) {
    com_osxkernel_driver_IOKitTestClient *me;
    me = (com_osxkernel_driver_IOKitTestClient*)target;
    
    return me->delayForTime((TimerValue*)arguments->structureInput);
}









