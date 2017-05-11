char __thiscall CallReadHeaderFile_3(PatchFile *this, char *patchFilePath, void *funcPtr)
{
  LARGE_INTEGER *v5; // ebx@1
  int *v6; // ecx@1
  int v7; // eax@1
  char result; // al@3
  FileWrapper *v10; // ecx@6
  LONGLONG v11; // kr08_8@8
  int v12; // ecx@8
  int v13; // eax@30
  char *entryStr; // edx@34
  unsigned int entryStrLen; // ecx@34
  char *v16; // esi@34
  signed int v17; // eax@38
  char *sqpkStr; // edx@46
  unsigned int sqpkStrLen; // ecx@46
  char *v20; // esi@46
  signed int v21; // eax@50
  char *addDirStr; // edx@60
  unsigned int addDirStrLen; // ecx@60
  char *v24; // esi@60
  signed int v25; // eax@64
  char *deleteStr; // edx@74
  unsigned int deleteStrLen; // ecx@74
  char *v28; // esi@74
  signed int v29; // eax@78
  char *applyStr; // edx@88
  unsigned int applyStrLen; // ecx@88
  char *v32; // esi@88
  signed int v33; // eax@92
  char *eofStr; // edx@112
  unsigned int eofStrLen; // ecx@112
  char *v36; // esi@112
  signed int v37; // eax@116
  PatchFile *v38; // esi@124
  unsigned int v39; // ebx@124
  signed int v40; // edi@125
  char v41; // bl@144
  LONGLONG v42; // kr10_8@147
  DWORD v43; // eax@147
  unsigned __int64 v44; // kr18_8@147
  int v45; // esi@147
  char *v46; // [sp+Ch] [bp-8CCh]@8
  int bytesRead; // [sp+10h] [bp-8C8h]@1
  int v48; // [sp+14h] [bp-8C4h]@4
  char v49; // [sp+1Ah] [bp-8BEh]@6
  char v50; // [sp+1Bh] [bp-8BDh]@1
  std::string v52; // [sp+20h] [bp-8B8h]@10
  unsigned int data; // [sp+3Ch] [bp-89Ch]@33
  char v54; // [sp+40h] [bp-898h]@34
  byte Buffer[4]; // [sp+44h] [bp-894h]@10
  char v56; // [sp+844h] [bp-94h]@100
  __int64 v57; // [sp+8C4h] [bp-14h]@8
  unsigned __int64 v58; // [sp+8CCh] [bp-Ch]@8

  sub_44F7A0(patchFilePath);
  this->field_198 = a3;
  sub_44D620(&this->gapFC[4]);
  sub_455F30(&this->gapFC[88]);
  ResetHash(&this->gapFC[96]);
  this->field_170 = 0;
  this->field_174 = 0;
  this->field_178 = 0;
  this->field_17C = 0;
  v5 = &this->field_180;
  v5->LowPart = 0;
  v5->HighPart = 0;
  this->field_188 = 0;
  this->field_18C = 0;
  this->field_190 = 0;
  this->field_194 = 0;
  v6 = this->field_88;
  bytesRead = 0;
  v7 = *v6;
  v50 = 0;
  (*(v7 + 4))(0);
  if ( !CallReadHeaderFile_2(this, patchFilePath, a3) )
  {
    (*(*this->field_90 + 4))(0);
    return 0;
  }
  v48 = 0;
  if ( a3 )
    v48 = a3;
  v10 = &this->hPatchFile;
  v49 = 0;
  this->field_188 = 0;
  this->field_18C = 0;
  LODWORD(this->fileReadPos) = 0;
  HIDWORD(this->fileReadPos) = 0;
  if ( !CreateFileWrapper(v10, patchFilePath, &off_4A75C7 + 1, 0) )
  {
    IpcHandleError(20639);
    goto LABEL_142;
  }
  GetFileSizeWrapper(v5);
  v46 = &this->fileSize;
  GetFileSizeWrapper(&this->fileSize);
  v11 = this->fileSize.QuadPart + this->field_2B0.QuadPart;
  LODWORD(v58) = this->fileSize.LowPart + this->field_2B0.LowPart;
  v12 = this->field_68;
  HIDWORD(v58) = HIDWORD(v11);
  _mm_storel_pd(&v57, 0i64);
  if ( (*(*v12 + 4))(&v57) )
  {
    IpcHandleError(20876);
    goto LABEL_142;
  }
  v52.capacity = 15;
  v52.length? = 0;
  LOBYTE(v52.data) = 0;
  std::string::append_(&v52, ZIPATCH_SIG_REF[0], strlen(ZIPATCH_SIG_REF[0]));
  if ( !ReadPatchFile(this, Buffer, v52.length?, &bytesRead) )
  {
    IpcHandleError(20628);
    if ( v52.capacity >= 0x10u )
      operator delete(v52.data);
    goto LABEL_142;
  }
  if ( bytesRead != v52.length? )
  {
    sub_452C50(20628);
LABEL_15:
    if ( v52.capacity >= 0x10u )
      operator delete(v52.data);
    goto LABEL_142;
  }
  if ( std::string::replace(&v52, 0, v52.length?, Buffer, bytesRead) )
  {
    IpcHandleError(20629);
    ClosePatchFile_(this);
    if ( v52.capacity >= 0x10u )
      operator delete(v52.data);
    goto LABEL_142;
  }
  if ( !SomethingBigToLittle2(this) )
  {
    if ( IpcUnknown3() )
      IpcHandleError(20630);
    goto LABEL_15;
  }
  if ( !SomethingSecondHeaderRead3(this) )
  {
    if ( IpcUnknown3() )
      IpcHandleError(20703);
LABEL_26:
    sub_40E030(&v52);
    goto LABEL_142;
  }
  if ( !sub_441E10(this) )
  {
    if ( IpcUnknown3() )
      IpcHandleError(20651);
    goto LABEL_26;
  }
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          _Thrd_yield();
          v13 = v48;
          if ( v48 && _InterlockedExchangeAdd((v48 + 4), 0) == 1 && _InterlockedCompareExchange((v13 + 4), 2, 1) == 1 )
          {
            v49 = 1;
            goto LABEL_139;
          }
          if ( !ReadUInt32LE(this, &data) )
          {
            if ( IpcGetStatus_() == 20654 )
            {
              IpcUnknown2();
              v50 = 1;
            }
            else
            {
              IpcHandleError(20652);
            }
            goto LABEL_139;
          }
          entryStr = ENTRY_REF[0];
          entryStrLen = strlen(ENTRY_REF[0]);
          v16 = &v54;
          if ( entryStrLen < 4 )
          {
LABEL_37:
            if ( !entryStrLen )
              goto LABEL_107;
          }
          else
          {
            while ( *v16 == *entryStr )
            {
              entryStrLen -= 4;
              entryStr += 4;
              v16 += 4;
              if ( entryStrLen < 4 )
                goto LABEL_37;
            }
          }
          v17 = *v16 - *entryStr;
          if ( *v16 == *entryStr )
          {
            if ( entryStrLen <= 1 )
              goto LABEL_107;
            v17 = v16[1] - entryStr[1];
            if ( v16[1] == entryStr[1] )
            {
              if ( entryStrLen <= 2 )
                goto LABEL_107;
              v17 = v16[2] - entryStr[2];
              if ( v16[2] == entryStr[2] )
              {
                if ( entryStrLen <= 3 )
                  goto LABEL_107;
                v17 = v16[3] - entryStr[3];
              }
            }
          }
          if ( !((v17 >> 31) | 1) )
            goto LABEL_107;
          sqpkStr = SQPK_REF[0];
          sqpkStrLen = strlen(SQPK_REF[0]);
          v20 = &v54;
          if ( sqpkStrLen < 4 )
          {
LABEL_49:
            if ( !sqpkStrLen )
              goto LABEL_58;
          }
          else
          {
            while ( *v20 == *sqpkStr )
            {
              sqpkStrLen -= 4;
              sqpkStr += 4;
              v20 += 4;
              if ( sqpkStrLen < 4 )
                goto LABEL_49;
            }
          }
          v21 = *v20 - *sqpkStr;
          if ( *v20 != *sqpkStr )
            goto LABEL_57;
          if ( sqpkStrLen > 1 )
          {
            v21 = v20[1] - sqpkStr[1];
            if ( v20[1] != sqpkStr[1] )
              goto LABEL_57;
            if ( sqpkStrLen > 2 )
            {
              v21 = v20[2] - sqpkStr[2];
              if ( v20[2] != sqpkStr[2] )
                goto LABEL_57;
              if ( sqpkStrLen > 3 )
                break;
            }
          }
LABEL_58:
          if ( !SomethingCallWriteFile4(this, data) )
          {
            if ( IpcUnknown3() )
LABEL_107:
              IpcHandleError(20638);
            goto LABEL_139;
          }
        }
        v21 = v20[3] - sqpkStr[3];
