#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <limits>

#include "day_05.h"

std::vector<long> seeds;
std::vector<std::pair<long,long>> seedsPairs;
std::vector<std::tuple<long,long,bool>> seedsTupls;
std::vector<std::vector<std::tuple<long, long, long>>> allMaps;

std::string readFile(const std::string &iFilePath)
{
     // Open the file
    std::ifstream inputFile(iFilePath);

    // Check if the file is open
    if (!inputFile.is_open())
        throw std::invalid_argument("File <" + iFilePath + "> doesn't exists.");

    // Get conent from file
    std::string content((std::istreambuf_iterator<char>(inputFile) ),
                       (std::istreambuf_iterator<char>()));

    return content;
}

void getContent(const std::string &iContent)
{
    // read first line (seeds)
    // and put the numbers into a vector
    auto posSeeds = iContent.find("seeds:");
    auto posSeedToSoil = iContent.find("seed-to-soil map:");

    long number;
    std::stringstream ss(iContent.substr(posSeeds+6,posSeedToSoil-posSeeds+6));
    while (ss >> number) {
        seeds.push_back(number);
    }

    std::stringstream leftContent(iContent.substr(posSeedToSoil,iContent.size()-posSeedToSoil));

    std::vector<std::tuple<long,long,long>> map;
    std::string line;
    // jump the first lien
    std::getline(leftContent,line);
    //loop on the rest 
    while(std::getline(leftContent,line))
    {
        // if not empty line
        if(line != "")
        {
            // get numbers as tuple and push them into a vector
            long destinationRangeStart, sourceRangeStart, rengeLength;
            std::stringstream ss(line);
            ss >> destinationRangeStart >> sourceRangeStart >> rengeLength;

            std::tuple t = std::make_tuple(destinationRangeStart, sourceRangeStart, rengeLength);
            map.push_back(t);
        }
        else // if the line is empty
        {
            //jump the text after empty line
            std::getline(leftContent,line);
            //insert the map  into a vector
            allMaps.push_back(map);
            map.clear();
        }
    }

    allMaps.push_back(map);

}

void lowestLocationNumbers()
{
    auto lowestLocation = std::numeric_limits<long>::max();
    
    for(auto seed: seeds)
    {
        for(auto &map : allMaps)
        {

            for(auto &coordinates: map)
            {
                
                auto destinationRangeStart = std::get<0>(coordinates);
                auto sourceRangeStart = std::get<1>(coordinates);
                auto rengeLength = std::get<2>(coordinates);

                if((seed >= sourceRangeStart)  && (seed < (sourceRangeStart + rengeLength)))
                {
                    seed += destinationRangeStart - sourceRangeStart;                 
                    break;
                }
            }
        }

      
         lowestLocation = std::min(static_cast<long>(seed),lowestLocation);
    }

   std::cout << "lowest map location: " << lowestLocation << std::endl;

}

