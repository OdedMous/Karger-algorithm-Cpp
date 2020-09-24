#include <iostream>
#include <vector>
#include <random>
#include <limits.h>


class Vertex {

    public:

        std::vector<int> data;

        Vertex() = default;

        Vertex(const std::vector<int> &input) {
            data = input;
        }


        // Combines two vertices
        Vertex operator+(const Vertex& vec2) {
            std::vector<int> new_vec(this->data);
            new_vec.insert(new_vec.end(), vec2.data.begin(), vec2.data.end());
            return Vertex(new_vec);
        }

        // Overloading == operator
        bool operator==(const Vertex& other) {
            return (this->data == other.data);
        }

        // Overloading << operator
        friend std::ostream& operator<<(std::ostream& os, const Vertex& input) {
            for (auto const& i : input.data) {
                os << i << " ";
            }
            return os;
        }
};


class Arc {

    public:

        Vertex v1;
        Vertex v2;

        Arc() = default;

        Arc(const Vertex& input1, const Vertex& input2) {
            v1 = input1;
            v2 = input2;
        }

        // Overloading << operator
        friend std::ostream& operator<<(std::ostream& os, const Arc& arc) {
            os << "(" << arc.v1 << ", " << arc.v2 << ")";
            return os;
        }

        // Overloading == operator
        bool operator==(const Arc& arc) {
            return (this->v1 == arc.v1 and this->v2 == arc.v2);
        }
};

/**
* Generate a random integer from the range [0, max_val]
*/
const int random_int(const int max_val) {

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, max_val); // define the range
    return distr(gen);
}


/**
* Perform the edge contraction operation: given the selected edge (u,v), remove it and it's identical edges,
* merges the nodes u and v to a single node uv, and  "reattached" to the merged node all edges
* which contains either u or v .
*/
void contraction(Arc &selected_arc, std::vector<Arc> &arcs) {

    Vertex new_vertex = selected_arc.v1 + selected_arc.v2;
    std::vector<Arc> new_arcs;
    for (std::vector<Arc>::iterator it= arcs.begin(); it != arcs.end(); it++) {

        // remove arc which is the same as the selected arc
        if (*it == selected_arc) {
            arcs.erase(it);
            it--;
            continue;
        }


        if (it->v1 == selected_arc.v1 or it->v1==selected_arc.v2) {
            new_arcs.insert(new_arcs.end(), Arc(new_vertex, it->v2));
            arcs.erase(it);
            it--;
            continue;
        }


        if (it->v2==selected_arc.v1 or it->v2==selected_arc.v2) {
            new_arcs.insert(new_arcs.end(), Arc(new_vertex, it->v1));
            arcs.erase(it);
            it--;
            continue;

        }
    }
    arcs.insert(arcs.begin(),new_arcs.begin(),new_arcs.end());
}


/**
* Implement one iteration of Karger's algorithm.
*/

auto karger_alg_loop(std::vector<Arc> arcs, int num_vertex)
{
    int rand_int;

    while (num_vertex > 2) {
        rand_int = random_int(arcs.size() - 1);
        Arc selected_arc = arcs[rand_int];
        contraction(selected_arc, arcs);
        num_vertex--;
    }
    Arc final = arcs[0]; // all arcs are identical now, so we pick one of them in order to get the two groups of vertices
    struct result{Arc arc; unsigned long cut_size;};

    return result{final, arcs.size()};
}


/**
* Implementation of Karger's algorithm for finding a minimum cut with high probability.
 * @param arcs - list of the graph arcs
 * @param num_vertex - number of vertices in the graph
 * @param iterations - number of iterations
 * @return a struct which contains: cut_size - the size of the resulting cut
 *                                  group1, group2 - the two groups of vertices which defines the cut.
*/
auto karger_alg(std::vector<Arc> arcs, int num_vertex, int iterations)
{
    unsigned long temp_cut_size = ULONG_MAX;
    Arc temp_arc;

    for (int i=0; i < iterations; i++) {
        auto  [arc, cut_size] = karger_alg_loop(arcs, num_vertex);

        if (cut_size < temp_cut_size) { // check if we did find smaller cut
            temp_cut_size = cut_size;
            temp_arc = arc;
             if (arcs.size() == 1) {
                 break;
             }
        }

    }
    struct result{Vertex group1, group2; unsigned long cut_size;};

    return result{temp_arc.v1, temp_arc.v2, temp_cut_size};
}


int main() {

    //     1-----3
    //     |    /
    //     |  /
    //     |/
    //     0-----2


    Arc arc1(std::vector<int> {1}, std::vector<int> {3});
    Arc arc2(std::vector<int> {1}, std::vector<int> {0});
    Arc arc3(std::vector<int> {3}, std::vector<int> {0});
    Arc arc4(std::vector<int> {0}, std::vector<int> {2});
    std::vector<Arc> arcs_list {arc1, arc2, arc3, arc4};
    int num_vertex = 4;

    auto [group1, group2, mincut_size] = karger_alg(arcs_list, num_vertex, 3);
    std::cout << "**Results**\nCut size:" << mincut_size << "\nGroup1: " << group1 << "\nGroup2: " << group2;


    return 0;
}






