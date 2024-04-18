#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to process user-selected option
void process_option(int option, int clientfd);

// Funciton to get record information from user
void get_record_info(char* s);

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


void concat(char dest[], const char src[]) {
	int i,j;
	for (i = 0; i < dest[i] != '\0'; i++);

	dest[i++] = ',';

	for (j = 0; src[j] != '\0'; j++) {
		dest[i + j] = src[j];
	}

	dest[i+j] = '\0';
}

void get_record_info(char* s) {
            int c;
            // Add record functionality
            printf("Adding a new record...\n");
            // clear the buffer 
            while ((c = getchar()) != '\n' && c != EOF);
	    char fname[100];
	    char lname[100];
	    char zip[100];
	    char dept[100];
	    char salary[100];

            // Prompt user for record details
            printf("Enter First Name: \n");
            if (fgets(fname, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }

            printf("Enter Last Name: \n");
            if (fgets(lname, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }

            printf("Enter Zip: \n");
            if (fgets(zip, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }

            printf("Enter Salary: \n");
            if (fgets(salary, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }

            printf("Enter Dept: \n");
            if (fgets(dept, MAXLINE, stdin) == NULL) {
                fprintf(stderr, "Error reading input\n");
                exit(EXIT_FAILURE);
            }


            fname[strcspn(fname, "\n")] = '\0'; // Remove newline character
            lname[strcspn(lname, "\n")] = '\0'; // Remove newline character
            zip[strcspn(zip, "\n")] = '\0'; // Remove newline character
            salary[strcspn(salary, "\n")] = '\0'; // Remove newline character
            dept[strcspn(dept, "\n")] = '\0'; // Remove newline character

	    printf("fname: %s\n", fname);
	    printf("lname: %s\n", lname);
	    printf("zip: %s\n", zip);
	    printf("salary: %s\n", salary);
	    printf("dept: %s\n", dept);

	    concat(fname, lname);
	    concat(fname, zip);
	    concat(fname, salary);
	    concat(fname, dept);
	    printf("%s\n",fname);

	    s = fname;
}

// Function to process user-selected option
void process_option(int option, int clientfd) {
    char buf[MAXLINE] = {0};
    char input[MAXLINE] = {0};
    char record[100] = {0};

    switch (option) {
        case 1:
            get_record_info(record);

            // send to server
            int res = rio_writen(clientfd, record, strlen(record) + 1);
            printf("res: %d\n", res);
            if ( res <= 0) {
                printf("Connection closed by server.\n");
                exit(EXIT_FAILURE);
            }
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
