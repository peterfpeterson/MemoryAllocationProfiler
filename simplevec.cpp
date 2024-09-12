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

  std::vector<std::size_t> const VECTOR_LENGTH{1000000,    1000000,    10000000,  100000000,
                                               1000000000, 2000000000, 3000000000};

  CPUTimer timer;
  MemoryStats memory;

  for (auto const length : VECTOR_LENGTH) {
    std::cout << "VECTOR SIZE = " << length << "\n";

    // pulsetime is int64_t, tof is double
    auto *buffer = new std::vector<int64_t>();
    buffer->resize(length);

    memory.update();
    cout << "Allocate: " << timer << "\n" << memory << std::endl;

    sleep(sleeptime);
    timer.reset();

    for (std::size_t n = 0; n < length; n++)
      buffer->emplace_back(0); // static_cast<uint8_t>(rand()%256));

    memory.update();
    cout << "Fill: " << timer << "\n" << memory << "\n";
    sleep(sleeptime);
    timer.reset();

    // printf ("Random string: %s\n",buffer);
    // free (buffer);

    delete buffer;

    memory.update();
    cout << "Free: " << timer << "\n" << memory << std::endl;
    timer.reset();
  }

  return 0;
}
