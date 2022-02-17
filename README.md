# Data-Structures-and-Algorithms

## Context
Four of us are developing a startup where we have a use case to capture the user data
we obtain from our platform and use it for various activities. Two of the main activities
where we are planning to use this data to start with is for targeted marketing and
mapping, searching, filtering various users by demographics for a data driven
approach to our decision making. This brings us to the two problems we are trying to
solve.

## Problem Statement
- What is an efficient way to store all this data and query it without a bad time
complexity?
- What is the best way to strategize marketing using our data?

## Our Idea
- We are planning to solve the first problem using a HashMap linked to an AVL tree. For instance, a bucket for the HashMap can be an age group such as 20 to
25. This bucket is composed of an AVL tree of user IDs of all individuals in the age group of 20 - 25. Now, if we are interested in finding more information about a specific user, we can go to the user ID on the node and that node points to an array with all the information of the user. The Hashmap enables us to have a quick way to access the user data. The AVL tree which is a self balancing binary search tree enables us to organize our data in an ordered manner since the
heights of the two subtrees will always differ by at most one. This in theory gives us confidence that it would enable us to efficiently traverse the dataset and provide answers to our queries. The functions we have thought of as of now are search, delete, print and sort.

- To strategize marketing, we are planning to go through our user data to find the centrality in various ways to enable targeting of the user who sits in the center of this user database. In addition, we are planning to look at different centrality algorithms to compare which central user that gives us the most cost efficient marketing tactic. We plan to solve this problem by making a graph data structure using an adjacency list. We decided to use an adjacency list to implement the
graph data structure because we expect the graph to be sparse (graph with not a lot of edges). This will enable us to save a lot of storage space as compared to
an adjacency matrix. The functions we have thought of as of now are add a vertex and an edge, delete a vertex and an edge, print the adjacent list, find the
center and functions for centrality algorithm.

- For our user dataset, we plan to generate a randomized dataset with at least 10,000 samples that include parameters such as user ID, age, location etc.
