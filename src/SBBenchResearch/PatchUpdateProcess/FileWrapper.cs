using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace PatchUpdateProcess
{
    public class FileWrapper
    {
        public FileStream file;
        public byte[] cacheBuffer;

        /// <summary>
        /// (sub_44CBE0) Same as ReadFileAt, expect it uses cached buffer when possible?
        /// </summary>
        /// <param name="data"></param>
        /// <param name="bytesToRead"></param>
        /// <param name="bytesRead"></param>
        /// <param name="readAt"></param>
        /// <returns></returns>
        public bool Unknown_ReadFile(out byte[] data, int bytesToRead, out int bytesRead, long readAt)
        {
            data = null;
            bytesRead = 0;

            if (this.cacheBuffer == null)
            {
                ReadFileAt(out data, bytesToRead, out bytesRead, readAt);
            }
            else
            { 

            }

            return true;
        }

        public bool UpdateHash()
        {

        }

        /// <summary>
        /// (sub_4560F0) Read file at position
        /// </summary>
        /// <param name="data"></param>
        /// <param name="bytesToRead"></param>
        /// <param name="bytesRead">Actual number of bytes read</param>
        /// <param name="readAt"></param>
        /// <returns>Returns true on success, false otherwise.</returns>
        public bool ReadFileAt(out byte[] data, int bytesToRead, out int bytesRead, long readAt)
        {
            data = null;
            bytesRead = 0;

            // save current file offset
            var fileOffsetTemp = this.file.Position;

            // check if file is open
            if (this.file != null)
            {
                // init buffer
                data = new byte[bytesToRead];

                // read file from offset
                this.file.Position = readAt;
                bytesRead = this.file.Read(data, 0, bytesToRead);
            }
            else
            {
                return false;
            }

            this.file.Position = fileOffsetTemp;
            return true;
        }
    }
}
