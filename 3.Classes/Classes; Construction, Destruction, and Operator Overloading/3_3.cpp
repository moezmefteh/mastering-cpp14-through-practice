#include <iostream>
#include <vector>
#include <algorithm>

class Histogram{
private:
    std::vector<double> bins;
    std::vector<int> counts;
public:
    Histogram(std::vector<double> bins) : bins{bins}, counts(bins.size() -1, 0) {
        if (bins.size() < 2) {
            throw std::invalid_argument("bins vector must contain at least two elements.");
        }
        if ( !std::is_sorted(bins.begin(),bins.end()) || std::adjacent_find(bins.begin(), bins.end(), std::greater_equal<>()) != bins.end()){
            throw std::invalid_argument("Bounds must be strictly monotonically increasing.");
        }
        std::cout<< "Default constructor" <<std::endl;
    }
    Histogram(const Histogram& other) : bins(other.bins) {
        std::cout<< "copy constructor" <<std::endl;
    }
    Histogram& operator=(const Histogram& other) {
        if (this != &other) {
            bins = other.bins;
        }
        std::cout << "Copy assignment" << std::endl;
        return *this;
    }
    
    Histogram(Histogram&& other) noexcept {
        bins = std::move(other.bins);
        std::cout<< "move constructor" <<std::endl;
    }
    Histogram& operator=(Histogram&& other) noexcept {
        if (this != &other) {
            bins = std::move(other.bins);
        }
        std::cout << "Move assignment" << std::endl;
        return *this;
    }

    void clear(){
        bins.clear();
    }
    void update(double x){
        auto it = std::upper_bound(bins.begin(), bins.end(), x);
        if (it != bins.begin() && it != bins.end()) {
            ++counts[std::distance(bins.begin(), it) -1];
        }
        else{
            std::cerr << "Value " << x << " is out of range." << std::endl;
        }
    }

    void display(std::ostream& os) const {
        for (size_t i = 0; i < counts.size(); ++i) {
            os << "[" << bins[i] << "," << bins[i + 1] << "): " << counts[i] << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Histogram& hist);
    ~Histogram(){}
};

std::ostream& operator<<(std::ostream& os, const Histogram& hist){
    os << "Histogram bins: ";
    for (const auto& bin : hist.bins) {
        os << bin << " ";
    }
    return os;
}

int main(){

    Histogram hist1(std::vector<double> {0.0, 3.14, 20.0, 42.42});
    hist1.display(std::cout);
    std::cout << "hist1: " << hist1 << std::endl;
    Histogram hist2(hist1);
    std::cout << "hist2: " << hist2 << std::endl;
    Histogram hist3(std::move(hist1));
    std::cout << "hist1: " << hist1 << std::endl;
    std::cout << "hist3: " << hist3 << std::endl;
    hist1 = std::move(hist3);
    hist2 = hist3;
    std::cout << "hist1: " << hist1 << std::endl;
    std::cout << "hist2: " << hist2 << std::endl;
    hist1.update(30);
    hist1.update(3.14);
    std::cout << "hist1: " << hist1 << std::endl;
    hist1.display(std::cout);

    return 0;
}