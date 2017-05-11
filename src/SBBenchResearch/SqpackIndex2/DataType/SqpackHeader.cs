using System.Runtime.InteropServices;

namespace SqpackIndex2
{
    [StructLayout(LayoutKind.Explicit, CharSet = CharSet.Ansi)]
    public unsafe struct SqpackHeader1
    {
        [FieldOffset(0x0), MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] signature;

    }

    [StructLayout(LayoutKind.Explicit)]
    public struct SqpackHeader2
    {
        [FieldOffset(0x8)]
        public SegmentCursor entryCursor;

        [FieldOffset(0x50)]
        public int unknown_50;

        [FieldOffset(0x54)]
        public SegmentCursor unknown_54;

        /// <summary>
        /// Only used in index version 0
        /// </summary>
        [FieldOffset(0xE4)]
        public SegmentCursor unknown_e4;

        [FieldOffset(0x12C)]
        public int version;
    }
}
