#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>

using namespace std;
// Store PID of currently running child processes
//Used so  Ctrl only kills the running command, not the shell 
pid_t childPid = -1;

// Handle Ctrl+C
void handle_sigint(int sig) {
    if (childPid > 0) {
        kill(childPid, SIGINT); // kill only child
    } else {
        cout << "\nmysh> ";
        cout.flush();
    }
}

// Split input into tokens

vector<string> parseInput(const string &input) {
    stringstream ss(input);
    string token;
    vector<string> args;

    while (ss >> token) {
        args.push_back(token);
    }
    return args;
}

// Convert vector<string> to char format required by execuvp 
char** buildArgs(vector<string> &args) {
    char** argv = new char*[args.size() + 1];

    for (size_t i = 0; i < args.size(); i++) {
        argv[i] = new char[args[i].size() + 1];
        strcpy(argv[i], args[i].c_str());
    }
// execvp requires Null at  end of arguement for argv 
    argv[args.size()] = nullptr;
    return argv;
}

// Free memory
void freeArgs(char** argv, int size) {
    for (int i = 0; i < size; i++) {
        delete[] argv[i];
    }
    delete[] argv;
}

int main() {
    string input;
// Register ctr +C handler 
    signal(SIGINT, handle_sigint);
// main shell loop  
    while (true) {
        cout << "mysh> ";
        getline(cin, input);
// ignores the empty input 
        if (input.empty()) continue;
// parse input inot command + arguement 
        vector<string> args = parseInput(input);
        string cmd = args[0];

        // Built- in command: exit 
        if (cmd == "exit") {
            break;
        }

        //Built-in command: CD
        //Changes the directory of the shell process 
        if (cmd == "cd") {
            if (args.size() < 2 || chdir(args[1].c_str()) != 0) {
                perror("mysh: cd failed");
            }
            continue;
        }

        //built-in command: PWD
        // prints the current directory that you are in 
        if (cmd == "pwd") {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != nullptr) {
                cout << cwd << endl;
            }
            continue;
        }

        // Fork + exec
        childPid = fork();

        if (childPid == 0) {
            // child
            char** argv = buildArgs(args);
            execvp(argv[0], argv);

            // if exec fails
            cerr << "mysh: " << cmd << ": command not found\n";
            exit(1);
        }
        else if (childPid > 0) {
            // parent waits
            waitpid(childPid, nullptr, 0);
            childPid = -1;
        }
        else {
            // fork failed 
            perror("fork failed");
        }
    }

    return 0;
}
