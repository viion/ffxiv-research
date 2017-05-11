using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace SqpackIndex2
{
    public struct Sqpack
    {
        //[FieldOffset(0x8)]
        public byte loaded;

        //[FieldOffset(0x9)]
        public byte loaded2;

        // since this is copyed with sign extension, assume signed type
        //[FieldOffset(0xC)]
        public int fileType2;

        //[FieldOffset(0x14)]
        public SqpackHeader1 header1;

        //[FieldOffset(0x414)]
        public SqpackHeader2 header2;

        //[FieldOffset(0x814)]
        public int fileType;

        //[FieldOffset(0x818)]
        public int fileSubType;

        //[FieldOffset(0x81C)]
        public uint entryCount;

        /// <summary>
        /// unknown entry count calculated from index offset 454h
        /// </summary>
        //[FieldOffset(0x820)]
        public uint unknown_820;

        /// <summary>
        /// unknown entry count calculated from index offset 4E4h
        /// </summary>
        //[FieldOffset(0x824)]
        public uint unknown_824;

        //[FieldOffset(0x830)]
        public uint unknown_830;

        /// <summary>
        /// Contains file data pointed by index offset 408h
        /// </summary>
        /// <remarks>
        /// Entry data
        /// </remarks>
        //[FieldOffset(0xA50)]
        public byte[] entryRawData;

        /// <summary>
        /// Contains file data pointed by index offset 454h
        /// </summary>
        //[FieldOffset(0xA58)]
        public byte[] unknown_a58;

        /// <summary>
        /// Contains file data pointed by index offset 4E4h
        /// </summary>
        //[FieldOffset(0xA60)]
        public byte[] unknown_a60;

        //[FieldOffset(0xA88)]
        public FileStream dataFile;

        // not so sure, data is from return value of CreateFile w/ dat; 0?
        //[FieldOffset(0xAE0)]
        public byte unknown_ae0;

        //[FieldOffset(0xAD8)]
        public FileStream indexFile;

        /// <summary>
        /// Store address to sub_140ce9210 if index.version == 2
        /// </summary>
        //[FieldOffset(0xAE8)]
        public IntPtr unknown_ae8;

        public byte OpenFile(int type, int subType)
        {
            this.fileType = type;
            this.fileSubType = subType;

            // some uninteresting packs are omitted.
            var indexPath = GetFilePath(-1);
            this.indexFile = File.Open(indexPath, FileMode.Open);
            
            // read 1k from the file
            indexFile.ReadBytes(out byte[] header1Raw, 1024);
            this.header1 = Utility.ByteArrayToStructure<SqpackHeader1>(header1Raw);

            // read another 1k from the file
            indexFile.ReadBytes(out byte[] header2Raw, 1024);
            this.header2 = Utility.ByteArrayToStructure<SqpackHeader2>(header2Raw);

            if (this.header2.version == 2)
            {
                // actually stores function address but whatever
                this.unknown_ae8 = new IntPtr(0x140ce9210);
            }

            // 140ce8d3a
            this.unknown_830 += 2;
            if (this.header2.unknown_54.size != 0)
            {
                this.indexFile.ReadBytesAt(out this.unknown_a58, this.header2.unknown_54.size, this.header2.unknown_54.offset);
                this.unknown_830 += 1;

                // shr eax, 8 but this one is more readable (prolly elided anyway)
                this.unknown_820 = this.header2.unknown_54.size / 256;

            }

            // 140ce8d8a
            // Only used in .index (version 0)
            if (this.header2.unknown_e4.size != 0)
            {
                // basically copy paste
                this.indexFile.ReadBytesAt(out this.unknown_a60, this.header2.unknown_e4.size, this.header2.unknown_e4.offset);
                this.unknown_830 += 1;
                
                // shift right by 4
                this.unknown_824 = this.header2.unknown_e4.size / 16;

                this.loaded2 = 1;
            }

            // 140ce8ddd
            if (this.loaded2 == 0)
            {
                if (this.header2.entryCursor.size != 0)
                {
                    this.indexFile.ReadBytesAt(out this.entryRawData, this.header2.entryCursor.size, this.header2.entryCursor.offset);

                    // get entry count from entry size and save it;
                    // this segment is depends on index version
                    // 00007FF641DC8E23  | 48 39 AB E8 0A 00 00  | cmp qword ptr ds:[rbx+AE8],rbp | rbp = function ptr from prev
                    // 00007FF641DC8E2A  | 75 05                 | jne ffxiv_dx11.7FF641DC8E31
                    // 00007FF641DC8E2C  | C1 E8 03              | shr eax,3
                    // 00007FF641DC8E2F  | EB 03                 | jmp ffxiv_dx11.7FF641DC8E34
                    // 00007FF641DC8E31  | C1 E8 04              | shr eax,4
                    var entrySize = this.header2.entryCursor.size;
                    if (this.header2.version == 2)
                    {
                        // versoin 2, entry size is 8
                        this.entryCount = entrySize / 8;
                    }
                    else
                    {
                        // version 0, entry size is 16
                        this.entryCount = entrySize / 16;
                    }
                }
            }

            OpenDataFile();

            this.loaded = 1;
            this.fileType2 = fileType; // duplicated field don't know why :<

            return 1;
        }

        /// <summary>
        /// Open related .dat file. This function does not parse all thing (sub_140ce8e80)
        /// </summary>
        private void OpenDataFile()
        {
            if (this.header2.unknown_50 == 0)
            {
                return;
            }


            // omit some stack smash check

            // omit some file alloc
            // (it turned out this is basically file wrapper)
            //if (this.dataFile == null)
            //{
            //    // basically heap alloc to a88 here
            //}
            //this.dataFile.unknown_20 = 0;

            // just use this for the mockup
            this.dataFile = File.Open(GetFilePath(0), FileMode.Open);

        }

        /// <summary>
        /// Get path to sqpack file. (sub_140ce8420)
        /// </summary>
        /// <remarks>
        /// Current implementation is vastly simplified compare to actual subroutine.
        /// Also code for finding subfile is unimplemented.
        /// </remarks>
        /// <param name="isIndex">(r8d) -1 if index file, dat otherwise</param>
        private string GetFilePath(int isIndex)
        {
            // actual impl is similar to Application.ExecutablePath, but hardcode it for this
            const string SQPACK_PATH = "C:\\Users\\Mino\\Desktop\\FFXIV-SB\\game\\sqpack\\ffxiv";

            // add filename
            var fileExt = isIndex == -1 ? "index" : "dat";
            var fileName = $"{this.fileType:x2}{this.fileSubType:x4}.win32.{fileExt}2";

            return Path.Combine(SQPACK_PATH, fileName);
        }

    }
}
