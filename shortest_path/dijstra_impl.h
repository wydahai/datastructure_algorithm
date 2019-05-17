/**
 * Dijstra算法C++实现
 * dijkstra算法介绍：即迪杰斯特拉算法，是从一个顶点到其余各顶点的最短路径算法，
 * 解决的是有向图中最短路径问题。 迪杰斯特拉算法主要特点是以起始点为中心向外层
 * 层扩展，直到扩展到终点为止，是一种广度优先的搜索方法。使用了广度优先搜索解
 * 决赋权有向图的单源最短路径问题。
 * dijkstra算法原理：最优子路径存在。假设从S→E存在一条最短路径SE，且该路径经过
 * 点A，那么可以确定SA子路径一定是S→A的最短路径。证明：反证法,如果子路径SA不是
 * 最短的，那么就必然存在一条更短的'SA，从而SE路径也就不是最短，与原假设矛盾。
 * dijkstra算法缺点：此算法能够求出从起点到其余每个结点的最短路径，所以需要遍历
 * 所有的路径和结点，计算复杂度比较大。
 * 基本思想：

 * 链接：https://www.jianshu.com/p/c9b27617502e
 */

#pragma once

#include <string>
#include <iostream>

using std::string;
using std::ostream;

// 该赋权有向图采用邻接矩阵的方式进行存储

// 记录起点到各个顶点的最短路径信息
struct Path{
    string path;  // 路径
    unsigned weight = 0;  // 权重
    bool visit = false;  // 是否已经被访问过
    explicit Path() = default;
};

class Graph;
std::ostream& operator<<(std::ostream &, const Graph &);

class Graph {
    // 打印原始图
    friend std::ostream& operator<<(std::ostream &os, const Graph &graph);

private:
    unsigned vexnum_;   // 图中顶点的数量
    unsigned edgenum_;  // 图中边的数量
    unsigned **matrix_ = nullptr; // 邻接矩阵，元素的值是权重
    Path *path_ = nullptr;  // 记录起点到各个顶点的最短路径信息

    static const unsigned MAX_WEIGHT_;

public:
    explicit Graph(unsigned vexnum, unsigned edgenum);
    ~Graph();

    Graph(const Graph &oth) = delete;
    Graph& operator=(const Graph &oth) = delete;

    Graph(Graph &&oth);
    Graph& operator=(Graph &&oth);

    bool CreateGraph();  // 创建赋权有向图

    // 通过Dijstra算法求出起点start到其余各个顶点到最短路径信息
    void Dijstra(unsigned start);
    void PrintShortestPath() const;  // 打印最短路径

private:
    void CreateMatrix();  // 创建邻接矩阵
    void DestroyMatrix(); // 销毁邻接矩阵
    // 判断边的信息是否合法，顶点编号从1开始
    bool CheckEdgeValue(unsigned start, unsigned end, unsigned weight);
    // 找到_path中未被访问过的且权重最小的顶点下标
    unsigned GetMinWeight() const;
};

inline
bool Graph::CheckEdgeValue(unsigned start, unsigned end, unsigned weight) {
    if (start<1 || end<1 || start>vexnum_ || end>vexnum_ || 
        weight>=MAX_WEIGHT_) {
        return false;
    }
    return true;
}
