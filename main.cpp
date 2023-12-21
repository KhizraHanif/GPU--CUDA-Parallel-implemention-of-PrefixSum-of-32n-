#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>
#include <execution>
#include <thread>
#include <chrono>
#include <ctime>
#include <ratio>
#include <cstdlib>
#include <ctime>
#include <chrono>

//so my system have 8 threads and i have 3200 elements in vector
//so i will divide 1000/8 = 125
//so i will create 8 threads and each thread will have 125 elements
using namespace std;



// Fills prefix sum array 
void fillPrefixSum(int arr[], int n, int prefixSum[])
{
    prefixSum[0] = arr[0];
    // Adding present element with previous element 
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];
}



// create vector for 32n elements
vector<int> createvector(int n) {
    vector<int> v(32 * n);
    for (int i = 0; i < 32 * n; i++)

        v[i] = rand() % 100;
    return v;
}


 //print vector
void printvector(vector<int> v) {
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

int main() 
{
     //create vector for 32n elements
    vector<int> v = createvector(5);

  
    cout << "Orignal vector: "<< endl;

 //print vector
printvector(v);

 //start the clock
auto start = std::chrono::high_resolution_clock::now();

	 //perform inclusive scan operation
	std::inclusive_scan(std::execution::par, v.begin(), v.end(), v.begin());

// stop the clock
auto stop = std::chrono::high_resolution_clock::now();
cout << "Prefix-sum vector: " << endl;
 //print resultant vector
printvector(v);

// calculate the elapsed time
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
std::cout << "time taken by inclusive-scan function: " << duration.count() << " microseconds" << std::endl;






return 0;
}


// To execute manually managed threads code, uncomment the below code and comment the above code


//#include <iostream>
//#include <iterator>
//#include <numeric>
//#include <vector>
//#include <algorithm>
//#include <execution>
//#include <thread>
//#include <chrono>
//#include <ctime>
//#include <ratio>
//#include <cstdlib>
//#include <ctime>
//#include <chrono>
//
////so my system have 8 threads and i have 3200 elements in vector
////so i will divide 1000/8 = 125
////so i will create 8 threads and each thread will have 125 elements
//using namespace std;
//
//
//
//// Fills prefix sum array 
//void fillPrefixSum(int arr[], int n, int prefixSum[])
//{
//    prefixSum[0] = arr[0];
//    // Adding present element with previous element 
//    for (int i = 1; i < n; i++)
//        prefixSum[i] = prefixSum[i - 1] + arr[i];
//}
//
//
//
//// create vector for 32n elements
//vector<int> createvector(int n) {
//    vector<int> v(32 * n);
//    for (int i = 0; i < 32 * n; i++)
//
//        v[i] = rand() % 100;
//    return v;
//}
//

////print vector
//void printvector(vector<int> v) {
//    for (int i = 0; i < v.size(); i++)
//        cout << v[i] << " ";
//    cout << endl;
//}
//
//int main()
//{
//    vector<int> v = createvector(5);
//
//    printvector(v);
//    //used 8 threads manually 
//    int num_threads = std::thread::hardware_concurrency();
//    std::cout << "number of threads available in hardware: " << num_threads << endl;
//    auto start = std::chrono::high_resolution_clock::now();
//    int n1 = v.size();
//    int numthreads = 8;
//    int chunksize = n1 / numthreads;
//    std::vector<std::thread> threads(numthreads);
//
//    for (int i = 0; i < numthreads; i++) {
//        threads[i] = std::thread([&, i, chunksize, n1]() {
//            // capture 'numthreads' by value
//            int start = i * chunksize;
//            int end = (i == numthreads - 1) ? n1 : (i + 1) * chunksize;
//
//            // perform partial sum on the chunk
//            std::partial_sum(v.begin() + start, v.begin() + end, v.begin() + start);
//
//            // accumulate the last element of the chunk to be added to the next chunk
//            int accumulate_value = (start > 0) ? v[start - 1] : 0;
//
//            // add the accumulated value to the remaining elements of the chunk
//            std::for_each(v.begin() + start, v.begin() + end, [accumulate_value](int& element) {
//                element += accumulate_value;
//                });
//            });
//    }
//
//    // join the threads
//    for (int i = 0; i < numthreads; i++) {
//        threads[i].join();
//    }
//
//    // stop the clock
//    auto stop = std::chrono::high_resolution_clock::now();
//
//
//    // print resultant vector
//    printvector(v);
//    // calculate the elapsed time
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//    std::cout << "time taken by function using 8 threads: " << duration.count() << " microseconds" << std::endl;
//    // Generate a random vector of length 32n
//
//
//
//    return 0;
//}
