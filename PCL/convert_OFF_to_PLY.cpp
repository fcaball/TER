#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

struct Vertex {
    float x, y, z;
};

struct Face {
    int vertexCount;
    std::vector<int> vertexIndices;
};

bool convertOFFtoPLY(const std::string& offFile, const std::string& plyFile) {
    std::ifstream inputFile(offFile);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open input file: " << offFile << std::endl;
        return false;
    }

    std::ofstream outputFile(plyFile);
    if (!outputFile.is_open()) {
        std::cout << "Failed to open output file: " << plyFile << std::endl;
        return false;
    }

    std::string line;
    std::getline(inputFile, line); // Skip the OFF header
    std::getline(inputFile, line); // Read the line with vertex and face counts

    int vertexCount, faceCount, edgeCount;
    std::sscanf(line.c_str(), "%d %d %d", &vertexCount, &faceCount, &edgeCount);

    // Read vertices
    std::vector<Vertex> vertices(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        std::getline(inputFile, line);
        std::sscanf(line.c_str(), "%f %f %f", &vertices[i].x, &vertices[i].y, &vertices[i].z);
    }

    // Read faces
    std::vector<Face> faces(faceCount);
    for (int i = 0; i < faceCount; ++i) {
        std::getline(inputFile, line);
        std::istringstream iss(line);
        int vertexCount;
        iss >> vertexCount;

        Face face;
        face.vertexCount = vertexCount;
        face.vertexIndices.resize(vertexCount);
        for (int j = 0; j < vertexCount; ++j) {
            iss >> face.vertexIndices[j];
        }
        faces[i] = face;
    }

    // Write PLY file
    outputFile << "ply" << std::endl;
    outputFile << "format ascii 1.0" << std::endl;
    outputFile << "element vertex " << vertexCount << std::endl;
    outputFile << "property float x" << std::endl;
    outputFile << "property float y" << std::endl;
    outputFile << "property float z" << std::endl;
    outputFile << "element face " << faceCount << std::endl;
    outputFile << "property list uchar int vertex_index" << std::endl;
    outputFile << "end_header" << std::endl;

    for (const auto& vertex : vertices) {
        outputFile << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
    }

    for (const auto& face : faces) {
        outputFile << face.vertexCount;
        for (int vertexIndex : face.vertexIndices) {
            outputFile << " " << vertexIndex;
        }
        outputFile << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return true;
}

void
printHelp (int, char **argv)
{
  pcl::console::print_error ("Syntax is: %s [-format 0|1] input.off output.ply\n", argv[0]);
}


int main(int  argc, char** argv) {
     if (argc < 3)
  {
    printHelp (argc, argv);
    return (-1);
  }

    std::string offFilePath = argv[1];
    std::string plyFilePath = argv[2];

    if (convertOFFtoPLY(offFilePath, plyFilePath)) {
        std::cout << "Conversion successful." << std::endl;
    } else {
        std::cout << "Conversion failed." << std::endl;
    }

    return 0;
}
