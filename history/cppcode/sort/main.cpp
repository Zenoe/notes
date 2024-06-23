#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {

    int index;
    char ch;
    while((ch = getopt(argc, argv, "ds:")) != EOF)
    {
        switch(ch)
        {
            case 'd':
                cout << "you have input d"<<endl;
                break;
            case 's':
                cout << "size: " << optarg <<endl;
                break;
            default:
                return 1;
        }
    }

    argc -= optind;
    argv += optind;

    return 0;
}
