#include "GlutViewController.h"

using namespace glutCppWrapper;

int main(int argc, char *argv[])
{
  GlutViewController glutView;
  glutView.setFPS(20);
  glutView.startFramework(argc, argv);

  return 0;
}

