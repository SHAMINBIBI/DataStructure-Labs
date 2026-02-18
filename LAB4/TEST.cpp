#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdlib>
using namespace std;
typedef unsigned long long ull;
ull compute(ull start, ull end) {
    ull sum = 0;
    for (ull i = start; i <= end; i++) {
        sum += i * i;
    }
    return sum;
}
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " N W" << endl;
        return 1;
    }    
    ull N = atoll(argv[1]);
    int W = atoi(argv[2]);
    ull chunk = N / W;    
    vector<int> read_fds(W);
    vector<pid_t> pids(W);    
    // Fork all children first (parallel execution)
    for (int k = 0; k < W; k++) {
        int fd[2];
        pipe(fd);
        
        ull start = k * chunk + 1;
        ull end = (k == W - 1) ? N : (k + 1) * chunk;
        
        pid_t pid = fork();
        
        if (pid == 0) {
            // Child process
            close(fd[0]);
            ull part = compute(start, end);
            write(fd[1], &part, sizeof(part));
            close(fd[1]);
            _exit(0);
        } else {
            // Parent process
            close(fd[1]);
            read_fds[k] = fd[0];
            pids[k] = pid;
        }
    }    
    // Collect results from all children
    ull total = 0;
    for (int k = 0; k < W; k++) {
        ull part;
        read(read_fds[k], &part, sizeof(part));
        total += part;
        close(read_fds[k]);
    }    
    // Wait for all children to finish
    while (wait(NULL) > 0);    
    cout << "Sum = " << total << endl;
    return 0;
}