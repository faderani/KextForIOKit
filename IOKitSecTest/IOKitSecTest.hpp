/* add your code here */

#include <IOKit/IOService.h>
#include <IOKit/IOUserClient.h>


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
    
    public :
    virtual bool initWithTask (task_t owningTask , void* securityToken , UInt32 type , OSDictionary* properties);
    virtual bool start (IOService* provider);

    virtual IOReturn clientClose (void);
    virtual void stop (IOService* provider);
    virtual void free (void);

};
