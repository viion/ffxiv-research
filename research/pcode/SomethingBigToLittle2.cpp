// parse something
char __thiscall SomethingBigToLittle2(PatchFile *this)
{
  char *fhdrStr; // edx@3
  unsigned int fhdrStrLen; // ecx@3
  char *v5; // esi@3
  signed int v6; // eax@7
  byte v8; // al@24
  int bytesRead; // [sp+4h] [bp-104h]@18
  byte Buffer[4]; // [sp+8h] [bp-100h]@18
  int v11; // [sp+Ch] [bp-FCh]@18
  int v12; // [sp+10h] [bp-F8h]@18
  int v13; // [sp+14h] [bp-F4h]@18
  int v14; // [sp+18h] [bp-F0h]@18
  size_t readLength; // [sp+FCh] [bp-Ch]@1 MAPDST
  char v16; // [sp+100h] [bp-8h]@3

  if ( !ReadUInt32LE(this, &readLength) )
  {
    IpcHandleError(20652);
    return 0;
  }
  fhdrStr = FHDR_REF[0];
  fhdrStrLen = strlen(FHDR_REF[0]);
  v5 = &v16;
  if ( fhdrStrLen < 4 )
  {
LABEL_6:
    if ( !fhdrStrLen )
      goto LABEL_16;
  }
  else
  {
    while ( *v5 == *fhdrStr )
    {
      fhdrStrLen -= 4;
      fhdrStr += 4;
      v5 += 4;
      if ( fhdrStrLen < 4 )
        goto LABEL_6;
    }
  }
  v6 = *v5 - *fhdrStr;
  if ( *v5 == *fhdrStr )
  {
    if ( fhdrStrLen <= 1 )
      goto LABEL_16;
    v6 = v5[1] - fhdrStr[1];
    if ( v5[1] == fhdrStr[1] )
    {
      if ( fhdrStrLen <= 2 )
        goto LABEL_16;
      v6 = v5[2] - fhdrStr[2];
      if ( v5[2] == fhdrStr[2] )
      {
        if ( fhdrStrLen <= 3 )
          goto LABEL_16;
        v6 = v5[3] - fhdrStr[3];
      }
    }
  }
  if ( (v6 >> 31) | 1 )
  {
    IpcSendUnknown(20644);
    return 0;
  }
LABEL_16:
  if ( readLength > 0xF4 )
  {
    IpcSendUnknown(20712);
    return 0;
  }
  *Buffer = 0;
  v12 = 0;
  v11 = 0;
  v13 = 0;
  v14 = 0;
  bytesRead = 0;
  if ( !ReadPatchFile(this, Buffer, readLength, &bytesRead) )
  {
LABEL_21:
    IpcHandleError(20645);
    return 0;
  }
  if ( bytesRead != readLength )
  {
    IpcHandleError(20600);
    ClosePatchFile_(this);
    goto LABEL_21;
  }
  if ( sub_441270(this) )
  {
    SomethingBigToLittle(Buffer);
    qmemcpy(this->Data1, Buffer, sizeof(this->Data1));
    v8 = this->Data1[2];
    if ( v8 && v8 <= 3u )
    {
      this->field_290 = sub_44D130(this->Data1[2]);
      IpcUnknown2();
      if ( (*(*this->field_8 + 4))(&this->field_98, Buffer, this->field_198) != -1 )
        return 1;
      if ( !sub_452850() )
        IpcHandleError(20631);
    }
    else
    {
      IpcSendUnknown(20696);
    }
  }
  else
  {
    IpcHandleError(20641);
  }
  return 0;
}
