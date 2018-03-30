#!/bin/sh

echo "Creating exported folder"
mkdir -p "exported"

echo "Creating folder exported/word"
mkdir -p "exported/word"
echo "Exporting README.md in .docx format"

pandoc EI/README.md -s -o exported/word/EI.docx &&
pandoc O1/README.md -s -o exported/word/O1.docx &&
pandoc O2_1/README.md -s -o exported/word/O2_1.docx &&
pandoc O2_2/README.md -s -o exported/word/O2_2.docx &&
pandoc O3_1/README.md -s -o exported/word/O3_1.docx &&
pandoc O3_2/README.md -s -o exported/word/O3_2.docx &&
pandoc O4_1/README.md -s -o exported/word/O4_1.docx &&
pandoc O4_2/README.md -s -o exported/word/O4_2.docx &&
pandoc O4_3/README.md -s -o exported/word/O4_3.docx &&
pandoc O5_1/README.md -s -o exported/word/O5_1.docx &&
pandoc O5_2/README.md -s -o exported/word/O5_2.docx

echo "done"
