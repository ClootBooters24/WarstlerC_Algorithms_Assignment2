#include <iostream>
#include <vector>
#include <linked_list.hpp> 
#include <graph.hpp> 
#include <string>
#include <map>
#include <fstream>
#include <search.hpp>

#ifdef OPENCV
#include <opencv2/opencv.hpp>
#endif

bool testGraph() {
    Graph G(7);

    G.insertEdge(0, 1);
    G.insertEdge(0, 5);
    G.insertEdge(5, 6);
    G.insertEdge(1, 2);
    G.insertEdge(1, 2);
    G.insertEdge(2, 3);
    G.insertEdge(3, 4);
    G.insertEdge(2, 4);
    G.insertEdge(6, 4);

    std::vector<std::string> algNames; algNames.clear();
    algNames.push_back("bfs");
    algNames.push_back("rdfs");
    algNames.push_back("dfs");
    int numberOfBuilding = 4;

    for (int idx = 0; idx < algNames.size(); ++idx) {
        std::string algName = algNames[idx];

        int (*searchfn)(Graph &, int, int, int, std::vector<int>&);
        if (algName == "bfs")
            searchfn = bfs;
        else if (algName == "dfs")
            searchfn = dfs;
        else
            searchfn = rdfs;

        std::vector<int> path; path.clear();

        int count = G.search(0, 4, numberOfBuilding, searchfn, path);

        if (path.size() != 0 && path.front() == 0 && path.back() == 4) {
            std::cout << "Path from 0 to 4 by " << algName << ": " ;
            for (int i = 0; i < path.size(); ++i) 
                std::cout << path[i] << " ";
            std::cout << "\n";
            std::cout << "Number of buildings in the path: " << path.size() << std::endl;
            if (! (algName == "bfs" || path.size() <= numberOfBuilding) ) {
                 std::cout << "[WARNING] The number of building in your path including start and destination produced by your " << algName << " was out of the number of buildings allowed in the requirement. You will not receive a full grade in this case. You may have to improve your implementation!" << std::endl;

            }
            if ( algName == "bfs") {
                std::cout << "The total number of shortest paths: " << count << std::endl;   
                if (count != 2) {
                    std::cout << "[WARNING] The number of shorest path produced by your " << algName << " was incorrect. There should be only two paths. You will not receive a full grade in this case. You may have to improve your implementation!" << std::endl;
                }
            }
            std::cout << std::endl;
            
        } else {
            std::cout << "It seems that your " << algName << " was implemented incorrectly" << std::endl;
            return false;
        }
    }
                
    return true;
}

bool searchOnCampus(std::string start = "BELL", std::string destination = "HAPG") {
    std::ifstream reader("assets/map_info.txt");
    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<int> xs;
    std::vector<int> ys;
    for (int i = 0; i < n; ++i) {
        int index, x, y;
        std::string name;
        reader >> index >> name >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
        name2index[name] = index;
        index2name[index] = name;
    }

    std::vector<std::string> algNames; algNames.clear();
    algNames.push_back("bfs");
    algNames.push_back("rdfs");
    algNames.push_back("dfs");

    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        reader >> u >> v;
        G.insertEdge(u, v);
    }

    int numberOfBuilding = 27;
    std::vector<std::vector<int> > paths;

    for (int idx = 0; idx < algNames.size(); ++idx) {

        std::string algName = algNames[idx];
        int (*searchfn)(Graph &, int, int, int, std::vector<int> &);
        if (algName == "bfs")
            searchfn = bfs;
        else if (algName == "dfs")
            searchfn = dfs;
        else
            searchfn = rdfs;

        std::vector<int> path; path.clear();
        int count = G.search(name2index[start], name2index[destination], numberOfBuilding, searchfn, path);

        if (path.size() != 0 && path.front() == name2index[start] && path.back() == name2index[destination]) {
            std::cout << "Path from " << start  << " to " << destination << " by the " << algName << " algorithm: " << start ;
            for (int i = 1; i < path.size(); ++i)
                std::cout << " -> " << index2name[path[i]];
            std::cout << "\n";

            std::cout << "Number of buildings in the path: " << path.size() << std::endl;

            if (! (algName == "bfs" || path.size() <= numberOfBuilding) ) {
                std::cout << "[WARNING] The number of building in your path including start and destination produced by your " << algName << " was out of the number of buildings allowed in the requirement. You will not receive a full grade in this case. You may have to improve your implementation!" << std::endl;
            }

            if ( algName == "bfs") {
                std::cout << "The total number of shortest paths: " << count << std::endl;   
            }

            
            paths.push_back(path);
            std::cout << std::endl;
        } else {
            std::cout << "It seems that your " << algName << " was implemented incorrectly" << std::endl;
            return false;
        }
    }

       
