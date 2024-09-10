/* malloc example: string generator*/
#include <MantidKernel/CPUTimer.h>
#include <MantidKernel/Timer.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

using Mantid::Kernel::CPUTimer;
using Mantid::Kernel::Timer;
using std::cout;
using std::endl;
using std::string;

//////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0

void process_mem_usage(double &vm_usage, double &resident_set) {
  using std::ifstream;
  using std::ios_base;
  using std::string;

  vm_usage = 0.0;
  resident_set = 0.0;

  // 'file' stat seems to give the most reliable results
  //
  ifstream stat_stream("/proc/self/stat", ios_base::in);

  // dummy vars for leading entries in stat that we don't care about
  //
  string pid, comm, state, ppid, pgrp, session, tty_nr;
  string tpgid, flags, minflt, cminflt, majflt, cmajflt;
  string utime, stime, cutime, cstime, priority, nice;
  string O, itrealvalue, starttime;

  // the two fields we want
  //
  unsigned long vsize;
  long rss;

  stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpgid >> flags >> minflt >> cminflt >>
      majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >> O >> itrealvalue >> starttime >>
      vsize >> rss; // don't care about the rest

  stat_stream.close();

  long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
  vm_usage = vsize / 1024.0;
  resident_set = rss * page_size_kb;
}

int main(int argc, char *argv[]) {
  int sleeptime = 2;
  double rss, vm;

  std::size_t i, n;
  // char * buffer;

  /*
  cout << "How long do you want the string? ";
  std::cin >> i;
  */
  i = 3000000000;

  CPUTimer timer;
  // buffer = (char*) malloc (i);
  // if (buffer==NULL) exit (1);
  std::vector<uint8_t> *buffer = new std::vector<uint8_t>();
  buffer->resize(i);

  cout << "Allocate: " << timer << endl;
  process_mem_usage(vm, rss);
  cout << "          VM: " << (vm / 1024.) << "MB RSS: " << (rss / 1024.) << "MB" << endl;

  sleep(sleeptime);
  timer.reset();

  for (n = 0; n < i; n++)
    buffer->push_back(0); // static_cast<uint8_t>(rand()%256));

  cout << "Fill: " << timer << endl;
  process_mem_usage(vm, rss);
  cout << "      VM: " << (vm / 1024.) << "MB RSS: " << (rss / 1024.) << "MB" << endl;
  sleep(sleeptime);
  timer.reset();

  // printf ("Random string: %s\n",buffer);
  // free (buffer);

  delete buffer;

  cout << "Free: " << timer << endl;
  process_mem_usage(vm, rss);
  cout << "      VM: " << (vm / 1024.) << "MB RSS: " << (rss / 1024.) << "MB" << endl;
  timer.reset();

  /*
  for (n=0; n<i; n++)
    static_cast<uint8_t>(rand()%256);
  cout << "rand: " << timer << endl;
  */

  return 0;
}
