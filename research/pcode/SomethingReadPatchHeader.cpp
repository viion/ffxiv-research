byte __thiscall SomethingReadPatchHeader(FileWrapper *this, byte *lpBuffer
  , size_t numBytesToRead, int *bytesReadOutArg, unsigned __int64 readAt)
{
  bool hasFileBuffer; // zf@1

  unsigned __int64 fileReadPos; // rax@2
  unsigned __int64 newFilePos; // kr08_8@3
  byte *v11; // eax@11
  int newCache; // eax@13
  byte fileReadResult; // al@15
  int v14; // ecx@15
  int bytesReadOut; // [sp+Ch] [bp-8h]@15
  size_t bytesRead; // [sp+10h] [bp-4h]@1 MAPDST
  bool readResult; // [sp+2Fh] [bp+1Bh]@5

  bytesRead = 0;
  if ( this->fileCacheBuffer == nullptr )
  {
    readResult = ReadFileAt(this, lpBuffer, numBytesToRead, &bytesRead, readAt);
    goto ProcessData;
  }

  fileReadPos = this->fileReadPos;
  if ( readAt >= fileReadPos )              // if arg pos is greater
  {
    newFilePos = fileReadPos + *&this->bytesRead;
    if ( readAt < newFilePos && readAt + numBytesToRead <= newFilePos )
    {
      // just copy from the object buffer
      readResult = 1;
copyData:
      memcpy(lpBuffer, &this->fileCacheBuffer[readAt - LODWORD(this->fileReadPos)], numBytesToRead);
      bytesRead = numBytesToRead;
ProcessData:
      if ( bytesReadOutArg )
        *bytesReadOutArg = bytesRead;
      if ( readResult )
      {
        *&this->field_90 += bytesRead;
        if ( bytesRead )
          ComputeCRC32(&this->hash, lpBuffer, bytesRead);
      }
      return readResult;
    }
  }
  if ( readAt < this->fileSize )
  {
    if ( numBytesToRead > this->cacheSize )      // something
    {
      this->cacheSize = numBytesToRead;
      free(this->fileCacheBuffer);
      v11 = malloc(this->cacheSize);
      this->fileCacheBuffer = v11;
      if ( !v11 )
      {
        sub_452440(20885);
        return 0;
      }
    }
    newCache = this->cacheSize;
    if ( readAt + this->cacheSize > this->fileSize )
      newCache = LODWORD(this->fileSize) - readAt;
    fileReadResult = ReadFileAt(this, this->fileCacheBuffer, newCache, &bytesReadOut, readAt);
    BYTE7(readAt) = fileReadResult;
    this->fileReadPos = readAt;
    this->bytesRead = bytesReadOut;
    this->field_84 = 0;
    if ( !fileReadResult )
      return readResult;
    goto copyData;
  }
  if ( bytesReadOutArg )
    *bytesReadOutArg = 0;
  return 1;
}
