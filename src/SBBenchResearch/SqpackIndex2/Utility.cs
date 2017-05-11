using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SqpackIndex2
{
    public static class Utility
    {
        // Taken from http://stackoverflow.com/a/41836532
        public static T ByteArrayToStructure<T>(byte[] bytes) where T : struct
        {
            var handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
            try {
                return (T) Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(T));
            }
            finally {
                handle.Free();
            }
        }
    }
}
