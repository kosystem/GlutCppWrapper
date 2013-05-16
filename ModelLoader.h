#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <vector>

typedef struct
{
  union{
    struct {float x, y, z;};
    float p[3];
  };
  operator float*() {return p;}
} VERTEX;

typedef struct
{
  VERTEX normal;
  VERTEX vertex[3];
} TRIANGLE; // or FACET


class ModelLoader
{
public:
  ModelLoader();
  ModelLoader(const char *filepath);
  ~ModelLoader();

private:
  std::vector<TRIANGLE> data;
  char note[80];  // NOTE : Optimize STL file


public:
  char* getNote(){return note;}
  bool loadSTL(const char *filepath);
  bool IsEmpty(void) const {return data.empty();}
  int  getNumberOfData(void) const {return data.size();}
  void getDataAtIndex(unsigned int index, TRIANGLE* dst);

};

#endif // MODELLOADER_H
