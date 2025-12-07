# Debugging C++ in Docker with VS Code

## Prerequisites
- VS Code with C/C++ extension installed
- Docker running

## Method 1: Attach to Running Container (Simpler)

### Step 1: Build debug image
```bash
docker build -f Dockerfile.debug -t terminal-roguelike:debug .
```

### Step 2: Run container with name
```bash
docker run -it --name roguelike-debug terminal-roguelike:debug
```

### Step 3: In another terminal, start the app
```bash
docker exec -it roguelike-debug /usr/local/bin/roguelike
```

### Step 4: In VS Code
1. Set breakpoints in your C++ source files
2. Open Run and Debug panel (Ctrl+Shift+D)
3. Select "Docker: Attach to C++ Container"
4. Pick the roguelike process from the list
5. Debug as normal!

### Cleanup
```bash
docker stop roguelike-debug
docker rm roguelike-debug
```

## Method 2: Remote Debugging with gdbserver (Advanced)

### Step 1: Install gdbserver in container
Add to Dockerfile.debug:
```dockerfile
RUN apk add --no-cache gdb gdbserver
```

### Step 2: Start container with port forwarding
```bash
docker run -it --name roguelike-debug -p 2345:2345 terminal-roguelike:debug
```

### Step 3: Inside container, run with gdbserver
```bash
gdbserver :2345 /usr/local/bin/roguelike
```

### Step 4: In VS Code
1. Set breakpoints
2. Select "Docker: Launch with gdbserver" configuration
3. Press F5 to start debugging

## Tips

**View container processes:**
```bash
docker exec roguelike-debug ps aux
```

**Copy files from container:**
```bash
docker cp roguelike-debug:/usr/local/bin/roguelike ./roguelike-binary
```

**Interactive debugging with gdb directly:**
```bash
docker exec -it roguelike-debug gdb /usr/local/bin/roguelike
```

## Limitations

- The game uses terminal input (_getch/termios), which can be tricky with debuggers
- Breakpoints will pause the game, potentially causing input issues
- Consider adding logging as an alternative debugging method
