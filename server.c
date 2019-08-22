#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int socket_ecoute;
    char buffer[1024];
    char *hello = "Bonjour Client";
    struct sockaddr_in servaddr, cliaddr;
   
    if ( (socket_ecoute = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        printf("Erreur");        
    }       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));     
    
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(60000);
           
    if ( bind(socket_ecoute, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 )
    {
        printf("Erreur");
    }
      
    int len, n;
    n = recvfrom(socket_ecoute, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)bonjour, strlen(bonjour),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Message envoyé.\n");  
      
    return 0;
}

