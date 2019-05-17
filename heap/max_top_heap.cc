/**
 * 堆是一个完全二叉树，具有如下性质：
 * 1.大顶堆：父节点的值大于或等于左右孩子节点的值
 * 2.小顶堆：父节点的值小于或等于左右孩子节点的值
 * 3.每个节点的左子树和右子树仍然是一个完全二叉树
 * 4.对于下标为i的节点，其父节点的下标：(i - 1) / 2；
 *   其左孩子下标：2 * i + 1；右孩子下标：2 * i + 2
 *
 * 大顶堆常规操作实现
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

template <typename T>
void Print(const std::vector<T> arrays) {
    std::for_each(arrays.begin(), arrays.end(), 
                  [](const T &elem) { std::cout << elem << ' '; });
    std::cout << std::endl;
}

template<typename T>
void AdjustUpward(std::vector<T> &arrays, 
                  size_t parent, 
                  size_t size=0) {
    assert(parent<arrays.size() && size<=arrays.size());

    size_t adjustSize = size==0?arrays.size():size;
    T parentValue = arrays[parent];
    size_t child = 2 * parent + 1;  // 左孩子索引
    /**
     * 对于大顶堆其实就是保持父节点、左孩子和右孩子三个节点中父节点最大，
     * 如果不满足，则交换父节点与值最大的孩子节点
     */
    while (child < adjustSize) {
        // 首先判断出具有最大值的孩子节点
        if ((child+1)<adjustSize && arrays[child+1]>arrays[child]) {
            // 右孩子节点存在且大于左孩子节点的值
            ++child;
        }
        if (parentValue < arrays[child]) {
            /**
             * 需要交换父节点与值最大的孩子节点，因为被调整后的孩子节点子树
             * 可能不满足大顶堆条件，所以需要以此孩子节点作为父节点继续向下
             * 调整，直至满足大顶堆条件，当不满足时，实际还是会用parentValue
             * 与孩子节点进行交换，所以为了性能提升，可以将parentVal的赋值放
             * 到直到满足条件时再操作
             */
            arrays[parent] = arrays[child];
            parent = child;
            child = 2 * parent + 1;
        } else {
            break;  // 父节点的值已经最大，不需要调整
        }
    }
    arrays[parent] = parentValue;
}

template<typename T>
void BuildMaxTopHeap(std::vector<T> &arrays) {
    /**
     * 构建堆时从最后一个非叶子节点、由左至右、由下到上依次
     * 判断父节点与左右孩子节点的大小关系，最后一个非叶子节
     * 点：arrs.length / 2 - 1
     */
    for (ssize_t idx=(arrays.size()/2-1); idx>=0; --idx) {
        AdjustUpward(arrays, idx);
    }
}

// 大顶堆适合进行生序堆排序
template<typename T>
void SortHeap(std::vector<T> &maxTopHeap) {
    /**
     * 基本思想：将堆顶元素与末尾元素进行交换，使末尾元素最大，
     * 然后继续调整堆（因为最后一个元素已经是最大值，所以再次调
     * 整时需要排除最后一个元素），再将堆顶元素与末尾元素交换，
     * 得到第二大元素。如此反复进行交换、重建、交换。
     *
     * NOTE：堆顶元素就是首元素
     */
    using MaxTopHeapSize = typename std::vector<T>::size_type;
    for (MaxTopHeapSize idx=maxTopHeap.size()-1; idx>0; --idx) {
        std::swap(maxTopHeap[0], maxTopHeap[idx]);
        /**
         * 因为交换了首尾两个节点，而最后一个节点已经是最大值，所以不需要
         * 再进行调整，只是需要调整首元素，调整范围：0 ～ idx（此处的idx
         * 表示需要调整的arrays长度，因为是索引所以不需要-1）
         */
        AdjustUpward(maxTopHeap, 0, idx);
    }
}

int main(int argc, char **argv) {
    std::vector<int> arrays = {23, 65, 12, 3, 8, 76, 
        345, 90, 21, 75, 34, 61};
    std::cout << "origin arrays:" << std::endl;
    Print(arrays);

    // 构建一个大顶堆
    BuildMaxTopHeap(arrays);
    std::cout << "init a max top heap:" << std::endl;
    // 输出：345 90 76 65 75 61 12 3 21 8 34 23
    Print(arrays);

    // 对堆进行生序排序
    SortHeap(arrays);
    std::cout << "after ascending sort:" << std::endl;
    Print(arrays);

    return 0;
}
