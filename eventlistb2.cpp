#include <iomanip>
#include <iostream>
#include <memory>
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

// copied from nexus to break out of iteration
static string const NULL_STR("NULL");
// things we care about
static string const NXEVENT_DATA("NXevent_data");
static string const GROUP_ERROR("bank_error_events");
static string const GROUP_UNMAPPED("bank_unmapped_events");
// event fields
static string const FIELD_TOF("event_time_offset");
static string const FIELD_DETID("event_id");
static string const FIELD_PULSE_TIME("event_time_zero");
static string const FIELD_PULSE_INDEX("event_index");

// thing that
template <typename T> std::unique_ptr<std::vector<T>> readData(NeXus::File &file, std::string const &fieldname) {
  file.openData(fieldname);
  auto const info = file.getInfo();

  auto data = std::make_unique<std::vector<T>>(info.dims[0]);
  file.getData(*data);
  file.closeData();

  return data;
}

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

    // loop over entries
    std::pair<string, string> temp;
    while (true) {
      temp = file.getNextEntry();
      // both being null string means there are no more entries
      if (temp.first == NULL_STR && temp.second == NULL_STR)
        break;

      // only process event data groups
      if (temp.second == NXEVENT_DATA) {
        if (temp.first == GROUP_ERROR || temp.first == GROUP_UNMAPPED)
          continue;
        std::cout << "reading " << temp.first << std::endl;
        file.openGroup(temp.first, NXEVENT_DATA);

        // these types and names are brittle
        auto pulseIndex = readData<uint64_t>(file, FIELD_PULSE_INDEX);
        auto pulseTimes = readData<double>(file, FIELD_PULSE_TIME);
        auto tof = readData<float>(file, FIELD_TOF);
        auto detid = readData<uint32_t>(file, FIELD_DETID);

        file.closeGroup();
      }
    }
    file.close();
  }
}
