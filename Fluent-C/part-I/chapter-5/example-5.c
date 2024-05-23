#include "api.h"

int main()
{

    struct Sender *s = createSender("192.168.0.1");
    char *dataToSend = "Hello World!";
    char *pointer = dataToSend;
    while (*pointer != '\0')
    {
        sendByteSender(s, *pointer);
        pointer++;
    }
    destroySender(s);
}
