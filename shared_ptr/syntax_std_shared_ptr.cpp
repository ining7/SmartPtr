#include <iostream>
#include <memory>
#include <chrono>

// Here is the syntactically valid declaration of shared_ptr
void declaration() {
	std::cout << "[declaration start]" << std::endl;

	// Initialize with make_shared
	std::shared_ptr<int> sp = std::make_shared<int>(10);
	std::shared_ptr<char> sp1 = std::make_shared<char>('A');
	std::shared_ptr<float> sp2 = std::make_shared<float>(3.14f);

	// Initialize with new
	std::shared_ptr<int> sp4(new int(10));
	std::shared_ptr<char> sp5(new char('A'));
	std::shared_ptr<float> sp6(new float(3.14f));
	
	// Initialize as null
	std::shared_ptr<int> sp7;
	std::shared_ptr<char> sp8 = nullptr;
	std::shared_ptr<float> sp9 = std::shared_ptr<float>();
	
	// Initialize with new for array
	// std::shared_ptr is not design to manage arrays by default. It expects to manage a single object,
	// and it calls delete instead of delete[] when the manged object is detroyed.
	// This can lead to undefined behavior if a shared_ptr is used to manage an array without a custom deleter.
	std::shared_ptr<int> sp10(new int[10], std::default_delete<int[]>());

	// Copy and assignment
	std::shared_ptr<int> copy_sp1 = sp;
	std::shared_ptr<int> copy_sp2;
	copy_sp2 = sp;

	std::cout << "[declaration end]" << std::endl;
}

// No need to clear memory explicitly
// Should not worry about calling delete or clearning the memory in an exiplict manner.
void useSharedForBuiltIn() {
	std::cout << "[useSharedForBuiltIn start]" << std::endl;

	std::shared_ptr<int> sp = std::make_shared<int>();
	*sp = 100;
	std::cout << "*sp is:" << *sp << std::endl;
	
	std::cout << "[useSharedForBuiltIn end]" << std::endl;
}

// Ownership and Reference Counts, it manages the lifetime of an object based on the Reference counts mechanism.
// The multiple shared_ptr can refer to one object, the object will not be destroyed till any one shared_ptr refers to it.
void ownershipAndRefCount() {
	std::cout << "[ownershipAndRefCount start]" << std::endl;

	class Sample{
	public:
		Sample() { std::cout << "Sample1 Constructor" << std::endl; }
		~Sample() { std::cout << "Sample1 Destructor" << std::endl; }
	};

	auto createSample = []() -> std::shared_ptr<Sample> {
		std::shared_ptr<Sample> sp = std::make_shared<Sample>();
		return sp;
	};

	std::shared_ptr<Sample> sp1;
	{
		auto sp2 = createSample();
		sp1 = sp2;
	}

	std::cout << "[ownershipAndRefCount end]" << std::endl;
}

// Usage of make_shared<>(), recommended to use make_shared<> instead of new
// make_shared<> call is a clean way to init, but also fast in memory allocation as compared to new.
void useMakeShared() {
	std::cout << "[useMakeShared start]" << std::endl;

	class Sample {
	public:
		Sample() {}
		~Sample() {}
	};

	auto createWithNew = [](size_t iterations) {
		auto start = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < iterations; ++i) std::shared_ptr<Sample> sp(new Sample());
		auto end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	};

	auto createWithMakeShared = [](size_t iterations) {
		auto start = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < iterations; ++i) std::shared_ptr<Sample> sp = std::make_shared<Sample>();
		auto end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	};

	size_t iterations = 10000000;
	std::cout << "iterations is: " << iterations << std::endl;
	auto timeWithNew = createWithNew(iterations);
	auto timeWithMakeShared = createWithMakeShared(iterations);
	std::cout << "Time with new: " << timeWithNew << " ms" << std::endl;
	std::cout << "Time with make_shared is: " << timeWithMakeShared << " ms" << std::endl;

	std::cout << "[useMakeShared end]" << std::endl;
}


// Using shared_ptr<> for Arrays
void useSharedForArrays() {
	std::cout << "[useSharedForArrays start]" << std::endl;

	std::shared_ptr<int[]> sp(new int[10], std::default_delete<int[]>());
	for (int i = 0; i < 10; ++i) sp[i] = i;
	
	std::cout << "[useShareForArrays end]" << std::endl;
}

int main() {
	declaration();
	std::cout << "------------------------------" << std::endl;
	useSharedForBuiltIn();
	std::cout << "------------------------------" << std::endl;
	ownershipAndRefCount();
	std::cout << "------------------------------" << std::endl;
	useMakeShared();
	std::cout << "------------------------------" << std::endl;
	useSharedForArrays();
	return 0;
}
