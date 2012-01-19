#include <stdint.h>
#include <stdio.h>
#include <vector>

void withArray(std::vector<uint8_t> &vec, const std::size_t size)
{
  uint8_t* array = new uint8_t[size];
  for (std::size_t i = 0; i < size ; ++i)
    array[i] = 0;

  vec.insert(vec.end(), array, array + size);

  delete array;
}

void withVector(std::vector<uint8_t> &vec, const std::size_t size)
{
  for (std::size_t i = 0; i < size ; ++i)
    vec.push_back(0);
}

int main (int argc, char *argv[])
{
  std::size_t TOTAL = 3000000000; // ~5GB

  std::vector<uint8_t> vec(TOTAL);

  // use one of these
  withArray(vec, TOTAL);
  //withVector(vec, TOTAL);

  return 0;
}
