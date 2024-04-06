#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to process user-selected option
void process_option(int option, int clientfd);

int main(int argc, char *argv[]) {
    // Check for correct number of command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    int clientfd = Open_clientfd(argv[1], argv[2]);
    if (clientfd < 0) {
        fprintf(stderr, "Error connecting to server\n");
        exit(EXIT_FAILURE);
    }

    // Main loop to process user options
    int option;
    while (1) {
        // Display menu options
        printf("(1) Add record\n");
        printf("(2) Search by Name\n");
        printf("(3) Search by Zip Code\n");
        printf("(4) Search by Salary\n");
        printf("(5) Terminate\n");
        printf("Select an option [1, 2, 3, 4, or 5]: ");
        scanf("%d", &option);

        // Process the selected option
        process_option(option, clientfd);

        // Terminate loop if user chooses option 5
        if (option == 5) {
            break;
        }
    }

    // Close connection
    Close(clientfd);

    return 0;
}

// Function to process user-selected option
void process_option(int option, int clientfd) {
    char buf[MAXLINE];
    char input[MAXLINE];

    switch (option) {
        case 1:
            // Add record functionality
            printf("Adding a new record...\n");

            // Prompt user for record details
            printf("Enter First Name: ");
            if (fgets(input, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (rio_writen(clientfd, input, strlen(input) + 1) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }

            // clear the buffer 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            // Prompt user for last name
            printf("Enter Last Name: ");
            if (fgets(input, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (rio_writen(clientfd, input, strlen(input) + 1) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }

            // Receive response from server
            if (Rio_readlineb(clientfd, buf, MAXLINE) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }
            printf("Message From Server: %s", buf);
            break;

        case 2:
            // Search by Name functionality
            printf("Enter First Name: ");
            if (fgets(input, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (rio_writen(clientfd, input, strlen(input) + 1) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }

             // clear the buffer 
            while ((c = getchar()) != '\n' && c != EOF);


            // Prompt user for last name
            printf("Enter Last Name: ");
            if (fgets(input, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (rio_writen(clientfd, input, strlen(input) + 1) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }

            // Receive response from server
            if (Rio_readlineb(clientfd, buf, MAXLINE) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }
            printf("Message From Server: %s", buf);
            break;

        case 3:
            // Search by Zip Code functionality
            printf("Enter Zip Code: ");
            if (fgets(input, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (rio_writen(clientfd, input, strlen(input) + 1) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }

            // Receive response from server
            if (Rio_readlineb(clientfd, buf, MAXLINE) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }
            printf("Message From Server: %s", buf);
            break;

        case 4:
            // Search by Salary functionality
            printf("Enter Salary: ");
            if (fgets(input, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (rio_writen(clientfd, input, strlen(input) + 1) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }

            // Receive response from server
            if (Rio_readlineb(clientfd, buf, MAXLINE) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }
            printf("Message From Server: %s", buf);
            break;

        case 5:
            // Terminate
            printf("Terminating connection.\n");
            if (rio_writen(clientfd, &option, sizeof(int)) <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }
            break;

        default:
            printf("Invalid option!\n");
            break;
    }
}
