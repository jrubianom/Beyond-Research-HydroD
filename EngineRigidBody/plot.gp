set term pdf
set out 'plot.pdf'
set xlabel 't'
set ylabel 'theta'
set title 'title'
plot 'datos.txt' u 1:3 w p
