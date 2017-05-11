byte __thiscall ReadBufferedFile(FileWrapper *this, byte *lpBuffer, size_t numBytesToRead, int *bytesReadBuf, unsigned __int64 readAt)
{
  bool hasFileBuffer; // zf@1
  int readAtHi; // ebx@2
  unsigned __int64 fileReadPosCopy; // rax@2
  unsigned __int64 newFilePos; // kr08_8@3
  byte *v11; // eax@11
  int newCacheBuf; // eax@13
  byte fileReadResult; // al@15
  int v14; // ecx@15
  int bytesReadOut; // [sp+Ch] [bp-8h]@15
  size_t bytesRead; // [sp+10h] [bp-4h]@1 MAPDST
  bool readResult; // [sp+2Fh] [bp+1Bh]@5

  hasFileBuffer = this->fileCacheBuffer == 0;   // null check for file buffer
  bytesRead = 0;
  if ( hasFileBuffer )
  {
    readResult = ReadFileAt(this, lpBuffer, numBytesToRead, &bytesRead, readAt);
    goto LABEL_18;
  }
  HIDWORD(fileReadPosCopy) = HIDWORD(this->fileReadPos);
  readAtHi = HIDWORD(readAt);
  LODWORD(fileReadPosCopy) = this->fileReadPos;
  if ( readAt >= fileReadPosCopy )              // if arg pos is greater
  {
    newFilePos = fileReadPosCopy + *&this->cacheOffset;
    if ( readAt < newFilePos && readAt + numBytesToRead <= newFilePos )
    {
      // just copy from the object buffer
      readResult = 1;
copyData:
      memcpy(lpBuffer, &this->fileCacheBuffer[readAt - LODWORD(this->fileReadPos)], numBytesToRead);
      bytesRead = numBytesToRead;
      bytesRead = numBytesToRead;
LABEL_18:
      if ( bytesReadBuf )
        *bytesReadBuf = bytesRead;
      if ( readResult )
      {
        *&this->field_90 += bytesRead;
        if ( bytesRead )
          UpdateCrc32(&this->hash, lpBuffer, bytesRead);
      }
      return readResult;
    }
  }
  if ( readAt < this->fileSize )
  {
    if ( numBytesToRead > this->cacheSize )     // something
    {
      this->cacheSize = numBytesToRead;
      free(this->fileCacheBuffer);
      v11 = malloc(this->cacheSize);
      this->fileCacheBuffer = v11;
      if ( !v11 )
      {
        IpcHandleError(20885);
        return 0;
      }
    }
    newCacheBuf = this->cacheSize;
    if ( readAt + this->cacheSize > this->fileSize )
      newCacheBuf = LODWORD(this->fileSize) - readAt;
    fileReadResult = ReadFileAt(this, this->fileCacheBuffer, newCacheBuf, &bytesReadOut, readAt);
    v14 = bytesReadOut;
    BYTE7(readAt) = fileReadResult;
    LODWORD(this->fileReadPos) = readAt;
    HIDWORD(this->fileReadPos) = readAtHi;
    this->cacheOffset = v14;
    this->field_84 = 0;
    if ( !fileReadResult )
      return readResult;
    goto copyData;
  }
  if ( bytesReadBuf )
    *bytesReadBuf = 0;
  return 1;
}
