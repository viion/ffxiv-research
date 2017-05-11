char __thiscall CallReadHeaderFile_2(PatchFile *this, int a2, int a3)
{
  FileWrapper *hPatchFile; // esi@1
  char v5; // bl@1
  char *v6; // edx@22
  unsigned int v7; // ecx@22
  char *v8; // esi@22
  signed int v9; // eax@26
  LONG v10; // edx@43
  FileWrapper *v12; // [sp+Ch] [bp-838h]@1
  size_t bytesRead; // [sp+10h] [bp-834h]@1
  int v14; // [sp+14h] [bp-830h]@20
  char v15; // [sp+1Bh] [bp-829h]@1
  unsigned int data; // [sp+1Ch] [bp-828h]@21
  char v17; // [sp+20h] [bp-824h]@22
  std::string zipatchSigStr; // [sp+24h] [bp-820h]@3
  byte *buffer; // [sp+40h] [bp-804h]@3
  char v20; // [sp+44h] [bp-800h]@35
  DWORD v21; // [sp+50h] [bp-7F4h]@43
  LONG v22; // [sp+54h] [bp-7F0h]@43

  hPatchFile = &this->hPatchFile;
  bytesRead = 0;
  this->field_188 = 0;
  this->field_18C = 0;
  this->fileReadPos = 0i64;
  v5 = 1;
  v15 = 1;
  v12 = &this->hPatchFile;
  if ( !CreateFileWrapper(&this->hPatchFile, a2, &off_4A75C3 + 1, 0) )
  {
    IpcHandleError(20639);
    v5 = 0;
    goto FAIL;
  }
  GetFileSizeWrapper(&hPatchFile->fileSize);
  GetFileSizeWrapper(&this->fileSize);
  zipatchSigStr.capacity = 15;
  zipatchSigStr.length? = 0;
  LOBYTE(zipatchSigStr.data) = 0;
  std::string::append_(&zipatchSigStr, ZIPATCH_SIG_REF[0], strlen(ZIPATCH_SIG_REF[0]));
  if ( !ReadPatchFile(this, &buffer, zipatchSigStr.length?, &bytesRead) )
  {
    IpcHandleError(20628);
    v5 = 0;
    if ( zipatchSigStr.capacity >= 0x10u )
      operator delete(zipatchSigStr.data);
    goto FAIL;
  }
  if ( bytesRead != zipatchSigStr.length? )
  {
    IpcSendUnknown(20628);
    v5 = 0;
    if ( zipatchSigStr.capacity >= 0x10u )
      operator delete(zipatchSigStr.data);
    goto FAIL;
  }
  if ( std::string::replace(&zipatchSigStr, 0, zipatchSigStr.length?, &buffer, bytesRead) )
  {
    IpcHandleError(20629);
    v5 = 0;
    ClosePatchFile_(this);
    goto FAIL2;
  }
  if ( !SomethingBigToLittle2(this) )
  {
    if ( IpcUnknown3() )
    {
      IpcHandleError(20630);
      goto FAIL2;
    }
LABEL_45:
    v5 = 0;
    goto FAIL2;
  }
  if ( !SomethingSecondHeaderRead3(this) )
  {
    if ( IpcUnknown3() )
    {
      IpcHandleError(20703);
      goto FAIL2;
    }
    goto LABEL_45;
  }
  if ( !sub_441E10(this) )
  {
    if ( IpcUnknown3() )
    {
      IpcHandleError(20651);
      goto FAIL2;
    }
    goto LABEL_45;
  }
  v14 = 0;
  while ( ReadUInt32LE(this, &data) )
  {
    v6 = SQPK_REF[0];
    v7 = strlen(SQPK_REF[0]);
    v8 = &v17;
    if ( v7 < 4 )
    {
LABEL_25:
      if ( !v7 )
        goto LABEL_34;
    }
    else
    {
      while ( *v8 == *v6 )
      {
        v7 -= 4;
        v6 += 4;
        v8 += 4;
        if ( v7 < 4 )
          goto LABEL_25;
      }
    }
    v9 = *v8 - *v6;
    if ( *v8 != *v6 )
      goto LABEL_33;
    if ( v7 > 1 )
    {
      v9 = v8[1] - v6[1];
      if ( v8[1] != v6[1] )
        goto LABEL_33;
      if ( v7 > 2 )
      {
        v9 = v8[2] - v6[2];
        if ( v8[2] != v6[2] )
          goto LABEL_33;
        if ( v7 > 3 )
        {
          v9 = v8[3] - v6[3];
LABEL_33:
          if ( (v9 >> 31) | 1 )
            goto LABEL_37;
          goto LABEL_34;
        }
      }
    }
LABEL_34:
    if ( !sub_440F90(&buffer, data) )
    {
      IpcHandleError(20645);
      goto LABEL_45;
    }
    sub_4405E0(&buffer);
    if ( v20 == 84 )
    {
      v10 = v22;
      v5 = v15;
      this->field_2B0.LowPart = v21;
      this->field_2B0.HighPart = v10;
      goto FAIL2;
    }
    if ( !sub_441270(this) )
    {
      IpcHandleError(20641);
      goto LABEL_45;
    }
LABEL_37:
    v5 = v15;
    if ( ++v14 >= 2 )
      goto FAIL2;
  }
  if ( IpcGetStatus_() == 20654 )
    IpcUnknown2();
  else
    IpcHandleError(20652);
FAIL2:
  sub_40E030(&zipatchSigStr);
FAIL:
  this->field_188 = 0;
  this->field_18C = 0;
  sub_455F30(v12);
  return v5;
}
