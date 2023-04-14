#include "ForestAnalyzer.h"
#include <chrono>

ForestAnalyzer::ForestAnalyzer( const char* FileName )
{
     inputFileHandler = std::ifstream(FileName);

    if(inputFileHandler.is_open())
    {
        inputBuffer = * new std::vector<std::vector<int>>;
        ReadFileToBuffer();
    }
    else
    {
        std::cout << "File can not be opened!" << std::endl;
    }
}

void ForestAnalyzer::ReadFileToBuffer( void )
{
    std::string     line;

    while (std::getline(inputFileHandler, line))
    {
        std::vector<int> row;
        row.reserve( line.size() );

        for (unsigned int i = 0; i < line.size(); i++)
        {
            row.emplace_back(line[i] - '0');
        }

        inputBuffer.emplace_back(row);
    }

    inputFileHandler.close();
}

int ForestAnalyzer::GetNumberOfVisibleTrees( void )
{
    return VisibleTreeCounter( inputBuffer );
}

int ForestAnalyzer::GetMaximumScenicScore( void )
{
    return ScenicScoreCalculator( inputBuffer );
}

ForestAnalyzer::~ForestAnalyzer()
{
    
}

int VisibleTreeCounter( std::vector<std::vector<int>> & buffer )
{
    /*Initializing with number of trees on edge*/
    
    int numOfVisibleTrees = 2 * buffer.size() + 2 * (buffer[0].size() - 2);

    for (unsigned int i = 1; i < (buffer.size() - 1); i++)
    {
        for (unsigned int j = 1; j < (buffer[0].size() - 1); j++)
        {
            /*Checking elements on top*/
            bool isTreeVisible = true;
            for (unsigned int k = 0; k < i; k++)
            {
                if (buffer[k][j] >= buffer[i][j])
                {
                    isTreeVisible = false;
                    break;
                }
            }
            if (isTreeVisible)
            {
                numOfVisibleTrees++;
                continue;
            }

            /*Checking elements on bottom*/
            isTreeVisible = true;
            for (unsigned int k = buffer.size() - 1; k > i; k--)
            {
                if (buffer[k][j] >= buffer[i][j])
                {
                    isTreeVisible = false;
                    break;
                }
            }
            if (isTreeVisible)
            {
                numOfVisibleTrees++;
                continue;
            }

            /*Checking elements on left*/
            isTreeVisible = true;
            for (unsigned int k = 0; k < j; k++)
            {
                if (buffer[i][k] >= buffer[i][j])
                {
                    isTreeVisible = false;
                    break;
                }
            }
            if (isTreeVisible)
            {
                numOfVisibleTrees++;
                continue;
            }

            /*Checking elements on right*/
            isTreeVisible = true;
            for (unsigned int k = buffer[0].size() - 1; k > j; k--)
            {
                if (buffer[i][k] >= buffer[i][j])
                {
                    isTreeVisible = false;
                    break;
                }
            }
            if (isTreeVisible)
                numOfVisibleTrees++;
        }
    }

    return numOfVisibleTrees;
}

int ScenicScoreCalculator( std::vector<std::vector<int>> & buffer )
{
    int maxScenicScore = 0;

    for (unsigned int i = 1; i < (buffer.size() - 1); i++)
    {
        for (unsigned int j = 1; j < (buffer[0].size() - 1); j++)
        {
            int numOfVisibleTreesOnTop = 0;
            for (int k = i - 1; k >= 0; k--)
            {
                numOfVisibleTreesOnTop++;
                if (buffer[k][j] >= buffer[i][j])
                    break;
            }

            int numOfVisibleTreesOnBottom = 0;
            for (unsigned int k = i + 1; k < buffer.size(); k++)
            {
                numOfVisibleTreesOnBottom++;
                if (buffer[k][j] >= buffer[i][j])
                    break;
            }

            int numOfVisibleTreesOnLeft = 0;
            for (int k = j - 1; k >= 0; k--)
            {
                numOfVisibleTreesOnLeft++;
                if (buffer[i][k] >= buffer[i][j])
                    break;
            }

            int numOfVisibleTreesOnRight = 0;
            for (unsigned int k = j + 1; k < buffer[0].size(); k++)
            {
                numOfVisibleTreesOnRight++;
                if (buffer[i][k] >= buffer[i][j])
                    break;
            }

            int scenicScore = numOfVisibleTreesOnTop * numOfVisibleTreesOnBottom * 
                              numOfVisibleTreesOnLeft * numOfVisibleTreesOnRight;
                              
            if(scenicScore > maxScenicScore)
                maxScenicScore = scenicScore;
        }
    }
    
    return maxScenicScore;
}