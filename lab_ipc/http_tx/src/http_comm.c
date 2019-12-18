#include "http_comm.h"

void post_data(const char* address)
{
    char curl_req[];
    char buf[];
    char data[];

    while (gets(buf))
        strcat(data, buf);

    sprintf(curl_req, "curl -X POST -H \"Content-Type: text/plain\" -d '%s' %s", data, address);
    system(curl_req);
}
