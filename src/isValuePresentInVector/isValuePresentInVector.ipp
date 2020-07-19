#include <algorithm>
#include <vector>

namespace Intel8080 {
    template <typename T>
    bool isValuePresentInVector(const std::vector<T>& vector, T value){
        auto iteratorToValue{
            std::find(
                vector.begin(),
                vector.end(),
                value
            )
        };

        return iteratorToValue != vector.end();
    }
}