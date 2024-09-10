/* malloc example: string generator*/
#include <MantidKernel/CPUTimer.h>
#include <MantidKernel/Memory.h>
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
using Mantid::Kernel::MemoryStats;
using Mantid::Kernel::Timer;
using std::cout;
using std::endl;
using std::string;

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
  MemoryStats memory;
  // buffer = (char*) malloc (i);
  // if (buffer==NULL) exit (1);
  std::vector<uint8_t> *buffer = new std::vector<uint8_t>();
  buffer->resize(i);

  memory.update();
  cout << "Allocate: " << timer << "\n" << memory << "\n";

  sleep(sleeptime);
  timer.reset();

  for (n = 0; n < i; n++)
    buffer->push_back(0); // static_cast<uint8_t>(rand()%256));

  memory.update();
  cout << "Fill: " << timer << "\n" << memory << "\n";
  sleep(sleeptime);
  timer.reset();

  // printf ("Random string: %s\n",buffer);
  // free (buffer);

  delete buffer;

  memory.update();
  cout << "Free: " << timer << "\n" << "FOU: " << memory << "\n";
  timer.reset();

  /*
  for (n=0; n<i; n++)
    static_cast<uint8_t>(rand()%256);
  cout << "rand: " << timer << endl;
  */

  return 0;
}
