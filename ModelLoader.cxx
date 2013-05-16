#include "ModelLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

ModelLoader::ModelLoader()
{
}

ModelLoader::ModelLoader(const char *filepath)
{
  const char *index;
  int c = '.';
  index = strrchr(filepath, c);
  if (strcmp(index+1, "stl") == 0)
    {
    this->loadSTL(filepath);
    }
}

ModelLoader::~ModelLoader()
{
  this->data.clear();
}


bool ModelLoader::loadSTL(const char *filepath)
{
  FILE *fp;
  unsigned int numberOfTriangle;
  char dummy[2];

  if ((fp = fopen(filepath, "rb")) == NULL)
    {
    std::cerr << "File open err : " << filepath << std::endl;
    exit(0);
    }

  // Read comment string
  fread(note, sizeof(char), 80, fp);
  fread(&numberOfTriangle, sizeof(int), 1, fp);

  // Read triangle data
  for (int i=0; i < numberOfTriangle; i++)
    {
    TRIANGLE triangle;

    fread(triangle.normal, sizeof(float), 3, fp);
    fread(triangle.vertex, sizeof(float), 9, fp);
    fread(dummy, sizeof(char), 2, fp);
    data.push_back(triangle);
    }
  fclose(fp);
}

void ModelLoader::getDataAtIndex(unsigned int index, TRIANGLE *dst)
{
  if(data.size() > index)
    {
    *dst = data.at(index);
    }
  else
    {
    dst = NULL;
    }
  return;
}
