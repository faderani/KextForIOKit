/* add your code here */

#include <IOKit/IOService.h>
#include <IOKit/IOUserClient.h>
#include "Common.h"


class com_osxkernel_driver_IOKitTest : public IOService {
    OSDeclareDefaultStructors(com_osxkernel_driver_IOKitTest)
public:
    
    virtual bool init (OSDictionary* dictionary = NULL);
    virtual void free (void);
    
    virtual IOService* probe (IOService* provider , SInt32* score);
    virtual bool start (IOService* provider);
    virtual void stop (IOService* provider);
    
    IOReturn setProperties (OSObject* properties);
    
    
    
    
    
    
    
};


class com_osxkernel_driver_IOKitTestClient : public IOUserClient {
    OSDeclareDefaultStructors(com_osxkernel_driver_IOKitTestClient);
    

    
    private :
    task_t m_task;
    com_osxkernel_driver_IOKitTest* m_driver;
    
    static const IOExternalMethodDispatch sMethods[kTestUserClientMethodCount];
    
    static IOReturn		sStartTimer (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn		sStopTimer (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn		sGetElapsedTimerTime (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn		sGetElapsedTimerValue (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn		sDelayForMs (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    static IOReturn		sDelayForTime (OSObject* target, void* reference, IOExternalMethodArguments* arguments);
    
    IOReturn		startTimer ();
    IOReturn		stopTimer ();
    IOReturn		getElapsedTimerTime (uint32_t* timerTime);
    IOReturn		getElapsedTimerValue (TimerValue* timerValue);
    IOReturn		delayForMs (uint32_t milliseconds);
    IOReturn		delayForTime (const TimerValue* timerValue);
    
    
    
    
    public :
    virtual bool initWithTask (task_t owningTask , void* securityToken , UInt32 type , OSDictionary* properties);
    virtual bool start (IOService* provider);

    virtual IOReturn clientClose (void);
    virtual void stop (IOService* provider);
    virtual void free (void);
   
    virtual IOReturn externalMethod(uint32_t selector , IOExternalMethodArguments* args , IOExternalMethodDispatch* dispatch , OSObject* target , void* reference);
    
    
    
    
    
    
    
    
    
    
    
    
    

};
