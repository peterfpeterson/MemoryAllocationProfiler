/* malloc example: string generator*/
#include <MantidKernel/CPUTimer.h>
#include <MantidKernel/Memory.h>
#include <MantidKernel/Timer.h>
#include <MantidTypes/Event/TofEventInt64.h>
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
using Mantid::Types::Event::TofEvent64;
using std::cout;
using std::string;

int main(int argc, char *argv[]) {
  constexpr int sleeptime{2};

  // this tops out at roughly 30GB
  std::vector<std::size_t> VECTOR_LENGTH{100000, 1000000, 10000000, 100000000, 1000000000, 2000000000};

  CPUTimer timer;
  MemoryStats memory;

  for (auto const length : VECTOR_LENGTH) {
    std::cout << "VECTOR SIZE = " << length << "\n";
    // reserve memory
    auto *buffer = new std::vector<TofEvent64>();
    buffer->reserve(length);
    memory.update();
    cout << "Allocate: " << timer << "\n" << memory << std::endl;

    sleep(sleeptime);
    timer.reset();

    // fill up the vector
    for (std::size_t n = 0; n < length; n++)
      buffer->emplace_back(0, 0);
    memory.update();
    cout << "Fill: " << timer << "\n" << memory << "\n";
    sleep(sleeptime);
    timer.reset();

    // free memory
    delete buffer;

    memory.update();
    cout << "Free: " << timer << "\n" << memory << std::endl;
    timer.reset();
  }

  return 0;
}
