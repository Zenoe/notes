https://code.visualstudio.com/docs/nodejs/nodejs-debugging
https://emacs-lsp.github.io/dap-mode/page/features/#windows

## ws://127.0.0.1:25069/fb402995-7f50-46c6-8598-4f0e92d93aa7
The message "Debugger listening on ws://127.0.0.1:25069/fb402995-7f50-46c6-8598-4f0e92d93aa7" is typically output by a Node.js application when it is started in debug mode. Let's break down the different parts of this message:

1. **Debugger listening on**: This indicates that the Node.js debugger is actively listening for a debugging client to connect.

2. **ws://127.0.0.1:25069**: This specifies the WebSocket (ws) address and port where the debugger is listening for incoming connections. In this case, it's listening on the loopback address (127.0.0.1) on port 25069.

3. **fb402995-7f50-46c6-8598-4f0e92d93aa7**: This is a unique identifier for the debugging session. It is used to identify and match the debugger with the corresponding debugging client that connects to it.

When you see this message, it means that the Node.js application is ready to be debugged, and you can use a compatible debugger client (such as Chrome DevTools or Visual Studio Code) to connect to the specified WebSocket address and port in order to start debugging the Node.js application.

If you have further questions or need additional details, feel free to ask!

## debug server
A debug server, in the context of software development, is a program or service that facilitates the debugging of another program or application. It acts as a communication bridge between the debugger client (such as a debugger interface in an integrated development environment or a web browser) and the target program being debugged.

Here are some key points about debug servers:

1. **Facilitates Communication**: The debug server enables communication between the debugger client and the target program. It listens for incoming debugger connections and relays debugging commands and information between the client and the target.

2. **Debugging Protocol**: Debug servers typically implement a debugging protocol that defines the messages and commands exchanged between the debugger client and the target program. This protocol allows the debugger client to control the execution of the target program, set breakpoints, inspect variables, and perform other debugging tasks.

3. **Support for Multiple Languages and Runtimes**: Debug servers are often designed to work with specific programming languages and runtime environments. For example, there are debug servers tailored for Node.js, Python, Java, and other languages, each understanding the intricacies of debugging within their respective environments.

4. **Remote Debugging**: Some debug servers support remote debugging, allowing the debugger client to connect to a target program running on a different machine or in a different environment. This can be useful for debugging applications deployed on remote servers or embedded devices.

5. **Customization and Extensibility**: Debug servers can often be extended and customized to support additional features or integrate with specific development tools. This flexibility allows developers to tailor the debugging experience to their specific needs.

In the context of Node.js, the "Debugger listening on" message indicates that the Node.js application is running in debug mode and is ready to be connected to by a debugger client, typically through a debug server built into the Node.js runtime.

6. **Debug Adapter Protocol (DAP): DAP is a protocol that defines the communication between a debugger client (such as Visual Studio Code) and a debug adapter. The debug adapter is responsible for controlling the execution of the target program, providing information about its state, and handling debugging-related commands.

7. **Debug Server as a Debug Adapter: In the context of Node.js, the debug server acts as a debug adapter by implementing the DAP. It understands the DAP messages and commands and translates them into actions that control the execution of the Node.js application being debugged.

VS Code has the built-in Node.js debugger
