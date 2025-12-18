# Linux System Programming – 5 Day Hands-on Practice

This repository documents my **structured 5-day hands-on learning** in Linux
System Programming using the C language.  
The focus is on understanding **how user-space programs interact with the Linux kernel**
through system calls, IPC mechanisms, memory management, and networking.

---

## 📅 Learning Breakdown (Day-wise)

### 🔹 Day 01 – File Operations & Environment Variables
Focus: Core Linux system calls and process environment

Programs implemented:
- **File Copy Utility**
  - Simulates a basic `cp` command
  - Uses `open()`, `read()`, `write()`, `close()`
  - Handles file open, read, and write errors
- **File Permissions**
  - Creates files with specific permissions
  - Modifies permissions using `chmod()`
- **Environment Variables**
  - Reads environment variables using `getenv()`
  - Sets new variables using `setenv()`

Key concepts learned:
- File descriptors and file access modes
- Permission bits and access control
- Process environment handling

---

### 🔹 Day 02 – Processes, Threads & File System
Focus: Process creation, threading, and directory operations

Programs implemented:
- **Multiple Child Processes**
  - Parent creates multiple children using `fork()`
  - Each child executes a different command using `exec()`
  - Parent waits for all children using `wait()`
- **File System Operations**
  - Directory creation (`mkdir`)
  - Listing contents (`opendir`, `readdir`)
  - File deletion (`unlink`)
- **Multithreading**
  - Multiple threads increment a shared counter
  - Synchronization using mutexes to prevent race conditions

Key concepts learned:
- Process lifecycle and parent–child relationship
- Threads vs processes
- Synchronization using mutexes
- Directory traversal

---

### 🔹 Day 03 – Inter-Process Communication & Synchronization
Focus: Communication between processes and real-world utilities

Programs implemented:
- **Multi-process Number Generator and Summation**
  - One process generates numbers
  - Another process computes the sum
  - Synchronization using IPC mechanisms (semaphores/shared memory)
- **Directory Synchronization Utility**
  - Compares source and destination directories
  - Ensures destination mirrors the source
  - Updates missing or modified files

Key concepts learned:
- IPC mechanisms
- Process synchronization
- Data consistency across processes
- Designing utility-style programs

---

### 🔹 Day 04 – Memory Management & Process Scheduling
Focus: Advanced OS concepts

Programs implemented:
- **Memory Mapping**
  - Maps a file into memory using `mmap()`
  - Modifies contents and writes changes back
  - Unmaps memory using `munmap()`
- **Priority-based Process Handling**
  - Multiple processes executed based on priority
- **Message Sharing Between Processes**
  - Demonstrates message exchange using IPC mechanisms

Key concepts learned:
- Virtual memory and memory-mapped files
- Process scheduling concepts
- Inter-process message sharing

---

### 🔹 Day 05 – Client–Server Communication
Focus: Networking and IPC using sockets

Programs implemented:
- **Socket-based Client–Server Application**
  - Client sends a message to server
  - Server responds with the reversed message
  - Uses TCP sockets for communication

Key concepts learned:
- Socket programming
- Client–server architecture
- Network-based IPC

---


