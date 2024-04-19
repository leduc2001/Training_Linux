#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    sigset_t pend_sig;

    while(1) {
        sigpending(&pend_sig);
        if (sigismember(&pend_sig, SIGINT)){
            printf("Ctrl+C is pending\n");
            exit(0);
        }

        sleep(1);
    }
}
