#include <bits/stdc++.h>
using namespace std;

enum class HashType {
    FNV1A,
    DJB2
};

class HashStrategy{
public:
    virtual ~HashStrategy(){}
    virtual int64_t hash(const string & data) const = 0;
};

class FNV1aHashStrategy : public HashStrategy {
private:
    // FNV-1a 64-bit constants
    static constexpr uint64_t FNV_PRIME = 0x100000001b3ULL;
    static constexpr uint64_t FNV_OFFSET_BASIS = 0xcbf29ce484222325ULL;

public:
    int64_t hash(const std::string& data) const override {
        uint64_t hashValue = FNV_OFFSET_BASIS;
        for (unsigned char byte : data) {
            hashValue ^= byte;
            hashValue *= FNV_PRIME;
        }
        return static_cast<int64_t>(hashValue);
    }
};

class DJB2HashStrategy : public HashStrategy {
public:
    int64_t hash(const std::string& data) const override {
        uint64_t hashValue = 5381;
        for (unsigned char byte : data) {
            // hash = hash * 33 + c
            hashValue = ((hashValue << 5) + hashValue) + byte;
        }
        return static_cast<int64_t>(hashValue);
    }
};

class HashStrategyFactory {
public:
    static std::unique_ptr<HashStrategy> create(HashType type) {
        switch (type) {
            case HashType::FNV1A:
                return std::make_unique<FNV1aHashStrategy>();
            case HashType::DJB2:
                return std::make_unique<DJB2HashStrategy>();
            default:
                throw std::invalid_argument("Unsupported hash type");
        }
    }
};

class BloomFilter{
private:
    std::vector<bool> bitSet;
    size_t bitSetSize;
    size_t numHashFunctions;
    std::vector<std::shared_ptr<HashStrategy>> hashStrategies;
    mutable std::mutex mtx;
    BloomFilter(size_t bitSetSize, size_t numHashFunctions,
            std::vector<std::shared_ptr<HashStrategy>> strategies)
    : bitSetSize(bitSetSize),
        numHashFunctions(numHashFunctions),
        bitSet(bitSetSize, false),
        hashStrategies(std::move(strategies)) {}

    friend class BloomFilterBuilder;

public:
    void add(const std::string& item) {
        std::lock_guard<std::mutex> lock(mtx);
        for (size_t i = 0; i < numHashFunctions; ++i) {
            int64_t hashValue = hashStrategies[i]->hash(item);
            size_t index = static_cast<size_t>(std::abs(hashValue)) % bitSetSize;
            bitSet[index] = true;
        }
    }

    bool mightContain(const std::string& item) const {
        std::lock_guard<std::mutex> lock(mtx);
        for (size_t i = 0; i < numHashFunctions; ++i) {
            int64_t hashValue = hashStrategies[i]->hash(item);
            size_t index = static_cast<size_t>(std::abs(hashValue)) % bitSetSize;
            if (!bitSet[index]) {
                return false;  // Definitely not in the set
            }
        }
        return true;  // Might be in the set
    }
};

class BloomFilterBuilder {
private:
    size_t bitSetSize = 0;
    size_t numHashFunctions = 0;
    std::vector<std::shared_ptr<HashStrategy>> strategies;
public:
    BloomFilterBuilder& withBitSetSize(size_t size) {
        if (size == 0) {
            throw std::invalid_argument("Bit set size must be positive.");
        }
        bitSetSize = size;
        return *this;
    }
    BloomFilterBuilder& withNumHashFunctions(size_t k) {
        if (k == 0) {
            throw std::invalid_argument("Number of hash functions must be positive.");
        }
        numHashFunctions = k;
        return *this;
    }
    BloomFilterBuilder& withHashStrategies(
            std::vector<std::shared_ptr<HashStrategy>> strats) {
        if (strats.empty()) {
            throw std::invalid_argument("At least one hash strategy must be provided.");
        }
        strategies = std::move(strats);
        return *this;
    }

