#include <iostream>
using namespace std;
#include <string>
#ifndef _WIN32
#include <libproc.h>
#include <unistd.h>

bool cdRepo() {
    int pathLen;
    char pathBuffer[PROC_PIDPATHINFO_MAXSIZE]; // hate old-school null-terminated strings

    pathLen = proc_pidpath (getpid(), pathBuffer, sizeof pathBuffer);
    if (pathLen <= 0) {
        return false;
    }
    int slashesFound = 0;
    while (--pathLen > 0 ) {
        if (pathBuffer[pathLen] != '/') continue;
        if (++slashesFound < 2) continue;
        pathBuffer [pathLen] = '\0'; // hate null-terminated
        return (chdir (pathBuffer) == 0);
    }

    cout << "Failed to change directory\n";
    return false;

}

int test_cdRepo () {
    cout << "Starting in "; cout.flush();
    system ("pwd");
    
    cdRepo();
    cout << "Ending in "; cout.flush();
    system ("pwd");
    return 0;
}

#else
    bool cdRepo() {
        return true;
    }

    void test_cdRepo() {
        cout << "cdRepo is not needed on Windows, no operation performed" << endl;
    }
#endif



