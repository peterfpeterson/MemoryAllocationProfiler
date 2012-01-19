#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <vector>

void withArray(std::vector<uint8_t> &vec, const std::size_t size)
{
  std::cout << "withArray" << std::endl;
  uint8_t* array = new uint8_t[size];
  for (std::size_t i = 0; i < size ; ++i)
    array[i] = 0;

  vec.insert(vec.end(), array, array + size);

  delete array;
}

void withIndex(std::vector<uint8_t> &vec, const std::size_t size)
{
  std::cout << "withIndex" << std::endl;
  vec.resize(size);
  for (std::size_t i = 0; i < size ; ++i)
    vec[i] = 0;
}

void withPushback(std::vector<uint8_t> &vec, const std::size_t size)
{
  std::cout << "withPushback" << std::endl;
  vec.reserve(size);
  for (std::size_t i = 0; i < size ; ++i)
    vec.push_back(0);
}

int main (int argc, char *argv[])
{
  std::size_t TOTAL = 3000000000; // ~5GB

  std::vector<uint8_t> vec;

  // use one of these
  //withArray(vec, TOTAL);
  //withIndex(vec, TOTAL);
  withPushback(vec, TOTAL);
  std::cout << "length " << vec.size() << std::endl;

  return 0;
}