void lowestLocationNumbersPart2()
{

    int error = 0;
    //create pairs
    for(auto i =0; i<seeds.size()-1;i+=2)
    {
        seedsPairs.push_back(std::make_pair(seeds[i],seeds[i]+seeds[i+1]));
        std::cout << "original seeds: " << seedsPairs[i].first << " " << seedsPairs[i].second << std::endl;
    }

    auto lowestLocation = std::numeric_limits<long>::max();
    
    for(auto &map : allMaps)
   
    {
         for(auto i = 0; i<seedsPairs.size(); i++)
        {
             int mapN =0;
            for(auto &coordinates: map)
            {
                                
                auto destinationRangeStart = std::get<0>(coordinates);
                auto sourceRangeStart = std::get<1>(coordinates);
                auto rengeLength = std::get<2>(coordinates);
                
                auto offset = destinationRangeStart - sourceRangeStart;

                auto sourceRangeEnd = sourceRangeStart + rengeLength;

                //start and end for each pair
                auto seedStart = seedsPairs[i].first;
                auto seedEnd = seedsPairs[i].second;

                // make a copy of the pair need it for some updates
                auto seedsPairsCopy = seedsPairs[i];

                // GREEN
                if((seedStart >= sourceRangeStart)  && (seedEnd < (sourceRangeEnd)) )
                {
                    std::cout << "." ;
                    seedStart += offset;
                    seedEnd += offset;
                   // std::cout << "GREEN before: " << seedsPairs[i].first << " " << seedsPairs[i].second << std::endl; 
                    seedsPairs[i].first += offset;
                    seedsPairs[i].second += offset; 
                       
                    //seedsPairs[i] = std::make_pair(seedStart,seedEnd);  
                    //std::cout << "GREEN after: " << seedsPairs[i].first << " " << seedsPairs[i].second << std::endl;    
                    break;

                }
                // PINK
                else if((seedStart >= sourceRangeStart)  && (seedStart < (sourceRangeEnd)))
                {
                    std::cout << "#" ;
                    seedEnd = sourceRangeEnd - 1;
                    seedStart += offset;
                    seedEnd += offset;
                    seedsPairs[i] = std::make_pair(seedStart, seedEnd);
                     
                    //std::cout << "PINK: " << seedsPairs[i].first << " " << seedsPairs[i].second << std::endl;    

                    //copy the rest to the seeds
                    seedStart = sourceRangeEnd;
                    seedEnd = seedsPairsCopy.second;
                    seedsPairs.push_back(std::make_pair(seedStart,seedEnd));
                    if(seedStart == 110)
                    {
                        std::cout << "pink" <<std::endl;
                        return;
                    }
                    break;
                }
                //BLUE
                else if((seedEnd >= sourceRangeStart)  && (seedEnd < (sourceRangeEnd)))
                {
                    std::cout << "*" ;
                    error++;
                    if(error >1000)
                    {
                         std::cout << "seedStart: " << seedStart << "\n";
                         std::cout << "seedEnd: " << seedEnd << "\n";
                         std::cout << "sourceRangeStart: " << sourceRangeStart << "\n";
                         std::cout << "sourceRangeEnd: " << sourceRangeEnd << "\n";
                          std::cout << "seeds: \n";
                        for(auto j = 0; j<seedsPairs.size(); j++)
                        {
                            std::cout << "" << seedsPairs[j].first << " " << seedsPairs[j].second << " | ";
                        }
                        return;
                    }
                    seedStart = sourceRangeStart + offset;
                    seedEnd += offset;
                    seedsPairs[i] = std::make_pair(seedStart,seedEnd);

                    //std::cout << "BLUE: " << seedsPairs[i].first << " " << seedsPairs[i].second << std::endl;    

                    //copy the rest to the seeds
                    seedStart = seedsPairsCopy.first;
                    seedEnd = sourceRangeEnd - 1;
                    seedsPairs.push_back(std::make_pair(seedStart,seedEnd));
                    if(seedStart == 110)
                    {
                        std::cout << "blue" <<std::endl;
                        return;
                    }
                    break;
                }
                //PURPULE
                else if((seedStart < sourceRangeStart)  && (seedEnd >= (sourceRangeEnd)))
                {
                    std::cout << "-" ;
                    seedStart = sourceRangeStart + offset;
                    seedEnd = sourceRangeEnd + offset -1;
                    seedsPairs[i] = std::make_pair(seedStart,seedEnd);

                    // before
                    seedStart = seedsPairsCopy.first;
                    seedEnd = sourceRangeStart - 1;
                    seedsPairs.push_back(std::make_pair(seedStart,seedEnd));
                    if(seedStart == 110)
                    {
                        std::cout << "purpule" <<std::endl;
                        return;
                    }

                    // after
                    seedStart = sourceRangeEnd;
                    seedEnd = seedsPairsCopy.second;
                    seedsPairs.push_back(std::make_pair(seedStart,seedEnd));
                    if(seedStart == 110)
                    {
                        std::cout << "purpule 2" <<std::endl;
                        return;
                    }
                    break;
                }
                //RED
                else{
                    std::cout << "+" ;
                    //break;
                }
            }
            
        }

        std::cout << "_________________________" << std::endl;
        for(auto j = 0; j<seedsPairs.size(); j++)
        {
            std::cout << "" << seedsPairs[j].first << " " << seedsPairs[j].second << " | ";
        }
            std::cout << "_________________________" << std::endl;
        //mapN++;

        // lowestLocation = std::min(seedsPairs[i].first,lowestLocation);
        // std::cout << "lowest map location: " << lowestLocation << std::endl;
        // std::cout << "seedsPairs[i]: " << seedsPairs[i].first << " " << seedsPairs[i].second << std::endl;

    }

   std::cout << "lowest map location: " << lowestLocation << std::endl;

}

