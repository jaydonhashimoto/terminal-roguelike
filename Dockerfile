# Use Alpine Linux as the lightweight base image
FROM alpine:3.19

# Install build dependencies and runtime libraries
# g++ and cmake for building, ncurses for terminal manipulation
RUN apk add --no-cache \
    g++ \
    cmake \
    make \
    ncurses-dev \
    ncurses-libs

# Set working directory
WORKDIR /app

# Copy source files and CMakeLists.txt
COPY CMakeLists.txt ./
COPY src/ ./src/

# Create build directory and compile the project
RUN mkdir build && \
    cd build && \
    cmake -G "Unix Makefiles" .. && \
    cmake --build . && \
    mv roguelike /usr/local/bin/roguelike

# Clean up build artifacts to keep image small
RUN rm -rf /app/build /app/src /app/CMakeLists.txt

# Remove build dependencies, but keep runtime libraries
# libstdc++ and libgcc are needed to run the compiled C++ program
RUN apk del cmake make ncurses-dev

# Set the working directory back to root
WORKDIR /

# Run the game when container starts
CMD ["roguelike"]
