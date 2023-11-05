# Solving the Maximum Clique Problem - Different Approaches

The maximum clique problem is a [well-known problem](https://en.wikipedia.org/wiki/Clique_problem) in computer science. Being a member of the notorious NP family, it's complexity grows exponentially as the number of elements rise. Thankfully, it is possible to use concepts developed in the field of supercomputing to solve this issue. This project will look into different approaches to solve the maximum clique problem, as well as documenting the advantages and disadvantages of each strategy.

## Index
1. [Project Structure](#project-structure)
2. [About the Problem](#about-the-problem)

## Project Structure
The description of the solutions as well as an analysis of it's performance are in the `performance_report.ipynb`. The solutions implemented in C++ are in the `scripts` folder with other utility scripts:

 - `/scripts`
    - `brute_force.cpp`: Solution via brute force
    - `check_answer.py`: Python utility script to check the right answer using the `networkx` lib
    - `generate_graph.py`: Python utility script to generate a random graph using the `networkx` lib
 - `/solution_report.ipynb`: Analysis of each solution approach

## About the Problem
The maximum clique problem is a fundamental concept in graph theory and combinatorial optimization. It revolves around identifying the largest possible subset of vertices within a given graph, where every pair of vertices is connected by an edge. In other words, a maximum clique is a group of nodes that are fully interconnected, with no additional vertices that can be added to maintain this complete connectivity. Solving the maximum clique problem involves finding this largest possible clique within a given graph, and it has numerous applications in fields such as social network analysis, computer network design, and bioinformatics, where identifying tightly-knit communities or functional relationships is of paramount importance.

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/3/3d/Brute_force_Clique_algorithm.svg" alt="https://upload.wikimedia.org/wikipedia/commons/3/3d/Brute_force_Clique_algorithm.svg">
</p>