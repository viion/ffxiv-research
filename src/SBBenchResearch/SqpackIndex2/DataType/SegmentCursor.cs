using System.Runtime.InteropServices;

namespace SqpackIndex2
{
    [StructLayout(LayoutKind.Explicit)]
    public unsafe struct SegmentCursor
    {
        [FieldOffset(0)]
        public uint offset;

        [FieldOffset(4)]
        public uint size;
    }
}
