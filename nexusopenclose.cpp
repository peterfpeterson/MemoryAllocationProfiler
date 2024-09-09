#include <iomanip>
#include <iostream>
#include <nexus/NeXusFile.hpp>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// -------------------------------------------------------------------
int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string filename(argv[1]);
  cout << "Trying with: " << filename << endl;
  for (std::size_t i = 0; i < 1; i++) {
    NeXus::File file(filename);
    file.openGroup("entry", "NXentry");
    file.openGroup("bank47_events", "NXevent_data");
    std::vector<uint32_t> data; //(11841710);
    file.openData("event_id");
    file.getData(data);
    file.close();
  }
}
