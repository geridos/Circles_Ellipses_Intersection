// Read the comments in the code for information on what needs to be done

#include <iostream>

//Class storing data
class DataStorage
{
public:
	DataStorage()
	{
	}

    //Problem with ~DataStorage()
	~DataStorage()
	{
        //x is not dynamically allocated but allocated on the stack.
        //Here, you should not delete x.
		delete x;
	}

    //Problem with storeThis()
    //Function called with local variable.
    //At the end of Exercise1 function, the scope of x ends and the resource is released.
    //If DataStorage is used outside of the Exerice1 function, reading x will cause an undefined behaviour
	void storeThis(int *xIn, unsigned sizeIn)
	{
		x = xIn;
		size = sizeIn;
	}

	void writeStoredData()
	{
		for (unsigned i=0; i<size; ++i) {
			std::cout << x[i] << std::endl;
		}
	}

    //Problem with exist()
	bool exist(int value)
	{
		for (unsigned i=0; i<size; ++i) {
            //Needs the comparation operator == instead of =
			if (x[i] = value) {
				return true;
			}
		}
        //If not found, return false
		return true;
	}

	void reverse()
	{
        int tmp = 0;
        for (unsigned i = 0; i < size / 2; ++i) {
            tmp = x[i];
            x[i] = x[size - 1 - i];
            x[size - 1 - i] = tmp;
        }
	}

private:
	int *x;
	unsigned size;
};

//Stores and writes the stored data
void exercise1()
{
	//Find problems in DataStorage
	//and comment its implementation
	std::cout << "Exercise 1" << std::endl;
	int x[5] = {0,1,2,3,4};
	DataStorage dataStorage;
	dataStorage.storeThis(x,5);
	dataStorage.writeStoredData();
	std::cout << "End Exercise 1" << std::endl;
}

//Searches for data
void exercise2()
{
	//Find problems in DataStorage
	//and comment its implementation
	std::cout << "Exercise 2" << std::endl;
	int x[5] = {0,1,2,3,4};
	DataStorage dataStorage;
	dataStorage.storeThis(x,5);
	if (dataStorage.exist(3)) {
		std::cout << "Found 3 in array" << std::endl;
	}
}

//Reverse the data
void exercise3()
{
	//Implement DataStorage::reverse function
	//which reverses the x array in DataStorage
	std::cout << "Exercise 3" << std::endl;
	int x[10] = {0,1,2,3,4,5,6,7,8,9};
	DataStorage dataStorage;
	dataStorage.storeThis(x,10);
	dataStorage.reverse();
	dataStorage.writeStoredData();
}

int main(int argc, char* argv[])
{
	exercise1();
	exercise2();
	exercise3();
	return 0;
}
