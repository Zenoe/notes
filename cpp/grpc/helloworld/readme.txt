after following quick start from grpc offocial website
here to implement a helloworld grpc

protoc -I. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` helloworld.proto
protoc -I. --cpp_out=. helloworld.proto

mkdir build
cd build
cmake ..
make


run:
./server
./client
