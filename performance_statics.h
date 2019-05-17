#ifndef __ALGORITHM_PERFORMANCE_STATICS_H__
#define __ALGORITHM_PERFORMANCE_STATICS_H__


#include <chrono>

using namespace std::chrono;

namespace algorithm {
namespace performance {

template <typename T>
class Duration {
private:
    decltype(system_clock::now()) start_{};
    static double duration_;  // microseond

public:
    explicit Duration() {
        start_ = system_clock::now();
    }

    ~Duration() {
        auto end = system_clock::now();
        duration_ = duration_cast<T>(end - start_).count();
    }

    static double GetDuration() {
        return duration_;
    }
};

template <typename T>
double Duration<T>::duration_ {};

}  // namespace: performance
}  // namespace: algorithm

#endif  // __ALGORITHM_PERFORMANCE_STATICS_H__
