// inlined function
int __cdecl SomethingWithCrc(size_t bufLen)
{
  int thisHash; // eax@0
  _BYTE *buffer; // ecx@0 passed by ecx
  unsigned int crc; // eax@1
  unsigned int v5; // edi@5
  unsigned int v6; // edx@6
  unsigned int v7; // eax@6
  unsigned int v8; // edx@6
  unsigned int v9; // eax@6
  unsigned int v10; // edx@6
  unsigned int v11; // eax@6
  unsigned int v12; // edx@6
  unsigned int v13; // edx@8
  unsigned int v14; // eax@9
  crc = ~thisHash
  for ( ; bufLen; --bufLen )
  {
    if ( !(buffer & 3) )
      break;
    crc = CRC32_m_tab_1[(crc ^ *buffer++)] ^ (crc >> 8);
  }
  if ( bufLen >= 0x20 )
  {
    v5 = bufLen >> 5;
    do
    {
      v6 = *(buffer + 1) ^ dword_4AE1A0[(*buffer ^ crc) & 0xFF] ^ CRC32_m_tab_1[(*buffer ^ crc) >> 24] ^ dword_4ADDA0[(*buffer ^ crc) >> 8] ^ dword_4AD9A0[((*buffer ^ crc) >> 16) & 0xFF];
      v7 = *(buffer + 2) ^ dword_4AE1A0[v6] ^ CRC32_m_tab_1[v6 >> 24] ^ dword_4ADDA0[v6 >> 8] ^ dword_4AD9A0[(v6 >> 16) & 0xFF];
      v8 = *(buffer + 3) ^ dword_4AE1A0[v7] ^ CRC32_m_tab_1[v7 >> 24] ^ dword_4ADDA0[v7 >> 8] ^ dword_4AD9A0[(v7 >> 16) & 0xFF];
      v9 = *(buffer + 4) ^ dword_4AE1A0[v8] ^ CRC32_m_tab_1[v8 >> 24] ^ dword_4ADDA0[v8 >> 8] ^ dword_4AD9A0[(v8 >> 16) & 0xFF];
      v10 = *(buffer + 5) ^ dword_4AE1A0[v9] ^ CRC32_m_tab_1[v9 >> 24] ^ dword_4ADDA0[v9 >> 8] ^ dword_4AD9A0[(v9 >> 16) & 0xFF];
      buffer += 32;
      v11 = *(buffer - 2) ^ dword_4AE1A0[v10] ^ CRC32_m_tab_1[v10 >> 24] ^ dword_4ADDA0[v10 >> 8] ^ dword_4AD9A0[(v10 >> 16) & 0xFF];
      bufLen -= 32;
      v12 = *(buffer - 1) ^ dword_4AE1A0[v11] ^ CRC32_m_tab_1[v11 >> 24] ^ dword_4ADDA0[v11 >> 8] ^ dword_4AD9A0[(v11 >> 16) & 0xFF];
      crc = dword_4AE1A0[v12] ^ CRC32_m_tab_1[v12 >> 24] ^ dword_4ADDA0[v12 >> 8] ^ dword_4AD9A0[(v12 >> 16) & 0xFF];
      --v5;
    }
    while ( v5 );
  }
  if ( bufLen >= 4 )
  {
    v13 = bufLen >> 2;
    do
    {
      v14 = *buffer ^ crc;
      buffer += 4;
      bufLen -= 4;
      --v13;
      crc = dword_4AE1A0[v14] ^ CRC32_m_tab_1[v14 >> 24] ^ dword_4ADDA0[v14 >> 8] ^ dword_4AD9A0[(v14 >> 16) & 0xFF];
    }
    while ( v13 );
  }
  for ( ; bufLen; --bufLen )
    crc = CRC32_m_tab_1[(crc ^ *buffer++)] ^ (crc >> 8);
  return ~crc;
}
