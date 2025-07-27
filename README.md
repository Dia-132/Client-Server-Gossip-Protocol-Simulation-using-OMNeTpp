# Client-Server-Gossip-Protocol-Simulation-using-OMNeTpp
# Client-Server Gossip Protocol Simulation using OMNeT++

This project simulates a dynamic client-server architecture using OMNeT++, where clients distribute data to servers, gather responses, and use a gossip protocol to collaboratively evaluate and rank server performance. The simulation includes automated NED generation to support customizable network topologies.

## Overview

- Implements a multi-round message exchange between clients and servers.
- Clients evaluate server performance using majority voting and statistical aggregation.
- A gossip protocol allows clients to share local evaluations and converge on global rankings.
- The NED file is auto-generated using Python based on user input (number of clients and servers).

## Project Structure

- network.cc # OMNeT++ logic implementing Tic9 (client) and Toc9 (server)
- topo.ned # Example NED file (can be generated via script)
- create_topology.py #  Python script to generate dynamic NED topology
─ README.md # Project documentation


## Features

- Dynamic network topology with user-defined number of clients and servers.
- Parallel data distribution and collection from servers.
- Client-side majority voting to evaluate responses.
- Inter-client gossip protocol to share server scores and finalize top server set.
- Automatic selection of top (n/2)+1 servers based on combined scores.

## Technologies Used

- OMNeT++
- C++ (cSimpleModule)
- Python (for NED generation)
- NED topology format

## How to Run

1. (Optional) Use `ned_generator.py` to create a dynamic `topo.ned` file.
2. Place the generated or provided NED file in the simulation directory.
3. Compile the simulation using OMNeT++ (`opp_makemake` and `make` or through OMNeT++ IDE).
4. Run the simulation using OMNeT++ IDE or command-line interface (`opp_run`).

## Customization

You can configure the following parameters:

- `clients`: Number of client modules (`Tic9`)
- `servers`: Number of server modules (`Toc9`)
- `data[]`: The data array distributed across clients
- Thresholds for gossiping and voting logic (via constants in `network.cc`)

## Example Output

The simulation outputs:
- Server scores at each client
- Top-performing servers selected through gossip
- Final list of selected servers based on majority ranking

