byte __thiscall ReadPatchFile(PatchFile *this, byte *lpBuffer, size_t readLength, size_t *bytesRead)
{
  unsigned __int8 v6; // cf@1
  DWORD v7; // edx@1
  DWORD v8; // ecx@1
  byte result; // al@2 MAPDST
  unsigned __int64 v11; // [sp+Ch] [bp-10h]@1
  unsigned __int64 v12; // [sp+14h] [bp-8h]@1

  result = (this->hPatchFile->ReadBufferedFile)(
             &this->hPatchFile,
             lpBuffer,
             readLength,
             bytesRead,
             this->fileReadPos,
             HIDWORD(this->fileReadPos));
  v6 = __CFADD__(*bytesRead, this->fileReadPos);
  LODWORD(this->fileReadPos) += *bytesRead;
  v7 = this->field_2B8.LowPart;
  v8 = this->field_2B0.LowPart;
  HIDWORD(this->fileReadPos) += v6;             // advance file pos
  v11 = *&this->field_188 + __PAIR__(this->field_2B8.HighPart, v7);
  v12 = this->fileSize.QuadPart + __PAIR__(this->field_2B0.HighPart, v8);
  if ( (*(*this->field_68 + 4))(&v11) )
  {
    IpcHandleError(20876);
    result = 0;
  }
  return result;
}
