#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void print_signal_mask() {
    sigset_t current_mask;
    sigprocmask(SIG_SETMASK, NULL, &current_mask);
    for (int i = 1; i <= NSIG; ++i) {
        if (sigismember(&current_mask, i)) { 
            printf("Signal %d: Blocked\n", i);
        } else {
            printf("Signal %d: Unblocked\n", i);
        }
    }
}

int main() {
    print_signal_mask();
    return 0;
}