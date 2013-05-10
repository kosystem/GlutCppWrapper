#include "GlutViewController.h"

using namespace glutCppWrapper;

int main(int argc, char *argv[])
{
  GlutViewController glutView;
  glutView.startFramework(argc, argv);

  return 0;
}

