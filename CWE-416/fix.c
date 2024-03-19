#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
printf("Wellcome to fixed auth\n");

    time_t start_time;
    time(&start_time);

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
                    printf("[root]: Forbiden!\n");
                    strcpy(username, "");
                }

                break;

            case 2:
                // Save password
                if (!username){
                    printf("Set a username first\n");
                    break;
                }

                password = malloc(20*sizeof(char));
                printf("Enter password: ");
                scanf("%254s", password);
                break;

            case 3:
                if (!password && !username){
                    printf("smth don't exist!\n");
                    break;
                }

                free(password);
                free(username);

                // Ensure no dangling pointers exist
                password = NULL;
                username = NULL;
                break;

            case 4:
                if (!password || !username){
                    printf("Needed log in without both credentials [username & password]\n");
                    break;
                }

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
                    printf("Logged as root!\n");
                    printf("---SOME PRIVILEGED SHIT GOING ON HERE---\n");

                    char * command = (char*)malloc(20*sizeof(char));
                    printf("root$: ");
                    scanf("%254s", command);
                    system(command);

                    free(command);
                    command = NULL;

                    exit(0);
                }

                if(!strcmp(temp_uname, username) && !strcmp(temp_pwd, password)){
                    // printf("%s -- %s -- %s -- %s\n", temp_uname, username, temp_pwd, password);
                    printf("Logged in successfully!\n");
                }
                else{
                    printf("Incorrect username or password!\n");
                }

                free(temp_pwd);
                free(temp_uname);

                temp_uname = NULL;
                temp_pwd = NULL;

                break;

            case 5:
                exit(0);
            default:
                printf("Invalid Option!\n");
                break;
        }
    }
}