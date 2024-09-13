/* malloc example: string generator*/
#include <MantidKernel/CPUTimer.h>
#include <MantidKernel/Memory.h>
#include <MantidKernel/Timer.h>
#include <MantidTypes/Core/DateAndTime.h>
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
using std::string;

typedef double tof_t;
typedef size_t pulseindex_t;

int main(int argc, char *argv[]) {
  constexpr int sleeptime{2};

  // this tops out at roughly 30GB
  std::vector<std::size_t> VECTOR_LENGTH{100000, 1000000, 10000000, 100000000, 1000000000, 2000000000, 3000000000};
  constexpr size_t EVENTS_PER_PULSE{1000}; // estimated from VULCAN_217967

  CPUTimer timer;
  MemoryStats memory;

  for (auto const length_event : VECTOR_LENGTH) {
    size_t const length_pulse{length_event / EVENTS_PER_PULSE};
    std::cout << "VECTOR SIZE = " << length_event << " PULSE_SIZE = " << length_pulse << "\n";
    // reserve memory
    auto *buffer_tof = new std::vector<tof_t>();
    buffer_tof->reserve(length_event);
    auto *buffer_index = new std::vector<pulseindex_t>();
    buffer_index->reserve(length_pulse);
    auto *buffer_pulse = new std::vector<Mantid::Types::Core::DateAndTime>();
    buffer_pulse->reserve(length_pulse);
    memory.update();
    cout << "Allocate: " << timer << "\n" << memory << std::endl;

    sleep(sleeptime);
    timer.reset();

    // fill up the vectors
    for (std::size_t pulse_num = 0; pulse_num < length_pulse; ++pulse_num) {
      buffer_index->emplace_back(0);
      buffer_pulse->emplace_back(0);
      for (std::size_t n = 0; n < EVENTS_PER_PULSE; n++)
        buffer_tof->emplace_back(0);
    }

    memory.update();
    cout << "Fill: " << timer << "\n" << memory << "\n";
    sleep(sleeptime);
    timer.reset();

    // free memory
    delete buffer_tof;
    delete buffer_index;
    delete buffer_pulse;

    memory.update();
    cout << "Free: " << timer << "\n" << memory << std::endl;
    timer.reset();
  }

  return 0;
}