    std::unique_ptr<BloomFilter> build() {
        if (bitSetSize == 0 || numHashFunctions == 0 || strategies.empty()) {
            throw std::logic_error(
                "Must set bit set size, number of hash functions, and strategies.");
        }

        if (strategies.size() < numHashFunctions) {
            throw std::logic_error(
                "The number of provided hash strategies (" +
                std::to_string(strategies.size()) +
                ") must be at least equal to the number of hash functions required (" +
                std::to_string(numHashFunctions) + ").");
        }

        return std::unique_ptr<BloomFilter>(
            new BloomFilter(bitSetSize, numHashFunctions, strategies));
    }
};

std::string generateUUID() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);

    std::stringstream ss;
    for (int i = 0; i < 32; ++i) {
        if (i == 8 || i == 12 || i == 16 || i == 20) {
            ss << '-';
        }
        ss << std::hex << dis(gen);
    }
    return ss.str();
}

int main() {
    // --- 1. Configure the Bloom Filter ---
    size_t bitSetSize = 10000;
    size_t numHashFunctions = 2;
    size_t expectedInsertions = 1000;

    // --- 2. Create hash strategies using the factory ---
    std::vector<std::shared_ptr<HashStrategy>> strategies;
    strategies.push_back(HashStrategyFactory::create(HashType::FNV1A));
    strategies.push_back(HashStrategyFactory::create(HashType::DJB2));

    // --- 3. Build the filter ---
    auto filter = BloomFilterBuilder()
        .withBitSetSize(bitSetSize)
        .withNumHashFunctions(numHashFunctions)
        .withHashStrategies(strategies)
        .build();

    std::cout << "Bloom Filter created with:\n";
    std::cout << "  - Bit set size (m): " << bitSetSize << "\n";
    std::cout << "  - Hash functions (k): " << numHashFunctions << "\n";

    // --- 4. Add elements to the filter ---
    std::cout << "\n--- Adding elements to the filter ---\n";
    std::vector<std::string> insertedElements;
    for (size_t i = 0; i < expectedInsertions; ++i) {
        std::string element = "user" + std::to_string(i) + "@example.com";
        insertedElements.push_back(element);
        filter->add(element);
    }
    std::cout << expectedInsertions << " elements have been added.\n";

    // --- 5. Verify no false negatives ---
    std::cout << "\n--- Verifying no false negatives ---\n";
    bool hasFalseNegatives = false;
    for (const auto& element : insertedElements) {
        if (!filter->mightContain(element)) {
            std::cerr << "FALSE NEGATIVE DETECTED FOR: " << element << "\n";
            hasFalseNegatives = true;
            break;
        }
    }
    if (!hasFalseNegatives) {
        std::cout << "Success! No false negatives found.\n";
        std::cout << "All " << expectedInsertions << " inserted elements were detected.\n";
    }

    // --- 6. Test for false positives ---
    std::cout << "\n--- Testing for false positives ---\n";
    size_t testSetSize = 10000;
    size_t falsePositivesCount = 0;
    for (size_t i = 0; i < testSetSize; ++i) {
        std::string randomElement = generateUUID();
        if (filter->mightContain(randomElement)) {
            ++falsePositivesCount;
        }
    }
    double falsePositiveRate = static_cast<double>(falsePositivesCount) / testSetSize * 100;
    std::cout << "False positives: " << falsePositivesCount << " out of " << testSetSize << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "False positive rate: " << falsePositiveRate << "%\n";

    // --- 7. Demonstrate idempotency ---
    std::cout << "\n--- Testing idempotency ---\n";
    std::string testElement = "test@example.com";
    filter->add(testElement);
    bool firstCheck = filter->mightContain(testElement);
    filter->add(testElement);  // Add again
    filter->add(testElement);  // And again
    bool secondCheck = filter->mightContain(testElement);
    std::cout << "After adding 'test@example.com' three times:\n";
    std::cout << "  First check: " << (firstCheck ? "true" : "false") << "\n";
    std::cout << "  Second check: " << (secondCheck ? "true" : "false") << "\n";
    std::cout << "  Idempotent: " << ((firstCheck == secondCheck) ? "true" : "false") << "\n";

    return 0;
}