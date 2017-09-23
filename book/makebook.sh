# strip and adjust header
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
echo "\part{Simulasi Packet Tracer}" > p07x.md
rm p05.md


## Classic Thesis Book ---------------------------------------------------------

#pandoc -s *.md -o book.tex
#sed '1d' book.tex > body.tex
#cat > head.tex << EOF
#\documentclass[11pt,a4paper,footinclude=true,headinclude=true]{scrbook}
#\usepackage[linedheaders,parts,pdfspacing]{classicthesis}
#EOF
#cat head.tex body.tex > book.tex
#sed -i '/hyperref/d' book.tex
#sed -i '/\\begin{document}/a \
#\\frontmatter' book.tex
#sed -i '/\\listoffigures/a \
#\\mainmatter' book.tex
#
#pdflatex book.tex
#pdflatex book.tex
#mv book.pdf komdat-lab_.pdf


## Tufte Book ------------------------------------------------------------------

pandoc -s *.md -o book.tex
sed -i 's/]{book}/nohyper]{tufte-book}/' book.tex
sed -i 's/subsubsection/paragraph/' book.tex
sed -i 's/\\title{Praktikum/\\title{Praktikum\\\\/' book.tex
sed -i 's/\\date{2017}/\\publisher{Ilmu Komputer IPB}/' book.tex
sed -i '/\\begin{document}/a \
\\frontmatter\\pagenumbering{roman}' book.tex
sed -i '/\\listoffigures/a \
\\mainmatter\\setcounter{page}{1}\\pagenumbering{arabic}' book.tex

pdflatex book.tex
pdflatex book.tex
mv book.pdf komdat-lab.pdf

## -----------------------------------------------------------------------------

rm *md *tex *aux *log *toc *out *lof *lot
