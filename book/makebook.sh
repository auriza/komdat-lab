# strip header and adjust header
for chapter in ../p*.md; do
    cat $chapter                |
        grep -Ev '(title:|author:|institute:|date:|theme:|header-includes:|usepackage|renewcommand|setmainlanguage|setotherlanguage|newfontfamily|^---$)' > $(basename $chapter)
done

# add book metadata
cat > p00-title.md << EOF
---
title: Praktikum Komunikasi Data & Jaringan Komputer
author: Auriza Akbar
date: 2017
papersize: a4
documentclass: book
toc: true
toc-depth: 2
lof: true
lot: true
header-includes:
    - \usepackage{tikz}
    - \renewcommand*\contentsname{Daftar Isi}
    - \renewcommand{\partname}{Bagian}
    - \renewcommand{\listfigurename}{Daftar Gambar}
    - \renewcommand{\listtablename}{Daftar Tabel}
    - \renewcommand{\figurename}{Gambar}
    - \renewcommand{\tablename}{Tabel}
---

\part{Layer Jaringan Komputer}
EOF
echo "\part{Simulasi Packet Tracer}" > p08_.md

# convert to TeX
pandoc -s *.md -o book.tex


## Classic Thesis Book ---------------------------------------------------------

sed '1d' book.tex > body.tex
cat > head.tex << EOF
\documentclass[11pt,a4paper,footinclude=true,headinclude=true]{scrbook}
\usepackage[linedheaders,parts,pdfspacing]{classicthesis}
EOF
cat head.tex body.tex > book1.tex
sed -i '/hyperref/d' book1.tex
sed -i '/\\begin{document}/a \
\\frontmatter' book1.tex
sed -i '/\\listoffigures/a \
\\mainmatter' book1.tex

pdflatex book1.tex
pdflatex book1.tex
mv book1.pdf netbook-c.pdf


## Tufte Book ------------------------------------------------------------------

cp book.tex book2.tex
sed -i 's/]{book}/nohyper]{tufte-book}/' book2.tex
sed -i 's/subsubsection/paragraph/' book2.tex
sed -i 's/\\title{Praktikum/\\title{Praktikum\\\\/' book2.tex
sed -i 's/\\date{2017}/\\publisher{Ilmu Komputer IPB}/' book2.tex
sed -i '/\\begin{document}/a \
\\frontmatter\\pagenumbering{roman}' book2.tex
sed -i '/\\listoffigures/a \
\\mainmatter\\setcounter{page}{1}\\pagenumbering{arabic}' book2.tex

pdflatex book2.tex
pdflatex book2.tex
mv book2.pdf netbook-t.pdf

## -----------------------------------------------------------------------------

rm *md *tex *aux *log *toc *out *lof *lot
