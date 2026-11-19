# GateCheck
GateCheck is an application with a C++ backend, built around an interval tree, and a React + TypeScript frontend. It automatically assigns each arriving flight to an open gate at a simulated airport.

# Why I built this
Sitting at the tarmac at the O'hare airport I thought to myself, there has to be a better way. I decided to make a project that would automatically assign flights as they come in and out of the airport. Essentially, flights have an interval of time in which they arrive and depart, and we check each gate to ensure that there is no conflict before assigning it to that particular gate. The MVP of this project will just take in new flights and will not include delays or cancelations. I look forward to building that out more once I get the MVP done. 

# What it does
- Loads a day's flight schedule for a gate from a json file (This will eventually load in an external API)
- Stores each flights gate, flight number, arrival and departure in an interval tree
- finds every flight that conflicts with a given time window
- serves the data over a small HTTP API to a React typescript frontend which displays the simulation.

# How it works

## The interval tree
- Each flight is an interval [arrive, depart), stored within a binary search tree.
- key:The intervals start time (low), so the tree is ordered on arrival.
- Augmented value: Each node also stores a max, the latest end time anywhere in its subtree.

- Max is what makes searching fast. Wjen looking for conflics within a window, the search skips:
  1. Any subtree whose max is at or before the query start. Every flight in it has already left
  2. Everything to the right of a node that starts at or after the query end. Those flights all arrive too late.

## Half open Intervals
- Intervals are have open [low, high). This means that a flight departing at 9:15 does not conflict with on arriving at 9:15.
- Two intervals overlap when:
- a.low < b.high && b.low < a.high

## Times 
- Times are stored as minutes since midnight (8:30 --> 510), which keeps the tree working with plain integers.

## Tech Stack
Backend 
- C++, Cmake, cpp-httplib, nlohmann/json

Frontend:
- React, Typescript, VITE





