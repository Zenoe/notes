#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Connection {
    public:
        // Connection() : _name(){}
        Connection(string in_str) : _name(in_str){}
        virtual ~Connection(){
            cout << "close " << getName() <<endl;
        }

        string getName() const{
            return _name;
        }
    private:
        string _name;
};


using namespace std;

int main(int argc, char *argv[]) {

    auto Deleter=[](Connection *connection){
        delete[] connection;
    };
    Connection* c1 = new Connection[2]{string("s1"), string("s2")};
    // c1[0] = new Connection("s1");
    // c1[1] = new Connection("s2");
    shared_ptr<Connection> sp(c1, Deleter);

    Connection* c2 = new Connection[2]{string("s3"), string("s4")};
    unique_ptr<Connection[]> up(c2);
    return 0;
}
