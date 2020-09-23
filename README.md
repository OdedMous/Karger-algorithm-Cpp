# Karger's algorithm

|<img src="../master/images/mincut_wiki.png" width="300">|
|:--:| 
| *by wikipedia* |

## Goal </br>
Implementation of karger's algorithm which designed to find a minimum cut with high probability.

## Motivation for the problem
1) Suppose a products company wants to design two catalogs, each is desinged for a different consumer sector. The company has a list of consumers and thier purchase history. How the set of consumers can be divided into two relevant sectors? A possible solution: create a graph in which each node is a consumer, and connect two nodes with an edge if thier purchase history is similar. Now the goal will be to divide the set of nodes into two groups of nodes such that between these 2 groups there are the fewest edges, meaning the purchase history between them is the least similar as required. Note that finding such two groups is equivalent to finding a minumum cut in the graph.

