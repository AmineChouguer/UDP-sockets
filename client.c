#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int sockfd;
    char buffer[1024];
    char *hello = "Bonjour serveur";
    struct sockaddr_in     servaddr;
       
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        printf("Erreur");
   
    }
    memset(&servaddr, 0, sizeof(servaddr));    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(60000);
    servaddr.sin_addr.s_addr = INADDR_ANY;
      
    int n, len;     
    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr));
    printf("Message envoyé.\n");         
    n = recvfrom(sockfd, (char *)buffer, 1024,  
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    close(sockfd);
    return 0;
}
