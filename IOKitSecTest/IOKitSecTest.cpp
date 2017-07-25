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
