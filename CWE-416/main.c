#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("Wellcome to VERY STRONG AND SECURY auth\n");

    char * username = 0;
    char * password = 0;

    int flag = 0;

    while(1)
    {
        // Print username and password (with address) to keep a track of the variables
        if(username){
            // printf("USERNAME ADDRESS: %x\nUSERNAME: %s\n", username, username);
            printf("USERNAME: %s\n", username);
        }
        if(password){
            // printf("PASSWORD ADDRESS: %x\nPASSWORD: %s\n", password, password);
            printf("PASSWORD: %s\n", password);
        }

        printf("1: Username\n");
        printf("2: Password\n");
        printf("3: Reset\n");
        printf("4: Login\n");
        printf("5: Exit\n");
        printf("Choose an option [1-5]: ");

        int choice = 0;
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                // Save username
                username = malloc(20*sizeof(char));
                printf("Enter username: ");
                scanf("%254s", username);

                // "root" username not allowed -> set username to ""
                if(!strcmp(username, "root"))
                {
                    printf("[root]: Forbidden\n");
                    strcpy(username, "");
                    // Possible Heap overflow?
                    // strcpy(username, argv[0])
                }

                break;

            case 2:
                // Save password
                if (!username){
                    printf("Pleas, set a username first\n");
                    break;
                }

                password = malloc(20*sizeof(char));
                printf("Enter password: ");
                scanf("%254s", password);
                printf("Password setted!\n");

                break;

            case 3:
                // Free username and password (order matters)
                if (!password && !username){
                    printf("[root]: Forbidden\n");
                    break;
                }

                free(password);
                free(username);
                //NULL Pointers?

                break;

            case 4:
                // Login/Exploit
                if (!password || !username){
                    printf("[username & password] First set both credentials!\n");
                    break;
                }

                // If case 4 follows case 3, temp_uname and temp_pwd get assigned the freed memory chunks
                // So if I enter "root" as temp username, it writes to username because the username pointer is still pointing to that memory chunk too
                // And the same goes for password
                char * temp_uname = (char*)malloc(20*sizeof(char));
                char * temp_pwd = (char*)malloc(20*sizeof(char));

                printf("Enter username: ");
                scanf("%254s", temp_uname);

                printf("Enter password: ");
                scanf("%254s", temp_pwd);

                // root does not need to authenticate
                if(!strcmp(username, "root"))
                {
                    flag = 1;
                    printf("[root] You are now logged in as root!\n");
                    printf("---SOME PRIVILEGED GOING ON HERE---\n");

                    //command injection
                    char * command = (char*)malloc(20*sizeof(char));
                    printf("root$: ");
                    scanf("%254s", command);

                    // system("/usr/bin/bash");
                    // system("/usr/bin/ls");
                    system(command);

                    free(command);

                    exit(0);
                }

                if(!strcmp(temp_uname, username) && !strcmp(temp_pwd, password)){
                    // printf("%s -- %s -- %s -- %s\n", temp_uname, username, temp_pwd, password);
                    // BUG -> If case 3 is followed by case 4, it is possible to log in with any username and password
                    printf("Logged in successfully!\n");
                }
                else{
                    printf("Incorrect username or password! Try again\n");
                }

                free(temp_pwd);
                free(temp_uname);

                break;

            case 5:
                exit(0);
            default:
                printf("Invalid Option!\n");
                break;
        }
    }
}