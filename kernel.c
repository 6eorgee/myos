void main()
{
    char* video_memory = (char*)0xb8000;
    *video_memory++ = 'G';
    *video_memory++ = 0xC0;
    *video_memory++ = 'O';
    *video_memory++ = 0xA0;
    *video_memory++ = 'G';
    *video_memory++ = 0x90;
    *video_memory++ = 'A';
    *video_memory++ = 0x70;
}

// void _start()
// {
//     main();
// }
