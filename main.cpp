#include <iostream>
#include <cmath>
#include <vector>
#include "sort/Sort.h"
#include "nt/nt.h"
#include "Search/search.h"
#include "Graph/Graph.h"
#include "Graph/sp.h"
#include "dp/dp.h"
#include "String/string.h"
#include "tree/AdvanceTree.h"


using namespace std;


int main() {
    cout << binaryPow(12, 1, 5) << std::endl;
    cout << binaryPow2(12, 1, 5);
    float A[]={45,2,3,4,51,1.23,3.1,5.3,6.4,34,234,546,678,1};
    Sort<float> a;
////    a.mergeSort(A, 0, sizeof(A) / sizeof(float) - 1);
////    a.mergeSort2(A, 0, sizeof(A) / sizeof(float) - 1);
    a.quickSort(A, 0, sizeof(A) / sizeof(float) - 1);
    a.print(A, 0, sizeof(A) / sizeof(float));
    std::vector<int> list;
    Find_Prime(10, &list);
    std::cout << std::endl;
    FactorFactors::FindFF(2147483646);
    ExGcd extgcd;
    Combination combina;
////    std::cout << combina.CMethod2(5, 2);
    std::cout << combina.Lucas(8, 3, 5) << std::endl;
    int per[] = {1, 2, 3};
    PrintPermutation(per, sizeof(per) / sizeof(int));
    std::cout << std::endl;
    auto tree = new BinaryTree::Tree<int>;

    tree->insert(12);
    tree->insert(13);
    tree->insert(11);
    tree->insert(123);

    for (int i = 0; i < 10; ++i) {
        tree->insert(i);
    }
    tree->erase(9);
    tree->erase(11);
    tree->erase(3);
    tree->erase(11);
    std::cout << tree->find(2)->data << std::endl;

    tree->postOrder();
    tree->preOrder();
    tree->inOrder();
    tree->LayerOrder();
    std::cout << tree->FindMin() << std::endl;
    delete tree;

    auto tree2 = new AVLTree::AVLTree<int>;
    tree2->insert(23);
    tree2->insert(24);
    for (int i = 16; i >= 0; i--) {
        tree2->insert(i);
    }
    tree2->inOrder();
    tree2->erase(10);
    tree2->erase(9);
    tree2->inOrder();
    delete tree2;
    HEAP::Test();
    std::cout << std::endl << std::endl;

    auto graph = new ShortestPath::MatrixGraph<int>(6, 8, false, true);
    graph->Set(0, 1, 1);
    graph->Set(0, 3, 4);
    graph->Set(0, 4, 4);
    graph->Set(1, 3, 2);
    graph->Set(2, 5, 1);
    graph->Set(3, 2, 2);
    graph->Set(3, 4, 3);
    graph->Set(4, 5, 3);
    graph->LongestPathDP();
    std::cout << graph->LongestPathDPEndComfirm(5) << std::endl;
    graph->Dijkstra(0);
    graph->Dijkstra(0, 5);
    graph->DijkstraDFS(0, 5);
    graph->Floyd();
    std::cout << graph->Prim() << std::endl;
    std::cout << std::endl;

    delete graph;
////
    ShortestPath::LinkedlistGraph<int> graph2(6, 10, false);
    graph2.Set(0, 1, 4);
    graph2.Set(0, 4, 1);
    graph2.Set(0, 5, 2);
    graph2.Set(1, 2, 1);
    graph2.Set(1, 5, 3);
    graph2.Set(2, 3, 6);
    graph2.Set(2, 5, 5);
    graph2.Set(3, 4, 5);
    graph2.Set(3, 5, 4);
    graph2.Set(4, 5, 3);
//    graph2.Set(3, 1, -3);
//    std::cout << graph2 << std::endl;
    std::cout << graph2.TopologicalSort() << std::endl;
//    graph2.LongestPathDP();
    graph2.Dijkstra(0);
    graph2.DijkstraHeap(0);
    graph2.Bellman(0);
    graph2.SPFA(0);
    graph2.SPFASLF(0);
    graph2.SPFALLL(0);
    graph2.SPFASLFLLL(0);
    std::cout << graph2.SPFADFS(0) << std::endl;
    graph2.Bellman(0, 3);
    graph2.Dijkstra(0, 3);
    graph2.DijkstraHeap(0, 3);
    graph2.Astar(0, 3);
    graph2.LongestPath();
    std::cout << graph2.Prim() << " " << graph2.PrimHeap() << " " << graph2.Kruskal() << std::endl;
////
    std::cout << std::endl;
    ShortestPath::LinkedListStar<int> star(6, 10, true);
    star.Set(0, 1, 4);
    star.Set(0, 4, 1);
    star.Set(0, 5, 2);
    star.Set(1, 2, 1);
    star.Set(1, 5, 3);
    star.Set(2, 3, 6);
    star.Set(2, 5, 5);
    star.Set(3, 4, 5);
    star.Set(3, 5, 4);
    star.Set(4, 5, 3);
////    std::cout << star << std::endl;
    star.Dijkstra();
    star.SPFA(0);
////
    std::cout << std::endl;
    std::cout << FactialLM(50) << std::endl;
    std::cout << DP::Factorial(40) << std::endl;
    std::cout << DP::NumberTower() << std::endl;
    std::cout << DP::LongestSequenze() << std::endl;
    std::cout << DP::LIS() << std::endl;
    std::cout << DP::LCS() << std::endl;
    std::cout << DP::Backword() << std::endl;
    std::cout << DP::MANACHER() << std::endl;
    std::cout << DP::ZeroOneBagpack() << std::endl;
    std::cout << DP::FullBagpack() << std::endl;
    std::cout << std::endl;

    std::cout << String::KMP("hahahaha", "ha") << std::endl;
    std::cout << String::KMPN("hahahaha", "ha") << std::endl;
////
    std::cout << std::endl;
    std::vector<int> TestSequence={0, 1, 2, 3, 9};
    ADTree::SegmentTree<int> Stree(TestSequence.size());

    std::cout << std::endl;
    Stree.Build(TestSequence);
    Stree.Update(1, 3, 10);
    std::cout << Stree.Query(1, 2) << std::endl;
    std::cout << Stree.QueryMin(1, 3, TestSequence)<< std::endl;

    ADTree::SegmentTree2<int> Stree2(TestSequence.size());
    Stree2.Build(TestSequence);
//    Stree2.Update(1, 3);
    Stree2.Update(1, 3, 10);
    std::cout << Stree2.IQuery(1, 2) << std::endl;

    ADTree::BIT<int> bitree(TestSequence.size());
    bitree.Build(TestSequence);
    bitree.update(4, 10);
    std::cout << bitree.Sum(3) << std::endl;

    std::cout << std::endl;
    ADTree::RBTree<int> rbtree;
    rbtree.insert(7);
    rbtree.insert(3);
    rbtree.insert(18);
    rbtree.insert(10);
    rbtree.insert(22);
    rbtree.insert(8);
    rbtree.insert(11);
    rbtree.insert(26);
    rbtree.insert(2);
    rbtree.insert(6);
    rbtree.insert(13);

    rbtree.InOrder();
    rbtree.LevelOrder();

    rbtree.deleteByVal(18);
    rbtree.deleteByVal(11);
    rbtree.deleteByVal(3);
    rbtree.deleteByVal(10);
    rbtree.deleteByVal(22);

    rbtree.InOrder();
    rbtree.LevelOrder();
    std::cout << std::endl;

    std::string txt = "HOCHSCHULDEUTSCH";
    String::SuffixTrid S(txt);
    S.search("SCH");
    return 0;
}