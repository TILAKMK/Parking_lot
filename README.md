# 🚗 Parking Lot Management System

Stack-based parking system in C using LIFO principle. Manage vehicles efficiently with O(1) parking and retrieval operations.

## Quick Start

```bash
gcc -o parking Parking_lot.c
./parking
```

## Features

- LIFO-based parking and retrieval (O(1))
- Middle vehicle removal with temporary stack
- Real-time parking status display
- Colorized terminal UI
- Overflow/underflow protection

## How It Works

**Park**: Push vehicle ID to stack  
**Retrieve**: Pop from stack (LIFO)  
**Middle Removal**: Use temporary stack to safely remove middle vehicles

## Use Cases

- Valet parking services
- Compact single-lane parking
- Data structure learning

## Tech Stack

- **Language**: C
- **Data Structure**: Stack (Array-based)
- **UI**: ANSI Terminal Colors

## Contributing

1. Fork the repo
2. Create a feature branch
3. Commit changes
4. Push and create a Pull Request

## License

MIT License - Free to use commercially and privately
