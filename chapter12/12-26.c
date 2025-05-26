/*
 * 12.26.c
 */
#include <stdio.h>
#include "csapp.h"

/*
 * struct hostent *gethostbyname(const char *name)
 *
 * struct hostent {
 *   char  *h_name;       // Official name of the host
 *   char **h_aliases;    // Null-terminated array of alternate names
 *   int    h_addrtype;   // Host address type (e.g., AF_INET)
 *   int    h_length;     // Length of address in bytes
 *   char **h_addr_list;  // Null-terminated array of addresses
 * }
 */

 static sem_t mutex;

 static void init_mutex(void) {
    Sem_init(&mutex, 0, 1);
 }

 struct hostent *gethostbyname_ts(const char* name, struct hostent *cphost) {
    struct hostent *sharedhost;
    int aliases_count, addr_count = 0;

    P(&mutex);
    sharedhost = gethostbyname(name);

    //copy char*
    cphost->h_name = Malloc(strlen(sharedhost->h_name) + 1);
    strcpy(cphost->h_name, sharedhost->h_name);

    int i;
    //copy char**
    for (i = 0; sharedhost->h_aliases[i] != NULL; i++) aliases_count++;  
    cphost->h_aliases = Malloc(sizeof(char *) * (aliases_count + 1));
    for (i = 0; i < aliases_count; i++) {
        cphost->h_aliases[i] = Malloc(strlen(sharedhost->h_aliases[i]) + 1);
        strcpy(cphost->h_aliases[i], sharedhost->h_aliases[i]);
    }

    for (i = 0; sharedhost->h_addr_list[i] != NULL; i++) addr_count++;
    cphost->h_addr_list = Malloc(sizeof(char *) * (addr_count + 1));
    for (i = 0; i < addr_count; i++) {
        cphost->h_addr_list[i] = Malloc(strlen(sharedhost->h_addr_list[i]) + 1);
        strcpy(cphost->h_addr_list[i], sharedhost->h_addr_list[i]);
    }

    // copy int
    cphost->h_addrtype = sharedhost->h_addrtype;
    cphost->h_length = sharedhost->h_length;

    V(&mutex);
    return cphost;
 }

 int main(int argc, char* argv[]) {
    init_mutex();
    struct hostent host;
    gethostbyname_ts("127.0.0.1", &host);
    return 0;
 }