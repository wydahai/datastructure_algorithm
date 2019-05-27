/**
 * 题目：最小的k个数
 * 描述：输入n个整数，找出其中最小的k个数。例如输入4、5、1、6、
 *       2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
 * 分析：这道题是典型的TopK问题，其最简单的思路莫过于把输入的n
 *       个整数排序，排序之后位于最前面的k个数就是最小的k个数。
 *       这种思路的时间复杂度是O(nlogn)，但是面试官会要求时间复
 *       杂度保持在O(n)。
 */

#include <iostream>

/**
 * 解法一：时间复杂度O(n)
 * 基于快速排序中的Partition函数来解决这个问题。如果基于数组的第
 * k个数字来调整，使得比第k个数字小的所有数字都位于数组的左边，
 * 比第k个数字大的所有数字都位于数组的右边。这样调整之后，位于数
 * 组中左边的k个数字就是最小的k个数字（这k个数字不一定是排序的）。
 * But，采用这种思路是有限制的。我们需要修改输入的数组，因为函数
 * Partition会调整数组中数字的顺序。
 *
 * 具体解法：
 * 快速排序的思路中，有一个分块函数partition.
 * partition函数，以升序数组a[]为例，它的作用：
 * 以a[l]为基准，将“<a[l]”的数据全部存放在 a[l]的左边，“>a[l]”的
 * 数据全部存放在 a[l]的右边。返回a[l]最终所在数组的正确索引位置。
 * 采用双路快排，从数组的两端开始，向中间推进。
 * 故：最小的k个数，就是找到查看 partition函数返回的索引p是否与索
 * 引k相等，
 * l:数组a最左边的数据，r:数组a最右边的数据
 * p<k,则检查[p+1,r]范围的数据
 * p>k,则检查[l,p-1]范围的数据.
 * p=k，结束递归。
 * 此时数组a[]中，索引k左边的数据都"<a[k]"，即第0~k-1个数都“<a[k]”，
 * 即找到了最小的k个数。
 */
// 分区函数
int Partition(int *nums, int start, int end) {
    int pivot = nums[0];
    int low = start;
    int high = end;
    while (low < high) {
        while (high>low && nums[high]>=pivot) {
            --high;
        }
        nums[low] = nums[high];
        while (low<high && nums[low]<=pivot) {
            ++low;
        }
        nums[high] = nums[low];
    }
    nums[low] = pivot;
    return low;
}
void GetLeaestNums(int *input, int len, int *output, int k) {
    if (!input || len<=0 || !output || k<=0 || k>len) {
        return;
    }

    int start = 0;
    int end = len - 1;
    int index = Partition(input, start, end);
    while (index != k-1) {
        if (index > k-1) {
            end = index - 1;
            index = Partition(input, start, end);
        } else {
            start = index + 1;
            index = Partition(input, start, end);
        }
    }

    for (int idx=0; idx<k; ++idx) {
        output[idx] = input[idx];
    }
}

/**
 * 解法二：
 * 本方法使用于海量数据处理。大致思想是建一个K个数的大堆，每次拿一个
 * 数和堆顶元素比较，如果这个数比堆顶元素大，则必然不是最小的K个数，
 * 如果这个数比堆顶元素小，则与堆顶元素交换，然后在向下调整一次建成新
 * 的大堆，然后遍历所有的数，直到最小的K个数都进堆里。
 *
 * 最大的K个数---- 建小堆
 * 最小的K个数---- 建大堆
 */
void AdjustUp(int *heap, int index, int num) {
    heap[index] = num;
    if (index == 0) {
        return;
    }
    int parent = (index - 1) >> 1;
    while (parent >= 0) {
        if (heap[index] > heap[parent]) {
            int temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            index = parent;
            parent = (index - 1) >> 1;
        } else {
            break;
        }
    }
}

void AdjustDown(int *heap, int size, int parent) {
    int lchild = 2*parent + 1;
    while (lchild < size) {
        if (lchild+1<size && heap[lchild]<heap[lchild+1]) {
            ++lchild;
        }
        if (heap[parent] < heap[lchild]) {
            heap[parent] ^= heap[lchild];
            heap[lchild] ^= heap[parent];
            heap[parent] ^= heap[lchild];
            parent = lchild;
            lchild = 2*parent + 1;
        } else {
            break;
        }
    }
}

void GetLeaestNumsV2(const int *input, int len, int *output, int k) {
    if (!input || len<=0 || !output || k<=0 || k>len) {
        return;
    }

    // 构建一个大小为k的大顶堆
    for (int idx=0; idx<k; ++idx) {
        AdjustUp(output, idx, input[idx]);
    }
    
    for (int idx=k; idx<len; ++idx) {
        if (input[idx] < output[0]) {
            output[0] = input[idx];
            AdjustDown(output, k, 0);
        }
    }
}

int main() {
    int nums[] = {4, 5, 1, 6, 2, 7, 3, 8};
    // int nums[] = {5,23,37,41,59,16,23};
    int min_k_nums[4];
    // GetLeaestNums(nums, sizeof(nums)/sizeof(nums[0]), min_k_nums, 4);
    GetLeaestNumsV2(nums, sizeof(nums)/sizeof(nums[0]), min_k_nums, 4);
    for (int idx=0; idx<4; ++idx) {
        std::cout << min_k_nums[idx] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
