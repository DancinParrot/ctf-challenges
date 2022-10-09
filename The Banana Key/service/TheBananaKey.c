#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void ignore_me_init_buffering() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void kill_on_timeout(int sig) {
    if (sig == SIGALRM) {
        printf("[!] Anti DoS Signal. Patch me out for testing.");
        _exit(0);
    }
}

void ignore_me_init_signal() {
    signal(SIGALRM, kill_on_timeout);
    alarm(60);
}

void welcome() {
    puts("\n"
         "______                                 _____           _                 \n"
         "| ___ \\                               /  ___|         | |                \n"
         "| |_/ / __ _ _ __   __ _ _ __   __ _  \\ `--. _   _ ___| |_ ___ _ __ ___  \n"
         "| ___ \\/ _` | '_ \\ / _` | '_ \\ / _` |  `--. \\ | | / __| __/ _ \\ '_ ` _ \\ \n"
         "| |_/ / (_| | | | | (_| | | | | (_| | /\\__/ / |_| \\__ \\ ||  __/ | | | | |\n"
         "\\____/ \\__,_|_| |_|\\__,_|_| |_|\\__,_| \\____/ \\__, |___/\\__\\___|_| |_| |_|\n"
         "                                              __/ |                      \n"
         "                                             |___/                       ");
    puts("Banana System v1.0");
    puts("===================");
    puts("Welcome!");
}

void banana() {
    char name[8];
    char pass[8];

    printf("Enter your name:\n");
    gets(name);
    printf("Enter your password:\n");
    gets(pass);
    if((strcmp(name, "MinionBob")) && (strcmp(pass, "Bananee@123") == 0)) {
        printf("Authorized?");
    } else {
        printf("Who are you?");
    }
}

void WINbeedo() {
  puts("Beedo?");
  system("/bin/sh");
}

int main() {
    ignore_me_init_buffering();
    ignore_me_init_signal();

    welcome();
    banana();
    return 0;
}

