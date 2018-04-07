all: slides.md
	pandoc -t html5 --template=./templates/template-revealjs.html --standalone --section-divs --variable theme="beige" --variable transition="linear" slides.md -o index.html

pdf: slides.md
	pandoc slides.md -t beamer -o output.pdf -V theme:Mate
