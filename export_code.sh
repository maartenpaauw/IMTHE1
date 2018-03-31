#!/usr/bin/env bash

touch EI/src/README.md && echo '```c' > EI/src/README.md && echo "$(cat EI/src/main.c)" >> EI/src/README.md && echo '```' >> EI/src/README.md;
pandoc EI/src/README.md -s -o exported/word/EI_code.docx;
rm EI/src/README.md;

touch O1/src/README.md && echo '```c' > O1/src/README.md && echo "$(cat O1/src/main.c)" >> O1/src/README.md && echo '```' >> O1/src/README.md;
pandoc O1/src/README.md -s -o exported/word/O1_code.docx;
rm O1/src/README.md;

touch O2_1/src/README.md && echo '```c' > O2_1/src/README.md && echo "$(cat O2_1/src/main.c)" >> O2_1/src/README.md && echo '```' >> O2_1/src/README.md;
pandoc O2_1/src/README.md -s -o exported/word/O2_1_code.docx;
rm O2_1/src/README.md;

touch O2_2/src/README.md && echo '```c' > O2_2/src/README.md && echo "$(cat O2_2/src/main.c)" >> O2_2/src/README.md && echo '```' >> O2_2/src/README.md;
pandoc O2_2/src/README.md -s -o exported/word/O2_2_code.docx;
rm O2_2/src/README.md;

touch O3_1/src/README.md && echo '```c' > O3_1/src/README.md && echo "$(cat O3_1/src/main.c)" >> O3_1/src/README.md && echo '```' >> O3_1/src/README.md;
pandoc O3_1/src/README.md -s -o exported/word/O3_1_code.docx;
rm O3_1/src/README.md;

touch O3_2/src/README.md && echo '```c' > O3_2/src/README.md && echo "$(cat O3_2/src/main.c)" >> O3_2/src/README.md && echo '```' >> O3_2/src/README.md;
pandoc O3_2/src/README.md -s -o exported/word/O3_2_code.docx;
rm O3_2/src/README.md;

touch O4_1/src/README.md && echo '```c' > O4_1/src/README.md && echo "$(cat O4_1/src/main.c)" >> O4_1/src/README.md && echo '```' >> O4_1/src/README.md;
pandoc O4_1/src/README.md -s -o exported/word/O4_1_code.docx;
rm O4_1/src/README.md;

touch O4_2/src/README.md && echo '```c' > O4_2/src/README.md && echo "$(cat O4_2/src/main.c)" >> O4_2/src/README.md && echo '```' >> O4_2/src/README.md;
pandoc O4_2/src/README.md -s -o exported/word/O4_2_code.docx;
rm O4_2/src/README.md;

touch O4_3/src/README.md && echo '```c' > O4_3/src/README.md && echo "$(cat O4_3/src/main.c)" >> O4_3/src/README.md && echo '```' >> O4_3/src/README.md;
pandoc O4_3/src/README.md -s -o exported/word/O4_3_code.docx;
rm O4_3/src/README.md;

touch O5_2/src/README.md && echo '```c' > O5_2/src/README.md && echo "$(cat O5_2/src/main.c)" >> O5_2/src/README.md && echo '```' >> O5_2/src/README.md;
pandoc O5_2/src/README.md -s -o exported/word/O5_2_code.docx;
rm O5_2/src/README.md;

touch O5_2/lib/hd44780/README.md && echo '```c' > O5_2/lib/hd44780/README.md && echo "$(cat O5_2/lib/hd44780/hd44780_settings.h)" >> O5_2/lib/hd44780/README.md && echo '```' >> O5_2/lib/hd44780/README.md;
pandoc O5_2/lib/hd44780/README.md -s -o exported/word/O5_2_setting_code.docx;
rm O5_2/lib/hd44780/README.md;
