/* malloc example: string generator*/
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/time.h>

using std::string;

class Timer
{
public:
  Timer()
  {
    gettimeofday(&m_start,0);
  }

  ~Timer(){}
  
  float elapsed(bool reset = true)
  {
    float retval = this->elapsed_no_reset();

    if (reset) this->reset();

    return retval;
  }

  float elapsed_no_reset() const
  {
    timeval now;
    gettimeofday(&now,0);
    const float retval = float(now.tv_sec - m_start.tv_sec) + 
      float(static_cast<float>(now.tv_usec - m_start.tv_usec)/1e6);
  }

  string str() const
  {
    std::stringstream buffer;
    buffer << this->elapsed_no_reset() << "s";
    return buffer.str();
  }

  void reset()
  {
    timeval now;
    gettimeofday(&now,0);
    m_start = now;
  }
  
private:
  timeval  m_start;
};

std::ostream& operator<<(std::ostream& out, const Timer& obj)
{
  out << obj.str();
  return out;
}

class CPUTimer
{
public:
  CPUTimer()
  {
    this->reset();
  }

  ~CPUTimer() {}

  float elapsed(bool doReset=true)
  {
    float retval = 0;
    clock_t end = clock();
    retval = ((float)(end - m_start)) / CLOCKS_PER_SEC;
    if (doReset) this->reset();

    return retval;
  }

  void reset()
  {
    m_start = clock();
    m_wallClockTime.reset();
  }

  float CPUfraction(bool doReset=true)
  {
    // Get the wall-clock time without resetting.
    double wallTime = m_wallClockTime.elapsed(false);
    double cpuTime = elapsed(false);
    if (doReset) this->reset();
    return static_cast<float>((cpuTime / wallTime));
  }

  string str()
  {
    std::stringstream buffer;
    buffer << std::fixed  << std::setw(7) << std::setprecision(4)
	   << m_wallClockTime << ", CPU " << std::setprecision(2)
	   << this->CPUfraction(false);
    this->reset();
    return buffer.str();
  }

private:
  clock_t m_start;
  Timer m_wallClockTime;

};

std::ostream& operator<<(std::ostream& out, CPUTimer& obj)
{
  out << obj.str();
  return out;
}

int main ()
{
  int i,n;
  char * buffer;

  printf ("How long do you want the string? ");
  scanf ("%d", &i);

  buffer = (char*) malloc (i+1);
  if (buffer==NULL) exit (1);

  for (n=0; n<i; n++)
    buffer[n]=rand()%26+'a';
  buffer[i]='\0';

  printf ("Random string: %s\n",buffer);
  free (buffer);

  return 0;
}
