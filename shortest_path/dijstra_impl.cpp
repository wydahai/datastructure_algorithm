#include "dijstra_impl.h"

#include <iostream>
#include <string>

const unsigned Graph::MAX_WEIGHT_ = 100000;  // 假设边到最大权重不超过此值

Graph::Graph(unsigned vexnum, unsigned edgenum) 
    : vexnum_{vexnum}, edgenum_{edgenum} {
        CreateMatrix();
        path_ = new Path[vexnum];
}

Graph::~Graph() {
    DestroyMatrix();
    delete[] path_;
}

void Graph::CreateMatrix() {
    matrix_ = new unsigned*[vexnum_];
    for (unsigned row=0; row!=vexnum_; ++row) {
        matrix_[row] = new unsigned[vexnum_];
        for (unsigned col=0; col!=vexnum_; ++col) {
            matrix_[row][col] = MAX_WEIGHT_;
        }
    }
}

void Graph::DestroyMatrix() {
    for (unsigned idx=0; idx!=vexnum_; ++idx) {
        delete[] matrix_[idx];
    }
    delete[] matrix_;
}

bool Graph::CreateGraph() {
    std::cout << "请输入每条边的起终点(顶点编号从1开始)及其权重" << std::endl;
    unsigned start = 0;
    unsigned end = 0;
    unsigned weight = 0;
    for (unsigned count=0; count!=edgenum_; ++count) {
again:
        std::cin >> start >> end >> weight;
        if (!CheckEdgeValue(start, end, weight)) {
            std::cout << "无效的边的起终点或权重，请重新输入" << std::endl;
            goto again;
        }
        matrix_[start-1][end-1] = weight;
        /**
         * 对于无向图来说，需要再加上下面的语句，因为没有方向
         * matrix_[end-1][start-1] = weight;
         */
    }

    return true;
}

unsigned Graph::GetMinWeight() const {
    unsigned minIdx = 0;
    unsigned minWeight = MAX_WEIGHT_;
    for (unsigned idx=0; idx!=vexnum_; ++idx) {
        if (!path_[idx].visit && path_[idx].weight<minWeight) {
            minWeight = path_[idx].weight;
            minIdx = idx;
        }
    }
    return minIdx;
}

void Graph::Dijstra(unsigned start) {
    // 第一步：初始化起点到图中其余各点的路径信息(比如距离，该顶点是否已被访问过)
    std::string startPre = "v" + std::to_string(start) + "-->v";
    for (unsigned idx=0; idx!=vexnum_; ++idx) {
        path_[idx].path = startPre + std::to_string(idx+1);
        path_[idx].weight = matrix_[start-1][idx];
    }

    // 第二步：更新到自身到权重及已被访问标记
    path_[start-1].weight = 0;
    path_[start-1].visit = true;

    // 第三步：更新剩余顶点到源顶点start的path信息
    unsigned count = 1;  // 源顶点自身已被处理
    unsigned minIdx = 0;
    while (count != vexnum_) {
        // 找到以start为起点的所有路径中权重最小的顶点
        // 实际上此时如果path_是一个小顶堆等类似结构会提升很大的性能
        minIdx = GetMinWeight();
        // 找到该顶点后，将该顶点标记为已访问过
        path_[minIdx].visit = true;
        // 查找与该顶点邻接的未被访问过的顶点，当源点到达该邻接点的权重大于
        // 通过通过该顶点到达此邻接点的权重时进行更新
        for (unsigned idx=0; idx!=vexnum_; ++idx) {
            if (!path_[idx].visit && matrix_[minIdx][idx]!=MAX_WEIGHT_ && 
                (matrix_[minIdx][idx]+path_[minIdx].weight)<path_[idx].weight) {
                path_[idx].weight = matrix_[minIdx][idx] + path_[minIdx].weight;
                // 更新路径为：起点+minIdx点+邻接点的路径
                path_[idx].path = path_[minIdx].path + "-->v" + 
                    std::to_string(idx+1);
            }
        }
        ++count;  // 一次遍历找到一个最小的顶点
    }
}

void Graph::PrintShortestPath() const {
    for (unsigned idx=0; idx!=vexnum_; ++idx) {
        if (path_[idx].weight == MAX_WEIGHT_) {
            std::cout << path_[idx].path << "无最短路径" << std::endl;
        } else {
            std::cout << path_[idx].path << " = " << path_[idx].weight 
                << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream &os, const Graph &graph) {
    for (unsigned row=0; row!=graph.vexnum_; ++row) {
        for (unsigned col=0; col!=graph.vexnum_; ++col) {
            if (graph.matrix_[row][col] == graph.MAX_WEIGHT_) {
                os << "∞";
            } else {
                os << graph.matrix_[row][col];
            }
            os << '\t';
        }
        os << std::endl;
    }

    return os;
}

// 对与顶点与边的关系，可以考虑放到Graph中去检测，这样就
// 调整Graph的vexnum和edgenum的赋值到CreateGraph中
inline
bool CheckVexAndEdgeCount(unsigned vexnum, unsigned edgenum) {
    /**
     * 对于一个图来说，顶点的数量必须大于0，但是边的数量可以等于0
     * 对于有向图来说，顶点和边的关系：0<=edgenum<=vexnum*(vexnum-1)
     * 对于无向图来说，顶点和边的关系：0<=edgenum<=vexnum*(vexnum-1)/2
     */
    if (vexnum==0 || edgenum>vexnum*(vexnum-1)) {
        return false;
    }
    return true;
}

/**
 * 输入：
 * 6 8
 * 1 3 10
 * 1 5 30
 * 1 6 100
 * 2 3 5
 * 3 4 50
 * 4 6 10
 * 5 6 60
 * 5 4 20
 *
 * 输出：
 * ∞	∞	10	∞	30	100
 * ∞	∞	5	∞	∞	∞
 * ∞	∞	∞	50	∞	∞
 * ∞	∞	∞	∞	∞	10
 * ∞	∞	∞	20	∞	60
 * ∞	∞	∞	∞	∞	∞
 *
 * v1-->v1 = 0
 * v1-->v2无最短路径
 * v1-->v3 = 10
 * v1-->v5-->v4 = 50
 * v1-->v5 = 30
 * v1-->v5-->v4-->v6 = 60
 */

int main(int argc, char **argv) {
    unsigned vexnum = 0;
    unsigned edgenum = 0;
again:
    std::cout << "请输入带权有向图中顶点和边的个数：";
    std::cin >> vexnum >> edgenum;
    if (!CheckVexAndEdgeCount(vexnum, edgenum)) {
        std::cout << "无效的顶点个数和边的个数" << std::endl;
        goto again;
    }

    Graph graph(vexnum, edgenum);
    graph.CreateGraph();
    std::cout << graph << std::endl;

    graph.Dijstra(1);
    graph.PrintShortestPath();

    return 0;
}
