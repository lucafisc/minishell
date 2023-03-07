<h1 align="center">minitalk</h1>

<p align="center">
<img src="https://i.imgur.com/KIzJ2vu.png" alt="drawing" width="120"/>
</p>

[![lde-ross's 42 minitalk Score](https://badge42.vercel.app/api/v2/clcrkbbp700300fkxp8nykj3n/project/2951327)](https://github.com/JaeSeoKim/badge42)

minitalk is a program that allows inter-process communication between a client and a server. The client sends messages to the server one bit at a time. The server should then receive and reconstruct the original message. It utilizes the use of signals to transfer the data.

The program has the bonus functionality of confirming the message received by the server and supporting unicode characters.

External functions: [`write`](https://man7.org/linux/man-pages/man2/write.2.html)  [`sigemptyset`](https://man7.org/linux/man-pages/man3/sigemptyset.3.html) [`sigaction`](https://man7.org/linux/man-pages/man2/sigaction.2.html) [`kill`](https://man7.org/linux/man-pages/man2/kill.2.html) [`getpid`](https://man7.org/linux/man-pages/man2/getpid.2.html) [`malloc`](https://man7.org/linux/man-pages/man3/malloc.3.html) [`free`](https://man7.org/linux/man-pages/man1/free.1.html) [`pause`](https://man7.org/linux/man-pages/man2/pause.2.html) [`usleep`](https://man7.org/linux/man-pages/man3/usleep.3.html) [`exit`](https://man7.org/linux/man-pages/man3/exit.3.html)

| ![Visualizer](https://i.imgur.com/8geLWwI.gif) | 
|:--:| 

## How to use

Clone the minitalk repository to your local machine:

```
git clone https://github.com/<username>/minitalk.git
```

Navigate to the minitalk directory:

```
cd minitalk
```

Compile the code to generate the executables (server and client):

```
make
```

Start the server by running the following command in your terminal:

```
./server
```

The server will display its PID (process ID) in the terminal. Take note of this PID as you will need it later.

Start the client by running the following command in a separate terminal window:

```
./client <SERVER PID> "Your message here ♥"
```

The server will display the message sent by the client. The client will receive a confirmation that the message has been successfully sent to the server.