LABEL_57:
        if ( !((v21 >> 31) | 1) )
          goto LABEL_58;
        addDirStr = ADD_DIR_REF[0];
        addDirStrLen = strlen(ADD_DIR_REF[0]);
        v24 = &v54;
        if ( addDirStrLen < 4 )
        {
LABEL_63:
          if ( !addDirStrLen )
            goto LABEL_72;
        }
        else
        {
          while ( *v24 == *addDirStr )
          {
            addDirStrLen -= 4;
            addDirStr += 4;
            v24 += 4;
            if ( addDirStrLen < 4 )
              goto LABEL_63;
          }
        }
        v25 = *v24 - *addDirStr;
        if ( *v24 != *addDirStr )
          goto LABEL_71;
        if ( addDirStrLen > 1 )
        {
          v25 = v24[1] - addDirStr[1];
          if ( v24[1] != addDirStr[1] )
            goto LABEL_71;
          if ( addDirStrLen > 2 )
          {
            v25 = v24[2] - addDirStr[2];
            if ( v24[2] != addDirStr[2] )
              goto LABEL_71;
            if ( addDirStrLen > 3 )
              break;
          }
        }
LABEL_72:
        if ( !sub_441320(this, data) )
        {
          if ( IpcUnknown3() )
            IpcHandleError(20704);
          goto LABEL_139;
        }
      }
      v25 = v24[3] - addDirStr[3];
