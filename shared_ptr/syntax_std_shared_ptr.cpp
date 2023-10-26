#include <iostream>
#include <memory>

// Here is the syntactically valid declaration of shared_ptr
void declaration() {
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
}

int main() {
	declaration();

	return 0;
}
