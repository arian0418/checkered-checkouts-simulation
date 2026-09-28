# Checkered Checkouts Simulation

A C++ checkout line simulation that implements a queue using a manually managed singly linked list.

## Features

- Custom queue built with a linked list
- Enqueue customers at the back and dequeue from the front
- Randomized customer arrivals and checkout events
- Configurable simulation length from 1 to 2,000 cycles
- Tracks customers waiting and customers served
- Calculates total items and item value in the queue
- Handles operations on an empty queue safely
- Frees dynamically allocated memory

## How It Works

Each simulation cycle randomly selects an event. A customer has a two in three chance of entering the checkout line and a one in three chance of a checkout event occurring.

New customers receive an automatically generated ID, a randomized number of items, and a randomized total item value.

## Data Structure

The checkout line is a FIFO queue backed by a singly linked list:

```
HEAD -> Customer -> Customer -> Customer -> nullptr
                                      ^
                                     TAIL
```

Enqueue operations append to the tail, while dequeue operations remove from the head.

## Build

```bash
g++ -std=c++17 src/main.cpp -o checkered-checkouts
```

Run with `./checkered-checkouts` on macOS/Linux or `checkered-checkouts.exe` on Windows.

## Concepts Demonstrated

Linked lists, queue/FIFO behavior, dynamic memory allocation, pointers, classes and encapsulation, random number generation, simulation logic, resource cleanup, and input validation.

## Improvements from the Original Coursework Version

The project uses a dedicated `CheckoutQueue` class to encapsulate queue operations, modern C++ utilities for random numbers instead of `rand()`, safer input handling, and automatic cleanup of dynamically allocated nodes.
