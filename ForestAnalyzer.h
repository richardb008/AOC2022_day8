#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int VisibleTreeCounter( std::vector<std::vector<int>> & buffer );
int ScenicScoreCalculator( std::vector<std::vector<int>> & buffer );

class ForestAnalyzer
{
private:
    std::vector<std::vector<int>> inputBuffer;
    std::ifstream inputFileHandler;

    void ReadFileToBuffer( void );

public:
    ~ForestAnalyzer();
    ForestAnalyzer( const char* FileName );
    int GetNumberOfVisibleTrees( void );
    int GetMaximumScenicScore( void );
};