typedef struct INTERNAL_DRIVER_STRUCT *DRIVER_HANDLE;
typedef void (*DriverSend_FP)(char byte); /* this is the */
typedef char (*DriverReceive_FP)();       /* interface definition */

struct DriverFunctions
{
    DriverSend_FP fpSend;
    DriverReceive_FP fpReceive;
};

DRIVER_HANDLE driverCreate(void *initArg, struct DriverFunctions f);
void driverDestroy(DRIVER_HANDLE h);
void sendByte(DRIVER_HANDLE h, char byte); /* internally calls fpSend */
char receiveByte(DRIVER_HANDLE h);         /* internally calls fpReceive */
void setIpAddress(DRIVER_HANDLE h, char *ip);
void setMacAddress(DRIVER_HANDLE h, char *mac);