using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace SqpackIndex2
{
    public static class FileWrapper
    {
        /// <summary>
        /// Read a file from the current cursor. (sub_140159d50)
        /// </summary>
        /// <remarks>
        /// This advance a cursor after read from the file in ffxiv.
        /// </remarks>
        /// <param name="fs">hFile</param>
        /// <param name="buffer">Pointer to buffer</param>
        /// <param name="bytesToRead"></param>
        /// <returns></returns>
        public static byte ReadBytes(this FileStream fs, out byte[] buffer, int bytesToRead)
        {
            buffer = new byte[bytesToRead];

            // error handling is skipped for here
            fs.Read(buffer, 0, bytesToRead);
            
            return 1;
        }

        /// <summary>
        /// Same thing as ReadBytes expect it preserves file offset (sub_140159df0)
        /// </summary>
        public static byte ReadBytesAt(this FileStream fs, out byte[] buffer, uint bytesToRead, uint offset)
        {
            var tempOffset = fs.Position;

            fs.Position = offset;
            var result = fs.ReadBytes(out buffer, bytesToRead);
            fs.Position = tempOffset;

            return result;
        }
        
    }
}
