/* malloc example: string generator*/
#include <MantidKernel/CPUTimer.h>
#include <MantidKernel/Memory.h>
#include <MantidKernel/Timer.h>
#include <MantidTypes/Event/TofEvent.h>
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
using Mantid::Types::Event::TofEvent;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
  constexpr int sleeptime{2};

  // constexpr std::size_t VECTOR_LENGTH = 3000000000; value from simplevec
  // this is roughly 30GB
  constexpr std::size_t VECTOR_LENGTH = 2000000000;

  CPUTimer timer;
  MemoryStats memory;

  // reserve memory
  auto *buffer = new std::vector<TofEvent>();
  buffer->reserve(VECTOR_LENGTH);
  memory.update();
  cout << "Allocate: " << timer << "\n" << memory << "\n";

  sleep(sleeptime);
  timer.reset();

  // fill up the vector
  for (std::size_t n = 0; n < VECTOR_LENGTH; n++)
    buffer->emplace_back(0, 0);
  memory.update();
  cout << "Fill: " << timer << "\n" << memory << "\n";
  sleep(sleeptime);
  timer.reset();

  // free memory
  delete buffer;

  memory.update();
  cout << "Free: " << timer << "\n" << memory << "\n";
  timer.reset();
  return 0;
}
