#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using matrixDouble = std::vector<std::vector<double>>;

matrixDouble createRandomMatrix(size_t size)
{
    matrixDouble randomMatrix(size, std::vector<double>(size, 0));
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.5, 2.0);
    
    for(auto& row : randomMatrix) 
    {
        for(auto& col : row)  
        {
            col = dis(gen);
        }
    }
    
    return randomMatrix;
}

matrixDouble multiplyMatrix(const matrixDouble& A, const matrixDouble& B)
{
    size_t n = A.size();
    matrixDouble C(n, std::vector<double>(n, 0.0));
    
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            for(size_t k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

matrixDouble squareMatrix(const matrixDouble& A)
{
    return multiplyMatrix(A, A);
}

int setRepetitions(size_t matrixSize)
{
    if(matrixSize <= 50) return 100;
    if(matrixSize <= 100) return 10;
    return 1;
}

int main()
{
    std::vector<size_t> sizes = {50, 100, 200};
    
    for(size_t size : sizes)
    {
        std::cout << "=== Macierz " << size << "x" << size << " ===" << std::endl;
        matrixDouble matrix = createRandomMatrix(size);
        
        int repetitions = setRepetitions(size);
        
        // Time measurement
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < repetitions; i++)
        {
            matrixDouble result = squareMatrix(matrix);
        }
        auto end = std::chrono::high_resolution_clock::now();
        
        // Calculating time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        long long totalMs = duration.count();
        long long avgMs = totalMs / repetitions;
        double avgMinutes = (totalMs / static_cast<double>(repetitions)) / 60000.0;
        
        // Printing results
        std::cout << "Number of repetitions: : " << repetitions << std::endl;
        std::cout << "Total time: " << totalMs << " ms" << std::endl;
        std::cout << "Avg time (int): " << avgMs << " ms" << std::endl;
        std::cout << "Avg time (double): " << std::fixed << std::setprecision(3) 
                  << avgMinutes << " minutes" << std::endl;
        std::cout << std::endl;
    }
    
    return 0;
}
