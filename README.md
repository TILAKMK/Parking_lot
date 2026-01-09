🚗 Parking Lot Management System (Stack – C)

A stack-based parking lot management system implemented in C that efficiently manages vehicles in a single-lane parking environment using the Last-In-First-Out (LIFO) principle.

The system models real-world parking scenarios where vehicles are parked sequentially and retrieved with minimal movement. It also supports middle vehicle retrieval using a temporary stack, preserving the correct order of remaining vehicles.

✨ Features

LIFO-based parking and retrieval

Temporary stack support for middle vehicle removal

Real-time parking status display

Overflow and underflow protection

Menu-driven console interface

Retro styled colored terminal UI

🛠️ Tech Stack

C Programming

Stack Data Structure

ANSI Escape Codes

▶️ Run
gcc park.c -o park
./park

📌 Use Cases

Valet parking systems

Compact single-lane parking areas

Automated parking simulations

Learning data structures through real-world models

⚙️ How It Works

New vehicles are pushed into the stack.

Last parked vehicles can be popped instantly.

For middle vehicles, a temporary stack is used to safely retrieve the target while maintaining order.

🚀 Future Enhancements

Multi-lane parking support

Persistent file storage

Parking fee calculation

GUI / Web version