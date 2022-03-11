# Pandemic Simulator Project
## Spreading V
### Description:
In this project a laboratory experiment will be simulated as a life game. There is a habitat that contains randomly distributed entities. In this experiment our habitat will be a NxN square place.

Each entity has 5 different gates which can be named from {A, B, C, D, E, F, G, H} set.
The Spreading V can infect an entity if the entity has A or B gate. If the entity has 3 gates which are named as A, B, C, D than this entity will die after 14 turns otherwise it will recover and get immune to Spreading V after 30 turns. Dead entities stay in habitat for five turns and be infectious. They cannot move.
Spreading V can infect from one entity to other if they are closer than 3 units (in square form). An entity becomes infectious after 3 turns.
The simulation will take the start information from input.txt file which will be on the same file with the executable. This file includes information about habitat constants, entities and their movements  in turns.

The simulation will write an output.txt file which will show the infected and died entities and last situation of the habitat. Also, after each turn the program will fill another file “turns.txt”. This file shows a brief outcome for each turn.

Examples are in the examples.txt file.
