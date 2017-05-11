bool __thiscall ReadUInt32LE(PatchFile *this, unsigned int *data)
{
  bool result; // al@2
  int bytesRead; // [sp+8h] [bp-4h]@1

  bytesRead = 0;
  if ( ReadPatchFile(this, data, 4u, &bytesRead) )
  {
    if ( bytesRead )
    {
      if ( bytesRead == 4 )                     // if read 4bytes
      {
        ResetFileHash(&this->hPatchFile);
        if ( ReadPatchFile(this, data + 4, 4u, &bytesRead) )
        {
          if ( bytesRead == 4 )
          {
            *data = ntohl(*data);
            result = 1;
          }
          else
          {
            IpcSendUnknown(20600);
            IpcHandleError(20647);
            result = 0;
          }
        }
        else
        {
          IpcHandleError(20647);
          result = 0;
        }
      }
      else
      {
        IpcSendUnknown(20600);
        IpcHandleError(20646);
        ClosePatchFile_(this);
        result = 0;
      }
    }
    else
    {
      IpcSendUnknown(20654);
      result = 0;
    }
  }
  else
  {
    IpcHandleError(20878);
    ClosePatchFile_(this);
    result = 0;
  }
  return result;
}
