# Karger's algorithm

|<img src="../master/images/mincut_wiki.png" width="300">|
|:--:| 
| *image from wikipedia* |

## Goal </br>
Implement karger's algorithm which designed to find a minimum cut in connected graph *with high probability*.

## Example of reducing a problem to a minimum-cut problem  
Suppose a products company wants to design two catalogs, each is desinged for a different consumer sector. The company has a list of consumers and thier purchase history. How the set of consumers can be divided into two relevant sectors?  </br>
A possible solution: create a graph in which each node is a consumer, and connect two nodes with an edge if thier purchase history is similar. Now the goal will be to divide the set of nodes into two groups of nodes such that between these 2 groups there are the fewest edges, meaning the purchase history between them is the least similar as required. Note that finding such two groups is equivalent to finding a minumum cut in the graph.

## The algorithm
...
## Theory
...
## Discussion
Here is another randomized algorithm for finding a minimum cut:
 > Randomly select a cut from all possibole cuts and return it. 
 
In order to implement it we can grill for each node a number 0 or 1 that will determine which set of nodes it will belong to.
The probability of sucsess (get a specific minimum cut) for this algorithm is:
$$1/2^n$$
while we get a higher probability in one iteration of karger's algorithm:
$$2/n(n-1)$$
Why is that?
Answer: in every phase of karger's algorithm we choose an edge that won't be in the final cut that we will return. In the first phase, the probability of choosing an edge that is belong to the specific minimum cut is relatibly low (because there are a few edges which belongs to this specific minimum cut in the graph). As we progress in the algorithm
