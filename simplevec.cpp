/* malloc example: string generator*/
#include <MantidKernel/CPUTimer.h>
#include <MantidKernel/Memory.h>
#include <MantidKernel/Timer.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using Mantid::Kernel::CPUTimer;
using Mantid::Kernel::MemoryStats;
using Mantid::Kernel::Timer;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
  constexpr int sleeptime{2};

  constexpr std::size_t VECTOR_LENGTH = 3000000000;

  CPUTimer timer;
  MemoryStats memory;
  // buffer = (char*) malloc (i);
  // if (buffer==NULL) exit (1);
  auto *buffer = new std::vector<uint8_t>();
  buffer->resize(VECTOR_LENGTH);

  memory.update();
  cout << "Allocate: " << timer << "\n" << memory << "\n";

  sleep(sleeptime);
  timer.reset();

  for (std::size_t n = 0; n < VECTOR_LENGTH; n++)
    buffer->emplace_back(0); // static_cast<uint8_t>(rand()%256));

  memory.update();
  cout << "Fill: " << timer << "\n" << memory << "\n";
  sleep(sleeptime);
  timer.reset();

  // printf ("Random string: %s\n",buffer);
  // free (buffer);

  delete buffer;

  memory.update();
  cout << "Free: " << timer << "\n" << memory << "\n";
  timer.reset();

  return 0;
}