LABEL_71:
      if ( !((v25 >> 31) | 1) )
        goto LABEL_72;
      deleteStr = DELETE_REF[0];
      deleteStrLen = strlen(DELETE_REF[0]);
      v28 = &v54;
      if ( deleteStrLen < 4 )
      {
LABEL_77:
        if ( !deleteStrLen )
          goto LABEL_86;
      }
      else
      {
        while ( *v28 == *deleteStr )
        {
          deleteStrLen -= 4;
          deleteStr += 4;
          v28 += 4;
          if ( deleteStrLen < 4 )
            goto LABEL_77;
        }
      }
      v29 = *v28 - *deleteStr;
      if ( *v28 != *deleteStr )
        goto LABEL_85;
      if ( deleteStrLen > 1 )
      {
        v29 = v28[1] - deleteStr[1];
        if ( v28[1] != deleteStr[1] )
          goto LABEL_85;
        if ( deleteStrLen > 2 )
        {
          v29 = v28[2] - deleteStr[2];
          if ( v28[2] != deleteStr[2] )
            goto LABEL_85;
          if ( deleteStrLen > 3 )
            break;
        }
      }
LABEL_86:
      if ( !sub_441470(this, data) )
      {
        if ( IpcUnknown3() )
          IpcHandleError(20705);
        goto LABEL_139;
      }
    }
    v29 = v28[3] - deleteStr[3];
LABEL_85:
    if ( !((v29 >> 31) | 1) )
      goto LABEL_86;
    applyStr = APPLY_REF[0];
    applyStrLen = strlen(APPLY_REF[0]);
    v32 = &v54;
    if ( applyStrLen < 4 )
    {
LABEL_91:
      if ( !applyStrLen )
        goto LABEL_100;
    }
    else
    {
      while ( *v32 == *applyStr )
      {
        applyStrLen -= 4;
        applyStr += 4;
        v32 += 4;
        if ( applyStrLen < 4 )
          goto LABEL_91;
      }
    }
    v33 = *v32 - *applyStr;
    if ( *v32 != *applyStr )
      goto LABEL_99;
    if ( applyStrLen > 1 )
    {
      v33 = v32[1] - applyStr[1];
      if ( v32[1] != applyStr[1] )
        goto LABEL_99;
      if ( applyStrLen > 2 )
      {
        v33 = v32[2] - applyStr[2];
        if ( v32[2] != applyStr[2] )
          goto LABEL_99;
        if ( applyStrLen > 3 )
          break;
      }
    }