void lowestLocationNumbersPart2_2()
{

    int error = 0;
    // create pairs
    for (auto i = 0; i < seeds.size() - 1; i += 2)
    {
        seedsTupls.push_back(std::make_tuple(seeds[i], seeds[i] + seeds[i + 1], false));
    }

    auto lowestLocation = std::numeric_limits<long>::max();

    for (auto &map : allMaps)
    {
        std::cout << "new map \n";
        
        for (auto i = 0; i < seedsTupls.size(); i++)
        {
            if(!std::get<2>(seedsTupls[i]))
            {
                for (auto &coordinates : map)
                {
                    auto destinationRangeStart = std::get<0>(coordinates);
                    auto sourceRangeStart = std::get<1>(coordinates);
                    auto rengeLength = std::get<2>(coordinates);

                    auto offset = destinationRangeStart - sourceRangeStart;

                    auto sourceRangeEnd = sourceRangeStart + rengeLength;

                    // start and end for each pair
                    auto seedStart = std::get<0>(seedsTupls[i]);
                    auto seedEnd = std::get<1>(seedsTupls[i]);

                    // make a copy of the pair need it for some updates
                    auto seedsTuplsCopy = seedsTupls[i];
                    
                    // std::cout << "start, from " << std::get<0>(seedsTupls[i]) << " to " << std::get<1>(seedsTupls[i]) <<"; "  << std::get<2>(seedsTupls[i])  << "\n";
                    // std::cout << "start, from " << seedStart << " to " << seedEnd << "\n";

                    // GREEN
                    if ((seedStart >= sourceRangeStart) && (seedEnd < (sourceRangeEnd)))
                    {
                        std::cout << "green, from " << std::get<0>(seedsTupls[i]) << " to " << std::get<1>(seedsTupls[i]) << "\n";
                        std::cout << ".";
                        seedStart += offset;
                        seedEnd += offset;

                        //std::cout << "green, from " << std::get<0>(seedsTupls[i]) << " " << std::get<1>(seedsTupls[i]) << "\n";
                        seedsTupls[i] = std::make_tuple(seedStart, seedEnd, true);
                        //std::cout << "to " << std::get<0>(seedsTupls[i]) << " " << std::get<1>(seedsTupls[i]);
                        

                        break;
                    }
                    // PINK
                    else if ((seedStart >= sourceRangeStart) && (seedStart < (sourceRangeEnd)) && (seedEnd >= (sourceRangeEnd)))
                    {
                        std::cout << "pink, from " << std::get<0>(seedsTupls[i]) << " to " << std::get<1>(seedsTupls[i]) << "\n";
                        std::cout << "#";
                        seedEnd = sourceRangeEnd - 1;
                        seedStart += offset;
                        seedEnd += offset;

                        //std::cout << "pink, from " << std::get<0>(seedsTupls[i]) << " " << std::get<1>(seedsTupls[i]) << "\n";
                        seedsTupls[i] = std::make_tuple(seedStart, seedEnd, true);
                        //std::cout << "to " << std::get<0>(seedsTupls[i]) << " " << std::get<1>(seedsTupls[i]);

                        // copy the rest to the seeds
                        seedStart = sourceRangeEnd;
                        seedEnd = std::get<1>(seedsTuplsCopy);
                        std::cout << "inserted pink, from " << seedStart << " to " << seedEnd  << "\n";
                        seedsTupls.push_back(std::make_tuple(seedStart, seedEnd, false));
                
                        break;
                    }
                    // BLUE
                    else if ((seedEnd >= sourceRangeStart) && (seedEnd < (sourceRangeEnd)))
                    {
                        std::cout << "blue before, from " << std::get<0>(seedsTupls[i]) << " to " << std::get<1>(seedsTupls[i]) << "\n";

                        std::cout << "seedsTuplsCopy,  " << std::get<0>(seedsTuplsCopy) << " to " << std::get<1>(seedsTuplsCopy) << "\n";
                        //std::cout << "*";
                        error++;
                        //   std::cout << "_________________________" << std::endl;
                        // for (auto j = 0; j < seedsTupls.size(); j++)
                        // {
                        //     std::cout << "" << std::get<0>(seedsTupls[j]) << " " << std::get<1>(seedsTupls[j]) << "; " <<std::get<2>(seedsTupls[j]) << " | " ; 
                        // }
                        // std::cout << "_________________________" << std::endl;
         
                        seedStart = sourceRangeStart + offset;
                        seedEnd += offset;
                        //std::cout << "pink, from " << std::get<0>(seedsTupls[i]) << " " << std::get<1>(seedsTupls[i]) << "\n";
                        seedsTupls[i] = std::make_tuple(seedStart, seedEnd,true);
                        //std::cout << "pink, from " << std::get<0>(seedsTupls[i]) << " " << std::get<1>(seedsTupls[i]) << "\n";

                        // std::cout << "BLUE: " << seedsTupls[i].first << " " << seedsTupls[i].second << std::endl;

                        // copy the rest to the seeds
                        seedStart =  std::get<0>(seedsTuplsCopy);
                        seedEnd = sourceRangeStart - 1;
                        std::cout << "inserted blue, from " << seedStart << " to " << seedEnd  << "\n";
                        seedsTupls.push_back(std::make_tuple(seedStart, seedEnd, false));
                        
                
                        break;
                    }
                    // PURPULE
                    else if ((seedStart < sourceRangeStart) && (seedEnd >= (sourceRangeEnd)))
                    {
                        std::cout << "purpule, from " << std::get<0>(seedsTupls[i]) << " to " << std::get<1>(seedsTupls[i]) << "\n";
                        std::cout << "-";
                        seedStart = sourceRangeStart + offset;
                        seedEnd = sourceRangeEnd + offset - 1;
                        seedsTupls[i] = std::make_tuple(seedStart, seedEnd,true);

                        // before
                        seedStart = std::get<0>(seedsTuplsCopy);
                        seedEnd = sourceRangeStart - 1;
                        std::cout << "inserted puroule, from " << seedStart << " to " << seedEnd  << "\n";
                        seedsTupls.push_back(std::make_tuple(seedStart, seedEnd,false));
                
                        // after
                        seedStart = sourceRangeEnd;
                        seedEnd = std::get<1>(seedsTuplsCopy);
                        std::cout << "inserted puroule, from " << seedStart << " to " << seedEnd  << "\n";
                        seedsTupls.push_back(std::make_tuple(seedStart, seedEnd,false));
                
                        break;
                    }
                    // RED
                    else
                    {
                        std::cout << "red, from " << std::get<0>(seedsTupls[i]) << " to " << std::get<1>(seedsTupls[i]) << "\n";
                        std::cout << "+";
                        // break;
                    }
                }
            }
        }

        std::cout << "_________________________" << std::endl;
        for (auto j = 0; j < seedsTupls.size(); j++)
        {
            std::cout << "" << std::get<0>(seedsTupls[j]) << " " << std::get<1>(seedsTupls[j]) << " | ";

            std::get<2>(seedsTupls[j]) = false;
        }
        std::cout << "_________________________" << std::endl;
        // mapN++;

        // lowestLocation = std::min(seedsPairs[i].first,lowestLocation);
        // std::cout << "lowest map location: " << lowestLocation << std::endl;
        // std::cout << "seedsPairs[i]: " << seedsPairs[i].first << " " << seedsPairs[i].second << std::endl;
    }

    std::cout << "lowest map location: " << lowestLocation << std::endl;
}


void display()
{
    for (auto n: seeds)
    {
        std::cout << n << " ";
    }
    std::cout << "\n";

    for (auto v: allMaps)
    {
        for (auto t: v)
        {
            std::cout << std::get<0>(t) <<" " <<std::get<1>(t) <<  " " <<std::get<2>(t) << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
