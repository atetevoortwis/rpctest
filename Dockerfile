from ubuntu:latest
RUN apt update && apt install -y cmake
RUN apt install -y build-essential autoconf libtool pkg-config
RUN apt install -y git
RUN git clone --recurse-submodules -b v1.48.1 --depth 1 --shallow-submodules https://github.com/grpc/grpc
WORKDIR /grpc
RUN mkdir -p cmake/build/
WORKDIR /grpc/cmake/build/
RUN mkdir -p ~/.local
RUN pwd
RUN cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=~/.local ../../
RUN make
RUN make install
CMD bash