LABEL_100:
    if ( !sub_440F90(&v56, data + 4) )
    {
      IpcHandleError(20645);
      (*(*this->field_90 + 4))(0);
      sub_40E030(&v52);
      return 0;
    }
  }
  v33 = v32[3] - applyStr[3];
LABEL_99:
  if ( !((v33 >> 31) | 1) )
    goto LABEL_100;
  eofStr = EOF_REF[0];
  eofStrLen = strlen(EOF_REF[0]);
  v36 = &v54;
  if ( eofStrLen < 4 )
  {
LABEL_115:
    if ( eofStrLen )
      goto LABEL_116;
    goto LABEL_124;
  }
  while ( *v36 == *eofStr )
  {
    eofStrLen -= 4;
    eofStr += 4;
    v36 += 4;
    if ( eofStrLen < 4 )
      goto LABEL_115;
  }
LABEL_116:
  v37 = *v36 - *eofStr;
  if ( *v36 == *eofStr )
  {
    if ( eofStrLen > 1 )
    {
      v37 = v36[1] - eofStr[1];
      if ( v36[1] != eofStr[1] )
        goto LABEL_123;
      if ( eofStrLen > 2 )
      {
        v37 = v36[2] - eofStr[2];
        if ( v36[2] != eofStr[2] )
          goto LABEL_123;
        if ( eofStrLen > 3 )
        {
          v37 = v36[3] - eofStr[3];
          goto LABEL_123;
        }
      }
    }
LABEL_124:
    v38 = this;
    v50 = 1;
    v39 = data;
    if ( data )
    {
      while ( 1 )
      {
        v40 = 10;
        if ( v39 <= 0xA )
          v40 = v39;
        if ( !sub_440F90(&v57 + 4, v40) )
          break;
        v39 -= v40;
        if ( !v39 )
          goto LABEL_129;
      }
      IpcHandleError(20645);
      ClosePatchFile_(v38);
      (*(*v38->field_90 + 4))(0);
      sub_40E030(&v52);
      return 0;
    }
LABEL_129:
    if ( !sub_441270(v38) )
    {
      IpcHandleError(20641);
LABEL_131:
      ClosePatchFile_(v38);
      (*(*v38->field_90 + 4))(v38->field_90, 0);
      sub_40E030(&v52);
      goto LABEL_132;
    }
    if ( v38->field_188 != *v46 )
    {
LABEL_137:
      IpcHandleError(20879);
      goto LABEL_131;
    }
    if ( v38->field_18C != *(v46 + 1) )
    {
      v38 = this;
      goto LABEL_137;
    }
  }
  else
  {
LABEL_123:
    if ( !((v37 >> 31) | 1) )
      goto LABEL_124;
    sub_452C50(20644);
  }
LABEL_139:
  sub_455F30(&this->hPatchFile);
  if ( v49 )
    goto LABEL_26;
  if ( v52.capacity >= 0x10u )
    operator delete(v52.data);
LABEL_142:
  if ( (*(*this->field_90 + 4))(0) || v49 )
    return 0;
  v41 = v50;
  if ( !v50 )
  {
    sub_455F30(&this->hPatchFile);
    if ( IpcUnknown3() )
      sub_452C50(20600);
  }
  v42 = *&this->field_188 + this->field_2B8.QuadPart;
  v43 = this->field_2B0.LowPart;
  LODWORD(v57) = this->field_188 + this->field_2B8.LowPart;
  v44 = this->fileSize.QuadPart + __PAIR__(this->field_2B0.HighPart, v43);
  v45 = this->field_68;
  HIDWORD(v57) = HIDWORD(v42);
  v58 = v44;
  if ( (*(*v45 + 4))(v45, &v57) )
  {
    IpcHandleError(20876);
LABEL_132:
    result = 0;
  }
  else
  {
    result = v41;
  }
  return result;
}
