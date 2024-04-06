#include "csapp.h"

#define MAXLINE 1024
#define RECORDS_FILE "records.csv"

void add_record(char *record_data) {
    FILE *file = fopen(RECORDS_FILE, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening records file\n");
        return; 
    }
    fprintf(file, "%s\n", record_data);
    fclose(file);
}

void search_records(char *criteria, int connfd) {
    FILE *file = fopen(RECORDS_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening records file\n");
        return; 
    }

    char line[MAXLINE];
    while (fgets(line, MAXLINE, file) != NULL) {
        // Implement search logic based on the received criteria
        // For example, if searching by name:
        if (strstr(line, criteria) != NULL) {
            Rio_writen(connfd, line, strlen(line) + 1);
        }
    }
    fclose(file);
}

void handle_client(int connfd) {
    char buf[MAXLINE];
    int option;
    while (1) {
        if (Rio_readn(connfd, &option, sizeof(int)) <= 0) {
            printf("Client disconnected\n");
            Close(connfd);
            return;
        }
        switch (option) {
            case 1:
                if (Rio_readlineb(connfd, buf, MAXLINE) <= 0) {
                    printf("Client disconnected\n");
                    Close(connfd);
                    return;
                }
                add_record(buf);
                Rio_writen(connfd, "Record added successfully\n", strlen("Record added successfully\n") + 1);
                break;
            case 2:
                if (Rio_readlineb(connfd, buf, MAXLINE) <= 0) {
                    printf("Client disconnected\n");
                    Close(connfd);
                    return;
                }
                search_records(buf, connfd);
                break;
            case 3:
                if (Rio_readlineb(connfd, buf, MAXLINE) <= 0) {
                    printf("Client disconnected\n");
                    Close(connfd);
                    return;
                }
                search_records(buf, connfd); // Assume buf contains zip code
                break;
            case 4:
                if (Rio_readlineb(connfd, buf, MAXLINE) <= 0) {
                    printf("Client disconnected\n");
                    Close(connfd);
                    return;
                }
                search_records(buf, connfd); // Assume buf contains salary
                break;
            case 5:
                Close(connfd);
                return;
            default:
                printf("Invalid option\n");
                break;
        }
    }
}

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    listenfd = Open_listenfd(argv[1]);
    printf("Server listening on port %s...\n", argv[1]); // Print when server starts listening
    
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        // Handle client requests
        handle_client(connfd);
        Close(connfd);
    }

    exit(EXIT_SUCCESS);
}
