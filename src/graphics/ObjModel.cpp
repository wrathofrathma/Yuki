#include "ObjModel.hpp"


ObjModel::ObjModel(){
  loaded = false;
}
ObjModel::ObjModel(std::string filepath){
  loaded = false;

  loadFromFile(filepath);
}
ObjModel::~ObjModel(){

}

void ObjModel::loadFromFile(std::string filepath){
  obj_file = filepath;
  if(filepath.size()==0)
    return;

  ifstream file(filepath.c_str(), ifstream::in);
  if(!file.is_open()){
    cout << "Unable to open object file " << filepath << endl;
    return;
  }
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;
  std::vector<unsigned int> indices;
  std::vector<float> texture_uvs_proper;
  std::vector<float> normals_proper;
  std::string line;
  while(getline(file, line)){
    if(line.size()==0 || line[0]=='#')
      continue;
    //Loading vertices, normals, and uvs
    std::vector<std::string> split_line = splitString(line);
    if(split_line[0].compare("v")==0){
      float v1 = stof(split_line[1]);
      float v2 = stof(split_line[2]);
      float v3 = stof(split_line[3]);
      vertices.push_back(glm::vec3(v1,v2,v3));
    }
    else if(split_line[0].compare("vn")==0){
      float v1 = stof(split_line[1]);
      float v2 = stof(split_line[2]);
      float v3 = stof(split_line[3]);
      normals.push_back(glm::vec3(v1,v2,v3));
    }
    else if(split_line[0].compare("vt")==0){
      float v1 = stof(split_line[1]);
      float v2 = stof(split_line[2]);
      uvs.push_back(glm::vec2(v1,v2));
    }
    else if(split_line[0].compare("f")==0){
      texture_uvs_proper = std::vector<float>(vertices.size()*2);
      normals_proper = std::vector<float>(vertices.size()*3);
      break;
    }
  }

  file.clear();
  file.seekg(0,ios::beg);
  //Loading the f lines to how to use them.
  while(getline(file, line)){
    std::vector<std::string> split_line = splitString(line);
    if(split_line[0].compare("f")!=0){
      continue;
    }
    std::vector<string> v1 = splitString(split_line[1],"/");
    std::vector<string> v2 = splitString(split_line[2],"/");
    std::vector<string> v3 = splitString(split_line[3],"/");
    parseVertex(v1, indices, uvs, normals, texture_uvs_proper, normals_proper);
    parseVertex(v2, indices, uvs, normals, texture_uvs_proper, normals_proper);
    parseVertex(v3, indices, uvs, normals, texture_uvs_proper, normals_proper);
  }
  file.close();
  mesh.setIndices(indices);
  mesh.setTextureUVs(texture_uvs_proper);
  mesh.setNormals(normals_proper);
  std::vector<float> proper_vertices;
  for(glm::vec3 v : vertices){
    proper_vertices.push_back(v.x);
    proper_vertices.push_back(v.y);
    proper_vertices.push_back(v.z);
    proper_vertices.push_back(1);
  }
  mesh.setVertices(proper_vertices);

}

void ObjModel::parseVertex(std::vector<std::string> vertex, std::vector<unsigned int> &indices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<float> &texture_array, std::vector<float> &normal_array){
  int curr = stoi(vertex[0])-1; //We index from 0, they index from 1.
  indices.push_back(curr);
  glm::vec2 cuv = uvs[stoi(vertex[1])-1];
  texture_array[curr*2] = cuv.x;
  texture_array[curr*2+1] = 1 - cuv.y;

  glm::vec3 cnorm = normals[stoi(vertex[2])-1];
  normal_array[curr*3] = cnorm.x;
  normal_array[curr*3+1] = cnorm.y;
  normal_array[curr*3+2] = cnorm.z;

}

bool ObjModel::isLoaded(){
  return loaded;
}

Mesh ObjModel::getMesh(){
  return mesh;
}
std::vector<std::string> ObjModel::splitString(std::string in, std::string delim){
  std::vector<std::string> strings;
  int pos = 0;
  while(in.find(delim,pos)!=string::npos){
    int length = in.find(delim,pos) - pos;
    string buffer = in.substr(pos,length);
    if(buffer.compare(delim)!=0 && buffer.size()>0)
      strings.push_back(buffer);
    pos = in.find(delim,pos)+1;
  }
  string buffer = in.substr(pos, in.size());
  if(buffer.size()>0)
    strings.push_back(buffer);
  return strings;
}
