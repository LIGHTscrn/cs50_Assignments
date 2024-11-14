#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t buffer[512];
char name[30];

int main(int argc, char *argv[])
{
    // buffer[0] == 0xff;
    // buffer[1] == 0xd8;
    // buffer[2] == 0xff;
    // (buffer[3] & 0xf0) == 0xe0;
    if (argc != 2)
    {
        printf("Usage : ./recover FILENAME\n");
        return 1;
    }
    int file_name = 0;
    FILE *pranav = fopen(argv[1], "r");
    FILE *output = NULL;
    if (pranav != NULL)
    {
        while (fread(&buffer, sizeof(uint8_t), 512, pranav) == 512)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                ((buffer[3] & 0xf0) == 0xe0))
            {
                if (output != NULL)
                {
                    fclose(output);
                }
                sprintf(name, "%03i.jpg", file_name++);

                output = fopen(name, "w");
                if (output != NULL)
                {
                    fwrite(&buffer, sizeof(uint8_t), 512, output);
                }
            }
            else
            {
                if (output != NULL)
                {
                    fwrite(&buffer, sizeof(uint8_t), 512, output);
                }
            }
        }
    }
    if (pranav != NULL)
    {
        fclose(pranav);
    }
    if (output != NULL)
    {
        fclose(output);
    }
    return 0;
}
