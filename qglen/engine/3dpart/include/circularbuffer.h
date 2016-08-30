#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H


class CircularBuffer
{
public:
  CircularBuffer(unsigned int capacity);
  ~CircularBuffer();

  unsigned int getSize() const { return m_iSize; }
  unsigned int getCapacity() const { return m_iCapacity; }
  // Return number of bytes written.
  unsigned int Write(const char *data, unsigned int size);
  // Return number of bytes read.
  unsigned int Read(char *data, unsigned int size);

private:
  unsigned int m_iBegIndex;
  unsigned int m_iEndIndex;
  unsigned int m_iSize;
  unsigned int m_iCapacity;

  char *m_pData_;
};


#endif // CIRCULARBUFFER_H