#ifdef OPENCV
    std::vector<cv::Mat> images;
    for (int idx = 0; idx < algNames.size(); ++idx) {
        std::string algName = algNames[idx];
        std::vector<int> path = paths[idx]; 

        cv::Mat image = cv::imread("assets/map.png");
        for (int i = 0; i < n; ++i) {
            cv::circle(image, cv::Point(xs[i], ys[i]), 10, cv::Scalar(255, 0, 0), -1);
            cv::putText(image, index2name[i],  cv::Point(xs[i], ys[i]-10),  cv::FONT_HERSHEY_DUPLEX, 0.7, cv::Scalar(255, 0, 0), 1);
        }   
        for (int i = 1; i < path.size(); ++i) 
            cv::line(image, cv::Point(xs[path[i]], ys[path[i]]), cv::Point(xs[path[i-1]], ys[path[i-1]]), cv::Scalar(0, 255, 0), 4);

        images.push_back(image);
    }
    cv::imshow("BFS", images[0]);
    cv::imshow("Recursive DFS", images[1]);
    cv::imshow("DFS", images[2]);
    cv::waitKey(0);

#else
    std::cout << "You have to use OpenCV to visualize your map road\n";
#endif

    return true;
}

bool testArticulationPointsAndBridges() {
    std::cout << "IF YOU ARE UNDERGRAD STUDENTS, PLEASE IGNORE THIS UNIT TEST OF FINDING ARTICULATION POINTS AND BRIDGES" << std::endl;
    Graph G(17);
    G.insertEdge(0, 1);
    G.insertEdge(1, 2);
    G.insertEdge(2, 3);
    G.insertEdge(3, 5);
    G.insertEdge(5, 4);
    G.insertEdge(4, 0);
    G.insertEdge(3, 6);
    G.insertEdge(6, 7);
    G.insertEdge(7, 9);
    G.insertEdge(9, 10);
    G.insertEdge(10, 11);
    G.insertEdge(11, 8);
    G.insertEdge(8, 6);
    G.insertEdge(3, 12);
    G.insertEdge(12, 13);
    G.insertEdge(13, 14);
    G.insertEdge(14, 15);
    G.insertEdge(15, 16);
    G.insertEdge(16, 12);

    std::vector<int> articulationPoints; articulationPoints.clear();
    std::vector<std::pair<int, int> > bridges; bridges.clear(); 

    findArticulationPointsAndBridges(G, articulationPoints, bridges);
    
    if (articulationPoints.size() != 3) {
        std::cout << "The number of articulation points is incorrect! There should be 3 articulation points." << std::endl;
        return false;
    }
    if (bridges.size() != 2) {
        std::cout << "The number of bridges is incorrect! There should be 2 bridges." << std::endl;
        return false;
    }

    std::cout << "List of Articulation Points: ";
    for (int i = 0; i < articulationPoints.size(); ++i)
        std::cout << articulationPoints[i] << " ";
    std::cout << std::endl;

    std::cout << "List of Bridges: ";
    for (int i = 0; i < bridges.size(); ++i)
        std::cout << "(" << bridges[i].first  << ", " << bridges[i].second << ") ";
    std::cout << std::endl;

    return true;

}

bool testArticulationPointsAndBridgesOnCampus() {
    std::cout << "IF YOU ARE UNDERGRAD STUDENTS, PLEASE IGNORE THIS UNIT TEST OF FINDING ARTICULATION POINTS AND BRIDGES ON CAMPUS" << std::endl;
    std::ifstream reader("assets/map_info.txt");
    int n, m;
    reader >> n >> m;
    std::map<std::string, int> name2index;
    std::map<int, std::string> index2name;
    std::vector<int> xs;
    std::vector<int> ys;
    for (int i = 0; i < n; ++i) {
        int index, x, y;
        std::string name;
        reader >> index >> name >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
        name2index[name] = index;
        index2name[index] = name;
    }

    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        reader >> u >> v;
        G.insertEdge(u, v);
    }

    std::vector<int> articulationPoints; articulationPoints.clear();
    std::vector<std::pair<int, int> > bridges; bridges.clear(); 

    findArticulationPointsAndBridges(G, articulationPoints, bridges);
    
    std::cout << "List of Articulation Points on Campus: ";
    for (int i = 0; i < articulationPoints.size(); ++i)
        std::cout << index2name[articulationPoints[i]] << " ";
    std::cout << std::endl;

    std::cout << "List of Bridges on Campus: ";
    for (int i = 0; i < bridges.size(); ++i)
        std::cout << "(" << index2name[bridges[i].first]  << ", " << index2name[bridges[i].second] << ") ";
    std::cout << std::endl;

    return true;

}

int main(int argc, char **args) {
    
    if (!testArticulationPointsAndBridges()) {
        std::cout << "Your findArticulationPointsandBridges implementation is incorrect!. If you are undergrad, please ignore this warning!" << std::endl;
    }

    std::cout << "\n";

    testArticulationPointsAndBridgesOnCampus(); 
    
    std::cout << "\n\n";
    

    
    std::cout << "Perform unit test on your searching implementation" << std::endl;
    
    if (!testGraph()) {
        std::cout << "Your searching implementation is incorrect!" << std::endl;
        return -1;
    }
    

    std::cout << "\n\n";
    
    std::cout << "Perform unit test on your searching implementation on campus map" << std::endl;

    if (!searchOnCampus("RSWE", "RCED")) {
        std::cout << "Your searching implementation is incorrect!" << std::endl;
        return -1;
    }
    
    return 0;
}
